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
        list_pvdatasets(source)
        list_bruker(source)

def list_pvdatasets(source):
    if source.is_file() and zipfile.is_zipfile(source):
        directory = pathlib.Path(tempfile.mkdtemp())
        try:
            with zipfile.ZipFile(source) as archive:
                archive.extractall(directory/source.name)
                list_bruker(directory/source.name, source)
                shutil.rmtree(directory/source.name)
        finally:
            shutil.rmtree(directory)

def list_bruker(source, label=None):
    entries = {}
    for path in source.rglob("2dseq"):
        current = entries
        for part in (source,)+path.relative_to(source).parts[:-2]:
            current = current.setdefault(part, {})
        current[path.parent.name] = dicomifier.bruker_to_dicom.io.get_bruker_info(
            path.parent)
    
    def sort(x):
        name, value = x
        return (
            (1, divmod(value.get("SeriesNumber", [1e30])[0], 2**16))
            if isinstance(value, odil.DataSet) 
            else (0, name))
    
    def format(info):
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
            return (
                "{}: {} / {} / {}:{} {}".format(
                    path.parent.relative_to(source), subject, 
                    study_description, series_number[0], series_number[1], 
                    series_description))
        else:
            return (
                "{}: unknown Bruker data".format(
                    path.parent.relative_to(source)))
    
    stack = [(
        0, name, value) 
        for name, value in sorted(entries.items(), key=sort, reverse=True)]
    while stack:
        level, name, value = stack.pop()
        if level != 0:
            print("{}{}".format(level*"  ", name))
        else:
            print(label or source)
        
        children = sorted(value.items(), key=sort)
        
        for child_name, child_value in children[::-1]:
            if isinstance(child_value, dict):
                stack.append((1+level, child_name, child_value))
        
        for child_name, child_value in children:
            if isinstance(child_value, odil.DataSet):
                print("{}{}: {}".format(
                    (1+level)*"  ", child_name, format(child_value)))
    return
