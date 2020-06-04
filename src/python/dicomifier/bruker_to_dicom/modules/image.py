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

from . import cached

def get_acquisition_number(data_set, generator, frame_index):
    index = [
        x for g, x in zip(generator.frame_groups, frame_index)
        if g[1] != "FG_SLICE"]
    shape = [g[0] for g in generator.frame_groups if g[1] != "FG_SLICE"]

    acquisition_number = (
        numpy.ravel_multi_index(index, shape) if (len(index) != 0) else 0)

    return [acquisition_number]

def get_pixel_data(data_set, generator, frame_index):
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
        non_slice = [g for g in generator.frame_groups if g[1] != "FG_SLICE"]
        if len(non_slice) == 0:
            slices_per_frame = data_set["VisuCoreFrameCount"][0]
        else:
            slices_per_frame = int(
                data_set["VisuCoreFrameCount"][0]
                / numpy.cumprod([x[0] for x in non_slice])[-1])
        frame_index = generator.get_linear_index(frame_index)
        volume, slice_index = divmod(frame_index, slices_per_frame)
        frame_index = volume*slices_per_frame+(slices_per_frame-slice_index-1)
    else:
        frame_index = generator.get_linear_index(frame_index)
    frame_data = data_set["PIXELDATA"][frame_index]
    
    return [bytearray(frame_data.tobytes())]

def get_frame_index(generator, frame_index):
    contribution = [
        [fg[1], frame_index[i]]
        for i, fg in enumerate(generator.frame_groups) 
        if fg[1] != 'FG_SLICE']
        
    return odil.DataSet(
        PurposeOfReferenceCodeSequence=[odil.DataSet(
            CodeValue=["109102"], CodingSchemeDesignator=["DCM"],
            CodeMeaning=["Processing Equipment"])],
        Manufacturer=["Dicomifier"], 
        ManufacturerModelName=["Bruker Frame Group index"],
        ContributionDescription=[json.dumps(contribution)])

GeneralImage = [ # PS 3.3, C.7.6.1
    (None, "InstanceNumber", 2, lambda d,g,i: [1+g.get_linear_index(i)]),
    (
        None, "ImageType", 3, 
        cached("__ImageType")(
            lambda d,g,i: [
                b"ORIGINAL", b"PRIMARY", b"", 
                d.get("RECO_image_type", [""])[0].encode("utf-8")])),
    (None, "AcquisitionNumber", 3, get_acquisition_number),
    ("VisuAcqDate", "AcquisitionDate", 3, None),
    ("VisuAcqDate", "AcquisitionTime", 3, None),
    (
        "VisuCoreFrameCount", "ImagesInAcquisition", 3,
        cached("__ImagesInAcquisition")(
            lambda d,g,i: 
                [int(d["VisuCoreFrameCount"])[0]*d["VisuCoreSize"][2]]
                if d["VisuCoreDim"]==3
                else [int(x) for x in d["VisuCoreFrameCount"]])),
]

ImagePlane = [ # PS 3.3, C.7.6.2
    (
        None, "PixelSpacing", 1,
        cached("__PixelSpacing")(
            lambda d, g, i,: numpy.asarray(d["VisuCoreExtent"], float)
                / numpy.asarray(d["VisuCoreSize"], float))),
    (
        "VisuCoreOrientation", "ImageOrientationPatient", 1,
        cached("__ImageOrientationPatient")(
            lambda d,g,i: numpy.squeeze(
                numpy.reshape(d["VisuCoreOrientation"], (-1, 9))[:,:6]))),
    (
        "VisuCorePosition", "ImagePositionPatient", 1,
        cached("__ImagePositionPatient")(
            lambda d,g,i: numpy.squeeze(
                numpy.reshape(d["VisuCorePosition"], (-1, 3))))),
    ("VisuCoreFrameThickness", "SliceThickness", 2, None)
]

ImagePixel = [ # PS 3.3, C.7.6.3
    (None, "SamplesPerPixel", 1, lambda d,g,i: [1]),
    (None, "PhotometricInterpretation", 1, lambda d,g,i: ["MONOCHROME2"]),
    ("VisuCoreSize", "Rows", 1, lambda d,g,i: [d["VisuCoreSize"][1]]),
    ("VisuCoreSize", "Columns", 1, lambda d,g,i: [d["VisuCoreSize"][0]]),
    (
        "VisuCoreWordType", "BitsAllocated", 1, 
        cached("__BitsAllocated")(
            lambda d,g,i: [{
                "_32BIT_FLOAT": 32, 
                "_32BIT_SGN_INT": 32, "_16BIT_SGN_INT": 16, "_8BIT_UNSGN_INT": 8
            }[d["VisuCoreWordType"][0]]])),
    ("VisuCoreWordType", "BitsStored", 1, lambda d,g,i: d["__BitsAllocated"]),
    (
        "VisuCoreByteOrder", "HighBit", 1, 
        cached("__HighBit")(
            lambda d,g,i: [
                d["__BitsAllocated"][0]-1 
                if d["VisuCoreByteOrder"][0] == "littleEndian" else 0])),
    (
        "VisuCoreWordType", "PixelRepresentation", 1, 
        cached("__PixelRepresentation")(
            lambda d,g,i: [{
                "_32BIT_FLOAT": 0, # mapped to uint32 
                "_32BIT_SGN_INT": 1, "_16BIT_SGN_INT": 1, "_8BIT_UNSGN_INT": 0
            }[d["VisuCoreWordType"][0]]])),
    (None, "PixelData", 1, get_pixel_data),
    # WARNING SmallestImagePixelValue and LargestImagePixelValue are either US
    # or SS and thus cannot accomodate 32 bits values. Use WindowCenter and
    # WindowWidth instead.
    (
        None, "WindowCenter", 3, 
        lambda d,g,i: [
            0.5*(
                d["VisuCoreDataMin"][g.get_linear_index(i)]
                +d["VisuCoreDataMax"][g.get_linear_index(i)])
        ]),
    (
        None, "WindowWidth", 3, 
        lambda d,g,i: [
            d["VisuCoreDataMax"][g.get_linear_index(i)]
            -d["VisuCoreDataMax"][g.get_linear_index(i)]
        ]),
]

PixelValueTransformation = [ # PS 3.3, C.7.6.16.2.9
    (
        "VisuCoreDataOffs", "RescaleIntercept", 1,
        lambda d,g,i: [d["VisuCoreDataOffs"][g.get_linear_index(i)]]),
    (
        "VisuCoreDataSlope", "RescaleSlope", 1,
        lambda d,g,i: [d["VisuCoreDataSlope"][g.get_linear_index(i)]]),
    (None, "RescaleType", 1, lambda d,g,i: ["US"]),
]

SOPCommon = [ # PS 3.3, C.12.1
    (None, "SOPInstanceUID", 1, lambda d,g,i: [odil.generate_uid()]),
    #SpecificCharacterSet
    (
        None, "InstanceCreationDate", 3, 
        lambda d,g,i: [str(datetime.datetime.now())]),
    (
        None, "InstanceCreationTime", 3, 
        lambda d,g,i: [str(datetime.datetime.now())]),
]

MutliFrameFunctionalGroups = [ # PS 3.3, C.7.6.16
    ("VisuCoreFrameCount", "NumberOfFrames", 1, None),
    (None, "ContentDate", 1, lambda d,g,i: [str(datetime.datetime.now())]),
    (None, "ContentTime", 1, lambda d,g,i: [str(datetime.datetime.now())]),
    (None, "InstanceNumber", 1, lambda d,g,i: [1]),
]

MultiFrameDimension = [ # PS 3.3, C.7.6.17
    (None, "DimensionOrganizationSequence", 1, lambda d,g,i: []),
    (None, "DimensionIndexSequence", 1, lambda d,g,i: []),
]

AcquisitionContext = [ # PS 3.3, C.7.6.14
    (None, "AcquisitionContextSequence", 1, lambda d,g,i: []),
]

PixelMeasures = [ # PS 3.3, C.7.6.16.2.1
    "PixelMeasuresSequence", False,
    [
        (
            None, "PixelSpacing", 3,
            cached("__PixelSpacing")(
                lambda d,g,i: numpy.asarray(d["VisuCoreExtent"], float)
                    / numpy.asarray(d["VisuCoreSize"], float))),
        ("VisuCoreFrameThickness", "SliceThickness", 3, None),
        (
            None, "SpacingBetweenSlices", 3,
            cached("__SpacingBetweenSlices")(
                lambda d,g,i: [
                    numpy.linalg.norm(
                        numpy.subtract(
                            d["VisuCorePosition"][3:6], 
                            d["VisuCorePosition"][0:3]))]
                    if len(d["VisuCorePosition"]) >= 6 else None)),
    ]
]

FrameContent = [ # PS 3.3, C.7.6.16.2.2
    "FrameContentSequence", True,
    [
        (None, "FrameAcquisitionNumber", 3, get_acquisition_number),
        (
            None, "FrameLabel", 3, 
            lambda d, g, i: 
                get_frame_index(g, i)[odil.registry.ContributionDescription])
    ]
]

PlanePosition = [ # PS 3.3, C.7.6.16.2.3
    "PlanePositionSequence", False,
    [
        (
            "VisuCorePosition", "ImagePositionPatient", 1,
            cached("__ImagePositionPatient")(
                lambda d,g,i: numpy.squeeze(
                    numpy.reshape(d["VisuCorePosition"], (-1, 3))))),
    ]
]

PlaneOrientation = [ # PS 3.3, C.7.6.16.2.4
    "PlaneOrientationSequence", False,
    [
        (
            "VisuCoreOrientation", "ImageOrientationPatient", 1,
            cached("__ImageOrientationPatient")(
                lambda d,g,i: numpy.squeeze(
                    numpy.reshape(d["VisuCoreOrientation"], (-1, 9))[:,:6]))),
    ]
]

FrameAnatomy = [ # PS 3.3, C.7.6.16.2.8
    "FrameAnatomySequence", False,
    [
        #WARNING FrameLaterality not handled correctly for the moment
        (None, "FrameLaterality", 1, lambda d,g,i: ["U"]),
        (None, "AnatomicRegionSequence", 1, lambda d,g,i: []),
    ]
]

PixelValueTransformation = [ # PS 3.3, C.7.6.16.2.9
    "PixelValueTransformationSequence", False,
    [
        (
            "VisuCoreDataOffs", "RescaleIntercept", 1,
            lambda d,g,i: [d["VisuCoreDataOffs"][g.get_linear_index(i)]]),
        (
            "VisuCoreDataSlope", "RescaleSlope", 1,
            lambda d,g,i: [d["VisuCoreDataSlope"][g.get_linear_index(i)]]),
        (None, "RescaleType", 1, lambda d,g,i: ["US"]),
    ]
]
