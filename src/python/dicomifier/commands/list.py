#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import json
import os
import pathlib
import shutil
import tempfile
import zipfile

import dicomifier
import odil

def setup(subparsers):
    parser = subparsers.add_parser(
        "list", aliases=["ls"], help="List convertible data",
        description="List Bruker and DICOM data which can be converted")

    parser.add_argument(
        "sources", nargs="+", type=pathlib.Path,
        help="Bruker directory, DICOM file, directory or DICOMDIR",
        metavar="source")
    parser.add_argument(
        "--json", "-j", action="store_true", dest="use_json",
        help="Display contents in JSON format")

    return parser

def action(sources, use_json):
    contents = {}

    for source in sources:
        directory_contents = []
        directory_contents.extend([("Bruker", x) for x in list_bruker(source)])
        directory_contents.extend(
            [("Bruker archive", x) for x in list_pvdatasets(source)])
        directory_contents.extend([("DICOM", x) for x in list_dicom(source)])
        if use_json:
            for format, item in directory_contents:
                item["format"] = format
            contents[str(source)] = [item for _, item in directory_contents]
        else:
            print(source)
            for format, item in directory_contents:
                print(
                    "  {} / {} / {} {} ({}, {})".format(
                        item["subject"],
                        item["StudyDescription"],
                        "{}:{}".format(*item["SeriesNumber"])
                            if isinstance(item["SeriesNumber"], tuple)
                            else item["SeriesNumber"],
                        item["SeriesDescription"],
                        item["directory"], format))

    if use_json:
        print(json.dumps(contents))

def list_bruker(source):
    entries = []
    for path in source.rglob("2dseq"):
        info = dicomifier.bruker_to_dicom.io.get_bruker_info(path.parent)
        entries.append((path.relative_to(source), info))

    entries.sort(
        key=lambda x: (
            x[1].get("PatientName", [""])[0],
            x[1].get("StudyDate", ["9999999"])[0],
            divmod(x[1].get("SeriesNumber", [1e30])[0], 2**16)))

    result = []

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

            result.append({
                "subject": subject, "StudyDescription": study_description,
                "SeriesNumber": series_number,
                "SeriesDescription": series_description,
                "directory": str(path.parent)})

    return result

def list_pvdatasets(source):
    result = []
    if source.is_file() and zipfile.is_zipfile(source):
        directory = pathlib.Path(tempfile.mkdtemp())
        try:
            with zipfile.ZipFile(source) as archive:
                archive.extractall(directory/source.name)
                result.append(list_bruker(directory/source.name))
                shutil.rmtree(directory/source.name)
        finally:
            shutil.rmtree(directory)
    return result

def list_dicom(source):
    series = {}
    series_files = {}
    for dirpath, dirnames, filenames in os.walk(str(source)):
        dicomdir = [x for x in filenames if x.upper() == "DICOMDIR"]
        if dicomdir:
            filenames = dicomifier.dicom_to_nifti.io.get_dicomdir_files(
                os.path.join(dirpath, dicomdir[0]))
            # Don't recurse
            dirnames[:] = []
        else:
            filenames = [os.path.join(dirpath, file_) for file_ in filenames]
        for file_ in filenames:
            try:
                _, data_set = odil.Reader.read_file(
                    file_,
                    halt_condition=lambda x: x > odil.registry.SeriesNumber)
            except odil.Exception:
                continue
            series_instance_uid = data_set[odil.registry.SeriesInstanceUID][0]
            series[series_instance_uid] = data_set
            series_files.setdefault(series_instance_uid, set()).add(file_)

    series_directories = {
        uid: os.path.relpath(
            os.path.commonpath([os.path.dirname(f) for f in files]),
            str(source))
        for uid, files in series_files.items()}

    def get_series_number(data_set):
        series_number = data_set.get("SeriesNumber", [0])[0]
        software = data_set.get(odil.registry.SoftwareVersions, [b""])[0]
        if software == b"ParaVision" and series_number > 2**16:
            # Bruker ID based on experiment number and reconstruction
            # number is not readable: separate the two values
            series_number = divmod(series_number, 2**16)
        elif software.startswith(b"ParaVision") and series_number > 10000:
            # Same processing for Bruker-generated DICOM
            series_number = divmod(series_number, 10000)
        return series_number

    result = []

    series = sorted(
        series.values(),
        key=lambda x: (
            x.get("PatientName", [b""])[0],
            x.get("StudyDate", [b"9999999"])[0],
            get_series_number(x)))

    for data_set in series:
        subject = odil.as_unicode(
            data_set.get("PatientName", [b"(no subject name)"])[0],
            data_set.get("SpecificCharacterSet", odil.Value.Strings()))
        study_description = odil.as_unicode(
            data_set.get("StudyDescription", [b"(no study description)"])[0],
            data_set.get("SpecificCharacterSet", odil.Value.Strings()))

        series_number = get_series_number(data_set)

        series_description = odil.as_unicode(
            data_set.get("SeriesDescription", [b"(no series description)"])[0],
            data_set.get("SpecificCharacterSet", odil.Value.Strings()))

        series_instance_uid = data_set[odil.registry.SeriesInstanceUID][0]

        result.append({
            "subject": subject, "StudyDescription": study_description,
            "SeriesNumber": series_number,
            "SeriesDescription": series_description,
            "directory": series_directories[series_instance_uid]})

    return result
