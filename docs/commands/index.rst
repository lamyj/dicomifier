.. _commands:

Commands
========

Dicomifier has a single command line executable, called ``dicomifier``, which accepts :ref:`several commands <commands>`:

- List convertible data in a directory: ``dicomifier list my_directory``
- Search for DICOM data matching the supplied search terms: ``dicomifier search -m PatientName="Doe^*" dicom_directory``
- Convert Bruker data to DICOM: ``dicomifier to-dicom bruker_directory dicom_directory``
- Convert Bruker or DICOM data to NIfTI+JSON: ``dicomifier to-nifti bruker_or_dicom_directory nifti_directory``
- Extract diffusion data from NIfTI+JSON: ``dicomifier diffusion-scheme meta_data_file mrtrix diffusion.scheme`` or ``dicomifier diffusion-scheme meta_data_file fsm diffusion.bvecs diffusion.bvals``

To list all available commands, run ``dicomifier --help``; to get help about a specific command, run ``dicomifier some-command --help``.

.. toctree::
   :maxdepth: 2
   :caption: Available commands
   :titlesonly:

   list.rst
   search.rst
   to-dicom.rst
   to-nifti.rst
   diffusion-scheme.rst
