#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import copy
import json
import os

import odil

from ..modules import (
    patient, study, series, frame_of_reference, equipment, image, mr)
from .. import convert, FrameIndexGenerator
from ... import convert_pixel_data

def enhanced_mr_image_storage(bruker_data_set, transfer_syntax, ideal_b_values):
    """ Convert bruker_data_set into dicom_data_set by using the correct 
        transfer_syntax.
        This function will create one data_set per reconstruction 
        (multiFrame format)

        :param bruker_data_set: Bruker data set in dictionary form
        :param transfer_syntax: Wanted transfer syntax for the conversion
    """

    if int(bruker_data_set.get("VisuCoreDim", [0])[0]) == 3:
        convert.to_2d(bruker_data_set)

    generator = FrameIndexGenerator(bruker_data_set)
    dicom_data_set = odil.DataSet(
        SpecificCharacterSet=["ISO_IR 192"],
        SharedFunctionalGroupsSequence=[odil.DataSet()],
        PerFrameFunctionalGroupsSequence=[
            odil.DataSet() for _ in range(generator.frames_count)])
    
    vr_finder_object = odil.VRFinder()
    vr_finder_function = lambda tag: vr_finder_object(
        tag, dicom_data_set, transfer_syntax)
    
    # Modules factory
    frame_independent_modules = [
        patient.Patient,
        study.GeneralStudy, study.PatientStudy,
        series.GeneralSeries + [(None, "Modality", 1, lambda d,g,i: ["MR"])],
        frame_of_reference.FrameOfReference,
        equipment.GeneralEquipment, equipment.EnhancedGeneralEquipment,
        image.MutliFrameFunctionalGroups,
        image.MultiFrameDimension,
        image.AcquisitionContext,
        mr.EnhancedMRImage,
        mr.MRPulseSequence,
        image.SOPCommon + [(
            None, "SOPClassUID", 1, 
            lambda d,g,i: [odil.registry.EnhancedMRImageStorage])],
    ]
    
    # Run image.ImagePixel without PixelData, which is done later.
    image_pixel = copy.copy(image.ImagePixel)
    image_pixel = [x for x in image_pixel if x[1] != "PixelData"]
    frame_dependent_modules = [
        image_pixel
    ]
    
    # Dummy call to set up the intensity intercept and slope.
    image.get_pixel_data(bruker_data_set, generator, next(iter(generator)))

    groups = [
        image.PixelMeasures,
        image.FrameContent,
        image.PlanePosition,
        image.PlaneOrientation,
        image.FrameAnatomy,
        image.PixelValueTransformation,
        mr.MRImageFrameType,
        mr.MRTimingAndRelatedParameters,
        mr.MREcho,
        mr.MRModifier,
        mr.MRImagingModifier,
        mr.MRFOVGeometry,
        mr.MRAverages
    ]

    if "FG_DIFFUSION" in [x[1] for x in generator.frame_groups]:
        groups.append(mr.MRDiffusionFactory(ideal_b_values))

    for module in frame_independent_modules:
        convert.convert_module(
            bruker_data_set, dicom_data_set, module,
            None, generator, vr_finder_function)
    for i, frame_index in enumerate(generator):
        for module in frame_dependent_modules:
            convert.convert_module(
                bruker_data_set, dicom_data_set, module,
                frame_index, generator, vr_finder_function)
        
        for tag, _, module in groups:
            child = odil.DataSet()
            
            convert.convert_module(
                bruker_data_set, child, module,
                frame_index, generator, vr_finder_function)
            
            dicom_data_set[
                    odil.registry.PerFrameFunctionalGroupsSequence
                ][i].add(tag, [child])
    
    merge_shared_groups(dicom_data_set, groups)
    
    # Make sure that the pixel data has been re-ordered if needed
    image.get_pixel_data(bruker_data_set, generator, next(iter(generator)))
    convert_pixel_data(bruker_data_set, dicom_data_set)
    
    # Add the raw Bruker meta-data, convert paths to Unicode if needed
    paths = [
        x.decode() if hasattr(x, "decode") else x
        for x in bruker_data_set["reco_files"]
    ]
    bruker_files = { 
        os.path.basename(x): open(x, "rb").read().decode("iso-8859-15") 
        for x in paths }
    dicom_data_set.add(
        "EncapsulatedDocument", 
        [odil.Value.BinaryItem(json.dumps(bruker_files).encode())])
    dicom_data_set.add("MIMETypeOfEncapsulatedDocument", ["application/json"])

    return [dicom_data_set]

def merge_shared_groups(dicom_data_set, groups):
    """ Merge the per-frame groups which are identical across all frame and
        store them in the shared-functional groups.
    """

    per_frame = dicom_data_set[odil.registry.PerFrameFunctionalGroupsSequence]
    number_of_frames = dicom_data_set[odil.registry.NumberOfFrames][0]

    shared_sequences = [
        tag for tag, per_frame_only, _ in groups
        if not per_frame_only]

    groups_data_sets = {}
    for i in range(number_of_frames):
        data_set = per_frame[i]
        for tag, elem in data_set.items():
            if tag.get_name() in shared_sequences:
                groups_data_sets.setdefault(tag, []).append(elem[0])

    shared = dicom_data_set[odil.registry.SharedFunctionalGroupsSequence][0]
    for name, data_sets in groups_data_sets.items():
        all_equal = (data_sets.count(data_sets[0]) == len(data_sets))
        if all_equal :
            shared.add(name, [data_sets[0]])
            for data_set in per_frame:
                data_set.remove(name)
