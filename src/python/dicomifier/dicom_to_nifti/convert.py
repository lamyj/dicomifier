#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import logging
import itertools

import numpy
import odil

import meta_data
import image
import odil_getter

import nifti_image
from .. import MetaData

# need here to have the first arg dicom_data_sets in odil format instead
# of JSON


def convert(dicom_data_sets, dtype):
    """ Convert a list of dicom data sets into Nfiti

        :param dicom_data_sets: list of dicom data sets to convert
        :param dtype: type to use when coverting images
    """

    nifti_data = []

    stacks = get_stacks(dicom_data_sets)
    logging.info(
        "Found {} stack{}".format(len(stacks), "s" if len(stacks) > 1 else ""))

    # Set up progress information
    stacks_count = {}
    stacks_converted = {}
    for key, data_sets in stacks.items():
        series_instance_uid = odil_getter._getter(
            data_sets[0], odil.registry.SeriesInstanceUID)[0]
        stacks_count.setdefault(series_instance_uid, 0)
        stacks_count[series_instance_uid] += 1
        stacks_converted[series_instance_uid] = 0

    def get_element(data_set, tag):
        value = odil_getter._default_getter(data_set, tag)
        return value[0] if value is not None else None

    for data_sets in stacks.values():
        data_set = data_sets[0]

        study = [
            get_element(data_set, odil.registry.StudyID),
            get_element(data_set, odil.registry.StudyDescription)]
        study = [unicode(x) for x in study if x is not None]

        series = [
            get_element(data_set, odil.registry.SeriesNumber),
            get_element(data_set, odil.registry.SeriesDescription)]
        series = [unicode(x) for x in series if x is not None]

        series_instance_uid = get_element(
            data_set, odil.registry.SeriesInstanceUID)

        if stacks_count[series_instance_uid] > 1:
            stack_info = " (stack {}/{})".format(
                1 + stacks_converted[series_instance_uid],
                stacks_count[series_instance_uid])
        else:
            stack_info = ""
        logging.info(
            u"Converting {} / {}{}".format(
                "-".join(study), "-".join(series), stack_info))
        stacks_converted[series_instance_uid] += 1

        sort(data_sets)

        nifti_image = image.get_image(data_sets, dtype)
        nifti_meta_data = meta_data.get_meta_data(data_sets)

        nifti_data.append((nifti_image, nifti_meta_data))

    # Try to preserve the original stacks order
    nifti_data.sort(key=lambda x: x[1].get("InstanceNumber", [None])[0])

    # Try to merge stacks in each series
    merged_stacks = []
    series = {}
    for nitfi_image, nifti_meta_data in nifti_data:
        series.setdefault(nifti_meta_data["SeriesInstanceUID"][0], []).append(
            (nitfi_image, nifti_meta_data))
    for stacks in series.values():
        mergeable = {}
        for nitfi_image, nifti_meta_data in stacks:
            geometry = nifti_image.shape + \
                tuple(nitfi_image.qform.ravel().tolist())
            mergeable.setdefault(geometry, []).append(
                (nitfi_image, nifti_meta_data))

        for stack in mergeable.values():
            if len(stack) > 1:
                logging.info(
                    "Merging {} stack{}".format(
                        len(stack), "s" if len(stack) > 1 else ""))
                merged = merge_images_and_meta_data(stack)
                merged_stacks.append(merged)
            else:
                merged_stacks.append(stack[0])

    return merged_stacks


def get_stacks(data_sets):
    """ Return a dict containing, a tuple of key = (tag,value) 
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
        key = []
        for tag, getter in splitters:
            tag = str(tag)
            value = getter(data_set, tag)
            if value is not None:
                key.append((tag, value))
        stacks.setdefault(tuple(key), []).append(data_set)
    return stacks


def sort(data_sets):
    """ Sort data_sets depending on their orientation
        :param data_sets: data_sets to sort
    """

    getter = odil_getter.OrientationGetter()
    orientations = set(
        getter(data_set, odil.registry.ImageOrientationPatient)
        for data_set in data_sets
    )
    if len(orientations) > 1:
        raise Exception("Cannot sort data sets with non-uniform orientation")

    orientation = orientations.pop()
    normal = numpy.cross(*numpy.reshape(orientation, (2, -1)))
    data_sets.sort(
        key=lambda x: numpy.dot(
            odil_getter._getter(x, odil.registry.ImagePositionPatient), normal))


def merge_images_and_meta_data(images_and_meta_data):
    """ Merge the pixel and meta-data of geometrically coherent images.
    """

    images = [x[0] for x in images_and_meta_data]

    pixel_data = numpy.ndarray(
        (len(images),) + images[0].shape,
        dtype=images[0].data.dtype)
    for i, image in enumerate(images):
        pixel_data[i] = image.data

    merged_image = nifti_image.NIfTIImage(
        pixdim=images[0].pixdim,
        cal_min=min(x.cal_min for x in images),
        cal_max=max(x.cal_max for x in images),
        qform_code=images[0].qform_code, sform_code=images[0].sform_code,
        qform=images[0].qform, sform=images[0].sform,
        xyz_units=images[0].xyz_units, time_units=images[0].time_units,
        data=pixel_data)

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
    """ Get splitters for each element of the data_sets :
        append specific MRImageStorage elements to basic elements (with getters) 
        dependent on the current element of the data_sets

        :param data_sets: current data_sets 
    """

    splitters = {
        "ALL": [
            (odil.registry.SeriesInstanceUID, odil_getter._default_getter),
            (odil.registry.ImageOrientationPatient,
             odil_getter.OrientationGetter()),
            (odil.registry.SpacingBetweenSlices, odil_getter._default_getter),
        ],
        odil.registry.MRImageStorage: [
            (odil.registry.AcquisitionNumber, odil_getter._default_getter),
            (odil.registry.RepetitionTime, odil_getter._default_getter),
            (odil.registry.EchoTime, odil_getter._default_getter),
            (odil.registry.InversionTime, odil_getter._default_getter),
            (odil.registry.EchoNumbers, odil_getter._default_getter),
            (odil.registry.MRDiffusionSequence, odil_getter._diffusion_getter),
            # Philips Ingenia stores these fields at top-level
            (odil.registry.DiffusionGradientOrientation, odil_getter._default_getter),
            (odil.registry.DiffusionBValue, odil_getter._default_getter),
        ],
    }

    sop_classes = set(
        odil_getter._getter(x, odil.registry.SOPClassUID)[0]
        for x in data_sets
    )

    return list(itertools.chain(
        splitters["ALL"],
        *[splitters.get(x, []) for x in sop_classes]
    ))
