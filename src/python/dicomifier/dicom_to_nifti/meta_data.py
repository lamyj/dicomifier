#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import base64
import itertools

import json
import numpy
import odil

import odil_getter

from .. import MetaData


def get_meta_data(data_sets):
    """ Return the merged meta-data from the DICOM data sets in the NIfTI+JSON
        format: a dictionary keyed by the DICOM keyword (or the string 
        representation of the tag if no keyword is found) and valued by the 
        Value (or InlineBinary) of the DICOM elements.
    """

    meta_data = [convert_meta_data(x) for x in data_sets]

    merged = merge_meta_data(meta_data)
    return tag_to_name(merged)

# argument charset added to get charset while converting dataset & then
# get the correct string


def convert_meta_data(data_set, charset=None):
    """ Convert the meta-data from DICOM data sets to the NIfTI+JSON format.
    """

    meta_data = {}

    skipped = [
        # Stored in the NIfTI image
        "Rows", "Columns",
        "ImageOrientationPatient", "ImagePositionPatient", "PixelSpacing",
        "SliceLocation",
        # Useless in the NIfTI world (?)
        "SOPInstanceUID", "InstanceCreationDate", "InstanceCreationTime",
        # Implicit with the NIfTI data type
        "PixelRepresentation", "HighBit", "BitsStored", "BitsAllocated",
        # Stored in the NIfTI image
        "PixelData",
        # PixelValueTransformation sequence is applied on the image
        "PixelValueTransformationSequence",
        "SmallestImagePixelValue", "LargestImagePixelValue",
    ]
    skipped = [str(getattr(odil.registry, x)) for x in skipped]

    for tag, element in data_set.items():
        if tag in skipped:
            continue
        elif tag == "SpecificCharacterSet":
            charset = odil_getter._getter(data_set, tag)
        converted_value = None

        if element.empty():
            # Nothing to do.
            pass
        elif element.vr == odil.VR.SQ:
            converted_value = [
                convert_meta_data(x, charset)
                for x in odil_getter._getter(data_set, tag)]
        elif element.vr == odil.VR.PN:
            # create fake data_set with only this element & charset if
            # specified
            pn_data_set = odil.DataSet()
            pn_data_set.add(tag.get_name(), element.as_string())
            if charset is not None:
                pn_data_set.add(odil.registry.SpecificCharacterSet, charset)
            # convert & load json
            dcm_json = json.loads(odil.as_json(pn_data_set))
            # get specific element
            converted_value = dcm_json[str(tag)]["Value"]
        elif element.is_binary():
            # Get string representation
            views = [x.get_memory_view() for x in element.as_binary()]
            converted_value = [base64.b64encode(x.tobytes()) for x in views]
        # VRs that can contain specific charset
        elif element.vr.name in ["UT", "ST", "SH", "LT", "LO"]:
            pn_data_set = odil.DataSet()
            pn_data_set.add(tag, element.as_string(), element.vr)
            if charset is not None:
                pn_data_set.add(odil.registry.SpecificCharacterSet, charset)
            # convert & load json
            dcm_json = json.loads(odil.as_json(pn_data_set))
            # get specific element
            converted_value = dcm_json[str(tag)]["Value"]
        else:
            converted_value = odil_getter._getter(data_set, tag)
        # BUG in odil: tag cannot be used as a dict key
        meta_data[tag.group, tag.element] = converted_value

    return meta_data


def merge_meta_data(data_sets):
    """ Merge the meta-data of DICOM data sets if they are equal.
    """

    merged = {}

    tags = set(itertools.chain(*[x.keys() for x in data_sets]))
    for tag in tags:
        # merged_value is the list of all values found for the current tag
        merged_value = []
        for data_set in data_sets:
            value = data_set.get(tag, None)
            merged_value.append(value)
        if all(x == merged_value[0] for x in merged_value):
            merged_value = merged_value[0]
        merged[tag] = merged_value

    return MetaData(merged)


def tag_to_name(meta_data):
    """ Convert the numeric keys to named keys of a single meta data or a list
        of meta data.
    """

    result = None

    if isinstance(meta_data, list):
        result = [tag_to_name(item) for item in meta_data]
    elif isinstance(meta_data, (dict, MetaData)):
        result = {}
        for tag, element in meta_data.items():
            if tag in ["Alphabetic", "Ideographic", "Phonetic"]:
                # PN, keep name of field
                pass
            else:
                try:
                    tag = odil.Tag(tag[0], tag[1]).get_name()
                except odil.Exception as e:
                    # Keep numeric tag
                    tag = "{:04x}{:04x}".format(tag[0], tag[1])
            result[tag] = tag_to_name(element)
    else:
        # Scalar data
        result = meta_data

    return result
