#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

def get_dicom_element(data_set, tag):
    """ Get an element from the dataset, return None if missing.
    """

    result = None
    if data_set.has(tag):
        element = data_set[tag]
        result = None
        if element.is_binary():
            result = element.as_binary()
        elif element.is_data_set():
            result = element.as_data_set()
        elif element.is_int():
            result = element.as_int()
        elif element.is_real():
            result = element.as_real()
        elif element.is_string():
            result = element.as_string()
        elif element.empty():
            result = None
        else:
            raise NotImplementedError("Unknown element type")
    else:
        return None
    return result


from . import convert, image, io, meta_data, series, siemens, stacks
