#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import itertools
import os

import dateutil.parser
import numpy
import odil

from ..modules import (
    patient, study, series, frame_of_reference, equipment, image, mr)
from .. import convert, FrameIndexGenerator

def mr_image_storage(bruker_data_set, transfer_syntax):
    """ Function to convert specific burker images into dicom

        :param bruker_data_set: bruker data set to convert
        :param transfer_syntax: target transfer syntax
    """

    if int(bruker_data_set.get("VisuCoreDim", [0])[0]) == 3:
        convert.to_2d(bruker_data_set)

    dicom_data_sets = []

    modules = [
        patient.Patient,
        study.GeneralStudy, study.PatientStudy,
        series.GeneralSeries + [
            (None, "Modality", 1, lambda d,g,i: ["MR"], None)],
        frame_of_reference.FrameOfReference,
        equipment.GeneralEquipment, 
        image.GeneralImage, image.ImagePlane, image.ImagePixel, 
        mr.MRImage,
        [
            (
                None, "PixelValueTransformationSequence", 1,
                lambda bruker_data_set, generator, frame_index: [
                    convert.convert_module(
                        bruker_data_set, odil.DataSet(), 
                        # NOTE: mr.MRDiffusion is a functional group, we use 
                        # its module only
                        image.PixelValueTransformation[2],
                        frame_index, generator, vr_finder_function)],
                None
            )
        ],
        [
            (
                None, "MRDiffusionSequence", 3,
                lambda bruker_data_set, generator, frame_index: [
                    convert.convert_module(
                        # NOTE: mr.MRDiffusion is a functional group, we use 
                        # its module only
                        bruker_data_set,odil.DataSet(), mr.MRDiffusion[2],
                        frame_index, generator, vr_finder_function)] 
                    if "FG_DIFFUSION" in [x[1] for x in generator.frame_groups]
                    else None,
                None
            )
        ],
        image.SOPCommon + [
            (
                None, "SOPClassUID", 1, 
                lambda d, g, i: [odil.registry.MRImageStorage], None),
            (
                None, "ContributingEquipmentSequence", 3, 
                lambda d, g, i: [image.get_frame_index(g, i)], None)]
    ]

    vr_finder_object = odil.VRFinder()
    vr_finder_function = lambda tag: vr_finder_object(
        tag, dicom_data_set, transfer_syntax)
    
    generator = FrameIndexGenerator(bruker_data_set)
    for frame_index in generator:
        dicom_data_set = odil.DataSet()
        dicom_data_set.add("SpecificCharacterSet", ["ISO_IR 192"])
        
        for module in modules:
            convert.convert_module(
                bruker_data_set, dicom_data_set, module,
                frame_index, generator, vr_finder_function)
        
        # FIXME: storing the Bruker meta-data in all instances is rather 
        # inefficient. It can amount to over 50 % of the total size of the
        # DICOM file
        # dict_files = {}
        # path_list = bruker_data_set["reco_files"]
        # for path in path_list:
        #     dict_files[os.path.basename(path)] = open(path).read()
        # reco_files_tag = odil.Tag("67890010")
        # dicom_data_set.add(reco_files_tag, [json.dumps(dict_files)], odil.VR.OB)

        dicom_data_sets.append(dicom_data_set)

    return dicom_data_sets
