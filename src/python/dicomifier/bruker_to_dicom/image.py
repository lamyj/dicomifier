#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import datetime
import json
import re

import numpy
import odil

def _get_acquisition_number(data_set, generator, frame_index):
    index = [
        x for g, x in zip(generator.frame_groups, frame_index)
        if g[1] != "FG_SLICE"]
    shape = [g[0] for g in generator.frame_groups if g[1] != "FG_SLICE"]

    acquisition_number = (
        numpy.ravel_multi_index(index, shape) if (len(index) != 0) else 0)

    return [acquisition_number]

def _get_pixel_data(data_set, generator, frame_index):
    """ Read the pixel data and return the given frame.
        This function MUST be called before converting VisuCoreDataOffs and 
        VisuCoreDataSlope.
    """
    
    if isinstance(data_set["PIXELDATA"], list):
        dtype = {
            "_8BIT_UNSGN_INT": numpy.uint8,
            "_16BIT_SGN_INT": numpy.int16,
            "_32BIT_SGN_INT": numpy.int32,
            "_32BIT_FLOAT": numpy.single,
        }[data_set["VisuCoreWordType"][0]]
        
        # Read the file
        with open(data_set["PIXELDATA"][0], "rb") as fd:
            pixel_data = numpy.fromfile(fd, dtype)
            data_set["PIXELDATA"] = pixel_data.reshape(
                -1, data_set["VisuCoreSize"][0]*data_set["VisuCoreSize"][1])
        if data_set["PIXELDATA"].dtype == numpy.single:
            # Map to uint32
            min = data_set["PIXELDATA"].min()
            max = data_set["PIXELDATA"].max()
            
            data_set["PIXELDATA"] -= min
            data_set["PIXELDATA"] *= (1<<32)/(max-min)
            data_set["PIXELDATA"] = data_set["PIXELDATA"].astype(numpy.uint32)
            
            data_set["VisuCoreDataOffs"] = [0]*len(data_set["VisuCoreDataOffs"])
            data_set["VisuCoreDataSlope"] = [1]*len(data_set["VisuCoreDataOffs"])
            
            if "VisuCoreDataOffs" in data_set:
                data_set["VisuCoreDataOffs"] = [
                    x+min for x in data_set["VisuCoreDataOffs"]]
            if "VisuCoreDataSlope" in data_set:
                data_set["VisuCoreDataSlope"] = [
                    x/((1<<32)/(max-min)) for x in data_set["VisuCoreDataSlope"]]
    
    if data_set.get("VisuCoreDiskSliceOrder", [None])[0] == "disk_reverse_slice_order":
        # Volumes are always in order, but slice order depends on
        # VisuCoreDiskSliceOrder
        #fg_slice = [g for g in generator.frame_groups if g[1] == "FG_SLICE"]
        non_slice = [g for g in generator.frame_groups if g[1] != "FG_SLICE"]
        if len(non_slice) == 0:
            slices_per_frame = data_set["VisuCoreFrameCount"][0]
        else:
            slices_per_frame = (
                data_set["VisuCoreFrameCount"][0]
                / numpy.cumprod([x[0] for x in non_slice])[-1])
        frame_index = generator.get_linear_index(frame_index)
        volume = frame_index / slices_per_frame
        slice_index = frame_index % slices_per_frame
        frame_index = int(
            volume*slices_per_frame+(slices_per_frame-slice_index-1))
    else:
        frame_index = generator.get_linear_index(frame_index)
    frame_data = data_set["PIXELDATA"][frame_index]
    
    return [frame_data.tostring()]

def _get_direction(data_set):
    return [
        _get_direction_and_b_value(data_set, x)[0] 
        for x in numpy.reshape(data_set["PVM_DwBMat"], (-1, 3, 3))]

def _get_b_value(data_set):
    return [
        _get_direction_and_b_value(data_set, x)[1] 
        for x in numpy.reshape(data_set["PVM_DwBMat"], (-1, 3, 3))]

def _get_direction_and_b_value(data_set, b_matrix):
    # Adapted from https://github.com/BRAINSia/BRAINSTools/blob/92cbbec97a8100a38bc019b30591f7c0f9a26951/DWIConvert/SiemensDWIConverter.h
    # FIXME: find a reference to support this
    
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

def _set_diffusion_gradient(value):
    """ Return an odil DataSet containing the DiffusionGradientDiffusion element
        required for the DiffusionGradientDirectionSequence
    """
    
    result = odil.DataSet()
    result.add("DiffusionGradientOrientation", value)
    return result

def _set_diffusion_b_matrix(matrix):
    """ Return an odil DataSet containing all required elements for
        the Diffusion B-Matrix Sequence
    """
    result = odil.DataSet()
    result.add("DiffusionBValueXX", [matrix[0][0, 0]])
    result.add("DiffusionBValueXY", [matrix[0][0, 1]])
    result.add("DiffusionBValueXZ", [matrix[0][0, 2]])
    result.add("DiffusionBValueYY", [matrix[0][1, 1]])
    result.add("DiffusionBValueYZ", [matrix[0][1, 2]])
    result.add("DiffusionBValueZZ", [matrix[0][2, 2]])
    return result

def _get_echo_time (data_set):
    echo_time = None
    # WARNING : keep this order to have the main priority for the visu_pars file
    values = [
        data_set.get("PVM_EchoTime", None),
        data_set.get("VisuAcqEchoTime", None),
    ]
    for i, v in enumerate(values):
        if v is not None:
            echo_time = v
    return echo_time

def _get_repetition_time (data_set):
    rep_time = None
    # WARNING : keep this order to have the main priority for the visu_pars file
    values = [
        data_set.get("MultiRepTime", None),
        data_set.get("PVM_RepetitionTime", None),
        data_set.get("VisuAcqRepetitionTime", None),
    ]
    for i, v in enumerate(values):
        if v is not None:
            rep_time = v
    return rep_time

def _get_echo_pulse_sequence (data_set, generator, frame_index):
    if "VisuAcqEchoSequenceType" in data_set:
        return [data_set["VisuAcqEchoSequenceType"][0].replace("Echo","").upper()]
    else:
        return None

def _get_time_of_flight_contrast(data_set, generator, frame_index):
    if "VisuAcqHasTimeOfFlightContrast" in data_set:
        return [data_set["VisuAcqHasTimeOfFlightContrast"][0].upper()]
    else:
        return None

def _get_echo_planar_pulse_seq(data_set, generator, frame_index):
    if "VisuAcqIsEpiSequence" in data_set:
        return [data_set["VisuAcqIsEpiSequence"][0].upper()]
    else:
        return None

def _get_spectrally_selected_suppression(data_set, generator, frame_index):
    if "VisuAcqSpectralSuppression" in data_set:
        return [data_set["VisuAcqSpectralSuppression"][0].replace("Suppression","").upper()]
    else:
        return None

def _get_geometry_of_kSpace_traversal(data_set, generator, frame_index):
    if "VisuAcqKSpaceTraversal" in data_set:
        return [data_set["VisuAcqKSpaceTraversal"][0].replace("Transversal","").upper()]
    else:
        return None

def _get_frame_index(bruker_data_set, generator, frame_index):
    purpose = odil.DataSet()
    purpose.add("CodeValue", ["109102"])
    purpose.add("CodingSchemeDesignator", ["DCM"])
    purpose.add("CodeMeaning", ["Processing Equipment"])
    
    data_set = odil.DataSet()
    data_set.add("PurposeOfReferenceCodeSequence", [purpose])
    data_set.add("Manufacturer", ["Dicomifier"])
    data_set.add("ManufacturerModelName", ["Bruker Frame Group index"])
    contribution = [
        [fg[1], frame_index[i]]
        for i, fg in enumerate(generator.frame_groups) 
        if fg[1] != 'FG_SLICE']
    data_set.add("ContributionDescription", [json.dumps(contribution)])
    
    return data_set

GeneralImage = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.html#sect_C.7.6.1
    (None, "InstanceNumber", 2, lambda d,g,i: [1+g.get_linear_index(i)], None),
    (
        None, "ImageType", 3, 
        lambda d,g,i: [
            b"ORIGINAL", b"PRIMARY", b"", 
            d["RECO_image_type"][0].encode("utf-8")], None),
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
        None, {
            "_32BIT_FLOAT": 32, 
            "_32BIT_SGN_INT": 32, "_16BIT_SGN_INT": 16, "_8BIT_UNSGN_INT": 8
        }
    ),
    (
        "VisuCoreWordType", "BitsStored", 1, 
        None, {
            "_32BIT_FLOAT": 32, 
            "_32BIT_SGN_INT": 32, "_16BIT_SGN_INT": 16, "_8BIT_UNSGN_INT": 8
        }
    ),
    (
        "VisuCoreByteOrder", "HighBit", 1, 
        lambda d,g,i: [
            {
                "_32BIT_FLOAT": 32, 
                "_32BIT_SGN_INT": 32, "_16BIT_SGN_INT": 16, "_8BIT_UNSGN_INT": 8
            }[d["VisuCoreWordType"][0]]-1 
            if d["VisuCoreByteOrder"][0]=="littleEndian" else 0
        ],
        None
    ),
    (
        "VisuCoreWordType", "PixelRepresentation", 1, 
        None, {
            "_32BIT_FLOAT": 0, # mapped to uint32 
            "_32BIT_SGN_INT": 1, "_16BIT_SGN_INT": 1, "_8BIT_UNSGN_INT": 0}
    ),
    (None, "PixelData", 1, _get_pixel_data, None),
    # WARNING SmallestImagePixelValue and LargestImagePixelValue are either US
    # or SS and thus cannot accomodate 32 bits values. Use WindowCenter and
    # WindowWidth instead.
    (
        None, "WindowCenter", 3, 
        lambda d,g,i: [
            0.5*(
                d["VisuCoreDataMin"][g.get_linear_index(i)]
                +d["VisuCoreDataMax"][g.get_linear_index(i)])
        ], 
        None
    ),
    (
        None, "WindowWidth", 3, 
        lambda d,g,i: [
            d["VisuCoreDataMax"][g.get_linear_index(i)]
            -d["VisuCoreDataMax"][g.get_linear_index(i)]
        ],
        None
    ),
]

MRImage = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.3.html#sect_C.8.3.1
    (None, "ScanningSequence", 1, lambda d,g,i: ["RM"], None),
    (None, "SequenceVariant", 1, lambda d,g,i: ["NONE"], None),
    (None, "ScanOptions", 2, lambda d,g,i: None, None),
    ("PVM_SpatDimEnum", "MRAcquisitionType", 2, None, None),
    ("VisuAcqRepetitionTime", "RepetitionTime", 2, lambda d,g,i: _get_repetition_time(d), None),
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


MRDiffusion = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.9.html
    (
        "VisuAcqDiffusionBMatrix", "DiffusionBValue", 1,
        lambda d,g,i: _get_b_value(d), None
    ),
    (None, "DiffusionDirectionality", 1, lambda d,g,i: ["BMATRIX"], None),
    (
        "VisuAcqDiffusionBMatrix", "DiffusionGradientDirectionSequence", 1,
        lambda d,g,i: _get_direction(d), 
        lambda x: [_set_diffusion_gradient(numpy.asarray(x).ravel().tolist())]
    ),
    (
        "VisuAcqDiffusionBMatrix", "DiffusionBMatrixSequence", 1,
        lambda d,g,i: numpy.reshape(d["PVM_DwBMat"], (-1, 3, 3)),
        lambda x: [_set_diffusion_b_matrix(x)]
    )
]

SOPCommon = [ # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.12.html#sect_C.12.1
    (None, "SOPInstanceUID", 1, lambda d,g,i: [odil.generate_uid()], None),
    #SpecificCharacterSet
    (None, "InstanceCreationDate", 3, lambda d,g,i: [str(datetime.datetime.now())], None),
    (None, "InstanceCreationTime", 3, lambda d,g,i: [str(datetime.datetime.now())], None),
]


# Below -> new image modules for enhanced image storage

MutliFrameFunctionalGroups = [#http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.16.html
    ("VisuCoreFrameCount", "NumberOfFrames", 1, None, None),
    (None, "ContentDate", 1, lambda d,g,i: [str(datetime.datetime.now())], None),
    (None, "ContentTime", 1, lambda d,g,i: [str(datetime.datetime.now())], None),
    (None, "InstanceNumber", 1, lambda d,g,i: [1], None), # Same as in GeneralImage but type 1 here
]

MultiFrameDimension = [#http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.17.html
    (None, "DimensionOrganizationSequence", 1, lambda d,g,i: [], None),
    (None, "DimensionIndexSequence", 1, lambda d,g,i: [], None),
]

AcquisitionContext = [#http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.14.html
    (None, "AcquisitionContextSequence", 1, lambda d,g,i: [], None),
]

EnhancedMRImage = [#http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.html#sect_C.8.13.1
    (None, "ImageType", 3, # Same as in GeneralImage but type is 1 here
    lambda d,g,i: [
        b"ORIGINAL", b"PRIMARY", b"", 
        d["RECO_image_type"][0].encode("ascii")], None),
    (None, "PixelPresentation", 1, lambda d,g,i: ["MONOCHROME"], None),
    (None, "VolumetricProperties", 1, lambda d,g,i: ["VOLUME"], None),
    (None, "VolumeBasedCalculationTechnique", 1, lambda d,g,i : ["NONE"], None),
    ("VisuAcqImagedNucleus", "ResonantNucleus", 3, None, None),
    ("VisuAcqDate", "AcquisitionDateTime", 3, None, None),
    (
        "VisuAcqImagingFrequency", "MagneticFieldStrength", 3, None,
        lambda x: [float(x[0])/42.577480610]
    ),
]

MRPulseSequence = [#http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.4.html
    ("PVM_SpatDimEnum", "MRAcquisitionType", 3, None, None),
    ("VisuAcqEchoSequenceType", "EchoPulseSequence", 3,
        _get_echo_pulse_sequence, None
    ),
    # (None, "MultipleSpinEcho", 3, None, None),
    # (None, "MultiPlanarExcitation", 3, None, None),
    # (None, "PhaseContrast", 3, None, None),
    ("VisuAcqHasTimeOfFlightContrast", "TimeOfFlightContrast", 3,
        _get_time_of_flight_contrast, None
    ),
    # (None, "ArterialSpinLabelingContrast", 3, None, None),
    # (None, "SteadyStatePulseSequence", 3, None, None),
    ("VisuAcqIsEpiSequence", "EchoPlanarPulseSequence", 3,
        _get_echo_planar_pulse_seq, None
    ),
    # (None, "SaturationRecovery", 3, None, None),
    ("VisuAcqSpectralSuppression", "SpectrallySelectedSuppression", 3,
        _get_spectrally_selected_suppression, None
    ),
    # (None, "OversamplingPhase", 3, None, None),
    ("VisuAcqKSpaceTraversal", "GeometryOfKSpaceTraversal", 3,
        _get_geometry_of_kSpace_traversal, None
    ),
    # (None, "RectilinearPhaseEncodeReordering", 3, None, None),
    # (None, "SegmentedKSpaceTraversal", 3, None, None),
    # (None, "CoverageOfKSpace", 3, None, None),
    ("VisuAcqKSpaceTrajectoryCnt", "NumberOfKSpaceTrajectories", 3, None, None),
]
