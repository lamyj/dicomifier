#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import json
import re
import os

import dateutil
import odil

from .. import bruker, logger

try:
    unicode
except NameError:
    unicode = str

# explicit conversions
def _convert_date_time(value, format_):
    date_time = dateutil.parser.parse(value.replace(b",", b"."))
    return date_time.strftime(format_)
vr_converters = {
    "DA": lambda x: _convert_date_time(x, "%Y%m%d") if x else x,
    "DS": lambda x: float(x),
    "DT": lambda x: _convert_date_time(x, "%Y%m%d%H%M%S") if x else x,
    "FD": lambda x: float(x),
    "FL": lambda x: float(x),
    "IS": lambda x: int(x),
    "SS": lambda x: int(x),
    "TM": lambda x: _convert_date_time(x, "%H%M%S") if x else x,
    "US": lambda x: int(x),
}

def convert_reconstruction(
        bruker_directory, series, reconstruction,
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
    
    logger.info("Converting {}:{}".format(series, reconstruction))
    
    bruker_binary = bruker_directory.get_dataset(
        "{}{:04d}".format(series, int(reconstruction)))
    bruker_json = json.loads(bruker.as_json(bruker_binary))
    logger.info("Found {}:{} - {} ({})".format(
        series, reconstruction, 
        bruker_json.get("VisuAcquisitionProtocol", ["(none)"])[0],
        bruker_json.get("RECO_mode", ["none"])[0]
    ))
    bruker_json["reco_files"] = list(bruker_directory.get_used_files(
        "{}{:04d}".format(series, int(reconstruction))))

    dicom_data_sets = iod_converter(bruker_json, writer.transfer_syntax)
    
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
    index = -1
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

    tag = str(getattr(odil.registry, dicom_name))
    vr = str(vr_finder(dicom_name))

    if value is None:
        if type_ == 1:
            raise Exception("{} must be present".format(dicom_name))
        elif type_ == 2:
            dicom_data_set.add(tag)
    elif vr == "SQ" and not value:
        # Type of empty value must be explicit
        dicom_data_set.add(tag, odil.Value.DataSets(), getattr(odil.VR, vr))
    else:
        if isinstance(setter, dict):
            value = [setter[x] for x in value]
        elif setter is not None:
            value = setter(value)
        if value and isinstance(value[0], unicode):
            value = [x.encode("utf-8") for x in value]

        vr_converter = vr_converters.get(vr)
        if vr_converter is not None :
            value = [vr_converter(x) for x in value]

        dicom_data_set.add(tag, value, getattr(odil.VR, vr))

    return value

def get_series_directory(data_set, iso_9660):
    """ Return the directory associated with the patient, study and series of
        the DICOM data set.
    """

    # Patient directory: <PatientName> or <PatientID>.
    patient_directory = None
    if "PatientName" in data_set and data_set.as_string("PatientName"):
        patient_directory = odil.as_unicode(
            data_set.as_string("PatientName")[0],
            data_set.as_string("SpecificCharacterSet") 
            if "SpecificCharacterSet" in data_set else odil.Value.Strings())
    else:
        patient_directory = odil.as_unicode(
            data_set.as_string("PatientID")[0],
            data_set.as_string("SpecificCharacterSet") 
            if "SpecificCharacterSet" in data_set else odil.Value.Strings())

    # Study directory: <StudyID>_<StudyDescription>, both parts are
    # optional. If both tags are missing or empty, raise an exception
    study_directory = []
    if "StudyID" in data_set and data_set.as_string("StudyID"):
        study_directory.append(
            odil.as_unicode(
                data_set.as_string("StudyID")[0],
                data_set.as_string("SpecificCharacterSet") 
                if "SpecificCharacterSet" in data_set else odil.Value.Strings()))
    if "StudyDescription" in data_set and data_set.as_string("StudyDescription"):
        study_directory.append(
            odil.as_unicode(
                data_set.as_string("StudyDescription")[0],
                data_set.as_string("SpecificCharacterSet") 
                if "SpecificCharacterSet" in data_set else odil.Value.Strings()))

    if not study_directory:
        raise Exception("Study ID and Study Description are both missing")

    study_directory = "_".join(study_directory)

    # Study directory: <SeriesNumber>_<SeriesDescription>, both
    # parts are optional. If both tags are missing or empty, raise an exception
    series_directory = []
    if "SeriesNumber" in data_set and data_set.as_int("SeriesNumber"):
        series_number = data_set.as_int("SeriesNumber")[0]
        if series_number > 2**16:
            # Bruker ID based on experiment number and reconstruction number is
            # not readable: separate the two values
            series_directory.append(str(divmod(series_number, 2**16)[0]))
        else:
            series_directory.append(str(series_number))
    if not iso_9660:
        if "SeriesDescription" in data_set and data_set.as_string("SeriesDescription"):
            series_directory.append(
                odil.as_unicode(
                    data_set.as_string("SeriesDescription")[0],
                    data_set.as_string("SpecificCharacterSet") 
                    if "SpecificCharacterSet" in data_set else odil.Value.Strings()))

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
