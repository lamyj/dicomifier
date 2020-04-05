#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import itertools
import json
import numpy
import os

import odil

from . import patient, study, series, frame_of_reference, equipment, image
from . import frame_groups as fg
from .mr_image_storage import to_2d
from .frame_index_generator import FrameIndexGenerator
from .convert import convert_element


def enhanced_mr_image_storage(bruker_data_set, transfer_syntax):
    """ Convert bruker_data_set into dicom_data_set by using the correct 
        transfer_syntax.
        This function will create one data_set per reconstruction 
        (multiFrame format)

        :param bruker_data_set: Bruker data set in dictionary form
        :param transfer_syntax: Wanted transfer syntax for the conversion
    """

    if int(bruker_data_set.get("VisuCoreDim", [0])[0]) == 3:
        to_2d(bruker_data_set)

    vr_finder_object = odil.VRFinder()
    vr_finder_function = lambda tag: vr_finder_object(
        tag, helper, transfer_syntax)

    helper = odil.DataSet()
    generator = FrameIndexGenerator(bruker_data_set)
    dicom_data_set = odil.DataSet(
        SpecificCharacterSet=["ISO_IR 192"],
        SharedFunctionalGroupsSequence=[odil.DataSet()],
        PerFrameFunctionalGroupsSequence=[
            odil.DataSet() for _ in range(generator._get_frames_count())])

    # Modules factory
    modules = [
        patient.Patient,
        study.GeneralStudy, study.PatientStudy,
        series.GeneralSeries + [
            (None, "Modality", 1, lambda d,g,i: ["MR"], None)],
        frame_of_reference.FrameOfReference,
        equipment.GeneralEquipment, equipment.EnhancedGeneralEquipment,
        image.MutliFrameFunctionalGroups,
        image.MultiFrameDimension,
        image.AcquisitionContext,
        image.EnhancedMRImage,
        image.MRPulseSequence,
        image.SOPCommon + [(
            None, "SOPClassUID", 1, 
            lambda d,g,i: [odil.registry.EnhancedMRImageStorage], None)],
        image.ImagePixel,
    ]

    framegroups = [
        fg.PixelMeasures,
        fg.FrameContent,
        fg.PlanePosition,
        fg.PlaneOrientation,
        fg.FrameAnatomy,
        fg.PixelValueTransformation,
        fg.MRImageFrameType,
        fg.MRTimingAndRelatedParameters,
        fg.MREcho,
        fg.MRModifier,
        fg.MRImagingModifier,
        fg.MRFOVGeometry,
        fg.MRAverages
    ]

    if "FG_DIFFUSION" in [x[1] for x in generator.frame_groups]:
        framegroups.append(fg.MRDiffusion)

    # parse here classical modules
    for i, frame_index in enumerate(generator):
        generator = itertools.chain(*modules)
        for bruker_name, dicom_name, type_, getter, setter in generator:
            value = convert_element(
                bruker_data_set, dicom_data_set,
                bruker_name, dicom_name, type_, getter, setter,
                frame_index, generator, vr_finder_function
            )
            if dicom_name in ["BitsAllocated", "PixelRepresentation"]:
                helper.add(getattr(odil.registry, dicom_name), value)

        # parse here frame groups
        for frame_g in framegroups :
            fg_modules = frame_g.values()
            d = odil.DataSet()
            generator = itertools.chain(*fg_modules)
            for bruker_name, dicom_name, type_, getter, setter in generator:
                value = convert_element(
                    bruker_data_set, d,
                    bruker_name, dicom_name, type_, getter, setter,
                    frame_index, generator, vr_finder_function
                )
            dicom_data_set[PerFrameFunctionalGroupsSequence][i].add(
                next(iter(frame_g.keys()))[0], [d])
    
    regroup_shared_data(dicom_data_set, framegroups)


    pixel_data_list = []
    for i, frame_index in enumerate(generator):
        pixel_data_list.append(
            image._get_pixel_data(bruker_data_set, generator, frame_index)[0]
        )

    dicom_data_set.add(
        odil.registry.PixelData, [b"".join(pixel_data_list)], 
        vr_finder_function("PixelData"))

    # Add the raw Bruker meta-data, convert paths to Unicode if needed
    paths = [
        x.decode() if hasattr(x, "decode") else x
        for x in bruker_data_set["reco_files"]
    ]
    bruker_files = { os.path.basename(x): open(x).read() for x in paths }
    dicom_data_set.add("EncapsulatedDocument", [json.dumps(bruker_files)])
    dicom_data_set.add("MIMETypeOfEncapsulatedDocument", ["application/json"])

    return [dicom_data_set]

def regroup_shared_data(dicom_data_set, framegroups):
    """ Regroup data from the perFrame functional groups into SharedFunctionalGroups
        using framegroups arg in order to know if the framegroup can be move or no
    """

    per_frame = dicom_data_set[odil.registry.PerFrameFunctionalGroupsSequence]
    shared = dicom_data_set[odil.registry.SharedFunctionalGroupsSequence][0]
    number_of_frames = dicom_data_set[odil.registry.NumberOfFrames][0]

    top_sequences = [
        x[0] for x in [next(iter(y.keys())) for y in framegroups] 
        if x[1] is False]

    seq_data_sets = {}
    for i in range(number_of_frames):
        current_data_set = per_frame[i]
        for tag, elem in current_data_set.items():
            if tag.get_name() in top_sequences:
                seq_data_sets.setdefault(tag.get_name(), {})[i] = current_data_set[tag][0]

    for name, data_sets in seq_data_sets.items():
        # Check whether all values are the same
        all_equal = True
        sample = data_sets[0]
        for i in range(number_of_frames):
            value = data_sets.get(i)
            if value != sample:
                all_equal = False
                break

        if all_equal :
            shared.add(name,[sample])
            # delete tag in the corresponding PerFrame elements
            for data_set in per_frame:
                data_set.remove(name)
        else :
            #Nothing to do
            continue
