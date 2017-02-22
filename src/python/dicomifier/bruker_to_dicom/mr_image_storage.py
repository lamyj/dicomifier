#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import itertools
import json
import logging
import os

import dateutil.parser
import numpy
import odil

import patient, study, series, frame_of_reference, equipment, image
from frame_index_generator import FrameIndexGenerator
from convert import convert_element

def convert_elements(
        bruker_data_set, dicom_data_set, conversions,
        frame_index, generator, vr_finder):
    """ Convert elements from the bruker_data_set into dicom_data_set

        :param bruker_data_set: Bruker data set to convert
        :param dicom_data_set: Dicom data set destination
        :param conversions: elements to convert (in case of sequence for example)
        :param frame_index: index in a frame group
        :param generator: object that will manage the frame_index
        :param vr_finder: function to find the VR knowing only the dicom_name
    """

    for bruker_name, dicom_name, type_, getter, setter in conversions:
        convert_element(
            bruker_data_set, dicom_data_set, 
            bruker_name, dicom_name, type_, getter, setter,
            frame_index, generator, vr_finder)
    return dicom_data_set

def mr_image_storage(bruker_data_set, transfer_syntax):
    """ Function to convert specific burker images into dicom

        :param bruker_data_set: bruker data set to convert
        :param transfer_syntax: target transfer syntax
    """

    if int(bruker_data_set.get("VisuCoreDim", [0])[0]) == 3:
        to_2d(bruker_data_set)

    dicom_data_sets = []

    modules = [
        patient.Patient,
        study.GeneralStudy, study.PatientStudy,
        series.GeneralSeries + [(None, "Modality", 1, lambda d,g,i: ["MR"], None)],
        frame_of_reference.FrameOfReference,
        equipment.GeneralEquipment, 
        image.GeneralImage, image.ImagePlane, image.ImagePixel, image.MRImage,
        [
            (
                None, "PixelValueTransformationSequence", 1,
                lambda bruker_data_set, generator, frame_index: [
                    convert_elements(
                        bruker_data_set,odil.DataSet(), image.PixelValueTransformation,
                        frame_index, generator, vr_finder_function
                    )
                ],
                None
            )
        ],
        [
            (
                None, "MRDiffusionSequence", 3,
                lambda bruker_data_set, generator, frame_index: [
                    convert_elements(
                        bruker_data_set,odil.DataSet(), image.MRDiffusion,
                        frame_index, generator, vr_finder_function
                    ) ] 
                    if "FG_DIFFUSION" in [x[1] for x in generator.frame_groups]
                    else None,
                None
            )
        ],
        image.SOPCommon + [(None, "SOPClassUID", 1, lambda d,g,i: [odil.registry.MRImageStorage], None)]
    ]

    vr_finder_object = odil.VRFinder()
    vr_finder_function = lambda tag: vr_finder_object(tag, helper, transfer_syntax)

    helper = odil.DataSet()

    generator = FrameIndexGenerator(bruker_data_set)
    for frame_index in generator:
        dicom_data_set = odil.DataSet()
        dicom_data_set.add("SpecificCharacterSet", ["ISO_IR 192"])

        for bruker_name, dicom_name, type_, getter, setter in itertools.chain(*modules):
            value = convert_element(
                bruker_data_set, dicom_data_set,
                bruker_name, dicom_name, type_, getter, setter,
                frame_index, generator, vr_finder_function)

            for name in ["BitsAllocated", "PixelRepresentation"]:
                if dicom_name == name:
                    helper.add(getattr(odil.registry, name), value)
        dict_files = {}
        path_list = bruker_data_set["reco_files"]
        for path in path_list:
            dict_files[os.path.basename(path)] = open(path).read()
        reco_files_tag = odil.Tag("67890010")
        dicom_data_set.add(reco_files_tag, [json.dumps(dict_files)], odil.VR.OB)

        dicom_data_sets.append(dicom_data_set)

    return dicom_data_sets

def to_2d(data_set):
    """ Convert the Bruker data set from 3D to 2D.
    """
    
    origin = data_set["VisuCorePosition"]
    z = numpy.asarray(data_set["VisuCoreOrientation"][6:9])
    dz = numpy.divide(
        numpy.asarray(data_set["VisuCoreExtent"][2], dtype=float),
        numpy.asarray(data_set["VisuCoreSize"][2], dtype=float))
    
    frame_count = int(data_set.get("VisuCoreFrameCount", [1])[0])
    slice_count = int(data_set["VisuCoreSize"][2])
    
    # Constant fields
    data_set["VisuCoreDim"] = [2]
    data_set["VisuCoreFrameCount"] = [frame_count*slice_count]

    # Frame groups
    groups = data_set.get("VisuFGOrderDesc", [])
    fields = data_set.get("VisuGroupDepVals", [])

    groups = [[slice_count, "FG_SLICE", "", 0, 2]] + [
        [count, name, comment, 2+start, length]
        for count, name, comment, start, length in groups]
    fields = [["VisuCoreOrientation", 0], ["VisuCorePosition", 0] ] + fields

    data_set["VisuFGOrderDescDim"] = [len(groups)]
    data_set["VisuFGOrderDesc"] = groups
    data_set["VisuGroupDepVals"] = fields

    # Sliced fields: subsets of original fields
    sliced_fields = [
        "VisuCoreSize", "VisuCoreDimDesc", "VisuCoreExtent", "VisuCoreUnits"]
    for name in sliced_fields:
        data_set[name] = data_set[name][0:2]

    # Repeated fields: repeat the same value for each slice
    repeated_fields = [
        ("VisuCoreDataMin", (1,)), ("VisuCoreDataMax", (1,)),
        ("VisuCoreDataOffs", (1,)), ("VisuCoreDataSlope", (1,)),
        ("VisuCoreOrientation", (9,))
    ]
    for name, shape in repeated_fields:
        if name not in data_set:
            continue

        value = numpy.reshape(data_set[name], (-1,)+shape)
        data_set[name] = list(
            itertools.chain(*
                [slice_count*x.tolist() for x in value]
            )
        )
    
    # Special case: position, depending on origin, dz and z
    data_set["VisuCorePosition"] = list(itertools.chain(*[
        (origin+i*dz*z).tolist() for i in range(slice_count)
    ]))
