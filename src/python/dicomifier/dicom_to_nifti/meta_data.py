#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import itertools

import numpy
import odil

from .. import MetaData

def get_meta_data(data_sets):
    """ Return the merged meta-data from the DICOM data sets in the NIfTI+JSON
        format: a dictionary keyed by the DICOM keyword (or the string 
        representation of the tag if no keyword is found) and valued by the 
        Value (or InlineBinary) of the DICOM elements.
    """
    
    meta_data = [convert_meta_data(x) for x in data_sets]
    
    merged = merge_meta_data(meta_data)

    named_meta_data = {}
    for key, value in merged.items():
        try:
            key = odil.Tag(key.encode()).get_name()
        except odil.Exception as e:
            # Keep numeric tag
            pass
        named_meta_data[key] = value

    return named_meta_data

def convert_meta_data(data_set):
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
    
    for key, value in data_set.items():
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

def merge_meta_data(data_sets):
    """ Merge the meta-data of DICOM data sets if they are equal.
    """
    
    merged = {}
    
    tags = set(itertools.chain(*[x.keys() for x in data_sets]))
    for tag in tags:
        merged_value = []
        for data_set in data_sets:
            value = data_set.get(tag, None)
            merged_value.append(value)

        if all(x == merged_value[0] for x in merged_value):
            merged_value = merged_value[0]
        merged[tag] = merged_value
    
    return MetaData(merged)
