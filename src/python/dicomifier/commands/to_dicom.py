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
import zipfile

import dicomifier
import odil

def setup(subparsers):
    parser = subparsers.add_parser(
        "to-dicom", aliases=["dicom", "dcm"],
        description="Convert Bruker data to DICOM", help="Convert to DICOM")

    parser.add_argument(
        "sources", nargs="+", type=pathlib.Path,
        metavar="source", help="Directories to scan for convertible data")
    parser.add_argument(
        "destination", type=pathlib.Path, help="Output directory")
    parser.add_argument(
        "--dicomdir", "-d", action="store_true", help="Create a DICOMDIR")
    parser.add_argument(
        "--layout", "-l", choices=["nested", "flat"],
        default="nested", help="Layout of the DICOM files on the disk")
    parser.add_argument(
        "--multiframe", "-m", action="store_true",
        help="Generate multiframe DICOM files")
    parser.add_argument(
        "--transfer-syntax", "-t",
        choices=["ImplicitVRLittleEndian", "ExplicitVRLittleEndian"],
        type=lambda x: getattr(odil.registry, x),
        default="ImplicitVRLittleEndian",
        help="Transfer syntax of the output files")

    return parser

def writer_from_name(name):
    writers = {
        "nested": dicomifier.bruker_to_dicom.io.NestedDICOMWriter,
        "flat": dicomifier.bruker_to_dicom.io.FlatDICOMWriter}
    return writers[name]

def action(sources, destination, transfer_syntax, layout, dicomdir, multiframe):
    if destination.is_dir() and list(destination.iterdir()):
        dicomifier.logger.warning("{} is not empty".format(destination))

    writer = writer_from_name(layout)(destination, True, transfer_syntax)

    directory = pathlib.Path(tempfile.mkdtemp())
    try:
        for source in sources:
            if zipfile.is_zipfile(str(source)):
                with zipfile.ZipFile(str(source)) as archive:
                    archive.extractall(str(directory/source.name))
                    source = directory/source.name
            dicomifier.bruker_to_dicom.convert.convert_directory(
                source, dicomdir, multiframe, writer)
    finally:
        shutil.rmtree(str(directory))
