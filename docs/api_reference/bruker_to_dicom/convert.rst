dicomifier.bruker_to_dicom.convert
==================================


.. py:module:: dicomifier.bruker_to_dicom.convert


.. py:class:: ReconstructionContext(path)
   :module: dicomifier.bruker_to_dicom.convert

   Add reconstruction context to logger. 



   .. py:method:: ReconstructionContext.filter(record)
      :module: dicomifier.bruker_to_dicom.convert

      Determine if the specified record is to be logged.

      Is the specified record to be logged? Returns 0 for no, nonzero for
      yes. If deemed appropriate, the record may be modified in-place.


.. py:function:: convert_directory(source, dicomdir, multiframe, writer)
   :module: dicomifier.bruker_to_dicom.convert

   Convert a Bruker directory to DICOM and write the files.

   :param source: source directory
   :param dicomdir: whether to create a DICOMDIR
   :param multiframe: whether to create multi-frame DICOM objects
   :param writer: writer object from the io module


.. py:function:: convert_element(bruker_data_set, dicom_data_set, bruker_name, dicom_name, type_, getter, frame_index, generator, vr_finder)
   :module: dicomifier.bruker_to_dicom.convert

   Convert a Bruker element to a DICOM element.

   :param bruker_data_set: source Bruker data set
   :param dicom_data_set: destination DICOM data set
   :param bruker_name: Bruker name of the element
   :param dicom_name: DICOM name of the element
   :param type_: DICOM type of the element (PS 3.5, 7.4)
   :param getter: function returning the value using the Bruker data set,
       the generator and the frame index or None (direct access)
   :param frame_index: index in frame group 
   :param generator: FrameIndexGenerator associated with the 
       Bruker data set
   :param vr_finder: function returning the DICOM VR from the dicom_name


.. py:function:: convert_module(bruker_data_set, dicom_data_set, module, frame_index, generator, vr_finder)
   :module: dicomifier.bruker_to_dicom.convert

   Convert a DICOM module..

   :param bruker_data_set: source Bruker data set
   :param dicom_data_set: destination DICOM data set
   :param module: sequence of 4-element tuples describing the conversions
       (Bruker name, DICOM name, DICOM type, getter)
   :param frame_index: index in a frame group
   :param generator: object that will manage the frame_index
   :param vr_finder: function to find the VR knowing only the dicom_name


.. py:function:: convert_reconstruction(data_set, iod_converter, writer)
   :module: dicomifier.bruker_to_dicom.convert

   Convert and save a single reconstruction.

   :param iod_converter: conversion function
   :param writer: writer object from the io module


.. py:function:: to_2d(data_set)
   :module: dicomifier.bruker_to_dicom.convert

   Convert the Bruker data set from 3D to 2D.

