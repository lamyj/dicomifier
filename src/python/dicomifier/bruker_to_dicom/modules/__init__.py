#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

def cached(key):
    """ Cache the results of a conversion in the data set.
    """
    def wrapper(function):
        def wrapped(d,g,i):
            if key not in d:
                d[key] = function(d,g,i)
            return d[key]
        return wrapped
    return wrapper


from . import equipment, frame_of_reference, image, mr, patient, series, study
