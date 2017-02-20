#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import collections
import json

import numpy

class MetaData(collections.MutableMapping):
    """ Meta-data for an n-dimensional data set, behaves like a dictionary.
        
        The meta-data is stored in compressed form: assuming the data-set is
        n-dimensional, an m-dimensional meta-data (where m<n) represents a
        n-dimensional meta-data where items in dimensions [m,n] are all equal.
    """
    
    def __init__(self, dictionary=None):
        dictionary = dictionary or {}
        self._dictionary = dictionary.copy()
    
    def __len__(self):
        return self._dictionary.__len__()
        
    def __iter__(self):
        return self._dictionary.__iter__()
    
    def __contains__(self, x):
        return self._dictionary.__contains__(x)
    
    def __getitem__(self, key):
        return self._dictionary.__getitem__(key)
    
    def __setitem__(self, key, value):
        return self._dictionary.__setitem__(key, value)
    
    def __delitem__(self, key):
        return self._dictionary.__delitem__(key)
    
    def expand(self, name, shape):
        """ Expand the meta-data identified by name to match the given shape.
        """
        
        value = self[name]
        # Check the shape of non-repeated values
        if numpy.shape(value)[:-1] != shape[:numpy.ndim(value)-1]:
            raise Exception("Pixel data and meta data not compatible")
        
        # Number of time we need to repeat the value: depends on the unspecified
        # (i.e. last) coordinates
        repeats = shape[-(len(shape)-numpy.ndim(value)+1):]
        repeats = numpy.cumprod(repeats)[-1]
        # Concatenate along the last (innermost) axis
        repeated = numpy.concatenate(repeats*[value], -1)
        # Restore original shape, don't forget that the value at each point is a list
        repeated = repeated.reshape(shape+(-1,))
        
        return repeated
    
    def at(self, name, index):
        """ Return the value of the meta-data identified by name at given index.
            :param index: [z,y,x,...] with z = coordinate in the meta_data "name" element

            Note that index here takes into account the image shape, for example
            meta_data.at(name, [0,2,2]) will return the first meta_data in the field "name" for the image [2,2]
        """
        
        value = numpy.asarray(self[name])
        value_dim = value.ndim
        
        for dimension, coordinate in enumerate(index):
            if dimension < value_dim-1:
                value = value[coordinate]
            else:
                break
        return value
    
    class JSONEncoder(json.JSONEncoder):
        def default(self, obj):
            return obj._dictionary
