dicomifier.dicom_to_nifti.image
===============================


.. py:function:: dicomifier.dicom_to_nifti.image.find_element(data_set, frame_index, tag, sequence)
  
  Return a data set, potentially nested inside the given data set and
  sequence, which contain the given tag.

.. py:function:: dicomifier.dicom_to_nifti.image.get_geometry(stack)
  
  Compute the geometry (origin, spacing, orientation) for the given stack.
      

.. py:function:: dicomifier.dicom_to_nifti.image.get_image(stack, dtype, cache=None)
  
  Get the NIfTI image of the given stack
  
  :param stack: collection of data set and an associated frame number for
      multi-frame datasets
  :param dtype: if not None, force the dtype of the result image
  :param cache: optional cache of linear pixel data for multi-frame data 
      sets

.. py:function:: dicomifier.dicom_to_nifti.image.get_linear_pixel_data(data_set)
  
  Return a linear numpy array containing the pixel data.

.. py:function:: dicomifier.dicom_to_nifti.image.get_orientation(stack)
  
  Compute the orientation of the stack.

.. py:function:: dicomifier.dicom_to_nifti.image.get_origin(stack)
  
  Compute the origin of the stack.

.. py:function:: dicomifier.dicom_to_nifti.image.get_shaped_pixel_data(data_set, frame_index, linear_pixel_data)
  
  Return the pixel data located in a dataset (and possibly one of its 
  frame) shaped according to numer of rows, columns and frames.

.. py:function:: dicomifier.dicom_to_nifti.image.get_spacing(stack)
  
  Compute the spacing of the stack.
