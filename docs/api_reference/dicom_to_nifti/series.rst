dicomifier.dicom_to_nifti.series
================================

.. py:class:: dicomifier.dicom_to_nifti.series.DefaultSeriesFinder()
  
  Simple series finder based on Series Instance UID.
      

.. py:class:: dicomifier.dicom_to_nifti.series.SiemensXAClassic2DSeriesFinder()
  
  Siemens MRI scanners with version XA have an export option which causes
  multi-volume series (e.g. fMRI or diffusion) to be exported as separate
  series with differente Series Instance UIDs, but with the same Series
  Number.


.. py:function:: dicomifier.dicom_to_nifti.series.split_series(files)
  
  Split specified DICOM files in series.
      
