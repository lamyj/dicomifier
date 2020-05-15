#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import pathlib

import dicomifier
import numpy
import odil

def setup(subparsers):
    parser = subparsers.add_parser(
        "to-nifti", aliases=["nifti", "nii"], 
        description="Convert DICOM to NIfTI", help="Convert to NIfTI")
    
    parser.add_argument(
        "sources", nargs="+", type=pathlib.Path,
        help="DICOM file, directory or DICOMDIR", metavar="source")
    parser.add_argument(
        "destination", type=pathlib.Path, help="Output directory")
    parser.add_argument(
        "--dtype", "-d", default=None, 
        type=lambda x: None if x is None else getattr(numpy, x),
        help="Pixel type")
    parser.add_argument(
        "--zip", "-z", action="store_true", help="Compress NIfTI files")
    
    return parser

def action(sources, destination, dtype, zip):
    dicomifier.dicom_to_nifti.convert.convert_paths(
        sources, destination, zip, dtype)
    
