#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import collections
import itertools

import nibabel
import numpy
import odil

from . import meta_data
from . import image
from . import odil_getter

from .. import logger, MetaData


def convert(dicom_data_sets, dtype):
    """ Convert a list of dicom data sets into Nfiti

        :param dicom_data_sets: list of dicom data sets to convert
        :param dtype: type to use when converting images
    """

    nifti_data = []

    stacks = get_stacks(dicom_data_sets)
    logger.info(
        "Found {} stack{}".format(len(stacks), "s" if len(stacks) > 1 else ""))

    # Set up progress information
    stacks_count = {}
    stacks_converted = {}
    for key, data_sets_frame_idx in stacks.items():
        series_instance_uid = data_sets_frame_idx[0][0].as_string("SeriesInstanceUID")[0]
        stacks_count.setdefault(series_instance_uid, 0)
        stacks_count[series_instance_uid] += 1
        stacks_converted[series_instance_uid] = 0

    def get_element(data_set, tag):
        value = odil_getter._default_getter(data_set, tag)
        return value[0] if (value is not None and len(value)>0) else None

    meta_data_cache = {}
    pixel_data_cache = {}
    # Try to preserve the original stacks order (multi-frame)
    stacks = sorted(
        stacks.items(),
        # WARNING: in Python3, None <= None is an error. Use -1 instead since
        # the frame index will always be positive
        key=lambda item: numpy.min([x[1] if x[1] is not None else -1 for x in item[1]])
    )
    for stack_index, (keys, data_sets_frame_idx) in enumerate(stacks):
        data_set = data_sets_frame_idx[0][0]

        study = [
            get_element(data_set, odil.registry.StudyID),
            get_element(data_set, odil.registry.StudyDescription)]
        
        series = [
            get_element(data_set, odil.registry.SeriesNumber),
            get_element(data_set, odil.registry.SeriesDescription)]
        if series[0] is not None:
            software = get_element(data_set, odil.registry.SoftwareVersions)
            if (software and software == "ParaVision" and series[0] > 2**16):
                # Bruker ID based on experiment number and reconstruction number is
                # not readable: separate the two values
                series[0] = u"{}:{}".format(*[str(x) for x in divmod(series[0], 2**16)])
            else:
                series[0] = u"{}".format(series[0])

        series_instance_uid = data_set.as_string("SeriesInstanceUID")[0]

        if stacks_count[series_instance_uid] > 1:
            stack_info = " (stack {}/{})".format(
                1 + stacks_converted[series_instance_uid],
                stacks_count[series_instance_uid])
        else:
            stack_info = ""
        if stack_index == 0:
            logger.info(
                u"Converting {} / {}".format(
                    "-".join(study), "-".join(series)))
        if stack_info:
            logger.debug(
                u"Converting {} / {}{}".format(
                    "-".join(study), "-".join(series), stack_info))
        stacks_converted[series_instance_uid] += 1

        sort(keys, data_sets_frame_idx)
        nifti_img = image.get_image(
            data_sets_frame_idx, dtype, pixel_data_cache)
        nifti_meta_data = meta_data.get_meta_data(
            data_sets_frame_idx, meta_data_cache)
        nifti_data.append((nifti_img, nifti_meta_data))

    # Try to preserve the original stacks order (single-frame)
    nifti_data.sort(
        key=lambda x: numpy.ravel(x[1].get("InstanceNumber", [None])).min())

    for nifti_img, nifti_meta_data in nifti_data:
        meta_data.cleanup(nifti_meta_data)

    series = {}
    for nitfi_img, nifti_meta_data in nifti_data:
        series.setdefault(nifti_meta_data["SeriesInstanceUID"][0], []).append(
            (nitfi_img, nifti_meta_data))

    merged_stacks = []
    for stacks in series.values():
        # Use OrderedDict to keep the relative order
        mergeable = collections.OrderedDict()
        for nifti_img, nifti_meta_data in stacks:
            geometry = nifti_img.shape + \
                tuple(nifti_img.affine.ravel().tolist())
            dt = nifti_img.dataobj.dtype
            mergeable.setdefault((geometry, dt), []).append(
                (nifti_img, nifti_meta_data))

        for _, stack in mergeable.items():
            if len(stack) > 1:
                logger.info(
                    "Merging {} stack{}".format(
                        len(stack), "s" if len(stack) > 1 else ""))
                merged = merge_images_and_meta_data(stack)
                merged_stacks.append(merged)
            else:
                merged_stacks.append(stack[0])
    return merged_stacks


def get_stacks(data_sets):
    """ Return a dict containing, a tuple of key = ((tag,...),value) 
        associated with the corresponding datasets
        :param data_sets: List of data_set for which we will get the stacks

        :return stacks = {
        (keys,keys,keys...) : [dataset_i, dataset_a, dataset_c, ...],
        (keys,keys,...)     : [dataset_k, dataset_z, dataset_b, ...] 
        ...
        } 
    """

    splitters = _get_splitters(data_sets)
    stacks = {}
    for data_set in data_sets:
        # Single Frame
        if not data_set.has(odil.registry.SharedFunctionalGroupsSequence):
            key = []
            for tags, getter in splitters:
                if len(tags) == 1:
                    tag = str(tags[0])
                    value = getter(data_set, tag)
                    if value is not None:
                        key.append(((None, None, tag), value))
                else:
                    continue
                    # Nothing to do (we can only use direct splitters for
                    # single frame dicom files)
            stacks.setdefault(tuple(key), []).append((data_set, None))
        # Multiple frame
        else:
            number_of_frames = data_set.as_int("NumberOfFrames")[0]
            shared = data_set.as_data_set(
                odil.registry.SharedFunctionalGroupsSequence)[0]
            in_stack_position_idx = odil_getter.get_in_stack_position_index(
                data_set)
            for frame_idx in range(number_of_frames):
                key = []
                top_seqs = []
                top_seqs.append(
                    (data_set.as_data_set(
                        odil.registry.PerFrameFunctionalGroupsSequence)[frame_idx],
                     str(odil.registry.PerFrameFunctionalGroupsSequence))
                )
                top_seqs.append(
                    (shared,
                     str(odil.registry.SharedFunctionalGroupsSequence))
                )
                for top_seq, top_seq_tag in top_seqs:  # Only use to make difference between Shared & Per-Frame
                                                       # We need this if multiple orientations
                                                       # available for example
                    for tags, getter in splitters:
                        if len(tags) == 1 and top_seq_tag == str(odil.registry.SharedFunctionalGroupsSequence):
                            # "and" case used to append element on key only once
                            tag = str(tags[0])
                            value = getter(data_set, tag)
                            if value is not None:
                                key.append(((None, None, tag), value))
                        elif len(tags) == 2:
                            seq, tag = tags
                            seq = str(seq)
                            if top_seq.has(seq):
                                data_set_seq = top_seq.as_data_set(seq)[0]
                                tag = str(tag)
                                if tag == "None":
                                    value = getter(top_seq, seq)
                                elif tag == str(odil.registry.DimensionIndexValues):
                                    # need to give idx of InStackPosition here
                                    value = getter(
                                        data_set_seq, tag, in_stack_position_idx)
                                else:
                                    value = getter(data_set_seq, tag)
                                if value is not None:
                                    key.append(
                                        ((top_seq_tag, seq, tag), value))
                stacks.setdefault(tuple(key), []).append((data_set, frame_idx))
    
    # Simplify keys: remove those that have the same value for all stacks
    keys = numpy.asarray(list(stacks.keys())) # stack_id, tag, value
    to_keep = []
    for index in range(keys.shape[1]):
        unique_values = set(keys[:,index,:][:,1])
        is_orientation = (keys[:,index,:][0][0][2] == str(odil.registry.ImageOrientationPatient))
        if len(unique_values) > 1 or is_orientation:
            # Key must be kept
            to_keep.append(index)
    stacks = {
        tuple(v for (i, v) in enumerate(stack_key) if i in to_keep): stack_value
        for stack_key, stack_value in stacks.items()
    }
    
    return stacks


def sort(keys, data_sets_frame_idx):
    """ Sort current stack frames/datasets depending on their common keys
        :param keys: Keys shared by all element of the stack
        :param data_sets_frame_idx: List containing the data sets of the frame 
                                    with the corresponding frame when it's a multiframe data set
    """

    number_of_frames = len(data_sets_frame_idx)
    if number_of_frames == 1:
        # WARNING : Can cause some problem when opening .nii file with Slicer
        logger.debug("Only one frame in the current stack")
        return
    else:
        for key in keys:
            for tags, value in keys:
                top_seq, sub_seq, tag = tags
                if str(odil.registry.DimensionIndexValues) == tag:
                    # sort by In-Stack Position
                    in_stack_position = []
                    for data_set, index in data_sets_frame_idx:
                        in_stack_position_idx = odil_getter.get_in_stack_position_index(
                            data_set)
                        frame = data_set.as_data_set(
                            odil.registry.PerFrameFunctionalGroupsSequence)[index]
                        frame_content_seq = frame.as_data_set(
                            odil.registry.FrameContentSequence)[0]
                        in_stack_position.append(frame_content_seq.as_int(
                            odil.registry.DimensionIndexValues)[in_stack_position_idx])
                    sorted_in_stack = sorted(
                        range(len(in_stack_position)), key=lambda k: in_stack_position[k])
                    keydict = dict(zip(data_sets_frame_idx, sorted_in_stack))
                    data_sets_frame_idx.sort(key = keydict.get)
                    return
                if str(odil.registry.ImageOrientationPatient) == tag:
                    if sort_position(data_sets_frame_idx, value) == True:
                        return
        available_tags = [x[0][2] for x in keys if len(x) > 1]
        logger.warning(
            "Cannot sort frames for the moment, available tags : {}".format(
                [odil.Tag(x).get_name() for x in available_tags]))


def sort_position(data_sets_frame_idx, orientation):
    """ Sort frames/datasets of the current stack depending on their orientation
        :param data_sets_frame_idx: List containing the data sets of the frame 
                                    with the corresponding frame when it's a multiframe data set
        :param orientation: Orientation shared by all the element of the stack
    """

    data_set, frame_idx = data_sets_frame_idx[0]
    if odil_getter._get_position(data_set, frame_idx) is not None:
        normal = numpy.cross(*numpy.reshape(orientation, (2, -1)))
        data_sets_frame_idx.sort(
            key=lambda x: numpy.dot(
                odil_getter._get_position(x[0], x[1]), normal))
        return True
    else:
        logger.warning(
            "Orientation found but no position available to sort frames")
        return False


def merge_images_and_meta_data(images_and_meta_data):
    """ Merge the pixel and meta-data of geometrically coherent images.
    """

    images = [x[0] for x in images_and_meta_data]

    pixel_data = numpy.ndarray(
        images[0].shape + (len(images),),
        dtype=images[0].dataobj.dtype, order="F")
    for i, image in enumerate(images):
        pixel_data[...,i] = image.dataobj

    merged_image = nibabel.Nifti1Image(pixel_data, images[0].affine)
    
    meta_data = [x[1] for x in images_and_meta_data]
    merged_meta_data = MetaData()
    keys = set()
    for m in meta_data:
        keys.update(m.keys())
    for key in keys:
        value = [m.get(key, None) for m in meta_data]
        if all(x == value[0] for x in value):
            value = value[0]
        merged_meta_data[key] = value

    return merged_image, merged_meta_data


def _get_splitters(data_sets):
    """ Return a list of splitters (tag and getter) depending on the SOPClassUID
        of each dataset

        :param data_sets: Data sets of the current stack 
    """

    splitters = {
        "ALL": [
            # Single Frame generic tags
            ((odil.registry.SeriesInstanceUID,), odil_getter._default_getter),
            ((odil.registry.ImageType,), odil_getter._default_getter),
            ((odil.registry.ImageOrientationPatient,),
             odil_getter.OrientationGetter()),
            ((odil.registry.SpacingBetweenSlices,), odil_getter._default_getter),
            ((odil.registry.Rows,), odil_getter._default_getter), 
            ((odil.registry.Columns,), odil_getter._default_getter), 
            ((odil.registry.PhotometricInterpretation,), odil_getter._default_getter), 
            # Multiframe generic tags
            ((odil.registry.FrameContentSequence, odil.registry.DimensionIndexValues),
             odil_getter.get_dimension_index_seq),
            ((odil.registry.PlaneOrientationSequence, odil.registry.ImageOrientationPatient),
             odil_getter.OrientationGetter()),
            ((odil.registry.PixelMeasuresSequence, odil.registry.SpacingBetweenSlices),
             odil_getter._default_getter),
            ((odil.registry.FrameContentSequence, odil.registry.FrameAcquisitionNumber),
             odil_getter._default_getter),
            ((odil.registry.FrameContentSequence, odil.registry.FrameLabel),
             odil_getter._default_getter)
        ],
        odil.registry.MRImageStorage: [
            ((odil.registry.AcquisitionNumber,), odil_getter._default_getter),
            ((odil.registry.RepetitionTime,), odil_getter._default_getter),
            ((odil.registry.EchoTime,), odil_getter._default_getter),
            ((odil.registry.InversionTime,), odil_getter._default_getter),
            ((odil.registry.EchoNumbers,), odil_getter._default_getter),
            ((odil.registry.MRDiffusionSequence,), odil_getter._diffusion_getter),
            # Philips Ingenia stores these fields at top-level
            ((odil.registry.DiffusionGradientOrientation,),
             odil_getter._default_getter),
            ((odil.registry.DiffusionBValue,), odil_getter._default_getter),
            ((odil.registry.TriggerTime,), odil_getter._default_getter),
            (
                (odil.registry.ContributingEquipmentSequence,), 
                odil_getter._frame_group_index_getter)
        ],
        odil.registry.EnhancedMRImageStorage: [
            ((odil.registry.MRTimingAndRelatedParametersSequence, odil.registry.RepetitionTime),
             odil_getter._default_getter),
            ((odil.registry.MREchoSequence, odil.registry.EffectiveEchoTime),
             odil_getter._default_getter),
            ((odil.registry.MRModifierSequence, odil.registry.InversionTimes),
             odil_getter._default_getter),
            ((odil.registry.MRImageFrameTypeSequence, odil.registry.FrameType),
             odil_getter._default_getter),
            ((odil.registry.MRMetaboliteMapSequence, odil.registry.MetaboliteMapDescription),
             odil_getter._default_getter),
            ((odil.registry.MRDiffusionSequence, None),
             odil_getter._diffusion_getter),
        ],
        odil.registry.EnhancedPETImageStorage: [
            ((odil.registry.PETFrameTypeSequence, odil.registry.FrameType),
             odil_getter._default_getter)
        ],
        odil.registry.EnhancedCTImageStorage: [
            ((odil.registry.CTImageFrameTypeSequence, odil.registry.FrameType),
             odil_getter._default_getter)
        ]
    }

    sop_classes = set(x.as_string("SOPClassUID")[0] for x in data_sets)

    return list(itertools.chain(
        splitters["ALL"],
        *[splitters.get(x, []) for x in sop_classes]
    ))
