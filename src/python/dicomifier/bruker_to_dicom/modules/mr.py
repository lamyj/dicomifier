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
    (
        "VisuAcqScanTime", "AcquisitionDuration", 3,
        lambda d, g, i: [d["VisuAcqScanTime"][0]/1e3]),
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
        "VisuAcqScanTime", "AcquisitionDuration", 3,
        lambda d, g, i: [d["VisuAcqScanTime"][0]/1e3]),
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
                )[0].replace("Echo","").upper()])),
    # (None, "MultipleSpinEcho", 3, None),
    # (None, "MultiPlanarExcitation", 3, None),
    # (None, "PhaseContrast", 3, None),
    (
        "VisuAcqHasTimeOfFlightContrast", "TimeOfFlightContrast", 3,
        cached("__TimeOfFlightContrast")(
            lambda d,g,i: [
                d.get("VisuAcqHasTimeOfFlightContrast", [""])[0].upper()])),
    # (None, "ArterialSpinLabelingContrast", 3, None),
    # (None, "SteadyStatePulseSequence", 3, None),
    (
        "VisuAcqIsEpiSequence", "EchoPlanarPulseSequence", 3,
        cached("__EchoPlanarPulseSequence")(
            lambda d,g,i: [
                d.get("VisuAcqIsEpiSequence", [""])[0].upper()])),
    # (None, "SaturationRecovery", 3, None),
    (
        "VisuAcqSpectralSuppression", "SpectrallySelectedSuppression", 3,
        cached("__SpectrallySelectedSuppression")(
            lambda d,g,i: [
                d.get(
                    "VisuAcqSpectralSuppression", [""]
                )[0].replace("Suppression","").upper()])),
    # (None, "OversamplingPhase", 3, None),
    (
        "VisuAcqKSpaceTraversal", "GeometryOfKSpaceTraversal", 3,
        cached("__GeometryOfKSpaceTraversal")(
            lambda d,g,i: [
                d.get(
                    "VisuAcqKSpaceTraversal", [""]
                )[0].replace("Traversal","").upper()])),
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
            "VisuAcqPhaseEncSteps", "MRAcquisitionPhaseEncodingStepsInPlane", 3, 
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
        # Cache the "ideal" b-values, directions of diffusion gradient, and
        # b-matrices.
        data_set["__Diffusion"] = [[], [], [], []]
        
        if "PVM_DwBvalEach" in data_set:
            # NOTE: even though FG_DIFFUSION may be in the frame groups, 
            # PVM_DwBvalEach may not be present (custom diffusion sequences)
            ideal_b_values = set(data_set["PVM_DwBvalEach"])
            ideal_b_values.add(0)
            ideal_b_values = list(ideal_b_values)
            
            # Map the effective b-values to the ideal b-values
            b_values = numpy.array(data_set["PVM_DwEffBval"])
            closest = numpy.argmin(
                [abs(b_values - x) for x in ideal_b_values], 0)
            individual_b_values = numpy.array(ideal_b_values)[closest]
            data_set["__Diffusion"][0] = individual_b_values
            
            # Keep the effective b-values
            data_set["__Diffusion"][3] = b_values
            
            # Normalize the directions, avoid divide-by-zero
            directions = numpy.reshape(data_set["PVM_DwGradVec"], (-1, 3))
            directions /= numpy.maximum(
                1e-20, numpy.linalg.norm(directions, axis=1))[:,None]
            # Convert to patient coordinates
            orientation = numpy.reshape(
                data_set["PVM_SPackArrGradOrient"], (3,3))
            directions = [orientation.T @ d for d in directions]
            # Store in cache
            data_set["__Diffusion"][1] = [
                odil.DataSet(DiffusionGradientOrientation=x)
                for x in directions]
            
            b_matrices = numpy.reshape(data_set["PVM_DwBMat"], (-1, 3, 3))
            # Convert to patient coordinates
            b_matrices = [orientation.T @ m @ orientation for m in b_matrices]
            # Store in cache
            data_set["__Diffusion"][2] = [
                odil.DataSet(**dict(zip(
                    [
                        f"DiffusionBValue{x}"
                        for x in ["XX", "XY", "XZ", "YY", "YZ", "ZZ"]],
                    [[x] for x in m[numpy.triu_indices(3)]])))
                for m in b_matrices]
    
    return data_set["__Diffusion"][what]

def MRDiffusionFactory(ideal_b_values):
    """ Return the MR Diffusion module (PS 3.3, C.8.13.5.9) with either the
        ideal b-values (mapped from PVM_DwEffBval to PVM_DwBvalEach) or the
        effective b-values (PVM_DwEffBval).
    """
    
    return [ # PS 3.3, C.8.13.5.9
        "MRDiffusionSequence", False,
        [
            # NOTE: VisuAcqDiffusionBMatrix does not exist in PV5. However, the 
            # diffusion frame group is normalized in order to include it in its
            # dependent fields.
            (
                "VisuAcqDiffusionBMatrix", "DiffusionBValue", 1,
                lambda d, g, i: get_diffusion_data(d, 0 if ideal_b_values else 3)),
            (None, "DiffusionDirectionality", 1, lambda d,g,i: ["DIRECTIONAL"]),
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
