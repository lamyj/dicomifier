dicomifier.nifti.diffusion
==========================


.. py:module:: dicomifier.nifti.diffusion

Extract diffusion-related information from JSON meta-data and convert it to 
other formats. Unless otherwise specified, all b-values extracted from meta-data
are expressed in :math:`s/m^2` (i.e. SI units).


.. py:function:: from_ge_private(data)
   :module: dicomifier.nifti.diffusion

   Extract diffusion gradient direction and b-value from GE-specific
   elements (0019,xxbb, 0019,xxbc, 0019,xxbd, and 0043,xx39).


.. py:function:: from_siemens_csa(data)
   :module: dicomifier.nifti.diffusion

   Extract diffusion gradient direction and b-value from Siemens-specific
   elements (CSA Image Header Info (0029,xx10)).


.. py:function:: from_standard(data)
   :module: dicomifier.nifti.diffusion

   Extract diffusion gradient direction and b-value from standard DICOM
   elements (MR Diffusion Sequence).


.. py:function:: to_fsl(scheme, transform, bvecs_fd, bvals_fd)
   :module: dicomifier.nifti.diffusion

   Save a diffusion scheme in FSL bvecs+bvals format. A reference 
   transform is required as the bvecs are store in image coordinates, not 
   in patient coordinates. This transform must correspond to an 
   image-to-patient transform, e.g. what is stored in the *affine* member
   of nibabel images.


.. py:function:: to_mrtrix(scheme, fd)
   :module: dicomifier.nifti.diffusion

   Save a diffusion scheme in MRtrix format to a file-like object.

