#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import collections
import logging
import os

import nibabel
import numpy
import odil

from . import image, io, meta_data
from .series import DefaultSeriesFinder, split_series
from .stacks import get_stacks, sort

from .. import logger, MetaData

def convert_paths(
        paths, destination, zip, dtype=None, extra_splitters=None, layout=None):
    """ Convert the DICOM files found in a collection of paths (files, 
        directories, or DICOMDIR) and save the result in the given destination.
        
        :param paths: Collection of paths to scan for DICOM files
        :param destination: Destination directory
        :param zip: whether to zip the NIfTI files
        :param dtype: if not None, force the dtype of the result image
        :param extra_splitters: additional splitters to be used when building
            stacks
        :param layout: Override the destination layout
    """
    
    if os.path.isdir(str(destination)) and len(os.listdir(str(destination))) > 0:
        logger.warning("%s is not empty", destination)

    dicom_files = io.get_files(paths)
    series = split_series(dicom_files)

    logger.info("%d series found", len(series))
    
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
        directory = io.get_series_directory(data_set, layout)
        
        series_directories[finder] = directory
        directories_series.setdefault(directory, []).append(finder)
    
    # Add suffix to duplicate directories
    for directory, finders in directories_series.items():
        if len(finders) > 1:
            for i, finder in enumerate(finders):
                series_directories[finder] += f"_{1+i}"
    
    all_nifti_files = []
    for finder, series_files in series.items():
        nifti_data = convert_series(
            series_files, dtype, finder, extra_splitters)
        if nifti_data is not None:
            nifti_files = io.write_nifti(
                nifti_data, destination, zip, series_directories[finder])
            all_nifti_files.extend(nifti_files)
    return all_nifti_files

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
                    series[0] = str(series[0])
            
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
            logger.debug("Series context configuration error: \"%s\"", e)
            self.prefix = ""
        
    def filter(self, record):
        record.msg = f"{self.prefix}{record.msg}"
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

def convert_series(series_files, dtype=None, finder=None, extra_splitters=None):
    """ Return the NIfTI image and meta-data from the files containing a single
        series.
        
        :param dtype: if not None, force the dtype of the result image
        :param finder: if not None, series finder object to overwrite the Series
            Instance UID
        :param extra_splitters: additional splitters to be used when building
            stacks
    """
    
    logger.info(
        "Reading %d DICOM file%s",
            len(series_files), "s" if len(series_files) > 1 else "")
    data_sets = [odil.Reader.read_file(x)[1] for x in series_files]

    # Add series context to the logging as soon as we can
    series_context = SeriesContext(data_sets[0])
    logger.addFilter(series_context)
    
    if not isinstance(finder, DefaultSeriesFinder):
        logger.debug("Setting Series Instance UID to %s",
            finder.series_instance_uid.decode())
        for data_set in data_sets:
            data_set[odil.registry.SeriesInstanceUID][0] = finder.series_instance_uid
    
    # Get only data_sets containing correct PixelData field
    data_sets = [x for x in data_sets if odil.registry.PixelData in x]

    if len(data_sets) == 0:
        logger.warning("No image in series")
        nifti_data = None
    else:
        nifti_data = convert_series_data_sets(data_sets, dtype, extra_splitters)
    
    # Restore the logging
    logger.removeFilter(series_context)
    
    return nifti_data

def convert_series_data_sets(data_sets, dtype=None, extra_splitters=None):
    """ Convert a list of dicom data sets into Nfiti

        :param data_sets: list of dicom data sets to convert
        :param dtype: if not None, force the dtype of the result image
        :param extra_splitters: additional splitters to be used when building
            stacks
    """
    
    nifti_data = []

    stacks = get_stacks(data_sets, extra_splitters)
    logger.info(
        "Found %d stack%s", len(stacks), "s" if len(stacks) > 1 else "")

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
        if len(stacks) > 1:
            stack_info = "{}/{}".format(1 + stack_index, len(stacks))
        else:
            stack_info = ""
        if stack_info:
            logger.debug("Converting stack %s", stack_info)

        sort(key, stack)
        nifti_meta_data = meta_data.get_meta_data(stack, meta_data_cache)
        nifti_data.append((stack, nifti_meta_data))

    # Try to preserve the original stacks order (single-frame)
    nifti_data.sort(
        key=lambda x: numpy.ravel(x[1].get("InstanceNumber", [None])).min())

    for stack, nifti_meta_data in nifti_data:
        skipped = [
            "InstanceNumber",
        ]
        for x in skipped:
            if x in nifti_meta_data:
                del nifti_meta_data[x]

    # Use OrderedDict to keep the relative order
    mergeable = collections.OrderedDict()
    for stack, nifti_meta_data in nifti_data:
        origin, spacing, orientation = image.get_geometry(stack)
        affine = numpy.diag([*spacing, 1])
        affine[:3, :3] = orientation @ affine[:3, :3]
        affine[:3, 3] = origin
        
        shape = image.get_shape(stack)
        
        key = (*shape, *affine.ravel())
        mergeable.setdefault(key, []).append((stack, nifti_meta_data))
    
    merged_stacks = []
    pixel_data_cache = {}
    for image_info, stacks_and_meta_data in mergeable.items():
        shape = (len(stacks_and_meta_data), *image_info[:-16])
        
        dtypes = set()
        rescale = {}
        for volume_index, (stack, _) in enumerate(stacks_and_meta_data):
            for slice_index, (data_set, frame_index) in enumerate(stack):
                dtypes.add(image.get_data_set_dtype(data_set))
        if dtype is None:
            deduced_dtype = image.find_common_dtype(dtypes)
            for stack, _ in stacks_and_meta_data:
                for data_set, frame_index in stack:
                    uid = data_set[odil.registry.SOPInstanceUID][0]
                    if (uid, frame_index) not in rescale:
                        rescale[(uid, frame_index)] = image.get_rescale(
                            data_set, frame_index)
            if any(rescale.values()):
                # Rescaling will create floats
                deduced_dtype = image.find_common_dtype(
                    [numpy.dtype("f4"), deduced_dtype])
        else:
            deduced_dtype = None
        
        nifti_data = numpy.zeros(shape, dtype or deduced_dtype)
        
        for volume_index, (stack, _) in enumerate(stacks_and_meta_data):
            for slice_index, (data_set, frame_index) in enumerate(stack):
                array = image.get_slice_image(
                    data_set, shape[-2:], pixel_data_cache)
                uid = data_set[odil.registry.SOPInstanceUID][0]
                frame_rescale = rescale[uid, frame_index]
                
                is_mosaic = b"MOSAIC" in data_set.get(odil.registry.ImageType, [])
                source = slice(None) if is_mosaic else frame_index
                destination = (
                    volume_index if is_mosaic
                    else (volume_index, slice_index))
                if frame_rescale:
                    slope, intercept = frame_rescale
                    nifti_data[destination] = array[source] * slope + intercept
                else:
                    nifti_data[destination] = array[source]
        
        data_set = stacks_and_meta_data[0][0][0][0]
        is_rgb = (
            data_set[odil.registry.SamplesPerPixel][0] == 3 
            and data_set[odil.registry.PhotometricInterpretation][0] == b"RGB")
        if is_rgb:
            rgb_dtype = numpy.dtype([
                (x, f"{nifti_data.dtype.kind}{nifti_data.dtype.itemsize}")
                for x in "RGB"])
            nifti_data = nifti_data.view(rgb_dtype).copy().squeeze(-1)
        
        # Convert from LPS (used by DICOM) to RAS (used by NIfTI)
        affine = numpy.reshape(image_info[-16:], (4, 4))
        lps_to_ras = numpy.diag([-1, -1, 1, 1])
        affine = lps_to_ras @ affine
        
        # Convert to 3D image if there is only one volume which is not RGB
        if len(stacks_and_meta_data) == 1:
            nifti_data = nifti_data[0, ...]
        
        # Convert to Fortran-order, expected by nibabel
        nifti_image = nibabel.Nifti1Image(numpy.transpose(nifti_data), affine)
        
        nifti_meta_data = merge_meta_data([x[1] for x in stacks_and_meta_data])
        
        merged_stacks.append((nifti_image, nifti_meta_data))
    
    return merged_stacks

def merge_meta_data(meta_data):
    """ Merge the meta-data of geometrically coherent images.
    """

    merged_meta_data = MetaData()
    keys = set()
    for m in meta_data:
        keys.update(m.keys())
    for key in keys:
        value = [m.get(key, None) for m in meta_data]
        if all(x == value[0] for x in value):
            value = value[0]
        merged_meta_data[key] = value

    return merged_meta_data
