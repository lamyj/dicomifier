dicomifier.nifti.diffusion
==========================


.. py:module:: dicomifier.nifti.diffusion

Extract diffusion-related information from JSON meta-data and convert it to 
other formats. Unless otherwise specified, all b-values extracted from meta-data
are expressed in :math:`s/m^2` (i.e. SI units).


.. py:function:: from_standard(data)
   :module: dicomifier.nifti.diffusion

   Extract diffusion gradient direction and b-value from standard DICOM
   elements (MR Diffusion Sequence).


.. py:function:: to_mrtrix(scheme, fd)
   :module: dicomifier.nifti.diffusion

   Save a diffusion scheme in MRtrix format to a file-like object.

