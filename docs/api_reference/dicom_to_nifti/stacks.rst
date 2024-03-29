dicomifier.dicom_to_nifti.stacks
================================


.. py:module:: dicomifier.dicom_to_nifti.stacks


.. py:class:: OrientationGetter()
   :module: dicomifier.dicom_to_nifti.stacks

   Return the ideal orientation of a data set, i.e. allow small variations
   in the actual orientation.


   .. py:property:: OrientationGetter.orientations
      :module: dicomifier.dicom_to_nifti.stacks


.. py:function:: frame_group_index_getter(data_set, tag)
   :module: dicomifier.dicom_to_nifti.stacks

   Return bruker_to_dicom-specific frame group information.



.. py:function:: ge_complex_image_component_getter(data_set, tag)
   :module: dicomifier.dicom_to_nifti.stacks

   Return GE-specific Complex Image Component data.



.. py:function:: ge_diffusion_getter(data_set, tag)
   :module: dicomifier.dicom_to_nifti.stacks

   Return GE-specific diffusion data.



.. py:function:: get_diffusion(data_set, tag)
   :module: dicomifier.dicom_to_nifti.stacks

   Get b-value and gradient diffusion from the data_set.



.. py:function:: get_dimension_index(data_set, tag, in_stack_position_index)
   :module: dicomifier.dicom_to_nifti.stacks

   Return the dimension index pointer without InStackPosition in order to 
   find the different volumes

   :param in_stack_position_index: index of the In Stack Position element 
       within the Dimension Index tuple


.. py:function:: get_frame_position(data_set, frame_index)
   :module: dicomifier.dicom_to_nifti.stacks

   Get the position of the specified frame.



.. py:function:: get_in_stack_position_index(data_set)
   :module: dicomifier.dicom_to_nifti.stacks

   Return the position of In Stack Position element inside the Dimension
   Index.


.. py:function:: get_stacks(data_sets, extra_splitters=None)
   :module: dicomifier.dicom_to_nifti.stacks

   Return the stacks contained in the data sets. The result is a dictionary
   in which the values are pairs of (data_set, frame_index) (in the case
   of single-frame data sets, frame_index is None), and in which the keys
   are tuples of selectors. In this context, a selector is defined as 
   a pair of (group sequence, group, tag) (group sequence and group being
   None for single-frame data sets), and a value.

   :param data_sets: list of dicom data sets
   :param extra_splitters: additional splitters to be used when building
       stacks


.. py:function:: siemens_coil_getter(data_set, tag)
   :module: dicomifier.dicom_to_nifti.stacks

   Return Siemens-specific coil identifier.



.. py:function:: sort(key, frames)
   :module: dicomifier.dicom_to_nifti.stacks

   Sort the frames of a stack according to the items present in the 
   stack key.
