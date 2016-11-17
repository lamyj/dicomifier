#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import base64

import json
import odil

from .. import MetaData

def get_meta_data(data_sets):
    """ Return the merged meta-data from the DICOM data sets in the NIfTI+JSON
        format: a dictionary keyed by the DICOM keyword (or the string 
        representation of the tag if no keyword is found) and valued by the 
        Value (or InlineBinary) of the DICOM elements.
    """

    # BUG in odil: tags are not hashed correctly
    # Use the tuple (group, element) in Python objects (dict, set)

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
    skipped = [getattr(odil.registry, x) for x in skipped]
    skipped = [(x.group, x.element) for x in skipped]

    # List all tags that appear in any of the data sets
    tags = set()
    for data_set in data_sets:
        data_set_tags = [(x.group, x.element) for x in data_set]
        tags.update(x for x in data_set_tags if x not in skipped)

    meta_data = MetaData()
    specific_character_set = []
    for tag_tuple in sorted(tags):
        tag_object = odil.Tag(*tag_tuple)

        # List the value of this tag in every data set (None if absent)
        values = []
        for data_set in data_sets:
            if data_set.has(tag_object):
                values.append(data_set[tag_object])
            else:
                value.append(None)

        # Check whether all values are the same
        all_equal = True
        sample = values[0]
        for value in values[1:]:
            if value != sample:
                all_equal = False
                break

        if all_equal:
            # Only use the unique value.
            value = convert_element(sample, specific_character_set)
        else:
            # Convert each value. If we have multiple values of Specific 
            # Character Set, use the one from the corresponding data set.
            if (
                    specific_character_set 
                    and isinstance(specific_character_set[0], list)):
                value = [
                    convert_element(x, specific_character_set[i]) 
                    for i, x in enumerate(values)]
            else:
                value = [
                    convert_element(x, specific_character_set) for x in values]

        if tag_object == odil.registry.SpecificCharacterSet:
            specific_character_set = value

        tag_name = get_tag_name(tag_object)

        meta_data[tag_name] = value
            
    return meta_data

def get_tag_name(tag):
    """ Convert a DICOM tag to its NIfTI+JSON representation: the tag keyword
        if known, and the standard DICOM JSON representation otherwise.
    """

    try:
        tag_name = tag.get_name()
    except odil.Exception as e:
        tag_name = str(tag)
    return tag_name

def convert_element(element, specific_character_set):
    """ Convert a DICOM element to its NIfTI+JSON representation: the "Value"
        (or "InlineBinary") attribute of its standard DICOM JSON 
        representation.
    """

    result = None
    if element.empty():
        result = None
    elif element.is_int():
        result = list(element.as_int())
    elif element.is_real():
        result = list(element.as_real())
    elif element.is_string():
        if element.vr.name in ["LO", "LT", "PN", "SH", "ST", "UT"]:
            data_set = odil.DataSet()
            if specific_character_set:
                data_set.add(
                    odil.registry.SpecificCharacterSet, specific_character_set)
            data_set.add(
                odil.Tag(0xffff, 0xffff), element.as_string(), element.vr)
            result = json.loads(odil.as_json(data_set))["ffffffff"]["Value"]
        else:
            result = list(element.as_string())
    elif element.is_data_set():
        result = [
            convert_data_set(x, specific_character_set) 
            for x in element.as_data_set()]
    elif element.is_binary():
        result = [
            base64.b64encode(x.get_memory_view().tobytes())
            for x in element.as_binary()]
    else:
        raise Exception("Unknown element type")

    return result

def convert_data_set(data_set, specific_character_set):
    """ Convert a DICOM data set to its NIfTI+JSON representation.
    """

    result = {}
    if data_set.has(odil.registry.SpecificCharacterSet):
        specific_character_set = data_set.as_string(
            odil.registry.SpecificCharacterSet)
    for tag, element in data_set.items():
        name = get_tag_name(tag)
        value = convert_element(element, specific_character_set)
        result[name] = value

    return result

