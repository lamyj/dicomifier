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

import nifti_image
from .. import nifti
import siemens


def get_image(data_sets, dtype):
    # WARNING: the following is much slower :
    # numpy.asarray([get_pixel_data(data_set) for data_set in data_sets])

    pixel_data_list = [get_pixel_data(x) for x in data_sets]

    if dtype is None:
        has_float = any(x.dtype.kind == "f" for x in pixel_data_list)
        if has_float:
            dtype = numpy.float32
        else:
            # Assume all data sets have the same type
            dtype = pixel_data_list[0].dtype
        logging.info("dtype deduced to be: {}".format(dtype))

    pixel_data = numpy.ndarray(
        (len(data_sets),) + pixel_data_list[0].shape, dtype=dtype)
    for i, data in enumerate(pixel_data_list):
        pixel_data[i] = data

    dt = nifti.DT_UNKNOWN
    scanner_transform = numpy.identity(4)

    origin, spacing, direction = get_geometry(data_sets)

    if (len(data_sets) == 1 and
            "MOSAIC" in data_sets[0].as_string(odil.registry.ImageType)):
        data_set = data_sets[0]

        siemens_data = data_set.as_binary(odil.Tag("00291010"))[0]
        siemens_header = siemens.parse_csa(
            siemens_data.get_memory_view().tobytes())

        number_of_images_in_mosaic = siemens_header[
            "NumberOfImagesInMosaic"][0]
        tiles_per_line = int(math.ceil(math.sqrt(number_of_images_in_mosaic)))

        mosaic_shape = numpy.asarray(pixel_data.shape[-2:])

        rows = pixel_data.shape[-2] / tiles_per_line
        columns = pixel_data.shape[-1] / tiles_per_line

        real_shape = numpy.asarray([rows, columns])

        # Re-arrange array so that tiles are contiguous
        pixel_data = pixel_data.reshape(
            tiles_per_line, rows, tiles_per_line, columns)
        pixel_data = pixel_data.transpose((0, 2, 1, 3))
        pixel_data = pixel_data.reshape(tiles_per_line**2, rows, columns)

        # Get the origin of the tiles (i.e. origin of the first tile), cf.
        # http://nipy.org/nibabel/dicom/dicom_mosaic.html
        # WARNING: need to invert their rows and columns
        R = direction[:, :2]
        Q = R * spacing[:2]
        origin = origin + \
            numpy.dot(Q, (mosaic_shape[::-1] - real_shape[::-1]) / 2.)

        direction[:, 2] = siemens_header["SliceNormalVector"]

    samples_per_pix = data_sets[0].as_int("SamplesPerPixel")[0]

    if samples_per_pix == 1:
        lps_to_ras = [
            [-1,  0, 0],
            [0, -1, 0],
            [0,  0, 1]
        ]

        scanner_transform[:3, :3] = numpy.dot(lps_to_ras, direction)
        scanner_transform[:3, :3] = numpy.dot(
            scanner_transform[:3, :3], numpy.diag(spacing))
        scanner_transform[:3, 3] = numpy.dot(lps_to_ras, origin)

    elif samples_per_pix == 3 and data_sets[0].as_string("PhotometricInterpretation")[0] == "RGB":
        if dtype != numpy.uint8:
            raise Exception("Invalid dtype {} for RGB".format(dtype))
        dt = nifti.DT_RGB

    image = nifti_image.NIfTIImage(
        pixdim=[0.] + spacing + (8 - len(spacing) - 1) * [0.],
        cal_min=float(pixel_data.min()), cal_max=float(pixel_data.max()),
        qform_code=nifti.NIFTI_XFORM_SCANNER_ANAT,
        sform_code=nifti.NIFTI_XFORM_SCANNER_ANAT,
        qform=scanner_transform, sform=scanner_transform,
        xyz_units=nifti.NIFTI_UNITS_MM,
        data=pixel_data,
        datatype_=dt)

    return image


def get_pixel_data(data_set):
    """ Return the pixel data located in a dataset

        :param data_set: The dataset containing the pixelData 
    """

    high_bit = data_set.as_int(odil.registry.HighBit)[0]

    byte_order = ">" if high_bit == 0 else "<"

    pixel_representation = 0
    if data_set.has(odil.registry.PixelRepresentation):
        pixel_representation = data_set.as_int(
            odil.registry.PixelRepresentation)[0]
    is_unsigned = (pixel_representation == 0)

    bits_allocated = data_set.as_int(odil.registry.BitsAllocated)[0]
    if bits_allocated % 8 != 0:
        raise NotImplementedError("Cannot handle non-byte types")

    dtype = numpy.dtype(
        "{}{}{}".format(
            byte_order, "u" if is_unsigned else "i", bits_allocated / 8))

    rows = data_set.as_int(odil.registry.Rows)[0]
    cols = data_set.as_int(odil.registry.Columns)[0]

    samples_per_pixel = data_set.as_int(odil.registry.SamplesPerPixel)[0]

    type_ = byte_order + str(rows * cols * samples_per_pixel) + dtype.char

    view = data_set.as_binary(odil.registry.PixelData)[0].get_memory_view()
    pixel_data = numpy.frombuffer(view.tobytes(), byte_order + dtype.char)
    if samples_per_pixel == 1:
        pixel_data = numpy.asarray(pixel_data).reshape(rows, cols)
    else:
        pixel_data = numpy.asarray(pixel_data).reshape(
            rows, cols, samples_per_pixel)

    # Mask the data using Bits Stored, cf. PS 3.5, 8.1.1
    bits_stored = data_set.as_int(odil.registry.BitsStored)[0]
    pixel_data = numpy.bitwise_and(pixel_data, 2**bits_stored - 1)

    # Rescale: look for Pixel Value Transformation sequence then Rescale Slope
    # and Rescale Intercept
    slope = None
    intercept = None
    if data_set.has(odil.registry.PixelValueTransformationSequence):
        transformation = data_set.as_data_set(
            odil.registry.PixelValueTransformationSequence)[0]
    else:
        transformation = data_set
    if transformation.has(odil.registry.RescaleSlope):
        slope = transformation.as_real(odil.registry.RescaleSlope)[0]
    if transformation.has(odil.registry.RescaleIntercept):
        intercept = transformation.as_real(odil.registry.RescaleIntercept)[0]
    if None not in [slope, intercept]:
        pixel_data = pixel_data * numpy.float32(slope) + numpy.float32(intercept)

    return pixel_data


def get_geometry(data_sets):
    if not data_sets[0].has(odil.registry.ImagePositionPatient):
        # default values
        origin = numpy.zeros((3,)).tolist()
        spacing = numpy.ones((3,)).tolist()
        direction = numpy.identity(3)
	logging.info("No geometry found, default returned")
        return origin, spacing, direction

    origin = data_sets[0].as_real(odil.registry.ImagePositionPatient)
    # Image Orientation gives the columns of the matrix, cf.
    # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.2.html#sect_C.7.6.2.1.1
    orientation = data_sets[0].as_real(odil.registry.ImageOrientationPatient)
    direction = numpy.zeros((3, 3))
    direction[:, 0] = orientation[:3]
    direction[:, 1] = orientation[3:]
    direction[:, 2] = numpy.cross(direction[:, 0], direction[:, 1])

    spacing = list(data_sets[0].as_real(odil.registry.PixelSpacing))

    if data_sets[0].has(odil.registry.SpacingBetweenSlices):
        spacing.append(
            data_sets[0].as_real(odil.registry.SpacingBetweenSlices)[0])
    elif len(data_sets) > 2:
        difference = numpy.subtract(
            data_sets[1].as_real(odil.registry.ImagePositionPatient),
            data_sets[0].as_real(odil.registry.ImagePositionPatient))
        spacing_between_slices = abs(numpy.dot(difference, direction[:, 2]))
        spacing.append(spacing_between_slices)
    else:
        # 2D data set, add dummy spacing at the end since DICOM images are
        # in a 3D space
        spacing.append(1.)

    return origin, spacing, direction
