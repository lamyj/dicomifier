#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import odil

from .series_finder import SeriesFinder

class DefaultSeriesFinder(SeriesFinder):
    def __init__(self):
        SeriesFinder.__init__(self)
    
    def __call__(self, data_set):
        self.series_instance_uid = None
        if odil.registry.SeriesInstanceUID in data_set:
            value = data_set[odil.registry.SeriesInstanceUID]
            if len(value) == 0:
                raise Exception(
                    "Invalid DICOM data set: SeriesInstanceUID is empty")
            elif len(value) > 1:
                raise Exception(
                    "Invalid DICOM data set: "
                    "multiple values of SeriesInstanceUID")
            else:
                self.series_instance_uid = value[0]
        return self.series_instance_uid
