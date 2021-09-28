dicomifier.dicom_to_nifti.image
===============================


.. py:module:: dicomifier.dicom_to_nifti.image


.. py:function:: find_element(data_set, frame_index, tag, sequence)
   :module: dicomifier.dicom_to_nifti.image

   Return a data set, potentially nested inside the given data set and
   sequence, which contain the given tag.


.. py:function:: get_geometry(stack)
   :module: dicomifier.dicom_to_nifti.image

   Compute the geometry (origin, spacing, orientation) for the given stack.



.. py:function:: get_image(stack, dtype, cache=None)
   :module: dicomifier.dicom_to_nifti.image

   Get the NIfTI image of the given stack

   :param stack: collection of data set and an associated frame number for
       multi-frame datasets
   :param dtype: if not None, force the dtype of the result image
   :param cache: optional cache of linear pixel data for multi-frame data
       sets


.. py:function:: get_linear_pixel_data(data_set)
   :module: dicomifier.dicom_to_nifti.image

   Return a linear numpy array containing the pixel data.


.. py:function:: get_orientation(stack)
   :module: dicomifier.dicom_to_nifti.image

   Compute the orientation of the stack.


.. py:function:: get_origin(stack)
   :module: dicomifier.dicom_to_nifti.image

   Compute the origin of the stack.


.. py:function:: get_shaped_pixel_data(data_set, frame_index, linear_pixel_data)
   :module: dicomifier.dicom_to_nifti.image

   Return the pixel data located in a dataset (and possibly one of its
   frame) shaped according to numer of rows, columns and frames.


.. py:function:: get_spacing(stack)
   :module: dicomifier.dicom_to_nifti.image

   Compute the spacing of the stack.
