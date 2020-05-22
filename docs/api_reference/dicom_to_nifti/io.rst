dicomifier.dicom_to_nifti.io
============================


.. py:function:: dicomifier.dicom_to_nifti.io.get_dicomdir_files(path)
  
  Return the list of files indexed in a DICOMDIR file.
      

.. py:function:: dicomifier.dicom_to_nifti.io.get_files(paths)
  
  Return the DICOM files found in the paths. Each path can be a single 
  file, a directory (scanned recursively), or a DICOMDIR file.

.. py:function:: dicomifier.dicom_to_nifti.io.get_series_directory(meta_data)
  
  Return the directory associated with the patient, study and series of
  the NIfTI meta-data.

.. py:function:: dicomifier.dicom_to_nifti.io.write_nifti(nifti_data, destination, zip)
  
  Write the NIfTI image and meta-data in the given destination.
  
  :param nifti_data: Pair of NIfTI image and meta-data
  :param destination: Destination directory
  :param zip: whether to zip the NIfTI files
