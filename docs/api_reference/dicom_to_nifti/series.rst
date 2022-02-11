dicomifier.dicom_to_nifti.series
================================


.. py:class:: DefaultSeriesFinder()
   :module: dicomifier.dicom_to_nifti.series
   :canonical: dicomifier.dicom_to_nifti.series.default_series_finder.DefaultSeriesFinder

   Simple series finder based on Series Instance UID.




.. py:class:: SiemensXAClassic2DSeriesFinder()
   :module: dicomifier.dicom_to_nifti.series
   :canonical: dicomifier.dicom_to_nifti.series.siemens_xa_classic_2d_series_finder.SiemensXAClassic2DSeriesFinder

   Siemens MRI scanners with version XA have an export option which causes
   multi-volume series (e.g. fMRI or diffusion) to be exported as separate
   series with differente Series Instance UIDs, but with the same Series
   Number.



.. py:module:: dicomifier.dicom_to_nifti.series


.. py:function:: split_series(files)
   :module: dicomifier.dicom_to_nifti.series

   Split specified DICOM files in series.

