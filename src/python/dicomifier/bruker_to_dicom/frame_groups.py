#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import datetime
import re
import numpy

import odil

from image import _get_acquisition_number, _get_direction_and_b_value, _set_diffusion_gradient, _set_diffusion_b_matrix

"""
Modele for frame groups
<Functional Group Macro> = {
    ("Sequence Name", PerFrameOnly) :
    [     
        (bruker_elemt, dcm_elem, type, getter, setter), ... 
    ]
}
"""

PixelMeasures = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.16.2.html#sect_C.7.6.16.2.1
    ("PixelMeasuresSequence", False) :
    [
        (
            None, "PixelSpacing", 3,
                    lambda d,g,i: numpy.divide(
                        numpy.asarray(d["VisuCoreExtent"], float),
                        numpy.asarray(d["VisuCoreSize"], float)
                    ).tolist(),
            None
        ),
        ("VisuCoreFrameThickness", "SliceThickness", 3, None, None),
        (
            None, "SpacingBetweenSlices", 3,
            lambda d,g,i: [numpy.linalg.norm(
                numpy.subtract(d["VisuCorePosition"][3:6], d["VisuCorePosition"][0:3]
            ))] if len(d["VisuCorePosition"]) >= 6 else None,
            None
        ),
    ]
}

FrameContent = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.16.2.html#sect_C.7.6.16.2.2
    ("FrameContentSequence", True) :
    [
        (None, "FrameAcquisitionNumber", 3, _get_acquisition_number, None),
    ]
}

PlanePosition = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.16.2.html#sect_C.7.6.16.2.3
    ("PlanePositionSequence", False) :
    [
        (
            "VisuCorePosition", "ImagePositionPatient", 1,
            lambda d,g,i: numpy.reshape(d["VisuCorePosition"], (-1, 3)),
            lambda x: x[0].tolist()
        ),
    ]
}

PlaneOrientation = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.16.2.html#sect_C.7.6.16.2.4
    ("PlaneOrientationSequence", False) :
    [
        (
            "VisuCoreOrientation", "ImageOrientationPatient", 1,
            lambda d,g,i: numpy.reshape(d["VisuCoreOrientation"], (-1, 9)),
            lambda x: x[0][:6].tolist()
        ),
    ]
}

FrameAnatomy = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.16.2.html#sect_C.7.6.16.2.8
    ("FrameAnatomySequence", False) :
    [
        #WARNING FrameLaterality not handled correctly for the moment
        (None, "FrameLaterality", 1, lambda d,g,i: ["U"], None),
        (None, "AnatomicRegionSequence", 1, lambda d,g,i: [odil.DataSet()], None),
    ]
}

PixelValueTransformation = {# http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.16.2.html#sect_C.7.6.16.2.9
    ("PixelValueTransformationSequence", False) :
    [
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
}

MRImageFrameType = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.html#sect_C.8.13.5.1
    ("MRImageFrameTypeSequence", False) :
    [
        (None, "FrameType", 1, lambda d,g,i: ["ORIGINAL", "PRIMARY"], None), #Same as ImageType but "Mixed" not allowed if... (see link above)
        (None, "PixelPresentation", 1, lambda d,g,i: ["MONOCHROME"], None),
        (None, "VolumetricProperties", 1, lambda d,g,i: ["VOLUME"], None),
        (None, "VolumeBasedCalculationTechnique", 1, lambda d,g,i : ["NONE"], None),
    ]
}

MRTimingAndRelatedParameters = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.2.html
    ("MRTimingAndRelatedParametersSequence", False) :
    [
        ("VisuAcqRepetitionTime", "RepetitionTime", 3, None, None),
        ("VisuAcqEchoTrainLength", "EchoTrainLength", 3, None, None),
        ("VisuAcqFlipAngle", "FlipAngle", 3, None, None),
    ]
}

MRFOVGeometry = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.3.html
    ("MRFOVGeometrySequence", False) :
    [
        ("VisuAcqPhaseEncSteps", "MRAcquisitionPhaseEncodingStepsInPlane", 3, None, None),
    ]
}

MREcho = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.4.html
    ("MREchoSequence", False) :
    [
        ("VisuAcqEchoTime", "EffectiveEchoTime", 3, None, None),
    ]
}

MRModifier = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.5.html
    ("MRModifierSequence", False) :
    [
        ("VisuAcqInversionTime", "InversionTime", 3, None, None),
    ]
}

MRImagingModifier = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.6.html
    ("MRImagingModifierSequence", False) :
    [
        ("VisuAcqPixelBandwidth", "PixelBandwidth", 3, None, None),
    ]
}

MRDiffusion = { # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.9.html
    ("MRDiffusionSequence", False) :
    [
        (
            "VisuAcqDiffusionBMatrix", "DiffusionBValue", 3,
            lambda d,g,i: [
                _get_direction_and_b_value(x)[1] 
                for x in numpy.reshape(d["VisuAcqDiffusionBMatrix"], (-1, 3, 3))],
            None
        ),
        (None, "DiffusionDirectionality", 3, lambda d,g,i: ["BMATRIX"], None),
        (
            "VisuAcqDiffusionBMatrix", "DiffusionGradientDirectionSequence", 3,
            lambda d,g,i: [
                _get_direction_and_b_value(x)[0] 
                for x in numpy.reshape(d["VisuAcqDiffusionBMatrix"], (-1, 3, 3))],
            lambda x: [_set_diffusion_gradient(numpy.asarray(x).ravel().tolist())]
        ),
        (
            "VisuAcqDiffusionBMatrix", "DiffusionBMatrixSequence", 3,
            lambda d,g,i: numpy.reshape(d["VisuAcqDiffusionBMatrix"], (-1, 3, 3)),
            lambda x: [_set_diffusion_b_matrix(x)]
        )
    ]
}

MRAverages = {# http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.10.html
    ("MRAveragesSequence", False) :
    [
        ("VisuAcqNumberOfAverages", "NumberOfAverages", 3, None, None),
    ]
}