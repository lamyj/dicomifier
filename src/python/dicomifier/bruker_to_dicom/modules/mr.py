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
    (None, "ScanningSequence", 1, lambda d,g,i: ["RM"]),
    (None, "SequenceVariant", 1, lambda d,g,i: ["NONE"]),
    (None, "ScanOptions", 2, lambda d,g,i: None),
    ("PVM_SpatDimEnum", "MRAcquisitionType", 2, None),
    (
        "VisuAcqRepetitionTime", "RepetitionTime", 2, 
        cached("__RepetitionTime")(
            lambda d,g,i: d.get(
                "VisuAcqRepetitionTime", d.get(
                    "PVM_RepetitionTime", d.get("MultiRepTime", None))))),
    ("VisuAcqEchoTime", "EchoTime", 2, None),
    ("VisuAcqEchoTrainLength", "EchoTrainLength", 2, None),
    ("VisuAcqInversionTime", "InversionTime", 3, None),
    ("VisuAcqSequenceName", "SequenceName", 3, None),
    ("VisuAcqNumberOfAverages", "NumberOfAverages", 3, None),
    ("VisuAcqImagingFrequency", "ImagingFrequency", 3, None),
    ("VisuAcqImagedNucleus", "ImagedNucleus", 3, None),
    (
        "VisuAcqImagingFrequency", "MagneticFieldStrength", 3, 
        cached("__MagneticFieldStrength")(
            lambda d,g,i: [d["VisuAcqImagingFrequency"][0]/42.577480610])),
    (
        None, "SpacingBetweenSlices", 3,
        cached("__SpacingBetweenSlices")(
            lambda d,g,i: [
                numpy.linalg.norm(
                    numpy.subtract(
                        d["VisuCorePosition"][3:6], d["VisuCorePosition"][0:3]))]
                if len(d["VisuCorePosition"]) >= 6 else None)),
    ("VisuAcqPhaseEncSteps", "NumberOfPhaseEncodingSteps", 3, None),
    ("VisuAcqPixelBandwidth", "PixelBandwidth", 3, None),
    ("VisuAcqFlipAngle", "FlipAngle", 3, None),
]

EnhancedMRImage = [ # PS 3.3, C.8.13.1
    (
        None, "ImageType", 3,
        cached("__ImageType")(
            lambda d,g,i: [
                b"ORIGINAL", b"PRIMARY", b"", 
                d.get("RECO_image_type", [""])[0].encode("ascii")])),
    (None, "PixelPresentation", 1, lambda d,g,i: ["MONOCHROME"]),
    (None, "VolumetricProperties", 1, lambda d,g,i: ["VOLUME"]),
    (None, "VolumeBasedCalculationTechnique", 1, lambda d,g,i : ["NONE"]),
    ("VisuAcqImagedNucleus", "ResonantNucleus", 3, None),
    ("VisuAcqDate", "AcquisitionDateTime", 3, None),
    (
        "VisuAcqImagingFrequency", "MagneticFieldStrength", 3, 
        cached("__MagneticFieldStrength")(
            lambda d,g,i: [d["VisuAcqImagingFrequency"][0]/42.577480610])),
]

MRPulseSequence = [ # PS 3.3, C.8.13.4
    ("PVM_SpatDimEnum", "MRAcquisitionType", 3, None),
    (
        "VisuAcqEchoSequenceType", "EchoPulseSequence", 3,
        cached("__EchoPulseSequence")(
            lambda d,g,i: [
                d.get(
                    "VisuAcqEchoSequenceType", [""]
                )[0].replace("Echo","").upper() or None])),
    # (None, "MultipleSpinEcho", 3, None),
    # (None, "MultiPlanarExcitation", 3, None),
    # (None, "PhaseContrast", 3, None),
    (
        "VisuAcqHasTimeOfFlightContrast", "TimeOfFlightContrast", 3,
        cached("__TimeOfFlightContrast")(
            lambda d,g,i: [
                d.get("VisuAcqHasTimeOfFlightContrast", [""])[0].upper() or None])),
    # (None, "ArterialSpinLabelingContrast", 3, None),
    # (None, "SteadyStatePulseSequence", 3, None),
    (
        "VisuAcqIsEpiSequence", "EchoPlanarPulseSequence", 3,
        cached("__EchoPlanarPulseSequence")(
            lambda d,g,i: [
                d.get("VisuAcqIsEpiSequence", [""])[0].upper() or None])),
    # (None, "SaturationRecovery", 3, None),
    (
        "VisuAcqSpectralSuppression", "SpectrallySelectedSuppression", 3,
        cached("__SpectrallySelectedSuppression")(
            lambda d,g,i: [
                d.get(
                    "VisuAcqSpectralSuppression", [""]
                )[0].replace("Suppression","").upper() or None])),
    # (None, "OversamplingPhase", 3, None),
    (
        "VisuAcqKSpaceTraversal", "GeometryOfKSpaceTraversal", 3,
        cached("__GeometryOfKSpaceTraversal")(
            lambda d,g,i: [
                d.get(
                    "VisuAcqKSpaceTraversal", [""]
                )[0].replace("Traversal","").upper() or None])),
    # (None, "RectilinearPhaseEncodeReordering", 3, None),
    # (None, "SegmentedKSpaceTraversal", 3, None),
    # (None, "CoverageOfKSpace", 3, None),
    ("VisuAcqKSpaceTrajectoryCnt", "NumberOfKSpaceTrajectories", 3, None),
]

MRImageFrameType = [ # PS 3.3, C.8.13.5.1
    "MRImageFrameTypeSequence", False,
    [
        (None, "FrameType", 1, lambda d,g,i: ["ORIGINAL", "PRIMARY"]), 
        (None, "PixelPresentation", 1, lambda d,g,i: ["MONOCHROME"]),
        (None, "VolumetricProperties", 1, lambda d,g,i: ["VOLUME"]),
        (None, "VolumeBasedCalculationTechnique", 1, lambda d,g,i : ["NONE"]),
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
                        "PVM_RepetitionTime", d.get("MultiRepTime", None))))),
        ("VisuAcqEchoTrainLength", "EchoTrainLength", 1, None),
        ("VisuAcqFlipAngle", "FlipAngle", 1, None),
    ]
]

MRFOVGeometry = [ # PS 3.3, C.8.13.5.3
    "MRFOVGeometrySequence", False,
    [
        (
            "VisuAcqPhaseEncSteps", "MRAcquisitionPhaseEncodingStepsInPlane", 1, 
            None),
    ]
]

MREcho = [ # PS 3.3, C.8.13.5.4
    "MREchoSequence", False,
    [
        (
            "VisuAcqEchoTime", "EffectiveEchoTime", 1, 
            cached("__EffectiveEchoTime")(
                lambda d,g,i: 
                    d.get("VisuAcqEchoTime", d.get("PVM_EchoTime", None)))),
    ]
]

MRModifier = [ # PS 3.3, C.8.13.5.5
    "MRModifierSequence", False,
    [
        ("VisuAcqInversionTime", "InversionTimes", 3, None),
    ]
]

MRImagingModifier = [ # PS 3.3, C.8.13.5.6
    "MRImagingModifierSequence", False,
    [
        ("VisuAcqPixelBandwidth", "PixelBandwidth", 1, None),
    ]
]

def get_diffusion_data(data_set, what):
    if "__Diffusion" not in data_set:
        # Cache the "ideal" diffusion direction and b-values.
        # The ideal direction is defined as the eigenvector associated with the
        # largest eigenvalue of the b-matrix. This assumes that the b-value is
        # large enough to mostly depend on the diffusion-sensitization gradient
        # and not on the imaging gradients.
        data_set["__Diffusion"] = ([], [], [])
        
        ideal_b_values = set(data_set["PVM_DwBvalEach"])
        ideal_b_values.add(0)
        ideal_b_values = list(ideal_b_values)
        
        b_matrices = numpy.reshape(data_set["PVM_DwBMat"], (-1, 3, 3))
        for index, b_matrix in enumerate(b_matrices):
            b_value = numpy.trace(b_matrix)
            closest = numpy.argmin([abs(b_value - x) for x in ideal_b_values])
            ideal_b_value = float(ideal_b_values[closest])
            
            direction = numpy.linalg.eigh(b_matrix)[1][:,-1]
            if ideal_b_value == 0:
                ideal_direction = direction
            else:
                ideal_directions = numpy.reshape(data_set["PVM_DwDir"], [-1, 3])
                closest = numpy.argmax([
                    numpy.abs(numpy.dot(direction, x)) 
                    for x in ideal_directions])
                ideal_direction = ideal_directions[closest].astype(float)
            
            b_matrix = odil.DataSet(**dict(zip(
                [
                    "DiffusionBValue{}".format(x) 
                    for x in ["XX", "XY", "XZ", "YY", "YZ", "ZZ"]], 
                [[x] for x in b_matrix[numpy.triu_indices(3)]])))
            
            data_set["__Diffusion"][0].append(ideal_b_value)
            data_set["__Diffusion"][1].append(
                odil.DataSet(
                    DiffusionGradientOrientation=ideal_direction.tolist()))
            data_set["__Diffusion"][2].append(b_matrix)
    
    return data_set["__Diffusion"][what]

MRDiffusion = [ # PS 3.3, C.8.13.5.9
    "MRDiffusionSequence", False,
    [
        (
            "VisuAcqDiffusionBMatrix", "DiffusionBValue", 1,
            lambda d, g, i: get_diffusion_data(d, 0)),
        (None, "DiffusionDirectionality", 1, lambda d,g,i: ["BMATRIX"]),
        (
            "VisuAcqDiffusionBMatrix", "DiffusionGradientDirectionSequence", 1,
            lambda d, g, i: get_diffusion_data(d, 1)),
        (
            "VisuAcqDiffusionBMatrix", "DiffusionBMatrixSequence", 1,
            lambda d, g, i: get_diffusion_data(d, 2))
    ]
]

MRAverages = [# PS 3.3, C.8.13.5.10
    "MRAveragesSequence", False,
    [
        ("VisuAcqNumberOfAverages", "NumberOfAverages", 1, None),
    ]
]
