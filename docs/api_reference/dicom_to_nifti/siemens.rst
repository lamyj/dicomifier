dicomifier.dicom_to_nifti.siemens
=================================


.. py:module:: dicomifier.dicom_to_nifti.siemens


.. py:function:: parse_csa(csa)
   :module: dicomifier.dicom_to_nifti.siemens

   Return a dictionary of (tag, items) of the CSA.



.. py:function:: parse_element(csa, start)
   :module: dicomifier.dicom_to_nifti.siemens

   Return a pair (name, items), total_size



.. py:function:: parse_item(csa, start)
   :module: dicomifier.dicom_to_nifti.siemens

   Return a pair content, size



.. py:function:: parse_protocol(data)
   :module: dicomifier.dicom_to_nifti.siemens

   Parse (as a nested dictionary) the ASCII version of protocol data.
