#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import json

import numpy
import odil

def getter(data_set, tag):
    """ Get an element from the dataset, 
        raise an exception if element not found, or unrecognized

        :param data_set: dataset wherein search the element
        :param tag: tag of the element looked for
    """

    # List is not hashable, use tuple instead
    result = None
    if data_set.has(tag):
        element = data_set[tag]
        result = None
        if element.is_binary():
            result = tuple(element.as_binary())
        elif element.is_data_set():
            result = tuple(element.as_data_set())
        elif element.is_int():
            result = tuple(element.as_int())
        elif element.is_real():
            result = tuple(element.as_real())
        elif element.is_string():
            result = tuple(element.as_string())
        elif element.empty():
            result = None
        else:
            return None
    else:
        return None
    return result

class OrientationGetter(object):

    def __init__(self):
        self._orientations = {}

    def __call__(self, data_set, tag):
        value = getter(data_set, tag)
        if value is None:
            return None
        orientation = numpy.reshape(value, (2, -1))
        normal = numpy.cross(*orientation)

        closest = None
        for candidate in self._orientations.items():
            if OrientationGetter._comparator(normal, candidate[0]):
                closest = candidate[1]
                break

        if closest is None:
            self._orientations[tuple(normal)] = value
        else:
            value = closest

        return tuple(value)

    @staticmethod
    def _comparator(o1, o2, epsilon=0.05):
        if numpy.shape(o1) == (0,) and numpy.shape(o2) == (0,):
            return True
        elif any(numpy.shape(x) == (0,) for x in (o1, o2)):
            return False
        else:
            return (
                numpy.linalg.norm(numpy.subtract(o1, o2), numpy.inf) <= epsilon)

def check_frame_index(data_set, frame_idx):
    if data_set.has("NumberOfFrames"):
        numberOfFrames = data_set.as_int("NumberOfFrames")[0]
        if frame_idx >= numberOfFrames :
            raise Exception("Frame index out of bound ({}/{})".format(frame_idx, numberOfFrames))
    else:
        raise Exception("No NumberOfFrames field found")

def get_position(data_set, frame_idx):
    """ Get the position of the wanted frame in the data set
        :param data_set: Data_set containing the wanted frame
        :param frame_idx: Index of the wanted frame
    """

    if data_set.has(odil.registry.PerFrameFunctionalGroupsSequence) and \
            data_set.has(odil.registry.NumberOfFrames):
        check_frame_index(data_set, frame_idx)
        frame = data_set.as_data_set(
            odil.registry.PerFrameFunctionalGroupsSequence)[frame_idx]
        if frame.has(odil.registry.PlanePositionSequence):
            plane_position_seq = frame.as_data_set(
                odil.registry.PlanePositionSequence)[0]
        else:
            return None
    else:
        plane_position_seq = data_set
    if not plane_position_seq.has(odil.registry.ImagePositionPatient):
        return None
    return(plane_position_seq.as_real(odil.registry.ImagePositionPatient))

def get_dimension_index_seq(frame_content_seq, tag, in_stack_position_index):
    """ Will return the dimension index pointer without InStackPosition
        in order to find the different volumes

        :param frame_content_seq: sequence containing the dimensionIndexValues
        :param tag: will DimensionIndexValues in this case
        :param in_stack_position_index: index of the InStackPosition element 
                                        within the dimensionIndexValues tuple

        :return dimension_idx_values without the InStackPosition element
    """

    if frame_content_seq.has(tag):
        dimension_idx_values = list(frame_content_seq.as_int(tag))
        if in_stack_position_index is not None:
            del(dimension_idx_values[in_stack_position_index])
            return tuple(dimension_idx_values)
        else:
            raise Exception(
                "Dimension Index Values found in Frame content but there is no InStackPosition")
    return None

def get_in_stack_position_index(data_set):
    """ Will return the position of in-Stack-Position element in the dimensionIndexValue
        Return None if no In-Stack-Position found
    """

    if data_set.has(odil.registry.DimensionIndexSequence) and \
            not data_set.empty(odil.registry.DimensionIndexSequence):
        dimension_index_sequences = data_set.as_data_set(
            odil.registry.DimensionIndexSequence)
        position = set()
        for i, dimension_index_sequence in enumerate(dimension_index_sequences):
            if dimension_index_sequence.has(odil.registry.DimensionIndexPointer):
                idx = dimension_index_sequence.as_string(odil.registry.DimensionIndexPointer)[0]
                if odil.Tag(idx) == odil.registry.InStackPositionNumber:
                    position.add(i)
        if len(position) == 1:
            return list(position)[0]
        else:
            return None
    else:
        return None

def diffusion_getter(data_set, tag):
    """ Get Diffusion information from the data_set

        :param data_set: data_set wherein read the diffusion information
        :param tag: tag used to store the diffusion information in the data_set
    """

    value = getter(data_set, tag)
    if value is not None:
        b_value = getter(value[0], odil.registry.DiffusionBValue)
        directionality = getter(
            value[0], odil.registry.DiffusionDirectionality)[0]
        sensitization = None
        if directionality == b"DIRECTIONAL":
            item = getter(
                value[0], odil.registry.DiffusionGradientDirectionSequence)[0]
            sensitization = getter(
                item, odil.registry.DiffusionGradientOrientation)
        elif directionality == b"BMATRIX":
            item = getter(value[0], odil.registry.DiffusionBMatrixSequence)[0]
            sensitization = tuple(
                getter(item, getattr(odil.registry, "DiffusionBValue{}".format(x)))[0]
                for x in ["XX", "XY", "XZ", "YY", "YZ", "ZZ"])
        elif directionality == b"ISOTROPIC" or directionality == b"NONE":
            return None
        else:
            raise Exception(
                "Unknown directionality: {}".format(directionality))
        value = (b_value, sensitization)
    return value

def frame_group_index_getter(data_set, tag):
    value = getter(data_set, tag)
    if value is None:
        return value
    
    frame_group_index_entries = [
        x for x in value 
        if (
            x.as_string("Manufacturer")[0] == b"Dicomifier"
            and x.as_string("ManufacturerModelName")[0] == b"Bruker Frame Group index")]
    if not frame_group_index_entries:
        return None
    elif len(frame_group_index_entries) > 1:
        raise Exception("Multiple Frame Group index entries found")
    
    contribution_description = json.loads(
        frame_group_index_entries[0].as_string("ContributionDescription")[0].decode())
    
    index = tuple(tuple(x) for x in contribution_description)
    return index
