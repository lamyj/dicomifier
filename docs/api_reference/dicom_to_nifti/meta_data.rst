dicomifier.dicom_to_nifti.meta_data
===================================


.. py:function:: dicomifier.dicom_to_nifti.meta_data.convert_data_set(data_set, specific_character_set)
  
  Convert a DICOM data set to its NIfTI+JSON representation.
      

.. py:function:: dicomifier.dicom_to_nifti.meta_data.convert_element(element, specific_character_set)
  
  Convert a DICOM element to its NIfTI+JSON representation: the "Value"
  (or "InlineBinary") attribute of its standard DICOM JSON 
  representation.

.. py:function:: dicomifier.dicom_to_nifti.meta_data.get_meta_data(stack, cache=None)
  
  Get the meta-data of the current stack 
  
  will keep the priority order for repeting element with the following rules:
  low_priority = per_frame_seq
  high_priority = top_level (data_set)
  (if the same element is present in both shared and per_frame,
  we will keep the element of the shared seq)
  
  :param stack: collection of data set and an associated frame number for
      multi-frame datasets
  :param cache: optional cache of meta-data for multi-frame data sets

.. py:function:: dicomifier.dicom_to_nifti.meta_data.get_tag_name(tag)
  
  Convert a DICOM tag to its NIfTI+JSON representation: the tag keyword
  if known, and the standard DICOM JSON representation otherwise.
