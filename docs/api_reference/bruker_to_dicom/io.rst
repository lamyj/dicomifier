dicomifier.bruker_to_dicom.io
=============================


.. py:module:: dicomifier.bruker_to_dicom.io


.. py:function:: create_dicomdir(paths, directory, patient_key, study_key, series_key, image_key)
   :module: dicomifier.bruker_to_dicom.io

   Create a DICOMDIR from all files found in paths.

   :param paths: list of DICOM files and directories storing DICOM files
   :param directory: destination directory of the DICOMDIR
   :param patient_key: patient-level keys to add to the DICOMDIR
   :param study_key: study-level keys to add to the DICOMDIR
   :param series_key: series-level keys to add to the DICOMDIR
   :param image_key: image-level keys to add to the DICOMDIR


.. py:function:: get_bruker_info(directory)
   :module: dicomifier.bruker_to_dicom.io

   Return basic information of a Bruker data set stored in the specified
   directory as a DICOM data set with the Patient, General Study,
   Patient Study, and General Series modules.
