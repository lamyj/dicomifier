dicomifier.dicom_to_nifti.siemens
=================================


.. py:function:: dicomifier.dicom_to_nifti.siemens.parse_csa(csa)
  
  Return a dictionary of (tag, items) of the CSA.
      

.. py:function:: dicomifier.dicom_to_nifti.siemens.parse_element(csa, start)
  
  Return a pair (name, items), total_size
      

.. py:function:: dicomifier.dicom_to_nifti.siemens.parse_item(csa, start)
  
  Return a pair content, size
      

.. py:function:: dicomifier.dicom_to_nifti.siemens.parse_protocol(data)
  
  Parse (as a nested dictionary) the ASCII version of protocol data.
      
