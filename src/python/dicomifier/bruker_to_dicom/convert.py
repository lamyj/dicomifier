#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import datetime
import itertools
import logging
import re

import dateutil
import numpy
import odil

from .. import bruker, logger
from . import io

def convert_directory(source, destination, dicomdir, multiframe, writer):
    """ Convert a Bruker directory to DICOM and write the files.
        
        :param source: source directory
        :param destination: destination directory
        :param dicomdir: whether to create a DICOMDIR
        :param multiframe: whether to create multi-frame DICOM objects
        :param writer: writer object from the io module
    """
    
    # NOTE import the IODs module late to avoid cross-dependence
    from . import iods
    
    known_files = [
        "subject", "acqp", "method", "imnd", "isa", "d3proc", "reco", 
        "visu_pars"]
    
    # Look for 2dseq as it contains the pixel data
    data_sets = {}
    for path in source.rglob("2dseq"):
        data_set = bruker.Dataset()
        for name in known_files:
            for directory in list(path.parents)[:3][::-1]:
                file_ = directory/name
                if file_.is_file():
                    try:
                        data_set.load(str(file_))
                    except Exception as e:
                        logger.info("Could not load {}: {}".format(file_, e))
        
        reco_files = data_set.get_used_files()    
        data_set = {k:v.value for k,v in data_set.items()}
        data_set["PIXELDATA"] = [path]
        data_set["reco_files"] = reco_files
        
        if not all(x in data_set for x in ["VisuStudyUid", "VisuUid"]):
            logger.info("Skipping {}: missing UIDs".format(path.parent))
            continue
        
        data_sets[path.parent] = data_set
    
    converters = {
        ("MR", False): iods.mr_image_storage,
        ("MR", True): iods.enhanced_mr_image_storage
    }
    
    for path, data_set in sorted(data_sets.items()):
        # TODO: parallelize (easy since dataset is a dict)
        logger_context = ReconstructionContext(path)
        logger.addFilter(logger_context)
        
        try:
            modality = data_set.get("VisuInstanceModality", [None])[0]
            if not modality:
                logger.info("Modality not found in data set, defaulting to MR")
                modality = "MR"
            
            convert_reconstruction(
                data_set, converters[(modality, multiframe)], writer)
        except Exception as e:
            logger.error("Could not convert: {}".format(e))
            logger.debug("Stack trace", exc_info=True)
        
        logger.removeFilter(logger_context)

    if dicomdir and writer.files:
        io.create_dicomdir(
            writer.files, destination, [], [], ["SeriesDescription:3"], [])

def convert_reconstruction(data_set, iod_converter, writer):
    """ Convert and save a single reconstruction.

        :param iod_converter: conversion function
        :param writer: writer object from the io module
    """
    
    logger.info("Converting {} ({})".format(
        data_set.get("VisuAcquisitionProtocol", ["(none)"])[0],
        data_set.get("RECO_mode", ["none"])[0]
    ))
    
    dicom_data_sets = iod_converter(data_set, writer.transfer_syntax)
    
    for dicom_data_set in dicom_data_sets:
        writer(dicom_data_set)

def convert_module(
        bruker_data_set, dicom_data_set, module,
        frame_index, generator, vr_finder):
    """ Convert a DICOM module..

        :param bruker_data_set: source Bruker data set
        :param dicom_data_set: destination DICOM data set
        :param module: sequence of 5-element tuples describing the conversions
            (Bruker name, DICOM name, DICOM type, getter and setter)
        :param frame_index: index in a frame group
        :param generator: object that will manage the frame_index
        :param vr_finder: function to find the VR knowing only the dicom_name
    """

    for bruker_name, dicom_name, type_, getter, setter in module:
        convert_element(
            bruker_data_set, dicom_data_set, 
            bruker_name, dicom_name, type_, getter, setter,
            frame_index, generator, vr_finder)
    return dicom_data_set

def convert_element(
        bruker_data_set, dicom_data_set, 
        bruker_name, dicom_name, type_, getter, setter,
        frame_index, generator, vr_finder):
    """ Convert a Bruker element to a DICOM element.

        :param bruker_data_set: source Bruker data set
        :param dicom_data_set: destination DICOM data set
        :param bruker_name: Bruker name of the element
        :param dicom_name: DICOM name of the element
        :param type_: DICOM type of the element (PS 3.5, 7.4)
        :param getter: function returning the value using the Bruker data set,
            the generator and the frame index or None (direct access)
        :param setter: mapping or function transforming the Bruker value 
            to a DICOM value, or None (no transformation performed)
        :param frame_index: index in frame group 
        :param generator: FrameIndexGenerator associated with the 
            Bruker data set
        :param vr_finder: function returning the DICOM VR from the dicom_name
    """
    
    value = None
    if getter is not None:
        value = getter(bruker_data_set, generator, frame_index)
    else:
        value = bruker_data_set.get(bruker_name)

    if bruker_name in generator.dependent_fields:
        # Frame-dependent value: get the correct item from the frame_index
        group_index = [
            index for index, (_, _, fields) in enumerate(generator.frame_groups) 
            if bruker_name in fields][0]
        value = [ value[frame_index[group_index]] ]

    tag = getattr(odil.registry, dicom_name)
    vr = vr_finder(tag)
    
    if value is None:
        if type_ == 1:
            raise Exception("{} must be present".format(dicom_name))
        elif type_ == 2:
            dicom_data_set.add(tag)
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
            value = [_convert_date_time(x, "%Y%m%d") for x in value if x]
        elif vr == odil.VR.DT:
            value = [_convert_date_time(x, "%Y%m%d%H%M%S") for x in value if x]
        elif vr == odil.VR.TM:
            value = [_convert_date_time(x, "%H%M%S") for x in value if x]
        
        dicom_data_set.add(tag, value, vr)
    
    return value

def _convert_date_time(value, format_):
    """ Parse the date and time in value, and return it formatted as specified.
    """
    
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

def to_2d(data_set):
    """ Convert the Bruker data set from 3D to 2D.
    """
    
    origin = data_set["VisuCorePosition"]
    z = numpy.asarray(data_set["VisuCoreOrientation"][6:9])
    dz = numpy.divide(
        numpy.asarray(data_set["VisuCoreExtent"][2], dtype=float),
        numpy.asarray(data_set["VisuCoreSize"][2], dtype=float))
    
    frame_count = int(data_set.get("VisuCoreFrameCount", [1])[0])
    slice_count = int(data_set["VisuCoreSize"][2])
    
    # Constant fields
    data_set["VisuCoreDim"] = [2]
    data_set["VisuCoreFrameCount"] = [frame_count*slice_count]

    # Frame groups
    groups = data_set.get("VisuFGOrderDesc", [])
    fields = data_set.get("VisuGroupDepVals", [])

    groups = [[slice_count, "FG_SLICE", "", 0, 2]] + [
        [count, name, comment, 2+start, length]
        for count, name, comment, start, length in groups]
    fields = [["VisuCoreOrientation", 0], ["VisuCorePosition", 0] ] + fields

    data_set["VisuFGOrderDescDim"] = [len(groups)]
    data_set["VisuFGOrderDesc"] = groups
    data_set["VisuGroupDepVals"] = fields

    # Sliced fields: subsets of original fields
    sliced_fields = [
        "VisuCoreSize", "VisuCoreDimDesc", "VisuCoreExtent", "VisuCoreUnits"]
    for name in sliced_fields:
        data_set[name] = data_set[name][0:2]

    # Repeated fields: repeat the same value for each slice
    repeated_fields = [
        ("VisuCoreDataMin", (1,)), ("VisuCoreDataMax", (1,)),
        ("VisuCoreDataOffs", (1,)), ("VisuCoreDataSlope", (1,)),
        ("VisuCoreOrientation", (9,))
    ]
    for name, shape in repeated_fields:
        if name not in data_set:
            continue

        value = numpy.reshape(data_set[name], (-1,)+shape)
        data_set[name] = list(
            itertools.chain(*
                [slice_count*x.tolist() for x in value]
            )
        )
    
    # Special case: position, depending on origin, dz and z
    data_set["VisuCorePosition"] = list(itertools.chain(*[
        (origin+i*dz*z).tolist() for i in range(slice_count)
    ]))

class ReconstructionContext(logging.Filter):
    """ Add reconstruction context to logger. 
    """
    
    def __init__(self, path):
        logging.Filter.__init__(self)
        self.prefix = "{} - ".format(path)
        
    def filter(self, record):
        record.msg = "{}{}".format(self.prefix, record.msg)
        return True
