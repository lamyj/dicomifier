#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import base64
import logging

import nifti
import numpy
import odil

def get_image(data_sets, dtype):
    pixel_data = [get_pixel_data(data_set) for data_set in data_sets]
    pixel_data = numpy.asarray(pixel_data, dtype=dtype)

    origin, spacing, direction = get_geometry(data_sets)

    image = nifti.NiftiImage(pixel_data)
    
    # According to NIfTI doc (http://nifti.nimh.nih.gov/nifti-1/documentation/nifti1fields/nifti1fields_pages/qsform.html),
    # the "normal" case is to use the qform
    qform = numpy.identity(4)
    lps_to_ras = [
        [-1,  0, 0],
        [ 0, -1, 0],
        [ 0,  0, 1]
    ]
    qform[:3,:3] = numpy.dot(lps_to_ras, direction)
    image.setQForm(qform, "scanner")

    # Origin must be transformed to LPS
    origin[0] = -origin[0]
    origin[1] = -origin[1]
    image.setQOffset(origin, "scanner")
    
    # Set pixdim *after* the others, otherwise pixdim gets reset.
    image.setVoxDims(spacing)
    
    image.setXYZUnit("mm")
    
    return image

def get_pixel_data(data_set):
    high_bit = data_set[str(odil.registry.HighBit)]["Value"][0]
    byte_order = ">" if high_bit==0 else "<"
    
    pixel_representation = data_set[str(odil.registry.PixelRepresentation)]["Value"][0]
    is_unsigned = (pixel_representation==0)
    
    bits_stored = data_set[str(odil.registry.BitsStored)]["Value"][0]
    if bits_stored%8 != 0:
        raise NotImplementedError("Cannot handle non-byte types")
    
    dtype = numpy.dtype(
        "{}{}{}".format(byte_order, "u" if is_unsigned else "i", bits_stored/8))
    
    pixel_data = numpy.fromstring(
        base64.b64decode(data_set[str(odil.registry.PixelData)]["InlineBinary"]),
        dtype
    )
    pixel_data = pixel_data.reshape((
        data_set[str(odil.registry.Rows)]["Value"][0],
        data_set[str(odil.registry.Columns)]["Value"][0]
    ))
    
    pixel_transformation = data_set.get(
        str(odil.registry.PixelValueTransformationSequence))
    if pixel_transformation is not None:
        pixel_transformation = pixel_transformation["Value"][0]
        slope = pixel_transformation[str(odil.registry.RescaleSlope)]["Value"][0]
        intercept = pixel_transformation[str(odil.registry.RescaleIntercept)]["Value"][0]
        pixel_data = pixel_data*slope+intercept
    
    return pixel_data

def get_geometry(data_sets):
    origin = data_sets[0][str(odil.registry.ImagePositionPatient)]["Value"]
    
    spacing = data_sets[0][str(odil.registry.PixelSpacing)]["Value"]
    if str(odil.registry.SpacingBetweenSlices) in data_sets[0]:
        spacing.append(data_sets[0][str(odil.registry.SpacingBetweenSlices)]["Value"][0])
    elif len(data_sets)>2:
        spacing.append(
            numpy.subtract(
                data_sets[0][str(odil.registry.ImagePositionPatient)]["Value"][0],
                data_sets[1][str(odil.registry.ImagePositionPatient)]["Value"][0]))
    else:
        # 2D data set, add dummy spacing at the end since DICOM images are
        # in a 3D space
        spacing.append(0)
    
    # Image Orientation gives the columns of the matrix, cf.
    # http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.7.6.2.html#sect_C.7.6.2.1.1
    orientation = data_sets[0][str(odil.registry.ImageOrientationPatient)]["Value"]
    direction = numpy.zeros((3,3))
    direction[:,0] = orientation[:3]
    direction[:,1] = orientation[3:]
    direction[:,2] = numpy.cross(direction[:,0], direction[:,1])
    
    return origin, spacing, direction
