#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import ctypes
import ctypes.util

import numpy.ctypeslib

clib = ctypes.CDLL(ctypes.util.find_library("niftiio"))
nifti_simple_init_nim = clib.nifti_simple_init_nim
nifti_image_read = clib.nifti_image_read
nifti_image_free = clib.nifti_image_free
nifti_image_write = clib.nifti_image_write
nifti_mat44_to_quatern = clib.nifti_mat44_to_quatern
nifti_quatern_to_mat44 = clib.nifti_quatern_to_mat44

DT_NONE = 0
DT_UNKNOWN = 0
DT_BINARY = 1
#DT_UNSIGNED_CHAR = 2
#DT_SIGNED_SHORT = 4
#DT_SIGNED_INT = 8
#DT_FLOAT = 16
#DT_COMPLEX = 32
#DT_DOUBLE = 64
#DT_RGB = 128
#DT_ALL = 255
DT_UINT8 = 2
DT_INT16 = 4
DT_INT32 = 8
DT_FLOAT32 = 16
DT_COMPLEX64 = 32
DT_FLOAT64 = 64
DT_RGB24 = 128
DT_INT8 = 256
DT_UINT16 = 512
DT_UINT32 = 768
DT_INT64 = 1024
DT_UINT64 = 1280
DT_FLOAT128 = 1536
DT_COMPLEX128 = 1792
DT_COMPLEX256 = 2048
DT_RGBA32 = 2304

NIFTI_INTENT_NONE = 0
NIFTI_INTENT_CORREL = 2
NIFTI_INTENT_TTEST = 3
NIFTI_INTENT_FTEST = 4
NIFTI_INTENT_ZSCORE = 5
NIFTI_INTENT_CHISQ = 6
NIFTI_INTENT_BETA = 7
NIFTI_INTENT_BINOM = 8
NIFTI_INTENT_GAMMA = 9
NIFTI_INTENT_POISSON = 10
NIFTI_INTENT_NORMAL = 11
NIFTI_INTENT_FTEST_NONC = 12
NIFTI_INTENT_CHISQ_NONC = 13
NIFTI_INTENT_LOGISTIC = 14
NIFTI_INTENT_LAPLACE = 15
NIFTI_INTENT_UNIFORM = 16
NIFTI_INTENT_TTEST_NONC = 17
NIFTI_INTENT_WEIBULL = 18
NIFTI_INTENT_CHI = 19
NIFTI_INTENT_INVGAUSS = 20
NIFTI_INTENT_EXTVAL = 21
NIFTI_INTENT_PVAL = 22
NIFTI_INTENT_LOGPVAL = 23
NIFTI_INTENT_LOG10PVAL = 24
NIFTI_FIRST_STATCODE = 2
NIFTI_LAST_STATCODE = 24
NIFTI_INTENT_ESTIMATE = 1001
NIFTI_INTENT_LABEL = 1002
NIFTI_INTENT_NEURONAME = 1003
NIFTI_INTENT_GENMATRIX = 1004
NIFTI_INTENT_SYMMATRIX = 1005
NIFTI_INTENT_DISPVECT = 1006
NIFTI_INTENT_VECTOR = 1007
NIFTI_INTENT_POINTSET = 1008
NIFTI_INTENT_TRIANGLE = 1009
NIFTI_INTENT_QUATERNION = 1010
NIFTI_INTENT_DIMLESS = 1011
NIFTI_INTENT_TIME_SERIES = 2001
NIFTI_INTENT_NODE_INDEX = 2002
NIFTI_INTENT_RGB_VECTOR = 2003
NIFTI_INTENT_RGBA_VECTOR = 2004
NIFTI_INTENT_SHAPE = 2005

NIFTI_XFORM_UNKNOWN = 0
NIFTI_XFORM_SCANNER_ANAT = 1
NIFTI_XFORM_ALIGNED_ANAT = 2
NIFTI_XFORM_TALAIRACH = 3
NIFTI_XFORM_MNI_152 = 4

NIFTI_UNITS_UNKNOWN = 0
NIFTI_UNITS_METER = 1
NIFTI_UNITS_MM = 2
NIFTI_UNITS_MICRON = 3
NIFTI_UNITS_SEC = 8
NIFTI_UNITS_MSEC = 16
NIFTI_UNITS_USEC = 24
NIFTI_UNITS_HZ = 32
NIFTI_UNITS_PPM = 40
NIFTI_UNITS_RADS = 48

mat33 = numpy.ctypeslib.ndpointer(numpy.single, 2, (3,3))
#mat44 = (ctypes.c_float*4)*4 #numpy.ctypeslib.ndpointer(numpy.single, 2, (4,4))
class mat44(ctypes.Structure):
    _fields_ = [("m", (ctypes.c_float*4)*4)]

class nifti_image(ctypes.Structure):
    _fields_ = [
        ("ndim", ctypes.c_int),
        ("nx", ctypes.c_int), ("ny", ctypes.c_int), ("nz", ctypes.c_int),
        ("nt", ctypes.c_int), ("nu", ctypes.c_int), ("nv", ctypes.c_int), ("nw", ctypes.c_int),
        ("dim", ctypes.c_int*8),
        ("nvox", ctypes.c_size_t),
        ("nbyper", ctypes.c_int),
        ("datatype", ctypes.c_int), 
        ("dx", ctypes.c_float), ("dy", ctypes.c_float), ("dz", ctypes.c_float), 
        ("dt", ctypes.c_float), ("du", ctypes.c_float), ("dv", ctypes.c_float), ("dw", ctypes.c_float),
        ("pixdim", ctypes.c_float*8),
        ("scl_slope", ctypes.c_float), ("scl_inter", ctypes.c_float),
        ("cal_min", ctypes.c_float), ("cal_max", ctypes.c_float),
        ("qform_code", ctypes.c_int), ("sform_code", ctypes.c_int),
        ("freq_dim", ctypes.c_int), ("phase_dim", ctypes.c_int), ("slice_dim", ctypes.c_int),
        ("slice_code", ctypes.c_int), 
        ("slice_start", ctypes.c_int), ("slice_end", ctypes.c_int), 
        ("slice_duration", ctypes.c_int),
        ("quatern_b", ctypes.c_float), ("quatern_c", ctypes.c_float), ("quatern_d", ctypes.c_float),
        ("qoffset_x", ctypes.c_float), ("qoffset_y", ctypes.c_float), ("qoffset_z", ctypes.c_float),
        ("qfac", ctypes.c_float),
        ("qto_xyz", mat44), ("qto_ijk", mat44),
        ("sto_xyz", mat44), ("sto_ijk", mat44),
        ("toffset", ctypes.c_float),
        ("xyz_units", ctypes.c_int), ("time_units", ctypes.c_int),
        ("nifti_type", ctypes.c_int), ("intent_code", ctypes.c_int),
        ("intent_p1", ctypes.c_float), ("intent_p2", ctypes.c_float), ("intent_p3", ctypes.c_float),
        ("intent_name", ctypes.c_char*16), ("descrip", ctypes.c_char*80),
        ("aux_file", ctypes.c_char*24), 
        ("fname", ctypes.c_char_p), ("iname", ctypes.c_char_p), 
        ("iname_offset", ctypes.c_int), 
        ("swapsize", ctypes.c_int), ("byteorder", ctypes.c_int),
        ("data", ctypes.c_void_p),
        # int 	num_ext
        # nifti1_extension* 	ext_list
        # analyze_75_orient_code 	analyze75_orient
    ]
