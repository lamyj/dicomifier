.. _getting-started:

Getting started
===============

Installing pre-compiled packages
--------------------------------

If you have `Anaconda <https://anaconda.org>`_ installed, a pre-built package is available on `conda-forge <https://conda-forge.org/>`_: running ``conda install -c conda-forge dicomifier`` will install the latest stable version.

Debian and Ubuntu user can also use unofficial packages: following the `instructions to set up the unofficial repository <https://github.com/lamyj/packages>`_, and install the *dicomifier-cli* package with the usual tools provided by your distribution. The latest stable version of Dicomifier is available for the two latest long-term support versions of Ubuntu and for the two latest versions of Debian. Old versions of Ubuntu and Debian may be supported, but may not have the latest version of Dicomifier.

Compiling from source
---------------------

If you need to compile Dicomifier from scratch, you will need

- A build environment with a C++11 compiler and Python ≥ 3.5
- `CMake <https://cmake.org>`_ ≥ 3.5
- The `Boost libraries <https://boost.org>`_ ≥ 1.58
- `Pybind11 <https://pybind11.readthedocs.io>`_ ≥ 2.0.1
- `Odil <https://odil.readthedocs.io>`_ ≥ 0.12.0
- The `dateutil <https://pypi.org/project/py-dateutil/>`_, `nibabel <https://nipy.org/nibabel/>`_ and `numpy <https://numpy.org/>`_ Python modules

The compilation process follows the usual CMake workflow: create a build directory, run ``cmake`` to configure the build environment, and run ``cmake --build .`` to build Dicomifier.

You may also refer to the `continuous integration scripts <https://github.com/lamyj/dicomifier/tree/master/.ci>`_ to see working examples.

Basic usage
-----------

Dicomifier has a single command line executable, called ``dicomifier``, which accepts :ref:`several commands <commands>`:

- List convertible data in a directory: ``dicomifier list my_directory``
- Convert Bruker data to DICOM: ``dicomifier to-dicom bruker_directory dicom_directory``
- Convert Bruker or DICOM data to NIfTI: ``dicomifier to-nifti bruker_or_dicom_directory nifti_directory``

To list all available commands, run ``dicomifier --help``; to get help about a specific command, run ``dicomifier some-command --help``.
