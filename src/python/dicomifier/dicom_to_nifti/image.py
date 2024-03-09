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

from .. import convert_pixel_data
from .. import logger
from . import siemens

def get_slice_image(data_set, shape, cache=None):
    """ Return a slice of an n-dimensional image.
    """
    
    uid = data_set[odil.registry.SOPInstanceUID][0]
    
    array = None
    if cache is not None and uid not in cache:
        dtype = get_data_set_dtype(data_set)
        array = convert_pixel_data(data_set, dtype).reshape((-1, *shape))
        
        # Mask the data using Bits Stored, cf. PS 3.5, 8.1.1
        bits_stored = data_set[odil.registry.BitsStored][0]
        array = numpy.bitwise_and(array, 2**bits_stored - 1, dtype=array.dtype)
        
        if b"MOSAIC" in data_set[odil.registry.ImageType]:
            item = data_set[odil.Tag(0x0029, 0x1010)][0]
            siemens_data = siemens.parse_csa(item.get_memory_view().tobytes())
            
            number_of_tiles = siemens_data["NumberOfImagesInMosaic"][0]
            tiles_per_line = int(math.ceil(math.sqrt(number_of_tiles)))
            
            # Re-arrange array so that tiles are contiguous
            array = array.reshape(
                tiles_per_line, shape[-2], tiles_per_line, shape[-1])
            array = array.transpose((0, 2, 1, 3))
            array = array.reshape(tiles_per_line**2, *shape[-2:])
            
            # Remove the black tiles. WARNING: assume they are always at the end 
            # of the mosaic
            array = array[:number_of_tiles]
            
        # Populate the cache
        cache[uid] = array
    else:
        array = cache[uid]
    
    return array

def get_data_set_dtype(data_set):
    """ Return the numpy dtype of the PixelData stored in a DICOM data set.
    """
    
    byte_order = ">" if data_set[odil.registry.HighBit][0] == 0 else "<"
    is_unsigned = (data_set.get(odil.registry.PixelRepresentation, [0])[0] == 0)
    
    bits_allocated = data_set[odil.registry.BitsAllocated][0]
    if bits_allocated % 8 != 0:
        raise NotImplementedError("Cannot handle non-byte types")
    
    return numpy.dtype(
        "{}{}{}".format(
            byte_order, "u" if is_unsigned else "i", bits_allocated // 8))

def find_common_dtype(dtypes):
    """ Return the dtype which encompasses all provided dtypes.
    """
    
    kinds = set(x.kind for x in dtypes)
    itemsizes = set(x.itemsize for x in dtypes)
    
    if len(kinds) == 1:
        # Single kind. Use it, with largest item size.
        return numpy.dtype(f"{kinds.pop()}{max(itemsizes)}")
    elif all(k in "iuf" for k in kinds):
        # Mixed signed and unsigned integers: promote to float
        # Mixed integers and floats: promote to float
        return numpy.dtype(f"f{max(itemsizes)}")
    elif all(k in "iufc" for k in kinds):
        # Same as above, but includes complex: promote to complex
        return numpy.dtype(f"c{max(itemsizes)}")
    else:
        # Non-numeric dtype
        raise Exception("Cannot find common dtype")

def get_shape(stack):
    """ Return the shape of the image data contained in the stack.
    """
    
    data_set = stack[0][0]
    
    if b"MOSAIC" in data_set[odil.registry.ImageType]:
        item = data_set[odil.Tag(0x0029, 0x1010)][0]
        siemens_data = siemens.parse_csa(item.get_memory_view().tobytes())
        
        number_of_tiles = siemens_data["NumberOfImagesInMosaic"][0]
        tiles_per_line = int(math.ceil(math.sqrt(number_of_tiles)))
        
        rows = data_set[odil.registry.Rows][0] // tiles_per_line
        cols = data_set[odil.registry.Columns][0] // tiles_per_line
        shape = [number_of_tiles*len(stack), rows, cols]
    else:
        rows = data_set[odil.registry.Rows][0]
        cols = data_set[odil.registry.Columns][0]
        shape = [len(stack), rows, cols]
        
    samples_per_pixel = data_set[odil.registry.SamplesPerPixel][0]
    if samples_per_pixel > 1:
        shape.append(samples_per_pixel)
    
    return tuple(shape)

def get_rescale(data_set, frame_index=None):
    """ Return the rescale information contained in a data set, as
        (slope, intercept). If rescale is not present, return None.
    """
    
    containers = [
        data_set,
        data_set.get(
                odil.registry.PixelValueTransformationSequence, [odil.DataSet()]
            )[0],
        data_set.get(
                odil.registry.SharedFunctionalGroupsSequence, 
                [odil.DataSet(PixelValueTransformationSequence=[odil.DataSet()])]
            )[0].get(odil.registry.PixelValueTransformationSequence, [odil.DataSet()])[0],
    ]
    if frame_index is not None:
        containers.append(
            data_set.get(
                    odil.registry.PerFrameFunctionalGroupsSequence, 
                    (1+frame_index)*[
                        odil.DataSet(PixelValueTransformationSequence=[odil.DataSet()])]
                )[frame_index].get(
                    odil.registry.PixelValueTransformationSequence, [odil.DataSet()]
                )[0])
    rescale = None
    for item in containers:
        slope = item.get(odil.registry.RescaleSlope, [None])[0]
        intercept = item.get(odil.registry.RescaleIntercept, [None])[0]
        if None not in (slope, intercept):
            rescale = (slope, intercept)
    
    if rescale is not None and not numpy.allclose(rescale, [1, 0]):
        return rescale
    else:
        return None

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
    """ Compute the origin of the stack.
        
        NOTE: if the stack contains mosaic data set, the return value of this
        function is unmodified by the mosaic info (cf. code in get_geometry).
    """
    
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
    """
        Compute the orientation of the stack.
        
        NOTE: if the stack contains mosaic data set, the return value of this
        function is unmodified by the mosaic info (cf. code in get_geometry).
    """
    
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
    
    return tuple(spacing)

def get_geometry(stack):
    """ Compute the geometry (origin, spacing, orientation) for the given stack.
    """
    
    default_origin = numpy.zeros((3,)).tolist()
    default_spacing = numpy.ones((3,)).tolist()
    default_orientation = numpy.identity(3)

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
    
    data_set = stack[0][0]
    if b"MOSAIC" in data_set[odil.registry.ImageType]:
        item = data_set[odil.Tag(0x0029, 0x1010)][0]
        siemens_data = siemens.parse_csa(item.get_memory_view().tobytes())
        
        number_of_tiles = siemens_data["NumberOfImagesInMosaic"][0]
        tiles_per_line = int(math.ceil(math.sqrt(number_of_tiles)))
        
        # Get the origin of the tiles (i.e. origin of the first tile), cf.
        # http://nipy.org/nibabel/dicom/dicom_mosaic.html
        # NOTE: shapes are expressed in Fortran order, as is the orientation
        mosaic_shape = numpy.asarray([
            data_set[odil.registry.Columns][0],
            data_set[odil.registry.Rows][0]])
        R = orientation[:, :2]
        Q = R * spacing[:2]
        real_shape = mosaic_shape // tiles_per_line
        origin = origin + numpy.dot(Q, (mosaic_shape - real_shape) / 2.)
        
        orientation[:, 2] = siemens_data["SliceNormalVector"]
        
    return origin, spacing, orientation
