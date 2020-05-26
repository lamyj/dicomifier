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
