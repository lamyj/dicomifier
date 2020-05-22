Dicomifier -- A medical image converter
=======================================

Dicomifier is a set of tools to convert Bruker data to DICOM files, and DICOM files to NIfTI. It retains meta-data (e.g. MR parameters such as echo time or subject parameters such as weight or height) throughout the conversion process, and aligns the meta-data from Bruker on the DICOM dictionary for unified processing pipelines.

Getting started? Have a look at the :ref:`installation instructions and basic usage <getting-started>`. If you're in a hurry and have `Anaconda <https://anaconda.org>`_ installed, ``conda install -c conda-forge dicomifier`` should get you going.

Need to know more about your options and arguments? The :ref:`commands reference <commands>` is for you.

Want to find out how it works? The :ref:`API reference <api-reference>` is a good place to start, followed by the `source code <https://github.com/lamyj/dicomifier>`_.

Interested in how the vendors store diffusion MRI meta-data? There is a :ref:`section <diffusion>` just for you.

.. toctree::
   :maxdepth: 2
   :caption: Contents
   :titlesonly:

   getting_started.rst
   commands/index.rst
   api_reference/index.rst
   diffusion/index.rst

Indices and tables
==================

* :ref:`genindex`
