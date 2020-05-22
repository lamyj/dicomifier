dicomifier.nifti.diffusion
==========================

Extract diffusion-related information from JSON meta-data and convert it to 
other formats. Unless otherwise specified, all b-values extracted from meta-data
are expressed in :math:`s/m^2` (i.e. SI units).

.. py:function:: dicomifier.nifti.diffusion.from_standard(data)
  
  Extract diffusion gradient direction and b-value from standard DICOM
  elements (MR Diffusion Sequence).

.. py:function:: dicomifier.nifti.diffusion.to_mrtrix(scheme, fd)
  
  Save a diffusion scheme in MRtrix format to a file-like object.
      
