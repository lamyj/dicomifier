#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import itertools
import logging

import dateutil.parser
import numpy
import odil

import patient, study, series, frame_of_reference, equipment, image
from frame_index_generator import FrameIndexGenerator
from convert import convert_element

def convert_elements(
        bruker_data_set, dicom_data_set, conversions,
        frame_index, generator, vr_finder):
    for bruker_name, dicom_name, type_, getter, setter in conversions:
        convert_element(
            bruker_data_set, dicom_data_set, 
            bruker_name, dicom_name, type_, getter, setter,
            frame_index, generator, vr_finder)
    return dicom_data_set

def mr_image_storage(bruker_data_set, transfer_syntax):
    if int(bruker_data_set.get("VisuCoreDim", ["unknown"])[0]) == 3:
        to_2d(bruker_data_set)
    
    dicom_data_sets = []
    
    modules = [
        patient.Patient,
        study.GeneralStudy, study.PatientStudy,
        series.GeneralSeries, 
        frame_of_reference.FrameOfReference,
        equipment.GeneralEquipment, 
        image.GeneralImage, image.ImagePlane, image.ImagePixel, image.MRImage, 
        [
            (
                None, "PixelValueTransformationSequence", 1,
                lambda bruker_data_set, generator, frame_index: [
                    convert_elements(
                        bruker_data_set, {}, image.PixelValueTransformation,
                        frame_index, generator, vr_finder_function
                    )
                ],
                None
            )
        ],
        image.SOPCommon
    ]
    
    vr_finder_object = odil.VRFinder()
    vr_finder_function = lambda tag: vr_finder_object(tag, helper, transfer_syntax)
    
    helper = odil.DataSet()
    
    generator = FrameIndexGenerator(bruker_data_set)
    for frame_index in generator:
        dicom_data_set = {}
        
        for bruker_name, dicom_name, type_, getter, setter in itertools.chain(*modules):
            value = convert_element(
                bruker_data_set, dicom_data_set, 
                bruker_name, dicom_name, type_, getter, setter,
                frame_index, generator, vr_finder_function)
            
            for name in ["BitsAllocated", "PixelRepresentation"]:
                if dicom_name == name:
                    helper.add(getattr(odil.registry, name), value)
        
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
    
    slice_count = data_set["VisuCoreSize"][2]
    
    # 1. Constant fields
    data_set["VisuCoreDim"] = [2]
    data_set["VisuCoreFrameCount"] = [slice_count]
    data_set["VisuFGOrderDescDim"] = [1]
    data_set["VisuFGOrderDesc"] = [[slice_count, "FG_SLICE", "", 0, 2]]
    data_set["VisuGroupDepVals"] = [
        ["VisuCoreOrientation", 0], 
        ["VisuCorePosition", 0] ]

    # 2. Sliced fields: subsets of original fields
    sliced_fields = [
        "VisuCoreSize", "VisuCoreDimDesc", "VisuCoreExtent", "VisuCoreUnits"]
    for name in sliced_fields:
        data_set[name] = data_set[name][0:2]

    # 3. Repeated fields: repeat the same value for each slice
    repeated_fields = [ 
        "VisuCoreOrientation", "VisuCoreDataMin", "VisuCoreDataMax",
        "VisuCoreDataOffs", "VisuCoreDataSlope"
    ]
    for name in repeated_fields:
        value = data_set.get(name)
        if value is not None:
            data_set[name] = list(itertools.chain(*(slice_count*[value])))
    
    # 4. Special case: position, depending on origin, dz and z
    data_set["VisuCorePosition"] = list(itertools.chain(*[
        (origin+i*dz*z).tolist() for i in range(slice_count)
    ]))
