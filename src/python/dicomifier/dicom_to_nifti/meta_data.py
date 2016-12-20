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
import odil_getter

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
        :param cache: used to store (tag,elem) for top priority sequences (top level & shared) in order to 
                      parse them only once per data_set
    """

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
        "SharedFunctionalGroupsSequence",
        "PerFrameFunctionalGroupsSequence",
    ]

    skipped = [getattr(odil.registry, x) for x in skipped]
    skipped = [(x.group, x.element) for x in skipped]

    # Must get directly this sequence (otherwise test fails)
    direct_sequences = [
        "MRDiffusionSequence"
    ]
    direct_sequences = [getattr(odil.registry, x) for x in direct_sequences]
    direct_sequences = [(x.group, x.element) for x in direct_sequences]

    tag_values = {}
    # Parse here all data_set, and all tags, in order to get top priority
    # level values with index
    for i, data_set_frame_idx in enumerate(data_sets_frame_idx):
        in_cache = True
        data_set, frame_idx = data_set_frame_idx
        sop_instance_uid = data_set.as_string(odil.registry.SOPInstanceUID)[0]
        priority_seq = []  # tuple (dataset, prio level)
        if sop_instance_uid not in [x[0] for x in cache.keys()]:
            priority_seq.append((data_set, 0))
            in_cache = False
        if frame_idx != None:
            per_frame = data_set.as_data_set(
                odil.registry.PerFrameFunctionalGroupsSequence)[frame_idx]
            if not in_cache:
                shared = data_set.as_data_set(
                    odil.registry.SharedFunctionalGroupsSequence)[0]
                priority_seq.append((shared, 1))
            priority_seq.append((per_frame, 2))

        if in_cache:
            # Pre fill the tag_values if data_set is in cache
            for (sop, tag), element in cache.iteritems():
                if sop == sop_instance_uid:
                    tag_values.setdefault(tag, {})[i] = element

        seq_s = []
        for (top_seq, prio_level) in priority_seq:
            seq_s.append(top_seq)
            for seq in seq_s:
                for tag, elem in seq.items():
                    tag_ = (tag.group, tag.element)
                    if tag_ not in skipped:
                        if seq.is_data_set(tag) and tag_ not in direct_sequences:
                            seq_s.append(seq.as_data_set(tag)[0])
                        else:
                            tag_values.setdefault(tag_, {})[i] = elem
                            if in_cache == False and prio_level in [0, 1]:
                                # Store only in cache for Top and Shared levels
                                cache[(sop_instance_uid, tag_)] = elem

    meta_data = MetaData()
    specific_character_set = []

    for tag, values_dict in tag_values.items():
        tag_object = odil.Tag(*tag)

        # Check whether all values are the same
        all_equal = True
        sample = values_dict[0]
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
    # element can be None because a get is called above
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
