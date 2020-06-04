#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

class SeriesFinder(object):
    """ Base class for all series finders.
    """
    
    def __init__(self):
        self.series_instance_uid = None
    
    def __eq__(self, other):
        return self.series_instance_uid == other.series_instance_uid
    
    def __hash__(self):
        return hash(self.series_instance_uid)
