dicomifier.dicom_to_nifti.convert
=================================


.. py:class:: dicomifier.dicom_to_nifti.convert.SeriesContext(data_set)
  
  Add series context to logger. 
      

  .. py:method:: filter(record)
    
    Determine if the specified record is to be logged.
    
    Is the specified record to be logged? Returns 0 for no, nonzero for
    yes. If deemed appropriate, the record may be modified in-place.

.. py:function:: dicomifier.dicom_to_nifti.convert.convert_and_write_series(series_files, destination, zip, dtype=None, finder=None)
  
  Convert the files containing a single series and save the result in the
  given destination.
  
  :param series_files: Collection of paths to scan for DICOM files
  :param destination: Destination directory
  :param zip: whether to zip the NIfTI files
  :param dtype: if not None, force the dtype of the result image
  :param finder: if not None, series finder object to overwrite the Series
      Instance UID

.. py:function:: dicomifier.dicom_to_nifti.convert.convert_paths(paths, destination, zip, dtype=None)
  
  Convert the DICOM files found in a collection of paths (files, 
  directories, or DICOMDIR) and save the result in the given destination.
  
  :param paths: Collection of paths to scan for DICOM files
  :param destination: Destination directory
  :param zip: whether to zip the NIfTI files
  :param dtype: if not None, force the dtype of the result image

.. py:function:: dicomifier.dicom_to_nifti.convert.convert_series(series_files, dtype=None, finder=None)
  
  Return the NIfTI image and meta-data from the files containing a single
  series.
  
  :param dtype: if not None, force the dtype of the result image
  :param finder: if not None, series finder object to overwrite the Series
      Instance UID

.. py:function:: dicomifier.dicom_to_nifti.convert.convert_series_data_sets(data_sets, dtype=None)
  
  Convert a list of dicom data sets into Nfiti
  
  :param data_sets: list of dicom data sets to convert
  :param dtype: if not None, force the dtype of the result image

.. py:function:: dicomifier.dicom_to_nifti.convert.merge_images_and_meta_data(images_and_meta_data)
  
  Merge the pixel and meta-data of geometrically coherent images.
      
