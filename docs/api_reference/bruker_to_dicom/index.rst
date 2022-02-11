dicomifier.bruker_to_dicom
==========================

.. toctree::
   :maxdepth: 2
   :caption: Modules
   :titlesonly:

   convert.rst
   io.rst
   iods.rst


.. py:class:: FrameIndexGenerator(data_set)
   :module: dicomifier.bruker_to_dicom
   :canonical: dicomifier.bruker_to_dicom.frame_index_generator.FrameIndexGenerator

   Generate the indices to iterate through the frame groups of a Bruker
   data set.


   .. py:property:: FrameIndexGenerator.dependent_fields
      :module: dicomifier.bruker_to_dicom

      Names of all fields mentioned in the frame groups.



   .. py:property:: FrameIndexGenerator.frame_groups
      :module: dicomifier.bruker_to_dicom


   .. py:property:: FrameIndexGenerator.frames_count
      :module: dicomifier.bruker_to_dicom

      Total number of frames.



   .. py:method:: FrameIndexGenerator.get_linear_index(index)
      :module: dicomifier.bruker_to_dicom

      Return the linear index associated to the multi-dimensional index.

