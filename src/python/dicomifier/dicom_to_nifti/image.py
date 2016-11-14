#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import base64
import logging
import math

import struct
import numpy
import odil

import odil_getter
import nifti_image
from .. import nifti
import siemens

def get_image(data_sets, dtype):
    # WARNING: the following is much slower :
    # numpy.asarray([get_pixel_data(data_set) for data_set in data_sets])
    sample = get_pixel_data(data_sets[0])
    pixel_data = numpy.ndarray((len(data_sets),)+sample.shape, dtype=dtype)
    pixel_data[0] = sample
    for i, data_set in enumerate(data_sets[1:]):
        pixel_data[1+i] = get_pixel_data(data_set)

    origin, spacing, direction = get_geometry(data_sets)

    if (len(data_sets) == 1 and
            "MOSAIC" in odil_getter._getter(
		data_sets[0],odil.registry.ImageType)):
        data_set = data_sets[0]
	
	siemens_header = siemens.parse_csa(
	    base64.b64decode(str(dicomifier.odil_getter._getter(tag_siemens_header)[0].
	    get_memory_view())))
	
        number_of_images_in_mosaic = siemens_header["NumberOfImagesInMosaic"][0]
        tiles_per_line = int(math.ceil(math.sqrt(number_of_images_in_mosaic)))

        mosaic_shape = numpy.asarray(pixel_data.shape[-2:])

        rows = pixel_data.shape[-2]/tiles_per_line
        columns = pixel_data.shape[-1]/tiles_per_line

        real_shape = numpy.asarray([rows, columns])

        # Re-arrange array so that tiles are contiguous
        pixel_data = pixel_data.reshape(tiles_per_line, rows, tiles_per_line, columns)
        pixel_data = pixel_data.transpose((0,2,1,3))
        pixel_data = pixel_data.reshape(tiles_per_line**2, rows, columns)

        # Get the origin of the tiles (i.e. origin of the first tile), cf.
        # http://nipy.org/nibabel/dicom/dicom_mosaic.html
        # WARNING: need to invert their rows and columns
        R = direction[:,:2]
        Q = R*spacing[:2]
        origin = origin + numpy.dot(Q, (mosaic_shape[::-1]-real_shape[::-1])/2.)

        direction[:,2] = siemens_header["SliceNormalVector"]

    lps_to_ras = [
        [-1,  0, 0],
        [ 0, -1, 0],
        [ 0,  0, 1]
    ]
    
    scanner_transform = numpy.identity(4)
    scanner_transform[:3, :3] = numpy.dot(lps_to_ras, direction)
    scanner_transform[:3, :3] = numpy.dot(
        scanner_transform[:3, :3], numpy.diag(spacing))
    scanner_transform[:3, 3] = numpy.dot(lps_to_ras, origin)

    image = nifti_image.NIfTIImage(
        pixdim=[0.]+spacing+(8-len(spacing)-1)*[0.],
        cal_min=float(pixel_data.min()), cal_max=float(pixel_data.max()),
        qform_code = nifti.NIFTI_XFORM_SCANNER_ANAT,
        sform_code = nifti.NIFTI_XFORM_SCANNER_ANAT,
        qform=scanner_transform, sform=scanner_transform,
        xyz_units=nifti.NIFTI_UNITS_MM,
        data=pixel_data)
    
    return image

def get_pixel_data(data_set):
    """ Return the pixel data located in a dataset
	
	:param data_set: The dataset containing the pixelData 
    """
    
    high_bit = odil_getter._getter(data_set,odil.registry.HighBit)[0]
    
    byte_order = ">" if high_bit==0 else "<"
    
    pixel_representation = 0
    pixel_representation = odil_getter._default_getter(
	data_set,odil.registry.PixelRepresentation)
    if pixel_representation is not None:
	pixel_representation = pixel_representation[0]
    is_unsigned = (pixel_representation==0)
    
    bits_allocated = odil_getter._getter(
	data_set,odil.registry.BitsAllocated)[0]
    if bits_allocated%8 != 0:
        raise NotImplementedError("Cannot handle non-byte types")
    
    dtype = numpy.dtype(
        "{}{}{}".format(
            byte_order, "u" if is_unsigned else "i", bits_allocated/8))
    
    rows = odil_getter._getter(data_set,odil.registry.Rows)[0]
    cols = odil_getter._getter(data_set,odil.registry.Columns)[0]
    
    type_ = byte_order+str(rows*cols)+dtype.char
    int_array = struct.unpack(type_,
	odil_getter._getter(data_set,odil.registry.PixelData)[0].get_memory_view())
    pixel_data = numpy.asarray(int_array).reshape(rows,cols)

    # Mask the data using Bits Stored, cf. PS 3.5, 8.1.1
    bits_stored = odil_getter._getter(data_set,odil.registry.BitsStored)[0]
    pixel_data = numpy.bitwise_and(pixel_data, 2**bits_stored-1)
    
    # Rescale: look for Pixel Value Transformation sequence then Rescale Slope
    # and Rescale Intercept
    slope = None
    intercept = None
    pixel_value_transformation = odil_getter._default_getter(
	data_set, odil.registry.PixelValueTransformationSequence
    )
    if pixel_value_transformation is not None:
	pixel_value_transformation = pixel_value_transformation[0]
	slope = odil_getter._default_getter(
	    pixel_value_transformation,odil.registry.RescaleSlope)
	if slope is not None:
	    slope = slope[0]
	intercept = odil_getter._default_getter(
	    pixel_value_transformation,odil.registry.RescaleIntercept)
	if intercept is not None:
	    intercept = intercept[0]
    if None not in [slope, intercept]:
        pixel_data = pixel_data*slope+intercept

    return pixel_data

def get_geometry(data_sets):
    origin = odil_getter._getter(data_sets[0],odil.registry.ImagePositionPatient)
    
    # Image Orientation gives the columns of the matrix, cf.
    # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.2.html#sect_C.7.6.2.1.1
    orientation = odil_getter._getter(data_sets[0],odil.registry.ImageOrientationPatient) 
    direction = numpy.zeros((3,3))
    direction[:,0] = orientation[:3]
    direction[:,1] = orientation[3:]
    direction[:,2] = numpy.cross(direction[:,0], direction[:,1])
    
    spacing = list(odil_getter._getter(data_sets[0],odil.registry.PixelSpacing))
    
    if data_sets[0].has(odil.registry.SpacingBetweenSlices):
	spacing.append(odil_getter._getter(data_sets[0],odil.registry.SpacingBetweenSlices)[0])
    elif len(data_sets)>2:
	difference = numpy.subtract(
	    odil_getter._getter(data_sets[1],odil.registry.ImagePositionPatient),
	    odil_getter._getter(data_sets[0],odil.registry.ImagePositionPatient))
	spacing_between_slices = abs(numpy.dot(difference, direction[:,2]))
        spacing.append(spacing_between_slices)
    else:
        # 2D data set, add dummy spacing at the end since DICOM images are
        # in a 3D space
        spacing.append(1.)
    
    return origin, spacing, direction
