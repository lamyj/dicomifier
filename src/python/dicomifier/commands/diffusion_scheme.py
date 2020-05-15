#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

import json
import pathlib

import dicomifier
import numpy
import odil

def setup(subparsers):
    parser = subparsers.add_parser(
        "diffusion-scheme", aliases=["diffusion", "diff"], 
        description="Convert dMRI meta-data stored in JSON", 
        help="Convert dMRI meta-data")
    
    parser.add_argument("source", type=pathlib.Path, help="Source JSON file")
    parser.add_argument("format", choices=["mrtrix"], help="Output format")
    parser.add_argument(
        "destination", type=pathlib.Path, help="Output directory")
    
    return parser

def action(source, format, destination):
    with open(source) as fd:
        data = json.load(fd)
    
    scheme = None
    if "MRDiffusionSequence" in data:
        scheme = dicomifier.nifti.diffusion.from_standard(data)
    
    writer = getattr(dicomifier.nifti.diffusion, "to_{}".format(format))
    with destination.open("w") as fd:
        writer(scheme, fd)
