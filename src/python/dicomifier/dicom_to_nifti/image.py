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

import numpy
import odil

import nifti_image
import niftiio
import siemens

def get_image(data_sets, dtype):
    pixel_data = [get_pixel_data(data_set) for data_set in data_sets]
    pixel_data = numpy.asarray(pixel_data, dtype=dtype)

    origin, spacing, direction = get_geometry(data_sets)

    if (len(data_sets) == 1 and
            "MOSAIC" in data_sets[0][str(odil.registry.ImageType)]["Value"]):
        data_set = data_sets[0]
        siemens_header = siemens.parse_csa(
            base64.b64decode(data_set["00291010"]["InlineBinary"]))

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
        cal_min=pixel_data.min(), cal_max=pixel_data.max(),
        qform_code = niftiio.NIFTI_XFORM_SCANNER_ANAT,
        sform_code = niftiio.NIFTI_XFORM_SCANNER_ANAT,
        qform=scanner_transform, sform=scanner_transform,
        xyz_units=niftiio.NIFTI_UNITS_MM,
        data=pixel_data)
    
    return image

def get_pixel_data(data_set):
    high_bit = data_set[str(odil.registry.HighBit)]["Value"][0]
    byte_order = ">" if high_bit==0 else "<"
    
    pixel_representation = data_set[str(odil.registry.PixelRepresentation)]["Value"][0]
    is_unsigned = (pixel_representation==0)
    
    bits_allocated = data_set[str(odil.registry.BitsAllocated)]["Value"][0]
    if bits_allocated%8 != 0:
        raise NotImplementedError("Cannot handle non-byte types")
    
    dtype = numpy.dtype(
        "{}{}{}".format(
            byte_order, "u" if is_unsigned else "i", bits_allocated/8))
    
    pixel_data = numpy.fromstring(
        base64.b64decode(data_set[str(odil.registry.PixelData)]["InlineBinary"]),
        dtype
    )
    
    # Mask the data using Bits Stored, cf. PS 3.5, 8.1.1
    bits_stored = data_set[str(odil.registry.BitsStored)]["Value"][0]
    pixel_data = numpy.bitwise_and(pixel_data, 2**bits_stored-1)
    
    pixel_data = pixel_data.reshape((
        data_set[str(odil.registry.Rows)]["Value"][0],
        data_set[str(odil.registry.Columns)]["Value"][0]
    ))
    
    # Rescale: look for Pixel Value Transformation sequence then Rescale Slope
    # and Rescale Intercept
    slope = None
    intercept = None
    pixel_value_transformation = data_set.get(
        str(odil.registry.PixelValueTransformationSequence))
    if pixel_value_transformation is not None:
        pixel_value_transformation = pixel_value_transformation["Value"][0]
        slope = pixel_value_transformation[
            str(odil.registry.RescaleSlope)]["Value"][0]
        intercept = pixel_value_transformation[
            str(odil.registry.RescaleIntercept)]["Value"][0]
    else:
        slope = data_set.get(str(odil.registry.RescaleSlope))
        if slope is not None:
            slope = slope["Value"][0]

        intercept = data_set.get(str(odil.registry.RescaleIntercept))
        if intercept is not None:
            intercept = intercept["Value"][0]
    
    if None not in [slope, intercept]:
        pixel_data = pixel_data*slope+intercept
    
    return pixel_data

def get_geometry(data_sets):
    origin = data_sets[0][str(odil.registry.ImagePositionPatient)]["Value"]
    
    # Image Orientation gives the columns of the matrix, cf.
    # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.2.html#sect_C.7.6.2.1.1
    orientation = data_sets[0][str(odil.registry.ImageOrientationPatient)]["Value"]
    direction = numpy.zeros((3,3))
    direction[:,0] = orientation[:3]
    direction[:,1] = orientation[3:]
    direction[:,2] = numpy.cross(direction[:,0], direction[:,1])
    
    spacing = data_sets[0][str(odil.registry.PixelSpacing)]["Value"]
    if str(odil.registry.SpacingBetweenSlices) in data_sets[0]:
        spacing.append(data_sets[0][str(odil.registry.SpacingBetweenSlices)]["Value"][0])
    elif len(data_sets)>2:
        difference = numpy.subtract(
            data_sets[1][str(odil.registry.ImagePositionPatient)]["Value"],
            data_sets[0][str(odil.registry.ImagePositionPatient)]["Value"])
        spacing_between_slices = abs(numpy.dot(difference, direction[:,2]))
        spacing.append(spacing_between_slices)
    else:
        # 2D data set, add dummy spacing at the end since DICOM images are
        # in a 3D space
        spacing.append(1.)
    
    return origin, spacing, direction
