#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import datetime
import itertools
import re

import dateutil
import odil

from .. import bruker, logger
from . import io

def convert_directory(
        source, destination, reconstructions, dicomdir, multiframe, writer):
    
    # NOTE import the IODs module later to avoid cross-dependence
    from . import iods
    
    directory = bruker.Directory()
    directory.load(source)
    
    # Create series and reconstruction if they are not given in parameters
    if reconstructions is None:
        everything = bruker.Directory.get_series_and_reco(source)
        reconstructions = list(
            itertools.chain.from_iterable(
                itertools.product([int(s)], r) for s,r in everything.items()))

    datasets = {}
    for series, reconstruction in sorted(reconstructions):
        dataset = directory.get_dataset(
            "{}{:04d}".format(series, int(reconstruction)))
        dataset = {k: v.value for k,v in dataset.items()}
            
        type_id = dataset.get("VisuSeriesTypeId", [""])[0]
        if not type_id.startswith("ACQ_"):
            logger.warning(
                "Skipping {}:{} - {} ({}): type is {}".format(
                    series, reconstruction,
                    dataset.get("VisuAcquisitionProtocol", ["(none)"])[0],
                    dataset.get("RECO_mode", ["none"])[0],
                    type_id))
            continue
        datasets[(series, reconstruction)] = dataset

    converters = {
        ("MR", False): iods.mr_image_storage,
        ("MR", True): iods.enhanced_mr_image_storage
    }

    for (series, reconstruction), dataset in sorted(datasets.items()):
        try:
            modality = dataset.get("VisuInstanceModality", [None])[0]
            if not modality:
                logger.info(
                    "reconstruction {}:{} - "
                    "VisuInstanceModality not found in bruker file, "
                    "MRI will be used by default".format(
                        series, reconstruction))
                modality = "MR"
            
            convert_reconstruction(
                directory, series, reconstruction,
                dataset,
                converters[(modality, multiframe)], writer)
            
        except Exception as e:
            logger.error(
                "Could not convert {}:{} - {}".format(
                    series, reconstruction, e))
            logger.debug("Stack trace", exc_info=True)

    if dicomdir and writer.files:
        io.create_dicomdir(
            writer.files, destination, [], [], ["SeriesDescription:3"], [])

def convert_reconstruction(
        bruker_directory, series, reconstruction,
        bruker_dict,
        iod_converter, writer):
    """ Convert and save a single reconstruction.

        :param bruker_directory: Bruker directory object
        :param series: series number in the Bruker directory
        :param reconstruction: reconstruction number in the series
        :param iod_converter: conversion function
        :param transfer_syntax: target transfer syntax
        :param destination: destination directory
        :param iso_9660: whether to use ISO-9660 compatible file names
    """
    
    logger.info("Converting {}:{} - {} ({})".format(
        series, reconstruction, 
        bruker_dict.get("VisuAcquisitionProtocol", ["(none)"])[0],
        bruker_dict.get("RECO_mode", ["none"])[0]
    ))
    bruker_dict["reco_files"] = list(bruker_directory.get_used_files(
        "{}{:04d}".format(series, int(reconstruction))))

    dicom_data_sets = iod_converter(bruker_dict, writer.transfer_syntax)
    
    for dicom_data_set in dicom_data_sets:
        writer(dicom_data_set)

def convert_element(
        bruker_data_set, dicom_data_set, 
        bruker_name, dicom_name, type_, getter, setter,
        frame_index, generator, vr_finder):
    """ Convert a specific element of a bruker_data_set into its
        corresponding equivalent in a odil.DataSet object : 
        dicom_data_set [ dicom_name ] = bruker_data_set [ bruker_name ]

        :param burker_data_set: data set containing the element we want to convert
        :param dicom_data_set: destination odil.DataSet object 
        :param bruker_name: name of the element to convert
        :param dicom_name: corresponding dicom name of the element in the dicom_data_set
        :param type_: Specify the element's requirement in the dicom_data_set
        :param getter: Either a string (to directly give the element to store in the dicom_data_set)
                       or a function (to get a specific frame in a frame group for example)
                       or None (to directly use the get() function on the bruker_data_set object)
        :param setter: Either a dict (in order to directly choose the value to store)
                       or a function (see image.py for examples)
        :param frame_index: index in frame group 
        :param generator: object that will manage the frame_index
        :param vr_finder: function to find the VR knowing only the dicom_name
    """
    
    value = None
    if getter is not None:
        value = getter(bruker_data_set, generator, frame_index)
    else:
        value = bruker_data_set.get(bruker_name)

    if bruker_name in generator.dependent_fields:
    # index of the first FG containing the bruker_name element
        group_index = [
            index for index, x in enumerate(generator.frame_groups) 
            if bruker_name in x[2]][0]
        value = [ value[frame_index[group_index]] ]

    tag = getattr(odil.registry, dicom_name)
    vr = vr_finder(tag)
    
    if value is None:
        if type_ == 1:
            raise Exception("{} must be present".format(dicom_name))
        elif type_ == 2:
            dicom_data_set.add(tag)
    elif vr == odil.VR.SQ and not value:
        # Type of empty value must be explicit
        dicom_data_set.add(tag, odil.Value.DataSets(), vr)
    else:
        if isinstance(setter, dict):
            value = [setter[x] for x in value]
        elif setter is not None:
            value = setter(value)
        
        if odil.is_int(vr):
            value = [int(x) for x in value]
        elif odil.is_real(vr):
            value = [float(x) for x in value]
        elif vr == odil.VR.DA:
            value = [_convert_date_time(x, "%Y%m%d") for x in value]
        elif vr == odil.VR.DT:
            value = [_convert_date_time(x, "%Y%m%d%H%M%S") for x in value]
        elif vr == odil.VR.TM:
            value = [_convert_date_time(x, "%H%M%S") for x in value]
        
        dicom_data_set.add(tag, value, vr)
    
    return value

def _convert_date_time(value, format_):
    expressions = [
        r"^(?P<year>\d{4})-(?P<month>\d{2})-(?P<day>\d{2})"
            r"[ T]"
            r"(?P<hour>\d{2}):(?P<minute>\d{2}):(?P<second>\d{2})"
            r"(?:[.,](?P<microsecond>\d{,6}))?"
            r"(?P<tzinfo>\+\w+)?", 
        r"(?P<year>\d{4})(?P<month>\d{2})(?P<day>\d{2})",
    ]
    date_time = None
    for expression in expressions:
        match = re.match(expression, value)
        if match:
            groups = match.groupdict()
            
            if "microsecond" in groups:
                groups["microsecond"] += (6-len(groups["microsecond"]))*"0"
            elements = {
                g: int(v) for g,v in groups.items()
                if v is not None and g != "tzinfo" }
            tzinfo = groups.get("tzinfo")
            
            if tzinfo:
                elements["tzinfo"] = datetime.datetime.strptime(tzinfo, "%z").tzinfo
            
            date_time = datetime.datetime(**elements)
            
            break
    if date_time is None:
        date_time = dateutil.parser.parse(value.replace(",", "."))
    
    return date_time.strftime(format_)
