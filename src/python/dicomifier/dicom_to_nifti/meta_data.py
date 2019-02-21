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

from . import odil_getter
from .. import MetaData

def get_meta_data(data_sets_frame_idx, cache):
    """ Get the meta data of the current stack 

        will keep the priority order for repeting element with the following rules:
        low_priority = per_frame_seq
        high_priority = top_level (data_set)
        (if the same element is present in both shared and per_frame,
         we will keep the element of the shared seq)

        :param data_sets_frame_idx: List containing the data sets of the frame 
                                    with the corresponding frame when it's a multiframe data set
        :param cache: dict used to store (tag,elem) for top priority sequences (top level & shared)
                      in order to parse them only once per data_set
    """

    skipped = [
        # Stored in the NIfTI image
        "Rows", "Columns",
        "ImageOrientationPatient", "ImagePositionPatient", "PixelSpacing",
        "SliceLocation",
        # Useless in the NIfTI world (?)
        "SOPInstanceUID", "InstanceCreationDate", "InstanceCreationTime",
        "DimensionIndexValues", "InStackPositionNumber",
        "WindowCenter", "WindowWidth",
        # Implicit with the NIfTI data type
        "PixelRepresentation", "HighBit", "BitsStored", "BitsAllocated",
        # Stored in the NIfTI image
        "PixelData",
        # PixelValueTransformation sequence is applied on the image
        "PixelValueTransformationSequence",
        "SmallestImagePixelValue", "LargestImagePixelValue",
        # Multi-frame related elements are extracted from their sequences
        "SharedFunctionalGroupsSequence",
        "PerFrameFunctionalGroupsSequence",
    ]

    skipped = [getattr(odil.registry, x) for x in skipped]

    # Must get directly this sequence (otherwise test fails)
    direct_sequences = [
        "MRDiffusionSequence"
    ]
    direct_sequences = [getattr(odil.registry, x) for x in direct_sequences]

    # Populate the Odil cache with the elements at top-level and in shared 
    # functional groups
    for data_set, frame_index in data_sets_frame_idx:
        sop_instance_uid = data_set.as_string(odil.registry.SOPInstanceUID)[0]
        if sop_instance_uid in cache:
            continue
            
        cache[sop_instance_uid] = {}
        
        for tag in data_set:
            if tag in skipped:
                continue
            value = data_set[tag]
            cache[sop_instance_uid][tag] = value
        if frame_index is not None:
            functional_groups = data_set.as_data_set(
                odil.registry.SharedFunctionalGroupsSequence)[0]
            _process_functional_groups(
                functional_groups, 
                lambda tag, value: 
                    cache[sop_instance_uid].__setitem__(tag, value), 
                skipped, direct_sequences)

    # Get the values of all (data_set, frame_index)
    tag_values = {}
    for list_index, (data_set, frame_index) in enumerate(data_sets_frame_idx):
        sop_instance_uid = data_set.as_string(odil.registry.SOPInstanceUID)[0]
        # Fetch non-frame-specific elements from cache
        for tag, element in cache[sop_instance_uid].items():
            tag_values.setdefault(tag, {})[list_index] = element
        if frame_index is not None:
            # Fetch frame-specific elements
            functional_groups = data_set.as_data_set(
                odil.registry.PerFrameFunctionalGroupsSequence)[frame_index]
            _process_functional_groups(
                functional_groups, 
                lambda tag, value: 
                    tag_values.setdefault(tag, {}).__setitem__(list_index, value), 
                skipped, direct_sequences)

    meta_data = MetaData()
    specific_character_set = odil.Value.Strings()

    # WARNING: we need to process items in tag order since SpecificCharacterSet
    # must be processed before any non-ASCII element is.
    for tag, values_dict in sorted(tag_values.items()):
        # Check whether all values are the same
        all_equal = True
        sample = next(iter(values_dict.values()))
        for i in range(len(data_sets_frame_idx)):
            value = values_dict.get(i)
            if value != sample:
                all_equal = False
                break
        if all_equal:
            # Only use the unique value.
            value = convert_element(sample, specific_character_set)
        else:
            # Convert each value. If we have multiple values of Specific
            # Character Set, use the one from the corresponding data set.
            if (specific_character_set
                    and isinstance(specific_character_set[0], list)):
                value = [
                    convert_element(
                        values_dict.get(idx), specific_character_set[idx])
                    for idx in range(len(data_sets_frame_idx))]
            else:
                value = [
                    convert_element(values_dict.get(idx), 
                        specific_character_set)
                    for idx in range(len(data_sets_frame_idx))]

        if tag == odil.registry.SpecificCharacterSet:
            if value and isinstance(value[0], list):
                specific_character_set = [
                    odil.Value.Strings([x.encode() for x in item]) 
                    for item in value]
            else:
                specific_character_set = odil.Value.Strings(
                    [x.encode() for x in value])
        
        tag_name = get_tag_name(tag)

        meta_data[tag_name] = value
    return meta_data


def cleanup(meta_data):
    """ Clean tags used after the merge
        for example, InstanceNumber is used to sort nifti_tuple in order to preserve the original stack order
    """

    skipped = [
        "InstanceNumber",
    ]
    for x in skipped:
        if x in meta_data:
            del (meta_data[x])


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
    # element can be None because a get is called above
    if element is None:
        result = None
    elif element.empty():
        result = None
    elif element.is_int():
        result = list(element.as_int())
    elif element.is_real():
        result = list(element.as_real())
    elif element.vr == odil.VR.PN:
        data_set = odil.DataSet()
        if specific_character_set:
            data_set.add("SpecificCharacterSet", specific_character_set)
        data_set.add(odil.registry.PersonName, element.as_string(), element.vr)
        json_data_set = json.loads(odil.as_json(data_set))
        result = json_data_set[str(odil.registry.PersonName)]["Value"]
    elif element.is_string():
        result = list(
            odil.as_unicode(x, specific_character_set)
            for x in element.as_string())
    elif element.is_data_set():
        result = [
            convert_data_set(x, specific_character_set)
            for x in element.as_data_set()]
    elif element.is_binary():
        result = [
            base64.b64encode(x.get_memory_view().tobytes()).decode()
            for x in element.as_binary()]
    else:
        raise Exception("Unknown element type")

    return result


def convert_data_set(data_set, specific_character_set):
    """ Convert a DICOM data set to its NIfTI+JSON representation.
    """

    result = {}
    if data_set.has(odil.registry.SpecificCharacterSet):
        specific_character_set = data_set.as_string("SpecificCharacterSet")
    for tag, element in data_set.items():
        name = get_tag_name(tag)
        value = convert_element(element, specific_character_set)
        result[name] = value

    return result

def _process_functional_groups(functional_groups, function, skipped, direct_sequences):
    """ Utility function used in get_meta_data: apply a function on each item
        of functional_groups depending on their status (skipped or direct 
        sequence)
    """
    for sequence_tag in functional_groups:
        if sequence_tag in skipped:
            continue
        functional_group = functional_groups[sequence_tag]
        if sequence_tag in direct_sequences:
            # Nothing to do, use value as is.
            function(sequence_tag, functional_group)
        elif not functional_group.is_data_set():
            # Seen in a private functional group, but should not happen
            if sequence_tag in skipped:
                continue
            function(sequence_tag, functional_group)
        elif not functional_group.empty():
            item = functional_group.as_data_set()[0]
            for item_tag, value in item.items():
                if item_tag in skipped:
                    continue
                function(item_tag, value)
