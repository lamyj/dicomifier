#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import ctypes
import math
import re

import numpy

import niftiio

class NIfTIImage(object):
    
    def __init__(self, **kwargs):
        self.pixdim = None
        self.scl_slope = 0
        self.scl_inter = 0
        self.cal_min = 0
        self.cal_max = 0
        self.qform_code = niftiio.NIFTI_XFORM_UNKNOWN
        self.sform_code = niftiio.NIFTI_XFORM_UNKNOWN
        # freq_dim, phase_dim, slice_dim, slice_code, slice_start, slice_end, slice_duration
        
        self.sform = numpy.identity(4)
        """Transformation to a standard space, expressed as a 4D homogeneous 
        affine matrix."""
        
        self.qform = numpy.identity(4)
        """Transformation to the scanner physical space, expressed as a 4D 
        rigid homogeneous matrix. This qform includes qfac."""
        
        self.xyz_units = niftiio.NIFTI_UNITS_UNKNOWN
        self.time_units = niftiio.NIFTI_UNITS_UNKNOWN
        # nifti_type
        # intent_code, intent_p1, intent_p2, intent_p3, intent_name
        self.descrip = ""
        # auxfile, fname, iname, iname_offset
        # swapsize, byteorder
        self.data = None
        # num_ext, ext_list, analyze75_orient
        
        for key, value in kwargs.items():
            if not hasattr(self, key):
                raise Exception("No such field: {}".format(key))
            setattr(self, key, value)
    
    @staticmethod
    def read(filename):
        import warnings
        warnings.filterwarnings(
            "ignore", 
            "Item size computed from the PEP 3118 buffer format string does not match the actual item size.",
            RuntimeWarning)
        
        pointer = niftiio.nifti_image_read(filename, True)
        if pointer == 0:
            raise Exception("Could not read")
        try:
            struct_ = ctypes.cast(
                pointer, ctypes.POINTER(niftiio.nifti_image)).contents
            
            kwargs = { }
            scalar_fields = [
                "scl_slope", "scl_inter", "cal_min", "cal_max", 
                "qform_code", "sform_code", 
                #"qfac", 
                "xyz_units", "time_units",
                "descrip",
            ]
            for field in scalar_fields:
                kwargs[field] = getattr(struct_, field)
            
            array_fields = ["pixdim"]
            for field in array_fields: 
                value = getattr(struct_, field)
                kwargs[field] = numpy.ctypeslib.as_array(
                    getattr(struct_, field)).copy()
            
            # sform
            kwargs["sform"] = numpy.ctypeslib.as_array(struct_.sto_xyz.m).copy()
            
            # qform
            a,b,c,d = [
                math.sqrt(1.0-(struct_.quatern_b**2+struct_.quatern_c**2+struct_.quatern_d**2)),
                struct_.quatern_b, struct_.quatern_c, struct_.quatern_d
            ]
            kwargs["qform"] = numpy.identity(4)
            kwargs["qform"][:3,:3] = [
                [a*a+b*b-c*c-d*d, 2*b*c-2*a*d    , 2*b*d+2*a*c],
                [2*b*c+2*a*d    , a*a+c*c-b*b-d*d, 2*c*d-2*a*b],
                [2*b*d-2*a*c    , 2*c*d+2*a*b    , a*a+d*d-c*c-b*b],
            ]
            kwargs["qform"][:3,:3] = numpy.dot(
                kwargs["qform"][:3,:3], 
                numpy.diag((struct_.dx, struct_.dy, struct_.dz)))
            kwargs["qform"][2,2] *= struct_.qfac
            
            kwargs["qform"][:3,3] = [
                struct_.qoffset_x, struct_.qoffset_y, struct_.qoffset_z]
            
            # data
            dtypes = { 
                getattr(niftiio, x): x 
                for x in dir(niftiio) if x.startswith("DT") }
            type_, width = re.match(
                r"DT_(\D+)(\d+)", 
                dtypes[struct_.datatype]).groups()
            if (type_, width) == ("FLOAT", "32"):
                dtype = ctypes.c_float
            elif (type_, width) == ("FLOAT", "64"):
                dtype = ctypes.c_double
            elif (type_, width) == ("FLOAT", "128"):
                dtype = ctypes.c_longdouble
            else:
                dtype = getattr(ctypes, "c_{}{}".format(type_.lower(), width))
            
            ArrayType = dtype*struct_.nvox
            shape = struct_.dim[1:1+struct_.dim[0]][::-1]
            kwargs["data"] = numpy.ctypeslib.as_array(
                ArrayType.from_address(struct_.data)).copy().reshape(shape)
            
            return NIfTIImage(**kwargs)
        finally:
            niftiio.nifti_image_free(pointer)
    
    def write(self, filename):
        pointer = niftiio.nifti_simple_init_nim()
        if pointer == 0:
            raise Exception("Could not read")
        try:
            struct_ = ctypes.cast(
                pointer, ctypes.POINTER(niftiio.nifti_image)).contents
            
            scalar_fields = [
                "ndim", "nvox", "nbyper", "datatype",
                "scl_slope", "scl_inter", "cal_min", "cal_max", 
                "qform_code", "sform_code", "xyz_units", "time_units",
                "descrip",
            ]
            for field in scalar_fields:
                setattr(struct_, field, getattr(self, field))
            
            # dim and nx, ..., nw
            struct_.dim[0] = self.ndim
            struct_.dim[1:1+struct_.ndim] = self.shape[::-1]
            struct_.dim[1+struct_.ndim:] = (len(struct_.dim)-self.ndim-1)*[1]
            for index, axis in enumerate(["x", "y", "z", "t", "u", "v", "w"]):
                setattr(struct_, "n{}".format(axis), struct_.dim[1+index])
            
            # pixdim and dx, ..., dw
            struct_.pixdim[0] = 0
            for index, axis in enumerate(["x", "y", "z", "t", "u", "v", "w"]):
                struct_.pixdim[1+index] = self.pixdim[1+index]
                setattr(struct_, "d{}".format(axis), struct_.pixdim[1+index])
            
            q_inverse = numpy.linalg.inv(self.qform)
            for i in range(4):
                for j in range(4):
                    struct_.qto_xyz.m[i][j] = self.qform[i,j]
                    struct_.qto_ijk.m[i][j] = q_inverse[i,j]
            
            qb, qc, qd = ctypes.c_float(), ctypes.c_float(), ctypes.c_float()
            qx, qy, qz = ctypes.c_float(), ctypes.c_float(), ctypes.c_float()
            dx, dy, dz = ctypes.c_float(), ctypes.c_float(), ctypes.c_float()
            qfac = ctypes.c_float()
            niftiio.nifti_mat44_to_quatern(
                struct_.qto_xyz, 
                ctypes.byref(qb), ctypes.byref(qc), ctypes.byref(qd), 
                ctypes.byref(qx), ctypes.byref(qy), ctypes.byref(qz), 
                ctypes.byref(dx), ctypes.byref(dy), ctypes.byref(dz), 
                ctypes.byref(qfac))
            
            struct_.quatern_b, struct_.quatern_c, struct_.quatern_d = qb, qc, qd
            struct_.qoffset_x, struct_.qoffset_y, struct_.qoffset_z = qx, qy, qz
            struct_.dx, struct_.dy, struct_.dz = dx, dy, dz
            struct_.qfac = qfac
            
            s_inverse = numpy.linalg.inv(self.sform)
            for i in range(4):
                for j in range(4):
                    struct_.sto_xyz.m[i][j] = self.sform[i,j]
                    struct_.sto_ijk.m[i][j] = s_inverse[i,j]
            
            # FIXME: nifti_makebasename / nifti_type / nifti_makehdrname / nifti_makeimgname
            struct_.fname = filename
            
            struct_.data = self.data.ctypes.data
            
            niftiio.nifti_image_write(pointer)
            struct_.fname = None
            struct_.iname = None
            struct_.data = None
            
        finally:
            niftiio.nifti_image_free(pointer)
    
    def __array__(self):
        return self.data
    
    def _get_ndim(self):
        return numpy.asarray(self).ndim
    ndim = property(_get_ndim)
    
    def _get_shape(self):
        return numpy.asarray(self).shape
    shape = property(_get_shape)

    def _get_nvox(self):
        return numpy.cumprod(self.shape)[-1]
    nvox = property(_get_nvox)

    def _get_nbyper(self):
        return numpy.asarray(self).dtype.itemsize
    nbyper = property(_get_nbyper)

    def _get_datatype(self):
        type_, width = re.match(r"(\D+)(\d+)", str(self.data.dtype)).groups()
        return getattr(niftiio, "DT_{}{}".format(type_.upper(), width))
    datatype = property(_get_datatype)
