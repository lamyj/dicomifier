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

import numpy

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
            raise Exception("Missing direction")
        direction = entry["DiffusionGradientDirectionSequence"][0]
        if "DiffusionGradientOrientation" not in direction:
            raise Exception("Missing direction")
        direction = numpy.array(direction["DiffusionGradientOrientation"])
        norm = numpy.linalg.norm(direction)
        if norm > 0:
            direction /= norm
        
        scheme.append((b_value, direction))
    
    return scheme

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
