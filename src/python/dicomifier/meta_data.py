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

# meta_data_4d = MetaData({
#     "ImageType": ["ORIGINAL", "PRIMARY"],
#     "EchoTime": [[10], [20], [30]],
#     "InstanceNumber": [
#         [[1], [2], [3]],
#         [[4], [5], [6]],
#         [[7], [8], [9]],
#         [[10], [11], [12]],
#         [[13], [14], [15]]
#     ],
# })
# 
# meta_data_3d = MetaData({
#     "ImageType": ["ORIGINAL", "PRIMARY"],
#     "EchoTime": [10],
#     "InstanceNumber": [[1], [2], [3]]
# })
# 
# import numpy
# 
# shape_4d = (5, 3, 2, 4)
# print meta_data_4d.get("ImageType", [0,0,0,0]) # ["ORIGINAL", "PRIMARY"]
# print meta_data_4d.get("ImageType", [0,0,0,1]) # ["ORIGINAL", "PRIMARY"]
# print meta_data_4d.get("ImageType", [0,0,1,1]) # ["ORIGINAL", "PRIMARY"]
# print meta_data_4d.get("ImageType", [0,1,1,1]) # ["ORIGINAL", "PRIMARY"]
# print meta_data_4d.get("ImageType", [1,1,1,1]) # ["ORIGINAL", "PRIMARY"]
# 
# print meta_data_4d.get("EchoTime", [0,0,0,0]) # [10]
# print meta_data_4d.get("EchoTime", [0,0,0,1]) # [10]
# print meta_data_4d.get("EchoTime", [0,0,1,1]) # [10]
# print meta_data_4d.get("EchoTime", [0,1,1,1]) # [10]
# print meta_data_4d.get("EchoTime", [1,1,1,1]) # [20]
# 
# print meta_data_4d.get("InstanceNumber", [0,0,0,0]) # [1]
# print meta_data_4d.get("InstanceNumber", [0,0,0,1]) # [1]
# print meta_data_4d.get("InstanceNumber", [0,0,1,1]) # [1]
# print meta_data_4d.get("InstanceNumber", [0,1,1,1]) # [2]
# print meta_data_4d.get("InstanceNumber", [1,1,1,1]) # [5]
# 
# print meta_data_4d.expand("InstanceNumber", shape_4d)
# 
# print
# 
# shape_3d = (3, 2, 4)
# 
# print meta_data_3d.get("ImageType", [0,0,0]) # ["ORIGINAL", "PRIMARY"]
# print meta_data_3d.get("ImageType", [0,0,1]) # ["ORIGINAL", "PRIMARY"]
# print meta_data_3d.get("ImageType", [0,1,1]) # ["ORIGINAL", "PRIMARY"]
# print meta_data_3d.get("ImageType", [1,1,1]) # ["ORIGINAL", "PRIMARY"]
# 
# print meta_data_3d.get("EchoTime", [0,0,0]) # [10]
# print meta_data_3d.get("EchoTime", [0,0,1]) # [10]
# print meta_data_3d.get("EchoTime", [0,1,1]) # [10]
# print meta_data_3d.get("EchoTime", [1,1,1]) # [10]
# 
# print meta_data_3d.get("InstanceNumber", [0,0,0]) # [1]
# print meta_data_3d.get("InstanceNumber", [0,0,1]) # [1]
# print meta_data_3d.get("InstanceNumber", [0,1,1]) # [1]
# print meta_data_3d.get("InstanceNumber", [1,1,1]) # [2]
# 
# print meta_data_3d.expand("InstanceNumber", shape_3d)
