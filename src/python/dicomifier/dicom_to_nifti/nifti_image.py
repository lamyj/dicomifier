#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import re

import numpy

from .. import nifti

class NIfTIImage(object):
    
    def __init__(self, **kwargs):
        self.pixdim = None
        self.scl_slope = 0.
        self.scl_inter = 0.
        self.cal_min = 0.
        self.cal_max = 0.
        self.qform_code = nifti.NIFTI_XFORM_UNKNOWN
        self.sform_code = nifti.NIFTI_XFORM_UNKNOWN
        # freq_dim, phase_dim, slice_dim, slice_code, slice_start, slice_end, slice_duration
        
        self.sform = numpy.identity(4)
        """Transformation to a standard space, expressed as a 4D homogeneous 
        affine matrix."""
        
        self.qform = numpy.identity(4)
        """Transformation to the scanner physical space, expressed as a 4D 
        rigid homogeneous matrix. This qform includes qfac."""
        
        self.xyz_units = nifti.NIFTI_UNITS_UNKNOWN
        self.time_units = nifti.NIFTI_UNITS_UNKNOWN
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
        return getattr(nifti, "DT_{}{}".format(type_.upper(), width))
    datatype = property(_get_datatype)
