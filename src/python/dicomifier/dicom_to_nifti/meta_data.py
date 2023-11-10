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

def get_meta_data(stack, cache=None):
    """ Get the meta-data of the current stack 

        will keep the priority order for repeating element with the following rules:
        low_priority = per_frame_seq
        high_priority = top_level (data_set)
        (if the same element is present in both shared and per_frame,
        we will keep the element of the shared seq)
        
        :param stack: collection of data set and an associated frame number for
            multi-frame datasets
        :param cache: optional cache of meta-data for multi-frame data sets
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
    skipped = {getattr(odil.registry, x) for x in skipped}
    
    # Multi-frame groups to keep as-as in the meta-data (the elements of other
    # multi-frame groups are set at top-level).
    no_recurse = [
        "MRDiffusionSequence"
    ]
    no_recurse = {getattr(odil.registry, x) for x in no_recurse}
    
    if cache is None:
        cache = {}

    # Populate the cache with the elements at top-level and in shared 
    # functional groups
    for data_set, frame in stack:
        sop_instance_uid = data_set[odil.registry.SOPInstanceUID][0]
        if sop_instance_uid in cache:
            continue
            
        cache[sop_instance_uid] = {}
        
        for tag, value in data_set.items():
            if tag in skipped:
                continue
            cache[sop_instance_uid][tag] = value
        if frame is not None:
            groups = data_set[odil.registry.SharedFunctionalGroupsSequence][0]
            _fill_meta_data_dictionary(
                groups, 
                lambda tag, value: cache[sop_instance_uid].update({tag: value}), 
                skipped, no_recurse)

    # Get the values of all (data_set, frame_index)
    elements = {}
    for i, (data_set, frame) in enumerate(stack):
        try:
            sop_instance_uid = data_set[odil.registry.SOPInstanceUID][0]
        except Exception as e:
            raise
        # Fetch non-frame-specific elements from cache
        for tag, element in cache[sop_instance_uid].items():
            elements.setdefault(tag, {})[i] = element
        if frame is not None:
            # Fetch frame-specific elements
            groups = data_set[odil.registry.PerFrameFunctionalGroupsSequence][frame]
            _fill_meta_data_dictionary(
                groups, 
                lambda tag, value: 
                    elements.setdefault(tag, {}).update({i: value}), 
                skipped, no_recurse)
    
    # Convert dictionary with possible holes to list: iteration is quicker.
    elements = {
        tag: [values.get(i) for i in range(len(stack))]
        for tag, values in elements.items()}
        
    meta_data = MetaData()
    specific_character_set = odil.Value.Strings()
    
    # WARNING: we need to process items in tag order since SpecificCharacterSet
    # must be processed before any non-ASCII element is.
    for tag, values in sorted(elements.items()):
        # Check whether all values are the same
        all_equal = (values.count(values[0]) == len(values))
        if all_equal:
            # Only use the unique value.
            value = convert_element(values[0], specific_character_set)
        else:
            # Convert each value. If we have multiple values of Specific
            # Character Set, use the one from the corresponding data set.
            if (specific_character_set
                    and isinstance(specific_character_set[0], list)):
                value = [
                    convert_element(x, specific_character_set[i]) 
                    for i, x in enumerate(values)]
            else:
                value = [
                    convert_element(x, specific_character_set) 
                    for x in values]

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
    elif element.is_int() or element.is_real():
        result = list(element)
    elif element.vr == odil.VR.PN:
        data_set = odil.DataSet()
        if specific_character_set:
            data_set.add(
                odil.registry.SpecificCharacterSet, specific_character_set)
        data_set.add(odil.registry.PersonName, element, element.vr)
        json_data_set = json.loads(odil.as_json(data_set))
        result = json_data_set[str(odil.registry.PersonName)]["Value"]
    elif element.is_string():
        result = [odil.as_unicode(x, specific_character_set) for x in element]
    elif element.is_data_set():
        result = [convert_data_set(x, specific_character_set) for x in element]
    elif element.is_binary():
        result = [
            base64.b64encode(x.get_memory_view().tobytes()).decode()
            for x in element]
    else:
        raise Exception("Unknown element type")

    return result

def convert_data_set(data_set, specific_character_set):
    """ Convert a DICOM data set to its NIfTI+JSON representation.
    """

    result = {}
    if odil.registry.SpecificCharacterSet in data_set:
        specific_character_set = data_set[odil.registry.SpecificCharacterSet]
    for tag, element in data_set.items():
        name = get_tag_name(tag)
        value = convert_element(element, specific_character_set)
        result[name] = value

    return result

def _fill_meta_data_dictionary(data_set, function, skipped, no_recurse):
    for tag, value in data_set.items():
        if tag in skipped:
            continue
        elif value.is_data_set():
            if tag in no_recurse:
                function(tag, value)
            else:
                element = data_set[tag]
                if not element:
                    continue
                item = element[0]
                for item_tag, item_value in item.items():
                    if item_tag not in skipped:
                        function(item_tag, item_value)
        else:
            function(tag, value)
