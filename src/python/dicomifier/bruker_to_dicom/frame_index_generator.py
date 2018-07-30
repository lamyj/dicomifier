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
        """ Constructor.
        """
        
        self.frame_groups = FrameIndexGenerator._get_frame_groups(data_set)
    
    def __iter__(self):
        """ Iterate through the frame groups.
        """
        
        return itertools.product(*[range(x[0]) for x in self.frame_groups])
    
    def get_linear_index(self, index):
        """ Return the linear index associated to the multi-dimensional index.
        """
        
        index = index[::-1]
        shape = [x[0] for x in self.frame_groups[::-1]]
        
        factor = 1
        linear_index = 0
        for dim, x in enumerate(index):
            linear_index += factor*x
            factor *= shape[dim]
        
        return linear_index
    
    def _get_frames_count(self):
        """ Return the total number of frames.
        """
        
        return functools.reduce(lambda x,y: x*y[0], self.frame_groups, 1)
    frames_count = property(_get_frames_count)
    
    def _get_dependent_fields(self):
        """ Return the name of fields mentioned in the frame groups.
        """
        
        return itertools.chain(*[x[2] for x in self.frame_groups])
    dependent_fields = property(_get_dependent_fields)
    
    @staticmethod
    def _get_frame_groups(data_set):
        """ Return the frame groups, as a list of [count, name, fields].
        """
        
        frame_groups = []
        for description in data_set.get("VisuFGOrderDesc", []):
            frame_count, name, _, begin, fields_count = description
            if fields_count == 0:
                fields = []
            else:
                fields = [
                    x[0] for x in 
                    data_set["VisuGroupDepVals"][begin:begin+fields_count]]
            frame_groups.append([frame_count, name]+[fields])
        # CAUTION: the frame groups are listed in innermost-to-outermost
        # order, while FrameIndexGenerator uses outermost-to-innermost order.
        # Invert now, to match the order of FrameIndexGenerator.
        return frame_groups[::-1]
