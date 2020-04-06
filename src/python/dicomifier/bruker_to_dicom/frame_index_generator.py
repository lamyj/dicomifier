#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import functools
import itertools

class FrameIndexGenerator(object):
    """ Generate the indices to iterate through the frame groups of a Bruker
        data set.
    """
    
    def __init__(self, data_set):
        frame_groups = []
        for description in data_set.get("VisuFGOrderDesc", []):
            frame_count, name, _, begin, fields_count = description
            fields = [
                x[0] for x in 
                data_set["VisuGroupDepVals"][begin:begin+fields_count]]
            frame_groups.append([frame_count, name, fields])
        # WARNING: the frame groups are listed in innermost-to-outermost
        # order, while FrameIndexGenerator uses outermost-to-innermost order.
        # Invert now, to match the order of FrameIndexGenerator.
        self.frame_groups =  frame_groups[::-1]
    
    def __iter__(self):
        return itertools.product(
            *[range(count) for count, _, _ in self.frame_groups])
    
    def get_linear_index(self, index):
        """ Return the linear index associated to the multi-dimensional index.
        """
        
        index = index[::-1]
        shape = [count for count, _, _ in self.frame_groups[::-1]]
        
        factor = 1
        linear_index = 0
        for dim, x in enumerate(index):
            linear_index += factor*x
            factor *= shape[dim]
        
        return linear_index
    
    @property
    def frames_count(self):
        """ Total number of frames.
        """
        
        shape = [count for count, _, _ in self.frame_groups]
        return functools.reduce(lambda x,y: x*y, shape, 1)
    
    @property
    def dependent_fields(self):
        """ Names of all fields mentioned in the frame groups.
        """
        
        return itertools.chain(*[fields for _, _, fields in self.frame_groups])
