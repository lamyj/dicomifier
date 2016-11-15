#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import odil
import numpy


def _default_getter(data_set, tag):
    """ Get an element from the dataset, but don't raise any exception if not found

        :param data_set: datast wherein search the element
        :param tag: tag of the element looked for
    """

    try:
        return _getter(data_set, tag)
    except odil.Exception:
        pass
    return None


def _getter(data_set, tag):
    """ Get an element from the dataset, 
        raise an exception if element not found, or unrecognized

        :param data_set: dataset wherein search the element
        :param tag: tag of the element looked for
    """

    # List is not hashable, use tuple instead
    result = None
    if data_set.has(tag):
        if (data_set.is_binary(tag)):
            result = tuple(data_set.as_binary(tag))
        elif (data_set.is_data_set(tag)):
            result = tuple(data_set.as_data_set(tag))
        elif (data_set.is_int(tag)):
            result = tuple(data_set.as_int(tag))
        elif (data_set.is_real(tag)):
            result = tuple(data_set.as_real(tag))
        elif (data_set.is_string(tag)):
            result = tuple(data_set.as_string(tag))
        elif data_set.empty(tag):  # present but empty
            result = None
        else:
            raise odil.Exception("Unknown element type")
    else:
        raise odil.Exception("No such element")
    return result


class OrientationGetter(object):

    def __init__(self):
        self._orientations = {}

    def __call__(self, data_set, tag):
        value = _getter(data_set, tag)
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
        if (o1, o2) == ((), ()):
            return True
        elif () in (o1, o2):
            return False
        else:
            return (numpy.linalg.norm(numpy.subtract(o1, o2), numpy.inf) <= epsilon)


def _diffusion_getter(data_set, tag):
    """ Get Diffusion information from the data_set

        :param data_set: data_set wherein read the diffusion information
        :param tag: tag used to store the diffusion information in the data_set
    """
    value = _default_getter(data_set, tag)
    if value is not None:
        b_value = _getter(value[0], odil.registry.DiffusionBValue)
        directionality = _getter(
            value[0], odil.registry.DiffusionDirectionality)[0]
        sensitization = None
        if directionality == "DIRECTIONAL":
            item = _getter(
                value[0], odil.registry.DiffusionGradientDirectionSequence)[0]
            sensitization = _getter(
                item, odil.registry.DiffusionGradientOrientation)
        elif directionality == "BMATRIX":
            item = _getter(value[0], odil.registry.DiffusionBMatrixSequence)[0]
            sensitization = tuple([_getter(item, getattr(odil.registry, "DiffusionBValue{}".format(x)))[0]
                                   for x in ["XX", "XY", "XZ", "YY", "YZ", "ZZ"]])
        else:
            raise Exception(
                "Unknown directionality: {}".format(directionality))
        value = (b_value, sensitization)
    return value
