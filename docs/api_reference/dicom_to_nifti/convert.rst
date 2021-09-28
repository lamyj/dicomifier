dicomifier.dicom_to_nifti.convert
=================================


.. py:module:: dicomifier.dicom_to_nifti.convert


.. py:class:: SeriesContext(data_set)
   :module: dicomifier.dicom_to_nifti.convert

   Add series context to logger.



   .. py:method:: SeriesContext.filter(record)
      :module: dicomifier.dicom_to_nifti.convert

      Determine if the specified record is to be logged.

      Returns True if the record should be logged, or False otherwise.
      If deemed appropriate, the record may be modified in-place.


.. py:function:: convert_paths(paths, destination, zip, dtype=None)
   :module: dicomifier.dicom_to_nifti.convert

   Convert the DICOM files found in a collection of paths (files,
   directories, or DICOMDIR) and save the result in the given destination.

   :param paths: Collection of paths to scan for DICOM files
   :param destination: Destination directory
   :param zip: whether to zip the NIfTI files
   :param dtype: if not None, force the dtype of the result image


.. py:function:: convert_series(series_files, dtype=None, finder=None)
   :module: dicomifier.dicom_to_nifti.convert

   Return the NIfTI image and meta-data from the files containing a single
   series.

   :param dtype: if not None, force the dtype of the result image
   :param finder: if not None, series finder object to overwrite the Series
       Instance UID


.. py:function:: convert_series_data_sets(data_sets, dtype=None)
   :module: dicomifier.dicom_to_nifti.convert

   Convert a list of dicom data sets into Nfiti

   :param data_sets: list of dicom data sets to convert
   :param dtype: if not None, force the dtype of the result image


.. py:function:: merge_images_and_meta_data(images_and_meta_data)
   :module: dicomifier.dicom_to_nifti.convert

   Merge the pixel and meta-data of geometrically coherent images.
