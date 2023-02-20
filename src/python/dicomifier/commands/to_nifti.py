#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import pathlib
import re
import shutil
import tempfile
import sys
import zipfile

import dicomifier
import numpy
import odil

from . import diffusion_scheme, to_dicom

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
    parser.add_argument(
        "--diffusion-scheme", "-s", choices=["mrtrix", "fsl"],
        dest="diffusion_format", help="Save diffusion data in specified format")
    parser.add_argument(
        "--layout", "-l",
        help="Set the layout of the destination directory. Values between "
            "braces are replaced by the value of the corresponding meta-data "
            "item. A set of pipe-separated items can be specified in the "
            "braces, in which case the first item present in the meta-data "
            "will be used. If no corresponding item is found in the meta-data, "
            "the empty string will be used.")
    return parser

def action(
        sources, destination, dtype, zip, ideal_b_values, diffusion_format,
        layout):
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
        nifti_files = dicomifier.dicom_to_nifti.convert.convert_paths(
            dicom_sources, destination, zip, dtype, layout=layout)
        
        if diffusion_format:
            for nifti_file in nifti_files:
                root = re.match(r"^(.+)\.nii(\.gz)?$", nifti_file).group(1)
                
                meta_data_file = "{}.json".format(root)
                
                if diffusion_format == "mrtrix":
                    destinations = ["{}.scheme".format(root)]
                elif diffusion_format == "fsl":
                    destinations = [
                        "{}.{}".format(root, suffix)
                        for suffix in ["bvecs", "bvals"]]
                destinations = [pathlib.Path(x) for x in destinations]
                
                try:
                    diffusion_scheme.action(
                        pathlib.Path(meta_data_file), diffusion_format,
                        destinations, nifti_file)
                except Exception as e:
                    dicomifier.logger.debug(
                        "No usable diffusion in {}: {}".format(root, e))
    finally:
        shutil.rmtree(str(directory))
