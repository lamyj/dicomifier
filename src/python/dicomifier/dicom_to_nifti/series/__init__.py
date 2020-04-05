#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

from .series_finder import SeriesFinder
from .default_series_finder import DefaultSeriesFinder
from .siemens_xa_classic_2d_series_finder import SiemensXAClassic2DSeriesFinder

finders = [SiemensXAClassic2DSeriesFinder, DefaultSeriesFinder]


import odil
from ... import logger

def split_series(files):
    logger.info(
        "Splitting {} DICOM file{} in series".format(
            len(files), "s" if len(files) > 1 else ""))
    
    series = {}
    for file_ in files:
        try:
            header, data_set = odil.Reader.read_file(
                file_,  
                halt_condition=lambda x: x>odil.registry.SeriesInstanceUID)
        except odil.Exception as e:
            dicomifier.logger.warning("Could not read {}: {}".format(file_, e))
            continue
        
        uncompressed_ts = [
            getattr(odil.registry, x) for x in [
                "ImplicitVRLittleEndian",
                "ExplicitVRLittleEndian",
                "ExplicitVRBigEndian_Retired"
            ]]
        if header[odil.registry.TransferSyntaxUID][0] not in uncompressed_ts:
            dicomifier.logger.warning(
                "Could not read {}: compressed transfer syntax".format(file_))
            continue
        
        series_instance_uid = None
        finder = None
        
        for finder_class in finders:
            finder = finder_class()
            try:
                series_instance_uid = finder(data_set)
            except Exception as e:
                logger.warning(
                    "Could not run {}: {}".format(finder_class.__name__, e))
                continue
            if series_instance_uid is not None:
                break
        
        if series_instance_uid is None:
            logger.warning("Could not find a series for {}".format(file_))
            continue
        
        series.setdefault(finder, []).append(file_)
    
    return series
