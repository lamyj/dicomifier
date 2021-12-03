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
import nibabel

def setup(subparsers):
    parser = subparsers.add_parser(
        "diffusion-scheme", aliases=["diffusion", "diff"], 
        description="Convert dMRI meta-data stored in JSON", 
        help="Convert dMRI meta-data")
    
    parser.add_argument("source", type=pathlib.Path, help="Source JSON file")
    parser.add_argument(
        "format", choices=["mrtrix", "fsl"], 
        help="Output format. MRtrix expects a single scheme file, FSL expects "
            "two files (bvecs and bvals, in that order)")
    parser.add_argument(
        "destinations", nargs="+", type=pathlib.Path, 
        metavar="destination", help="Output file")
    parser.add_argument(
        "--image", "-i", type=pathlib.Path, 
        help="Image file for formats using image-based direction coordinates")
    
    return parser

def action(source, format, destinations, image):
    with source.open() as fd:
        data = json.load(fd)
    
    scheme = None
    for name in ["standard", "siemens_csa", "ge_private"]:
        try:
            getter = getattr(dicomifier.nifti.diffusion, "from_{}".format(name))
            scheme = getter(data)
        except Exception:
            pass
        if scheme is not None:
            break
    
    if scheme is None:
        raise NotImplementedError("Could not read diffusion data")
    globals()["to_{}".format(format)](scheme, destinations, image)

def to_mrtrix(scheme, destinations, image):
    with destinations[0].open("w") as fd:
        dicomifier.nifti.diffusion.to_mrtrix(scheme, fd)

def to_fsl(scheme, destinations, image):
    if len(destinations) != 2:
        raise Exception("Destinations must contain bvecs and bvals files")

    if image is None:
        raise Exception("Image must be provided")

    image = nibabel.load(str(image))
    with destinations[0].open("w") as bvecs_fd, destinations[1].open("w") as bvals_fd:
        dicomifier.nifti.diffusion.to_fsl(
            scheme, image.affine[:3,:3], bvecs_fd, bvals_fd)
