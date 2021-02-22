dicomifier.dicom_to_nifti.io
============================


.. py:module:: dicomifier.dicom_to_nifti.io


.. py:function:: get_dicomdir_files(path)
   :module: dicomifier.dicom_to_nifti.io

   Return the list of files indexed in a DICOMDIR file.



.. py:function:: get_files(paths)
   :module: dicomifier.dicom_to_nifti.io

   Return the DICOM files found in the paths. Each path can be a single 
   file, a directory (scanned recursively), or a DICOMDIR file.


.. py:function:: get_series_directory(meta_data)
   :module: dicomifier.dicom_to_nifti.io

   Return the directory associated with the patient, study and series of
   the NIfTI meta-data.


.. py:function:: write_nifti(nifti_data, destination, zip, series_directory=None)
   :module: dicomifier.dicom_to_nifti.io

   Write the NIfTI image and meta-data in the given destination.

   :param nifti_data: Pair of NIfTI image and meta-data
   :param destination: Destination directory
   :param zip: whether to zip the NIfTI files
   :param series_directory: if provided, override the automated 
       series-based output directory name
