#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import math

import nibabel
import numpy
import odil

from .. import logger
from . import siemens

def get_image(stack, dtype, cache=None):
    """ Get the NIfTI image of the given stack
        
        :param stack: collection of data set and an associated frame number for
            multi-frame datasets
        :param dtype: if not None, force the dtype of the result image
        :param cache: optional cache of linear pixel data for multi-frame data 
            sets
    """
    
    if cache is None:
        cache = {}

    # Cache the linear pixel data since this is a time-consuming operation for
    # large data sets and needs to be repeated for multi-frame data sets.
    for data_set, _ in stack:
        if data_set[odil.registry.SOPInstanceUID][0] not in cache:
            linear_array = get_linear_pixel_data(data_set)
            cache[data_set[odil.registry.SOPInstanceUID][0]] = linear_array
    
    pixel_data_list = [
        get_shaped_pixel_data(
            data_set, frame_index, 
            cache[data_set[odil.registry.SOPInstanceUID][0]])
        for data_set, frame_index in stack]

    if dtype is None:
        if any(numpy.dtype(x.dtype).kind == "f" for x in pixel_data_list):
            dtype = numpy.float32
        else:
            # WARNING: Assume all data sets have the same type
            dtype = pixel_data_list[0].dtype
        logger.debug("dtype set to: {}".format(dtype))

    pixel_data = numpy.ndarray(
        (len(stack),) + pixel_data_list[0].shape, dtype=dtype)
    for i, data in enumerate(pixel_data_list):
        pixel_data[i] = data

    scanner_transform = numpy.identity(4)

    origin, spacing, direction = get_geometry(stack)

    data_set = stack[0][0]
    image_type = data_set.get(odil.registry.ImageType, [])
    if len(stack) == 1 and b"MOSAIC" in image_type and "00291010" in data_set:
        item = data_set[odil.Tag(0x0029, 0x1010)][0]
        siemens_data = siemens.parse_csa(item.get_memory_view().tobytes())

        number_of_tiles = siemens_data["NumberOfImagesInMosaic"][0]
        tiles_per_line = int(math.ceil(math.sqrt(number_of_tiles)))

        rows = round(pixel_data.shape[-2] / tiles_per_line)
        columns = round(pixel_data.shape[-1] / tiles_per_line)
        
        # Re-arrange array so that tiles are contiguous
        pixel_data = pixel_data.reshape(
            tiles_per_line, rows, tiles_per_line, columns)
        pixel_data = pixel_data.transpose((0, 2, 1, 3))
        pixel_data = pixel_data.reshape(tiles_per_line**2, rows, columns)
        
        # Remove the black tiles. WARNING: assume those are /always/ at the end 
        # of the mosaic
        pixel_data = pixel_data[:number_of_tiles]

        # Get the origin of the tiles (i.e. origin of the first tile), cf.
        # http://nipy.org/nibabel/dicom/dicom_mosaic.html
        # WARNING: need to invert their rows and columns
        R = direction[:, :2]
        Q = R * spacing[:2]
        mosaic_shape = numpy.asarray(pixel_data.shape[-2:])
        real_shape = numpy.asarray([rows, columns])
        origin = origin + \
            numpy.dot(Q, (mosaic_shape[::-1] - real_shape[::-1]) / 2.)

        direction[:, 2] = siemens_data["SliceNormalVector"]

    samples = data_set[odil.registry.SamplesPerPixel][0]
    is_rgb = (
        samples == 3 
        and data_set[odil.registry.PhotometricInterpretation][0] == b"RGB")
    
    if samples == 1:
        lps_to_ras = [
            [-1,  0, 0],
            [0, -1, 0],
            [0,  0, 1]
        ]

        scanner_transform[:3, :3] = numpy.dot(lps_to_ras, direction)
        scanner_transform[:3, :3] = numpy.dot(
            scanner_transform[:3, :3], numpy.diag(spacing))
        scanner_transform[:3, 3] = numpy.dot(lps_to_ras, origin)
    elif is_rgb:
        if dtype != numpy.uint8:
            logger.warning(
                "Invalid dtype {} for RGB, re-sampling".format(dtype))
            min = pixel_data.min((0,1,2))
            max = pixel_data.max((0,1,2))
            pixel_data = ((pixel_data-min)/(max-min)*255).round().astype(numpy.uint8)
        pixel_data = pixel_data.view(
                nibabel.nifti1.data_type_codes.dtype["RGB"]
            ).reshape(pixel_data.shape[:3])

    # WARNING: ArrayWriter.to_fileobj is Fortran-order by default whereas numpy
    # is C-order by default
    return nibabel.Nifti1Image(pixel_data.T, scanner_transform)

def get_linear_pixel_data(data_set):
    """Return a linear numpy array containing the pixel data."""
    
    byte_order = ">" if data_set[odil.registry.HighBit][0] == 0 else "<"
    is_unsigned = (data_set.get(odil.registry.PixelRepresentation, [0])[0] == 0)

    bits_allocated = data_set[odil.registry.BitsAllocated][0]
    if bits_allocated % 8 != 0:
        raise NotImplementedError("Cannot handle non-byte types")

    dtype = numpy.dtype(
        "{}{}{}".format(
            byte_order, "u" if is_unsigned else "i", int(bits_allocated / 8)))

    pixel_data = data_set.as_binary(odil.registry.PixelData)[0]
    view = pixel_data.get_memory_view()
    linear_array = numpy.frombuffer(view.tobytes(), byte_order + dtype.char)
    
    # Mask the data using Bits Stored, cf. PS 3.5, 8.1.1
    bits_stored = data_set[odil.registry.BitsStored][0]
    linear_array = numpy.bitwise_and(
        linear_array, 2**bits_stored - 1, dtype=linear_array.dtype)
    
    return linear_array

def get_shaped_pixel_data(data_set, frame_index, linear_pixel_data):
    """ Return the pixel data located in a dataset (and possibly one of its 
        frame) shaped according to numer of rows, columns and frames.
    """
    
    rows = data_set[odil.registry.Rows][0]
    cols = data_set[odil.registry.Columns][0]
    
    def reshape(array, shape):
        try:
            return array.reshape(shape)
        except ValueError:
            return array[:-1].reshape(shape)

    samples_per_pixel = data_set[odil.registry.SamplesPerPixel][0]
    if samples_per_pixel == 1:
        if (
                odil.registry.PerFrameFunctionalGroupsSequence in data_set
                and odil.registry.NumberOfFrames in data_set):
            number_of_frames = data_set[odil.registry.NumberOfFrames][0]
            pixel_data = reshape(linear_pixel_data, (number_of_frames, rows, cols))
            pixel_data = pixel_data[frame_index, :]
        else:
            pixel_data = reshape(linear_pixel_data, (rows, cols))
    else:
        pixel_data = reshape(linear_pixel_data, (rows, cols, samples_per_pixel))

    # Rescale: look for Pixel Value Transformation sequence then Rescale Slope
    # and Rescale Intercept
    rescale = data_set
    if odil.registry.SharedFunctionalGroupsSequence in data_set:
        rescale = data_set[odil.registry.SharedFunctionalGroupsSequence][0]
    if odil.registry.PixelValueTransformationSequence in rescale:
        rescale = rescale[odil.registry.PixelValueTransformationSequence][0]
    
    slope = rescale.get(odil.registry.RescaleSlope, [None])[0]
    intercept = rescale.get(odil.registry.RescaleIntercept, [None])[0]
    if None not in [slope, intercept] and not numpy.allclose([slope, intercept], [1, 0]):
        pixel_data = pixel_data * numpy.float32(slope) + numpy.float32(intercept)

    return pixel_data

def find_element(data_set, frame_index, tag, sequence):
    """ Return a data set, potentially nested inside the given data set and
        sequence, which contain the given tag.
    """
    
    container = None
    
    if odil.registry.SharedFunctionalGroupsSequence in data_set:
        shared = data_set[odil.registry.SharedFunctionalGroupsSequence][0]
        frame = data_set[odil.registry.PerFrameFunctionalGroupsSequence][frame_index]
        if sequence in frame:
            container = frame[sequence][0]
        elif sequence in shared:
            container = shared[sequence][0]
    else:
        container = data_set
    
    if container is not None and tag not in container:
        container = None
    
    return container

def get_origin(stack):
    """Compute the origin of the stack."""
    
    data_set, index = stack[0]
    
    # Look for a (sub-)data set containing the plane position
    container = find_element(
        data_set, index, 
        odil.registry.ImagePositionPatient, odil.registry.PlanePositionSequence)

    origin = None
    if container is not None:
        origin = tuple(container[odil.registry.ImagePositionPatient])
    
    return origin

def get_orientation(stack):
    """Compute the orientation of the stack."""
    
    data_set, index = stack[0]
    
    # Look for a (sub-)data set containing the plane orientation
    container = find_element(
        data_set, index, 
        odil.registry.ImageOrientationPatient, 
        odil.registry.PlaneOrientationSequence)

    orientation = None
    if container is not None:
        orientation = container[odil.registry.ImageOrientationPatient]
        orientation = numpy.transpose(numpy.array([
            orientation[:3],
            orientation[3:],
            numpy.cross(orientation[:3], orientation[3:])]))
    
    return orientation

def get_spacing(stack):
    """Compute the spacing of the stack."""
    
    data_set, index = stack[0]
    
    # Look for a (sub-)data set containing the pixel spacing
    container = find_element(
        data_set, index, 
        odil.registry.PixelSpacing, odil.registry.PixelMeasuresSequence)
    
    spacing = None
    if container is not None:
        spacing = list(container[odil.registry.PixelSpacing])
        
        # Look for SpacingBetweenSlices
        container = find_element(
            data_set, index,
            odil.registry.SpacingBetweenSlices, 
            odil.registry.PixelMeasuresSequence)
        if container:
            spacing.append(container[odil.registry.SpacingBetweenSlices][0])
        elif len(stack)>1:
            other_data_set, other_index = stack[1]
            container = find_element(
                other_data_set, other_index,
                odil.registry.ImagePositionPatient, 
                odil.registry.PlanePositionSequence)
            if container:
                position = get_origin(stack)
                other_position = container[odil.registry.ImagePositionPatient]
                difference = numpy.subtract(other_position, position)
                
                orientation = get_orientation(stack)
                spacing_between_slices = abs(numpy.dot(
                    difference, orientation[:, 2]))
                spacing.append(spacing_between_slices)
        else:
            container = find_element(
                data_set, index,
                odil.registry.SliceThickness, 
                odil.registry.PixelMeasuresSequence)
            if container:
                slice_thickness = container[odil.registry.SliceThickness]
                if slice_thickness:
                    spacing.append(slice_thickness[0])
    
    if spacing and len(spacing) == 2:
        logger.warning("No slice thickness, using default")
        spacing.append(1.)
    
    return spacing

def get_geometry(stack):
    """ Compute the geometry (origin, spacing, orientation) for the given stack.
    """
    
    default_origin = numpy.zeros((3,)).tolist()
    default_spacing = numpy.ones((3,)).tolist()
    default_orientation = numpy.identity(3)

    data_set, first_idx = stack[0]

    origin = get_origin(stack)
    if origin is None:
        logger.warning("No position found, using default")
        origin = default_origin
    
    orientation = get_orientation(stack)
    if orientation is None:
        logger.warning("No orientation found, using default")
        orientation = default_orientation

    spacing = get_spacing(stack)
    if spacing is None:
        logger.warning("No spacing found, using default")
        spacing = default_spacing
    
    return origin, spacing, orientation
