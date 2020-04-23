#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import numpy
import odil

from . import cached

MRImage = [ # PS 3.3, C.8.3.1
    (None, "ScanningSequence", 1, lambda d,g,i: ["RM"], None),
    (None, "SequenceVariant", 1, lambda d,g,i: ["NONE"], None),
    (None, "ScanOptions", 2, lambda d,g,i: None, None),
    ("PVM_SpatDimEnum", "MRAcquisitionType", 2, None, None),
    (
        "VisuAcqRepetitionTime", "RepetitionTime", 2, 
        cached("__RepetitionTime")(
            lambda d,g,i: d.get(
                "VisuAcqRepetitionTime", d.get(
                    "PVM_RepetitionTime", d.get("MultiRepTime", None)))), 
        None),
    ("VisuAcqEchoTime", "EchoTime", 2, None, None),
    ("VisuAcqEchoTrainLength", "EchoTrainLength", 2, None, None),
    ("VisuAcqInversionTime", "InversionTime", 3, None, None),
    ("VisuAcqSequenceName", "SequenceName", 3, None, None),
    ("VisuAcqNumberOfAverages", "NumberOfAverages", 3, None, None),
    ("VisuAcqImagingFrequency", "ImagingFrequency", 3, None, None),
    ("VisuAcqImagedNucleus", "ImagedNucleus", 3, None, None),
    (
        "VisuAcqImagingFrequency", "MagneticFieldStrength", 3, 
        cached("__MagneticFieldStrength")(
            lambda d,g,i: [d["VisuAcqImagingFrequency"][0]/42.577480610]),
        None
    ),
    (
        None, "SpacingBetweenSlices", 3,
        cached("__SpacingBetweenSlices")(
            lambda d,g,i: [
                numpy.linalg.norm(
                    numpy.subtract(
                        d["VisuCorePosition"][3:6], d["VisuCorePosition"][0:3]))]
                if len(d["VisuCorePosition"]) >= 6 else None), 
        None
    ),
    ("VisuAcqPhaseEncSteps", "NumberOfPhaseEncodingSteps", 3, None, None),
    ("VisuAcqPixelBandwidth", "PixelBandwidth", 3, None, None),
    ("VisuAcqFlipAngle", "FlipAngle", 3, None, None),
]

EnhancedMRImage = [ # PS 3.3, C.8.13.1
    (
        None, "ImageType", 3,
        cached("__ImageType")(
            lambda d,g,i: [
                b"ORIGINAL", b"PRIMARY", b"", 
                d.get("RECO_image_type", [""])[0].encode("ascii")]), 
        None),
    (None, "PixelPresentation", 1, lambda d,g,i: ["MONOCHROME"], None),
    (None, "VolumetricProperties", 1, lambda d,g,i: ["VOLUME"], None),
    (None, "VolumeBasedCalculationTechnique", 1, lambda d,g,i : ["NONE"], None),
    ("VisuAcqImagedNucleus", "ResonantNucleus", 3, None, None),
    ("VisuAcqDate", "AcquisitionDateTime", 3, None, None),
    (
        "VisuAcqImagingFrequency", "MagneticFieldStrength", 3, 
        cached("__MagneticFieldStrength")(
            lambda d,g,i: [d["VisuAcqImagingFrequency"][0]/42.577480610]),
        None
    ),
]

MRPulseSequence = [ # PS 3.3, C.8.13.4
    ("PVM_SpatDimEnum", "MRAcquisitionType", 3, None, None),
    ("VisuAcqEchoSequenceType", "EchoPulseSequence", 3,
        cached("__EchoPulseSequence")(
            lambda d,g,i: [
                d.get(
                    "VisuAcqEchoSequenceType", [""]
                )[0].replace("Echo","").upper() or None]),
        None
        
    ),
    # (None, "MultipleSpinEcho", 3, None, None),
    # (None, "MultiPlanarExcitation", 3, None, None),
    # (None, "PhaseContrast", 3, None, None),
    ("VisuAcqHasTimeOfFlightContrast", "TimeOfFlightContrast", 3,
        cached("__TimeOfFlightContrast")(
            lambda d,g,i: [
                d.get("VisuAcqHasTimeOfFlightContrast", [""])[0].upper() or None]),
        None
    ),
    # (None, "ArterialSpinLabelingContrast", 3, None, None),
    # (None, "SteadyStatePulseSequence", 3, None, None),
    ("VisuAcqIsEpiSequence", "EchoPlanarPulseSequence", 3,
        cached("__EchoPlanarPulseSequence")(
            lambda d,g,i: [
                d.get("VisuAcqIsEpiSequence", [""])[0].upper() or None]),
        None
    ),
    # (None, "SaturationRecovery", 3, None, None),
    ("VisuAcqSpectralSuppression", "SpectrallySelectedSuppression", 3,
        cached("__SpectrallySelectedSuppression")(
            lambda d,g,i: [
                d.get(
                    "VisuAcqSpectralSuppression", [""]
                )[0].replace("Suppression","").upper() or None]),
        None
    ),
    # (None, "OversamplingPhase", 3, None, None),
    ("VisuAcqKSpaceTraversal", "GeometryOfKSpaceTraversal", 3,
        cached("__GeometryOfKSpaceTraversal")(
            lambda d,g,i: [
                d.get(
                    "VisuAcqKSpaceTraversal", [""]
                )[0].replace("Traversal","").upper() or None]),
        None
    ),
    # (None, "RectilinearPhaseEncodeReordering", 3, None, None),
    # (None, "SegmentedKSpaceTraversal", 3, None, None),
    # (None, "CoverageOfKSpace", 3, None, None),
    ("VisuAcqKSpaceTrajectoryCnt", "NumberOfKSpaceTrajectories", 3, None, None),
]

MRImageFrameType = [ # PS 3.3, C.8.13.5.1
    "MRImageFrameTypeSequence", False,
    [
        (None, "FrameType", 1, lambda d,g,i: ["ORIGINAL", "PRIMARY"], None), 
        (None, "PixelPresentation", 1, lambda d,g,i: ["MONOCHROME"], None),
        (None, "VolumetricProperties", 1, lambda d,g,i: ["VOLUME"], None),
        (
            None, "VolumeBasedCalculationTechnique", 1, 
            lambda d,g,i : ["NONE"], None),
    ]
]

MRTimingAndRelatedParameters = [ # PS 3.3, C.8.13.5.2
    "MRTimingAndRelatedParametersSequence", False,
    [
        # WARNING : First argument cannot be None if present if FG
        (
            "VisuAcqRepetitionTime", "RepetitionTime", 1, 
            cached("__RepetitionTime")(
                lambda d,g,i: d.get(
                    "VisuAcqRepetitionTime", d.get(
                        "PVM_RepetitionTime", d.get("MultiRepTime", None)))), 
            None),
        ("VisuAcqEchoTrainLength", "EchoTrainLength", 1, None, None),
        ("VisuAcqFlipAngle", "FlipAngle", 1, None, None),
    ]
]

MRFOVGeometry = [ # PS 3.3, C.8.13.5.3
    "MRFOVGeometrySequence", False,
    [
        (
            "VisuAcqPhaseEncSteps", "MRAcquisitionPhaseEncodingStepsInPlane", 1, 
            None, None),
    ]
]

MREcho = [ # PS 3.3, C.8.13.5.4
    "MREchoSequence", False,
    [
        (
            "VisuAcqEchoTime", "EffectiveEchoTime", 1, 
            cached("__EffectiveEchoTime")(
                lambda d,g,i: 
                    d.get("VisuAcqEchoTime", d.get("PVM_EchoTime", None))), 
            None),
    ]
]

MRModifier = [ # PS 3.3, C.8.13.5.5
    "MRModifierSequence", False,
    [
        ("VisuAcqInversionTime", "InversionTimes", 3, None, None),
    ]
]

MRImagingModifier = [ # PS 3.3, C.8.13.5.6
    "MRImagingModifierSequence", False,
    [
        ("VisuAcqPixelBandwidth", "PixelBandwidth", 1, None, None),
    ]
]

def get_direction_and_b_value(data_set, b_matrix):
    # The "ideal" direction is defined as the eigenvector associated with the
    # largest eigenvalue of the b-matrix. This assumes that the b-value is
    # large enough to mostly depend on the diffusion-sensitization gradient and
    # not on the imaging gradients.
    
    ideal_b_values = set(data_set["PVM_DwBvalEach"])
    ideal_b_values.add(0)
    ideal_b_values = list(ideal_b_values)
    
    b_value = numpy.trace(b_matrix)
    b_value_distances = [abs(b_value - x) for x in ideal_b_values]
    ideal_b_value = ideal_b_values[numpy.argmin(b_value_distances)]
    
    direction = numpy.linalg.eigh(b_matrix)[1][:,-1]
    if ideal_b_value == 0:
        ideal_direction = direction
    else:
        ideal_directions = numpy.reshape(data_set["PVM_DwDir"], [-1, 3])
        direction_dot = [
            numpy.abs(numpy.dot(direction, x)) for x in ideal_directions]
        ideal_direction = ideal_directions[numpy.argmax(direction_dot)]
    
    return ideal_direction.astype(float), float(ideal_b_value)

MRDiffusion = [ # PS 3.3, C.8.13.5.9
    "MRDiffusionSequence", False,
    [
        (
            "VisuAcqDiffusionBMatrix", "DiffusionBValue", 1,
            cached("__DiffusionBValue")(
                lambda d,g,i: [ 
                    get_direction_and_b_value(d, x)[1] 
                    for x in numpy.reshape(d["PVM_DwBMat"], (-1, 3, 3))]),
            None
        ),
        (None, "DiffusionDirectionality", 1, lambda d,g,i: ["BMATRIX"], None),
        (
            "VisuAcqDiffusionBMatrix", "DiffusionGradientDirectionSequence", 1,
            cached("__DiffusionGradientDirectionSequence")(
                lambda d,g,i: [
                    get_direction_and_b_value(d, x)[0] 
                    for x in numpy.reshape(d["PVM_DwBMat"], (-1, 3, 3))]),
            lambda x: [odil.DataSet(DiffusionGradientOrientation=numpy.ravel(x))]
        ),
        (
            "VisuAcqDiffusionBMatrix", "DiffusionBMatrixSequence", 1,
            cached("__DiffusionBMatrixSequence")(
                lambda d,g,i: numpy.reshape(d["PVM_DwBMat"], (-1, 3, 3))),
            lambda m: [
                odil.DataSet(**dict(zip(
                    [
                        "DiffusionBValue{}".format(x) 
                        for x in ["XX", "XY", "XZ", "YY", "YZ", "ZZ"]], 
                    [[x] for x in m[0][numpy.triu_indices(3)]])))]
        )
    ]
]

MRAverages = [# PS 3.3, C.8.13.5.10
    "MRAveragesSequence", False,
    [
        ("VisuAcqNumberOfAverages", "NumberOfAverages", 1, None, None),
    ]
]
