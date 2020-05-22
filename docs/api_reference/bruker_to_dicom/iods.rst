dicomifier.bruker_to_dicom.iods
===============================

.. py:function:: dicomifier.bruker_to_dicom.iods.enhanced_mr_image_storage(bruker_data_set, transfer_syntax)
  
  Convert bruker_data_set into dicom_data_set by using the correct 
  transfer_syntax.
  This function will create one data_set per reconstruction 
  (multiFrame format)
  
  :param bruker_data_set: Bruker data set in dictionary form
  :param transfer_syntax: Wanted transfer syntax for the conversion

.. py:function:: dicomifier.bruker_to_dicom.iods.mr_image_storage(bruker_data_set, transfer_syntax)
  
  Function to convert specific burker images into dicom
  
  :param bruker_data_set: bruker data set to convert
  :param transfer_syntax: target transfer syntax
