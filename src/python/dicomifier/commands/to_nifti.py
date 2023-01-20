#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import pathlib
import shutil
import tempfile
import sys
import zipfile

import dicomifier
import numpy
import odil

from . import to_dicom

def setup(subparsers):
    parser = subparsers.add_parser(
        "to-nifti", aliases=["nifti", "nii"], 
        description="Convert Bruker or DICOM data to NIfTI", 
        help="Convert to NIfTI")
    
    parser.add_argument(
        "sources", nargs="+", type=pathlib.Path,
        help="Bruker directory, DICOM file, directory or DICOMDIR, or '-'", 
        metavar="source")
    parser.add_argument(
        "destination", type=pathlib.Path, help="Output directory")
    parser.add_argument(
        "--dtype", "-d", default=None, 
        type=lambda x: None if x is None else getattr(numpy, x),
        help="Pixel type")
    parser.add_argument(
        "--zip", "-z", action="store_true", help="Compress NIfTI files")
    parser.add_argument(
        "--effective-b-values", "-e",
        action="store_false", dest="ideal_b_values",
        help="Store effective b-values instead of ideal ones")
    
    return parser

def action(sources, ideal_b_values, destination, dtype, zip):
    bruker_sources = []
    dicom_sources = []
    for source in sources:
        if str(source) == "-":
            paths = [x for x in sys.stdin.read().split("\0") if x]
            dicom_sources.extend(paths)
        elif source.is_dir() and list(source.rglob("2dseq")):
            bruker_sources.append(source)
        elif source.is_file() and zipfile.is_zipfile(source):
            with zipfile.ZipFile(source, "r") as fd:
                if any(pathlib.Path(x).name == "2dseq" for x in fd.namelist()):
                    bruker_sources.append(source)
                else:
                    dicom_sources.append(source)
        else:
            dicom_sources.append(source)
    
    directory = pathlib.Path(tempfile.mkdtemp())
    try:
        # Convert Bruker sources to DICOM
        for index, source in enumerate(bruker_sources):
            dicom_destination = directory/str(index)
            to_dicom.action(
                [source], ideal_b_values, dicom_destination,
                odil.registry.ImplicitVRLittleEndian, "nested",
                dicomdir=False, multiframe=True)
            dicom_sources.append(dicom_destination)
        
        # Convert all sources to NIfTI
        dicomifier.dicom_to_nifti.convert.convert_paths(
            dicom_sources, destination, zip, dtype)
    finally:
        shutil.rmtree(str(directory))
