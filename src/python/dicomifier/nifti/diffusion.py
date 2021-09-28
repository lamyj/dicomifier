#########################################################################
# Dicomifier - Copyright (C) Universite de Strasbourg
# Distributed under the terms of the CeCILL-B license, as published by
# the CEA-CNRS-INRIA. Refer to the LICENSE file or to
# http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
# for details.
#########################################################################

"""
Extract diffusion-related information from JSON meta-data and convert it to
other formats. Unless otherwise specified, all b-values extracted from meta-data
are expressed in :math:`s/m^2` (i.e. SI units).
"""

import base64
import binascii
import re

import numpy

from .. import dicom_to_nifti
from .. import logger

def from_standard(data):
    """ Extract diffusion gradient direction and b-value from standard DICOM
        elements (MR Diffusion Sequence).
    """

    diffusion_data = data["MRDiffusionSequence"]

    scheme = []
    for entry in diffusion_data:
        entry = entry[0]
        if "DiffusionBValue" not in entry:
            raise Exception("Missing b-value")
        b_value = entry["DiffusionBValue"][0]
        # Convert from s/mm^2 to s/m^2
        b_value *= 1e6

        if "DiffusionGradientDirectionSequence" not in entry:
            if b_value != 0:
                raise Exception("Missing direction")
            else:
                entry["DiffusionGradientDirectionSequence"] = [{
                    "DiffusionGradientOrientation": [0,0,0]}]
        direction = entry["DiffusionGradientDirectionSequence"][0]
        if "DiffusionGradientOrientation" not in direction:
            raise Exception("Missing direction")
        direction = numpy.array(direction["DiffusionGradientOrientation"])
        norm = numpy.linalg.norm(direction)
        if norm > 0:
            direction /= norm

        scheme.append((b_value, direction))

    return scheme

def from_siemens_csa(data):
    """ Extract diffusion gradient direction and b-value from Siemens-specific
        elements (CSA Image Header Info (0029,xx10)).
    """

    logger.warning(
        "The coordinate system of the gradient direction is unspecified. "
        "Results may be wrong on non-axial images.")

    scheme = []

    # Look for "SIEMENS CSA HEADER" private creator and get the concrete tag
    # of CSA Image Header Info (0029,xx10)
    element = None
    for tag, item in data.items():
        match = re.match(r"([\da-f]{4})00([\da-f]{2})", tag)
        if match:
            try:
                item = [base64.b64decode(item[0]).decode()]
            except binascii.Error:
                pass
            except UnicodeDecodeError:
                pass
            if item[0] == "SIEMENS CSA HEADER":
                element = match.group(1)+match.group(2)+"10"
                break

    item = data[element]
    for entry in numpy.ravel(item):
        siemens_data = dicom_to_nifti.siemens.parse_csa(base64.b64decode(entry))

        b_value = siemens_data["B_value"][0]
        # Convert from s/mm^2 to s/m^2
        b_value *= 1e6

        direction = siemens_data["DiffusionGradientDirection"]
        if len(direction) == 0:
            direction = [0,0,0]
        norm = numpy.linalg.norm(direction)
        if norm > 0:
            direction /= norm

        scheme.append((b_value, direction))
    return scheme

def from_ge_private(data):
    """ Extract diffusion gradient direction and b-value from GE-specific
        elements (0019,xxbb, 0019,xxbc, 0019,xxbd, and 0043,xx39).
    """

    # Look for "GEMS_ACQU_01" and "GEMS_PARM_01" private creators and build base
    # tags.
    gems_acq = None
    gems_parm = None
    for tag, item in sorted(data.items()):
        if tag[:4] == "0019" and tag[-4:-2] == "00":
            if item and item[0] == "GEMS_ACQU_01":
                gems_acq = "0019"+tag[-2:]
        if tag[:4] == "0043" and tag[-4:-2] == "00":
            if item and item[0] == "GEMS_PARM_01":
                gems_parm = "0043"+tag[-2:]
        if tag>"004300ff" or None not in [gems_acq, gems_parm]:
            break

    directions = None
    if gems_acq is not None:
        directions = numpy.squeeze(
            numpy.transpose([data[gems_acq+x] for x in ["bb", "bc", "bd"]]))
        norm = numpy.maximum(1e-30, numpy.linalg.norm(directions, axis=1))
        directions /= norm[:,None]

    b_values = None
    if gems_parm is not None:
        b_values = data.get(gems_parm+"39")
        if b_values is not None:
            b_values = [x[0] for x in b_values]
    if b_values is None:
        b_values = [x[0] if x else 0 for x in data.get("DiffusionBValue")]
    # Convert from s/mm^2 to s/m^2
    b_values = [x*1e6 for x in b_values]

    return list(zip(b_values, directions))

def to_mrtrix(scheme, fd):
    """ Save a diffusion scheme in MRtrix format to a file-like object.
    """

    # https://mrtrix.readthedocs.io/en/latest/concepts/dw_scheme.html
    # > the direction vectors are assumed to be provided with respect to real
    # > or scanner coordinates. This is the same convention as is used in the
    # > DICOM format.
    # NOTE: DICOM uses *patient* coordinates, not *scanner* coordinates
    for b_value, direction in scheme:
        # Convert from s/m^2 to s/mm^2
        b_value /= 1e6
        print(*direction, b_value, file=fd)

def to_fsl(scheme, transform, bvecs_fd, bvals_fd):
    """ Save a diffusion scheme in FSL bvecs+bvals format. A reference
        transform is required as the bvecs are store in image coordinates, not
        in patient coordinates. This transform must correspond to an
        image-to-patient transform, e.g. what is stored in the *affine* member
        of nibabel images.
    """

    # https://fsl.fmrib.ox.ac.uk/fsl/fslwiki/FDT/UserGuide#Diffusion_data_in_FSL
    # https://fsl.fmrib.ox.ac.uk/fsl/fslwiki/FDT/FAQ#What_conventions_do_the_bvecs_use.3F

    directions = numpy.array([direction for b_value, direction in scheme])
    # Convert from patient coordinates to image coordinates
    # WARNING: for highly anisotropic images and non axis-aligned transforms,
    # this seem to introduce a slight bias in the directions.
    bvecs = numpy.array([numpy.linalg.inv(transform) @ d for d in directions])

    if numpy.linalg.det(transform)>0:
        bvecs[:,0] *= -1

    bvecs[bvecs == numpy.NZERO] = 0

    # Re-normalize (not required by FSL)
    norm = numpy.maximum(1e-20, numpy.linalg.norm(bvecs, axis=1))
    bvecs /= norm[:,None]
    for row in bvecs.T:
        print(*row, file=bvecs_fd)

    # Convert from s/m^2 to s/mm^2
    b_values = numpy.array([b_value for b_value, direction in scheme]) / 1e6
    print(*b_values, file=bvals_fd)
