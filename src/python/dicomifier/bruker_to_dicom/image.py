#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import base64
import datetime
import re

import numpy
import odil

def _get_acquisition_number(data_set, generator, frame_index):
    acquisition_number = 0
    empty_frame_groups_size = 1
    for frame_group_index, frame_group in enumerate(generator.frame_groups):
        if len(frame_group[2]) == 0:
            acquisition_number += empty_frame_groups_size*frame_index[frame_group_index]
            empty_frame_groups_size *= 1+len(frame_group[2])
    return [acquisition_number]

def _get_pixel_data(data_set, generator, frame_index):
    if isinstance(data_set["PIXELDATA"], list):
        dtype = {
            "_8BIT_UNSGN_INT": numpy.uint8,
            "_16BIT_SGN_INT": numpy.int16,
            "_32BIT_SGN_INT": numpy.int32
        }[data_set["VisuCoreWordType"][0]]
        
        # Read the file
        with open(data_set["PIXELDATA"][0], "rb") as fd:
            pixel_data = numpy.fromfile(fd, dtype)
            data_set["PIXELDATA"] = pixel_data.reshape(
                -1, data_set["VisuCoreSize"][0]*data_set["VisuCoreSize"][1])
    
    frame_index = (
        generator.frames_count-generator.get_linear_index(frame_index)-1
        if data_set.get("VisuCoreDiskSliceOrder", [None])[0] == "disk_reverse_slice_order"
        else generator.get_linear_index(frame_index))
    frame_data = data_set["PIXELDATA"][frame_index]
    
    encoded = base64.b64encode(frame_data)
    
    return [encoded]

GeneralImage = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.html#sect_C.7.6.1
    (None, "InstanceNumber", 2, lambda d,g,i: [1+g.get_linear_index(i)], None),
    (None, "ImageType", 3, lambda d,g,i: ["ORIGINAL", "PRIMARY"], None),
    (None, "AcquisitionNumber", 3, _get_acquisition_number, None),
    ("VisuAcqDate", "AcquisitionDate", 3, None, None),
    ("VisuAcqDate", "AcquisitionTime", 3, None, None),
    (
        "VisuCoreFrameCount", "ImagesInAcquisition", 3,
        lambda d,g,i: 
            [int(d["VisuCoreFrameCount"])[0]*d["VisuCoreSize"][2]]
            if d["VisuCoreDim"]==3 
            else [int(x) for x in d["VisuCoreFrameCount"]], 
        None
    ),
]

ImagePlane = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.2.html
    (
        None, "PixelSpacing", 1,
        lambda d,g,i: numpy.divide(
                numpy.asarray(d["VisuCoreExtent"], float), 
                numpy.asarray(d["VisuCoreSize"], float)
            ).tolist(), 
        None
    ),
    (
        "VisuCoreOrientation", "ImageOrientationPatient", 1, 
        lambda d,g,i: numpy.reshape(d["VisuCoreOrientation"], (-1, 9)), 
        lambda x: x[0][:6].tolist()
    ),
    (
        "VisuCorePosition", "ImagePositionPatient", 1, 
        lambda d,g,i: numpy.reshape(d["VisuCorePosition"], (-1, 3)), 
        lambda x: x[0].tolist()
    ),
    ("VisuCoreFrameThickness", "SliceThickness", 2, None, None)
]

ImagePixel = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.3.html
    (None, "SamplesPerPixel", 1, lambda d,g,i: [1], None),
    (None, "PhotometricInterpretation", 1, lambda d,g,i: ["MONOCHROME2"], None),
    ("VisuCoreSize", "Rows", 1, lambda d,g,i: [d["VisuCoreSize"][1]], None),
    ("VisuCoreSize", "Columns", 1, lambda d,g,i: [d["VisuCoreSize"][0]], None),
    (
        "VisuCoreWordType", "BitsAllocated", 1, 
        None, {"_32BIT_SGN_INT": 32, "_16BIT_SGN_INT": 16, "_8BIT_UNSGN_INT": 8}
    ),
    (
        "VisuCoreWordType", "BitsStored", 1, 
        None, {"_32BIT_SGN_INT": 32, "_16BIT_SGN_INT": 16, "_8BIT_UNSGN_INT": 8}
    ),
    (
        "VisuCoreByteOrder", "HighBit", 1, 
        lambda d,g,i: [
            {"_32BIT_SGN_INT": 32, "_16BIT_SGN_INT": 16, "_8BIT_UNSGN_INT": 8}[d["VisuCoreWordType"][0]]-1 
            if d["VisuCoreByteOrder"][0]=="littleEndian" else 0
        ],
        None
    ),
    (
        "VisuCoreWordType", "PixelRepresentation", 1, 
        None, {"_32BIT_SGN_INT": 1, "_16BIT_SGN_INT": 1, "_8BIT_UNSGN_INT": 0}
    ),
    (None, "PixelData", 1, _get_pixel_data, None),
    (
        "VisuCoreDataMin", "SmallestImagePixelValue", 3, 
        lambda d,g,i: [d["VisuCoreDataMin"][g.get_linear_index(i)]], None
    ),
    (
        "VisuCoreDataMax", "LargestImagePixelValue", 3, 
        lambda d,g,i: [d["VisuCoreDataMax"][g.get_linear_index(i)]], None
    ),
]

MRImage = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.3.html#sect_C.8.3.1
    (None, "ScanningSequence", 1, lambda d,g,i: ["RM"], None),
    (None, "SequenceVariant", 1, lambda d,g,i: ["NONE"], None),
    (None, "ScanOptions", 2, lambda d,g,i: None, None),
    ("PVM_SpatDimEnum", "MRAcquisitionType", 2, None, None),
    ("VisuAcqRepetitionTime", "RepetitionTime", 2, None, None),
    ("VisuAcqEchoTime", "EchoTime", 2, None, None),
    ("VisuAcqEchoTrainLength", "EchoTrainLength", 2, None, None),
    ("VisuAcqInversionTime", "InversionTime", 3, None, None),
    ("VisuAcqSequenceName", "SequenceName", 3, None, None),
    ("VisuAcqNumberOfAverages", "NumberOfAverages", 3, None, None),
    ("VisuAcqImagingFrequency", "ImagingFrequency", 3, None, None),
    ("VisuAcqImagedNucleus", "ImagedNucleus", 3, None, None),
    (
        "VisuAcqImagingFrequency", "MagneticFieldStrength", 3, None, 
        lambda x: [float(x[0])/42.577480610]
    ),
    (
        None, "SpacingBetweenSlices", 3, 
        lambda d,g,i: [numpy.linalg.norm(
            numpy.subtract(d["VisuCorePosition"][3:6], d["VisuCorePosition"][0:3]
        ))] if len(d["VisuCorePosition"]) >= 6 else None, 
        None
    ),
    ("VisuAcqPhaseEncSteps", "NumberOfPhaseEncodingSteps", 3, None, None),
    ("VisuAcqPixelBandwidth", "PixelBandwidth", 3, None, None),
    ("VisuAcqFlipAngle", "FlipAngle", 3, None, None),
]

PixelValueTransformation = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.16.2.html#sect_C.7.6.16.2.9
    (
        "VisuCoreDataOffs", "RescaleIntercept", 1, 
        lambda d,g,i: [d["VisuCoreDataOffs"][g.get_linear_index(i)]], None
    ),
    (
        "VisuCoreDataSlope", "RescaleSlope", 1, 
        lambda d,g,i: [d["VisuCoreDataSlope"][g.get_linear_index(i)]], None
    ),
    (None, "RescaleType", 1, lambda d,g,i: ["US"], None),
]

def _get_direction_and_b_value(b_matrix):
    # Adapted from https://github.com/BRAINSia/BRAINSTools/blob/master/DWIConvert/SiemensDWIConverter.h#L457
    # FIXME: find a reference to support this
    values, vectors = numpy.linalg.eigh(b_matrix)
    direction = vectors[:, -1]
    b_value = numpy.trace(b_matrix)
    
    return direction, b_value

MRDiffusion = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.9.html
    (
        "VisuAcqDiffusionBMatrix", "DiffusionBValue", 1, 
        lambda d,g,i: [
            _get_direction_and_b_value(x)[1] 
            for x in numpy.reshape(d["VisuAcqDiffusionBMatrix"], (-1, 3, 3))], 
        None),
    (None, "DiffusionDirectionality", 1, lambda d,g,i: ["BMATRIX"], None),
    (
        "VisuAcqDiffusionBMatrix", "DiffusionGradientDirectionSequence", 1,
        lambda d,g,i: [
            _get_direction_and_b_value(x)[0] 
            for x in numpy.reshape(d["VisuAcqDiffusionBMatrix"], (-1, 3, 3))], 
        lambda x: [{ 
            str(odil.registry.DiffusionGradientOrientation): {
                "vr": "FD", "Value": numpy.asarray(x).ravel().tolist() } 
        }]
    ),
    (
        "VisuAcqDiffusionBMatrix", "DiffusionBMatrixSequence", 1,
        lambda d,g,i: numpy.reshape(d["VisuAcqDiffusionBMatrix"], (-1, 3, 3)), 
        lambda x: [{ 
            str(odil.registry.DiffusionBValueXX): { "vr": "FD", "Value": [x[0][0,0]] },
            str(odil.registry.DiffusionBValueXY): { "vr": "FD", "Value": [x[0][0,1]] },
            str(odil.registry.DiffusionBValueXZ): { "vr": "FD", "Value": [x[0][0,2]] },
            str(odil.registry.DiffusionBValueYY): { "vr": "FD", "Value": [x[0][1,1]] }, 
            str(odil.registry.DiffusionBValueYZ): { "vr": "FD", "Value": [x[0][1,2]] },
            str(odil.registry.DiffusionBValueZZ): { "vr": "FD", "Value": [x[0][2,2]] },
        }]
    )
]

SOPCommon = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.12.html#sect_C.12.1
    (None, "SOPClassUID", 1, lambda d,g,i: [odil.registry.MRImageStorage], None),
    (None, "SOPInstanceUID", 1, lambda d,g,i: [odil.generate_uid()], None),
    #SpecificCharacterSet
    (None, "InstanceCreationDate", 3, lambda d,g,i: [str(datetime.datetime.now())], None),
    (None, "InstanceCreationTime", 3, lambda d,g,i: [str(datetime.datetime.now())], None),
]
