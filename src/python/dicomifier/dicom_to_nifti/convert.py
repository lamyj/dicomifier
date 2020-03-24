#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import collections
import itertools
import multiprocessing
import os
import traceback

import nibabel
import numpy
import odil

from . import image, io, meta_data, odil_getter
from .series import DefaultSeriesFinder, split_series
from .stacks import get_stacks

from .. import logger, MetaData

def convert_paths(paths, destination, zip, dtype=None, parallel=1):
    """ Convert the DICOM files found in a collection of paths (files, 
        directories, or DICOMDIR) and save the result in the given destination.
        
        :param paths: Collection of paths to scan for DICOM files
        :param destination: Destination directory
        :param zip: whether to zip the NIfTI files
        :param dtype: if not None, force the dtype of the result image
        :param parallel: number of series to convert in parallel
    """
    
    if os.path.isdir(destination) and len(os.listdir(destination)) > 0:
        logger.warning("{} is not empty".format(destination))

    dicom_files = io.get_files(paths)
    series = split_series(dicom_files)

    logger.info("{} series found".format(len(series)))

    with multiprocessing.Pool(parallel) as pool:
        for finder, series_files in series.items():
            pool.apply_async(
                convert_and_write_series, 
                [series_files, destination, zip, dtype, finder])
        pool.close()
        pool.join()

def convert_and_write_series(
        series_files, destination, zip, dtype=None, finder=None):
    """ Convert the files containing a single series and save the result in the
        given destination.
    
        :param series_files: Collection of paths to scan for DICOM files
        :param destination: Destination directory
        :param zip: whether to zip the NIfTI files
        :param dtype: if not None, force the dtype of the result image
        :param finder: if not None, series finder object to overwrite the Series
            Instance UID
    """
    
    try:
        nifti_data = convert_series(series_files, dtype, finder)
        if nifti_data is None:
            logger.info("No image in the series")
            return
        io.write_nifti(nifti_data, destination, zip)
    except Exception as e:
        traceback.print_exc()

def convert_series(series_files, dtype=None, finder=None):
    """ Return the NIfTI image and meta-data from the files containing a single
        series.
        
        :param dtype: if not None, force the dtype of the result image
        :param finder: if not None, series finder object to overwrite the Series
            Instance UID
    """
    
    logger.info(
        "Reading {} DICOM file{}".format(
            len(series_files), "s" if len(series_files) > 1 else ""))
    data_sets = []
    for series_file in series_files:
        with odil.open(series_file) as fd:
            data_sets.append(odil.Reader.read_file(fd)[1])

    if not isinstance(finder, DefaultSeriesFinder):
        logger.debug("Setting Series Instance UID to {}".format(
            finder.series_instance_uid))
        for data_set in data_sets:
            data_set.remove(odil.registry.SeriesInstanceUID)
            data_set.add(
                odil.registry.SeriesInstanceUID, [finder.series_instance_uid])
    
    # Get only data_sets containing correct PixelData field
    data_sets = [x for x in data_sets if "PixelData" in x]

    if len(data_sets) == 0:
        logger.warning("No Pixel Data found")
        return None
    nifti_data = convert_series_data_sets(data_sets, dtype)

    return nifti_data

def convert_series_data_sets(dicom_data_sets, dtype=None):
    """ Convert a list of dicom data sets into Nfiti

        :param dicom_data_sets: list of dicom data sets to convert
        :param dtype: if not None, force the dtype of the result image
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
        value = odil_getter.getter(data_set, tag)
        if value:
            value = value[0]
            if isinstance(value, bytes) and data_set.has(odil.registry.SpecificCharacterSet):
                value = odil.as_unicode(
                    value, data_set.as_string(odil.registry.SpecificCharacterSet))
        else:
            value = None
        return value

    meta_data_cache = {}
    pixel_data_cache = {}
    # Try to preserve the original stacks order (multi-frame)
    stacks = sorted(
        stacks.items(),
        # WARNING: in Python3, None <= None is an error. Use -1 instead since
        # the frame index will always be positive
        key=lambda item: numpy.min([x[1] if x[1] is not None else -1 for x in item[1]])
    )
    for stack_index, (key, stack) in enumerate(stacks):
        data_set = stack[0][0]

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
                series[0] = "{}:{}".format(*[str(x) for x in divmod(series[0], 2**16)])
            else:
                series[0] = "{}".format(series[0])

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
                    "-".join(str(x) for x in study), 
                    "-".join(str(x) for x in series)))
        if stack_info:
            logger.debug(
                u"Converting {} / {}{}".format(
                    "-".join(str(x) for x in study), 
                    "-".join(str(x) for x in series), stack_info))
        stacks_converted[series_instance_uid] += 1

        sort(key, stack)
        nifti_img = image.get_image(stack, dtype, pixel_data_cache)
        nifti_meta_data = meta_data.get_meta_data(stack, meta_data_cache)
        nifti_data.append((nifti_img, nifti_meta_data))

    # Try to preserve the original stacks order (single-frame)
    nifti_data.sort(
        key=lambda x: numpy.ravel(x[1].get("InstanceNumber", [None])).min())

    for nifti_img, nifti_meta_data in nifti_data:
        skipped = [
            "InstanceNumber",
        ]
        for x in skipped:
            if x in nifti_meta_data:
                del nifti_meta_data[x]

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

def sort(key, stack):
    """ Sort the elements of a stack according to the items present in the 
        stack key.
        
        :param key: key of the stack
        :param stack: collection of data set and an associated frame number for
            multi-frame datasets
    """

    if len(stack) == 1:
        # WARNING : Can cause some problem when opening .nii file with Slicer
        logger.debug("Only one frame in the current stack")
        return
    
    ordering = None
    for (top_seq, sub_seq, tag), value in key:
        if tag == odil.registry.DimensionIndexValues:
            # sort by In-Stack Position
            in_stack_position = []
            for data_set, index in stack:
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
            keydict = dict(zip(stack, sorted_in_stack))
            ordering = keydict.get
            break
        if tag == odil.registry.ImageOrientationPatient:
            data_set, frame_idx = stack[0]
            if odil_getter.get_position(data_set, frame_idx) is not None:
                normal = numpy.cross(value[:3], value[3:])
                ordering = lambda x: numpy.dot(
                    odil_getter.get_position(x[0], x[1]), normal)
                break
            else:
                logger.warning(
                    "Orientation found but no position available to sort frames")
    
    if ordering is not None:
        stack.sort(key=ordering)
    else:
        available_tags = [x[0][2] for x in key if len(x) > 1]
        logger.warning(
            "Cannot sort frames for the moment, available tags : {}".format(
                [x.get_name() for x in available_tags]))

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
