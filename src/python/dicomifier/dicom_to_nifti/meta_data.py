#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import itertools

import odil

def get_nifti_meta_data(data_sets, key):
    meta_data = [convert_meta_data(x) for x in data_sets]
    
    named_key = []
    for item in key:
        name = item[0]
        try:
            name = odil.Tag(name).get_name()
        except odil.Exception as e:
            pass
        named_key.append(name)
            
    return merge_meta_data(meta_data, named_key)

def convert_meta_data(data_set):
    meta_data = {}
    
    skipped = [
        "Rows", "Columns", 
        "ImageOrientationPatient", "ImagePositionPatient", "PixelSpacing",
        "SOPInstanceUID", 
        "PixelRepresentation", "HighBit", "BitsStored", "BitsAllocated",
        "PixelData",
        "PixelValueTransformationSequence",
        "SmallestImagePixelValue", "LargestImagePixelValue",
    ]
    
    for key, value in data_set.items():
        try:
            key = odil.Tag(key.encode()).get_name()
        except odil.Exception:
            # Keep string version
            pass
        
        if key in skipped:
            continue
        
        converted_value = None
        if "Value" in value:
            if value["vr"] == "SQ":
                converted_value = [convert_meta_data(x) for x in value["Value"]]
            else:
                converted_value = value["Value"]
        elif "InlineBinary" in value:
            value = value["InlineBinary"]
            converted_value = value
        else:
            converted_value = None
        
        meta_data[key] = converted_value
    
    return meta_data

def merge_meta_data(data_sets, key):
    merged = {}
    
    tags = set(itertools.chain(*[x.keys() for x in data_sets]))
    for tag in tags:
        multiplicity = "unknown"
        try:
            multiplicity = odil.registry.public_dictionary[
                getattr(odil.registry, tag)].vm
        except:
            # Nothing is known about the multiplicity
            pass
        
        merged_value = None
        if tag in key:
            if multiplicity == "1":
                merged_value = data_sets[0][tag]
            else:
                merged_value = data_sets[0][tag]
        else:
            merged_value = []
            for data_set in data_sets:
                value = data_set.get(tag, None)
                if value is not None and multiplicity == "1":
                    value = value[0]
                merged_value.append(value)
            
            if all(x == merged_value[0] for x in merged_value):
                merged_value = merged_value[0]
        merged[tag] = merged_value
    
    return merged
