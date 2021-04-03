#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import collections
import logging
import multiprocessing
import os
import traceback

import nibabel
import numpy
import odil

from . import image, io, meta_data
from .series import DefaultSeriesFinder, split_series
from .stacks import get_stacks, sort

from .. import logger, MetaData

def convert_paths(paths, destination, zip, dtype=None):
    """ Convert the DICOM files found in a collection of paths (files, 
        directories, or DICOMDIR) and save the result in the given destination.
        
        :param paths: Collection of paths to scan for DICOM files
        :param destination: Destination directory
        :param zip: whether to zip the NIfTI files
        :param dtype: if not None, force the dtype of the result image
    """
    
    if os.path.isdir(str(destination)) and len(os.listdir(str(destination))) > 0:
        logger.warning("{} is not empty".format(destination))

    dicom_files = io.get_files(paths)
    series = split_series(dicom_files)

    logger.info("{} series found".format(len(series)))
    
    # Look for duplicate output directories. This may happen with data having 
    # the same Series Number and Series Description, as seen on a Siemens 
    # Biograph Vision.
    series_directories = {}
    directories_series = {}
    for finder, series_files in series.items():
        path = series_files[0]
        # NOTE: don't read the whole data set. This should be adjusted when
        # io.get_series_directory changes.
        data_set = odil.Reader.read_file(
            path, halt_condition=lambda x:x>odil.registry.SeriesNumber)[1]
        data_set = meta_data.convert_data_set(
            data_set, data_set.get("SpecificCharacterSet", odil.Value.Strings()))
        directory = io.get_series_directory(data_set)
        
        series_directories[finder] = directory
        directories_series.setdefault(directory, []).append(finder)
    
    # Add suffix to duplicate directories
    for directory, finders in directories_series.items():
        if len(finders) > 1:
            for i, finder in enumerate(finders):
                series_directories[finder] += "_{}".format(1+i)
    
    for finder, series_files in series.items():
        nifti_data = convert_series(series_files, dtype, finder)
        if nifti_data is not None:
            io.write_nifti(
                nifti_data, destination, zip, series_directories[finder])

class SeriesContext(logging.Filter):
    """ Add series context to logger. 
    """
    
    def __init__(self, data_set):
        logging.Filter.__init__(self)
        
        try:
            patient = SeriesContext._get_element(
                data_set, odil.registry.PatientName)
            if not patient:
                patient = SeriesContext._get_element(
                    data_set, odil.registry.PatientID)
            
            study = [
                SeriesContext._get_element(data_set, x)
                for x in [odil.registry.StudyID, odil.registry.StudyDescription]]
            
            series = [
                SeriesContext._get_element(data_set, x)
                for x in [odil.registry.SeriesNumber, odil.registry.SeriesDescription]]
            if series[0] is not None:
                software = SeriesContext._get_element(
                    data_set, odil.registry.SoftwareVersions)
                if software == "ParaVision" and series[0] > 2**16:
                    # Bruker ID based on experiment number and reconstruction 
                    # number is not readable: separate the two values
                    series[0] = "{}:{}".format(
                        *[str(x) for x in divmod(series[0], 2**16)])
                elif software and software.startswith("ParaVision") and series[0] > 10000:
                    # Same processing for Bruker-generated DICOM
                    series[0] = "{}:{}".format(
                        *[str(x) for x in divmod(series[0], 10000)])
                else:
                    series[0] = "{}".format(series[0])
            
            if series[1] is None:
                series[1] = SeriesContext._get_element(
                    data_set, odil.registry.ProtocolName) or ""
            
            elements = []
            if patient:
                elements.append(patient)
            if any(study):
                elements.append("-".join(x for x in study if x))
                if any(series):
                    elements.append("-".join(x for x in series if x))
            
            self.prefix = "{}: ".format(" / ".join(elements))
        except Exception as e:
            logger.debug("Series context configuration error: \"{}\"".format(e))
            self.prefix = ""
        
    def filter(self, record):
        record.msg = "{}{}".format(self.prefix, record.msg)
        return True
    
    @staticmethod
    def _get_element(data_set, tag):
        value = data_set.get(tag)
        if value:
            value = value[0]
            if isinstance(value, bytes):
                value = odil.as_unicode(
                    value, data_set.get(
                        odil.registry.SpecificCharacterSet, odil.Value.Strings()))
        else:
            value = None
        return value

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
    data_sets = [odil.Reader.read_file(x)[1] for x in series_files]

    # Add series context to the logging as soon as we can
    series_context = SeriesContext(data_sets[0])
    logger.addFilter(series_context)
    
    if not isinstance(finder, DefaultSeriesFinder):
        logger.debug("Setting Series Instance UID to {}".format(
            finder.series_instance_uid.decode()))
        for data_set in data_sets:
            data_set[odil.registry.SeriesInstanceUID][0] = finder.series_instance_uid
    
    # Get only data_sets containing correct PixelData field
    data_sets = [x for x in data_sets if odil.registry.PixelData in x]

    if len(data_sets) == 0:
        logger.warning("No image in series")
        nifti_data = None
    else:
        nifti_data = convert_series_data_sets(data_sets, dtype)
    
    # Restore the logging
    logger.removeFilter(series_context)
    
    return nifti_data

def convert_series_data_sets(data_sets, dtype=None):
    """ Convert a list of dicom data sets into Nfiti

        :param data_sets: list of dicom data sets to convert
        :param dtype: if not None, force the dtype of the result image
    """
    
    nifti_data = []

    stacks = get_stacks(data_sets)
    logger.info(
        "Found {} stack{}".format(len(stacks), "s" if len(stacks) > 1 else ""))

    # Set up progress information
    stacks_count = {}
    stacks_converted = {}
    for key, frames in stacks.items():
        series_instance_uid = frames[0][0][odil.registry.SeriesInstanceUID][0]
        stacks_count.setdefault(series_instance_uid, 0)
        stacks_count[series_instance_uid] += 1
        stacks_converted[series_instance_uid] = 0

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
        
        # Update progress information
        series_instance_uid = data_set[odil.registry.SeriesInstanceUID][0]
        if stacks_count[series_instance_uid] > 1:
            stack_info = "{}/{}".format(
                1 + stacks_converted[series_instance_uid],
                stacks_count[series_instance_uid])
        else:
            stack_info = ""
        if stack_info:
            logger.debug("Converting stack {}".format(stack_info))
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
