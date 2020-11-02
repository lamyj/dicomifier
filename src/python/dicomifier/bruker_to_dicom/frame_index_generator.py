#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import itertools

import numpy

class FrameIndexGenerator(object):
    """ Generate the indices to iterate through the frame groups of a Bruker
        data set.
    """
    
    def __init__(self, data_set):
        self._frame_groups = []
        self._frames_count = 0
        self._dependent_fields = []
        self._strides = []
        
        frame_groups = []
        for description in data_set.get("VisuFGOrderDesc", []):
            frame_count, name, _, begin, fields_count = description
            if fields_count == 0:
                # This may happen with Paravision 5
                fields = []
            else:
                fields = [
                    x[0] for x in 
                    data_set["VisuGroupDepVals"][begin:begin+fields_count]]
            frame_groups.append([frame_count, name, fields])
        # WARNING: the frame groups are listed in innermost-to-outermost
        # order, while FrameIndexGenerator uses outermost-to-innermost order.
        # Invert now, to match the order of FrameIndexGenerator.
        self.frame_groups = frame_groups[::-1]
    
    def __iter__(self):
        return itertools.product(
            *[range(count) for count, _, _ in self.frame_groups])
    
    def get_linear_index(self, index):
        """ Return the linear index associated to the multi-dimensional index.
        """
        
        return numpy.dot(index[::-1], self._strides) if self._frames_count else 0
    
    @property
    def frame_groups(self):
        return self._frame_groups
    
    @frame_groups.setter
    def frame_groups(self, value):
        self._frame_groups = value
        
        shape = [count for count, _, _ in self._frame_groups][::-1]
        
        self._frames_count = numpy.cumprod(shape)[-1] if shape else 0
        self._dependent_fields = list(
            itertools.chain(*[fields for _, _, fields in self.frame_groups]))
        self._strides = numpy.cumprod([1]+shape[:-1])
    
    @property
    def frames_count(self):
        """ Total number of frames.
        """
        
        return max(1, self._frames_count)
    
    @property
    def dependent_fields(self):
        """ Names of all fields mentioned in the frame groups.
        """
        
        return self._dependent_fields
