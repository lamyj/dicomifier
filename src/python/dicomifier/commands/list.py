#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import os
import pathlib
import shutil
import tempfile
import zipfile

import dicomifier
import odil

def setup(subparsers):
    parser = subparsers.add_parser(
        "list", aliases=["ls"], description="List convertible data", 
        help="List Bruker and DICOM data which can be converted")
    
    parser.add_argument(
        "sources", nargs="+", type=pathlib.Path,
        help="DICOM file, directory or DICOMDIR", metavar="source")
    
    return parser

def action(sources):
    for source in sources:
        source_printed = list_bruker(source)
        list_pvdatasets(source, source_printed)
        list_dicom(source, source_printed)

def list_bruker(source, label=None, source_printed=False):
    entries = []
    for path in source.rglob("2dseq"):
        info = dicomifier.bruker_to_dicom.io.get_bruker_info(path.parent)
        entries.append((path.relative_to(source), info))
    
    def sort(x):
        name, value = x
        return (
            (1, divmod(value.get("SeriesNumber", [1e30])[0], 2**16))
            if isinstance(value, odil.DataSet) 
            else (0, name))
    
    if not entries:
        return
    
    entries.sort(
        key=lambda x: (
            x[1].get("PatientName", [""])[0], 
            x[1].get("StudyDate", ["9999999"])[0], 
            divmod(x[1].get("SeriesNumber", [1e30])[0], 2**16)))
    
    if not source_printed:
        print(label or source)
    
    print("  Bruker")
    for path, info in entries:
        if "SeriesNumber" in info:
            subject = odil.as_unicode(
                info.get("PatientName", [b"(no subject name)"])[0],
                odil.Value.Strings(["ISO_IR 192"]))
            study_description = odil.as_unicode(
                info.get("StudyDescription", [b"(no study description)"])[0],
                odil.Value.Strings(["ISO_IR 192"]))
            series_number = divmod(info.get("SeriesNumber")[0], 2**16)
            series_description = odil.as_unicode(
                info.get("SeriesDescription", [b"(no series description)"])[0],
                odil.Value.Strings(["ISO_IR 192"]))
            message = (
                "{} / {} / {}:{} {}".format(
                    subject, 
                    study_description, series_number[0], series_number[1], 
                    series_description))
        else:
            message = "unknown Bruker data"
        print("    {}: {}".format(path, message))
    
    return True

def list_pvdatasets(source, source_printed):
    if source.is_file() and zipfile.is_zipfile(source):
        directory = pathlib.Path(tempfile.mkdtemp())
        try:
            with zipfile.ZipFile(source) as archive:
                archive.extractall(directory/source.name)
                list_bruker(directory/source.name, source)
                shutil.rmtree(directory/source.name)
        finally:
            shutil.rmtree(directory)

def list_dicom(source, source_printed):
    series = {}
    for dirpath, dirnames, filenames in os.walk(source):
        dicomdir = [x for x in filenames if x.upper() == "DICOMDIR"]
        if dicomdir:
            filenames = dicomifier.dicom_to_nifti.io.get_dicomdir_files(
                os.path.join(dirpath, dicomdir[0]))
            # Don't recurse
            dirnames[:] = []
        
        for file_ in filenames:
            try:
                header, data_set = odil.Reader.read_file(
                    os.path.join(dirpath, file_),
                    halt_condition=lambda x: x > odil.registry.SeriesNumber)
            except odil.Exception:
                continue
            series_instance_uid = data_set[odil.registry.SeriesInstanceUID][0]
            series[series_instance_uid] = data_set
    
    def get_series_number(data_set):
        series_number = data_set.get("SeriesNumber", [0])[0]
        software = data_set.get(odil.registry.SoftwareVersions, [""])[0]
        if software and software == b"ParaVision" and series_number > 2**16:
            # Bruker ID based on experiment number and reconstruction 
            # number is not readable: separate the two values
            series_number = divmod(series_number, 2**16)
        elif software.startswith(b"ParaVision") and series_number > 10000:
            # Same processing for Bruker-generated DICOM
            series_number = divmod(series_number, 10000)
        return series_number
    
    if not series:
        return
    
    series = sorted(
        series.values(),
        key=lambda x: (
            x.get("PatientName", [""])[0], 
            x.get("StudyDate", ["9999999"])[0], 
            get_series_number(x)))
    
    if not source_printed:
        print(source)
    
    print("  DICOM")
    for data_set in series:
        subject = odil.as_unicode(
            data_set.get("PatientName", [b"(no subject name)"])[0],
            odil.Value.Strings(["ISO_IR 192"]))
        study_description = odil.as_unicode(
            data_set.get("StudyDescription", [b"(no study description)"])[0],
            odil.Value.Strings(["ISO_IR 192"]))
        
        series_number = get_series_number(data_set)
        
        series_description = odil.as_unicode(
            data_set.get("SeriesDescription", [b"(no series description)"])[0],
            odil.Value.Strings(["ISO_IR 192"]))
            
        print(
            "    {} / {} / {} {}".format(
                subject, study_description, 
                "{}:{}".format(*series_number) 
                    if isinstance(series_number, tuple) 
                    else series_number, 
                series_description))
        
