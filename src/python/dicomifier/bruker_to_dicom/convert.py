#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import json
import logging
import math
import re
import os

import dateutil
import odil

from .. import bruker

vr_converters = {
    "DA": lambda x: dateutil.parser.parse(x.replace(",", ".")).strftime("%Y%m%d"),
    "DS": lambda x: float(x),
    "FD": lambda x: float(x),
    "FL": lambda x: float(x),
    "IS": lambda x: int(x),
    "PN": lambda x: {"Alphabetic": x},
    "TM": lambda x: dateutil.parser.parse(x.replace(",", ".")).strftime("%H%M%S"),
}

def convert_reconstruction(
        bruker_directory, series, reconstruction,
        iod_converter, transfer_syntax,
        destination, iso_9660, layout):
    """ Convert and save a single reconstruction.

        :param bruker_directory: Bruker directory object
        :param series: series number in the Bruker directory
        :param reconstruction: reconstruction number in the series
        :param iod_converter: conversion function
        :param transfer_syntax: target transfer syntax
        :param destination: destination directory
        :param iso_9660: whether to use ISO-9660 compatible file names
        :param layout: file layout in destination directory ("flat" or "hierarchical")
    """
    
    logging.info("Converting {}:{}".format(series, reconstruction))
    
    bruker_binary = bruker_directory.get_dataset(
        "{}{:04d}".format(series, int(reconstruction)))
    bruker_json = json.loads(bruker.as_json(bruker_binary))
    logging.info("Found {}:{} - {} ({})".format(
        series, reconstruction, 
        bruker_json.get("VisuAcquisitionProtocol", ["(none)"])[0],
        bruker_json.get("RECO_mode", ["none"])[0]
    ))

    dicom_jsons = iod_converter(bruker_json, transfer_syntax)

    logging.info(
        "Writing {} dataset{}".format(
            len(dicom_jsons), "s" if len(dicom_jsons)>1 else ""))
    
    files = []
    for index, dicom_json in enumerate(dicom_jsons):
        dicom_binary = odil.from_json(json.dumps(dicom_json))
        
        if iso_9660:
            filename = "IM{:06d}".format(1+index)
        else:
            filename = dicom_binary.as_string("SOPInstanceUID")[0]
        
        if layout == "flat":
            destination_file = os.path.join(destination, filename)
        elif layout == "hierarchical":
            destination_file = os.path.join(
                destination, get_series_directory(dicom_binary, iso_9660),
                filename)
        else:
            raise Exception("Unknown layout: {}".format(layout))
        
        if not os.path.isdir(os.path.dirname(destination_file)):
            os.makedirs(os.path.dirname(destination_file))

        odil.write(
            dicom_binary, destination_file, 
            transfer_syntax=transfer_syntax)
        files.append(destination_file)
    
    return files

def convert_element(
        bruker_data_set, dicom_data_set, 
        bruker_name, dicom_name, type_, getter, setter,
        frame_index, generator, vr_finder):
    value = None
    if getter is not None:
        if isinstance(getter, basestring):
            value = getter
        else:
            value = getter(bruker_data_set, generator, frame_index)
    else:
        value = bruker_data_set.get(bruker_name)

    if bruker_name in generator.dependent_fields:
        group_index = [
            index for index, x in enumerate(generator.frame_groups) 
            if bruker_name in x[2]][0]
        value = [ value[frame_index[group_index]] ]

    tag = str(getattr(odil.registry, dicom_name))
    vr = str(vr_finder(dicom_name))

    if value is None:
        if type_ == 1:
            raise Exception("{} must be present".format(dicom_name))
        elif type_ == 2:
            dicom_data_set[tag] = {"vr": vr}
        elif type_ == 3:
            # May be absent
            pass
    else:
        dicom_data_set[tag] = {"vr": vr}
        if isinstance(setter, dict):
            value = [setter[x] for x in value]
        elif setter is not None:
            value = setter(value)
        
        vr_converter = vr_converters.get(vr)
        if vr_converter is not None:
            value = [vr_converter(x) for x in value]
        
        if vr in ["OB", "OD", "OF", "OL", "OW"]:
            dicom_data_set[tag]["InlineBinary"] = value[0]
        else:
            dicom_data_set[tag]["Value"] = value
    
    return value

def get_series_directory(data_set, iso_9660):
    """ Return the directory associated with the patient, study and series of
        the DICOM data set.
    """

    # Patient directory: <PatientName> or <PatientID>.
    patient_directory = None
    if "PatientName" in data_set and data_set.as_string("PatientName"):
        patient_directory = data_set.as_string("PatientName")[0]
    else:
        patient_directory = data_set.as_string("PatientID")[0]

    # Study directory: <StudyID>_<StudyDescription>, both parts are
    # optional. If both tags are missing or empty, raise an exception
    study_directory = []
    if "StudyID" in data_set and data_set.as_string("StudyID"):
        study_directory.append(data_set.as_string("StudyID")[0])
    if ("StudyDescription" in data_set and
            data_set.as_string("StudyDescription")):
        study_directory.append(
            data_set.as_string("StudyDescription")[0])

    if not study_directory:
        raise Exception("Study ID and Study Description are both missing")

    study_directory = "_".join(study_directory)

    # Study directory: <SeriesNumber>_<SeriesDescription>, both
    # parts are optional. If both tags are missing or empty, raise an exception
    series_directory = []
    if "SeriesNumber" in data_set and data_set.as_int("SeriesNumber"):
        series_directory.append(str(data_set.as_int("SeriesNumber")[0]))
    if ("SeriesDescription" in data_set and
            data_set.as_string("SeriesDescription")):
        series_directory.append(
            data_set.as_string("SeriesDescription")[0])

    if not series_directory:
        raise Exception("Series Number and Series Description are both missing")

    series_directory = "_".join(series_directory)

    if iso_9660:
        patient_directory = to_iso_9660(patient_directory)
        study_directory = to_iso_9660(study_directory)
        series_directory = to_iso_9660(series_directory)

    return os.path.join(patient_directory, study_directory, series_directory)

def to_iso_9660(value):
    """Return an ISO-9660 compatible version of input string."""
    value = value[:8].upper()
    value = re.sub(r"[^A-Z0-9_]", "_", value)
    return value
