.. _getting-started:

Getting started
===============

Installing pre-compiled packages
--------------------------------

If you have `Anaconda <https://anaconda.org>`_ installed, a pre-built package is available on `conda-forge <https://conda-forge.org/>`_: running ``conda install -c conda-forge dicomifier`` will install the latest stable version.

Compiling from source
---------------------

If you need to compile Dicomifier from scratch, you will need

- A build environment with a C++11 compiler and Python ≥ 3.5
- `CMake <https://cmake.org>`_ ≥ 3.5
- The `Boost libraries <https://boost.org>`_ ≥ 1.58
- `Pybind11 <https://pybind11.readthedocs.io>`_ ≥ 2.0.1
- `Odil <https://odil.readthedocs.io>`_ ≥ 0.12.0
- The `dateutil <https://pypi.org/project/py-dateutil/>`_, `nibabel <https://nipy.org/nibabel/>`_ and `numpy <https://numpy.org/>`_ Python modules

If using Conda, all dependencies can be installed by ``conda install --yes -c conda-forge boost cmake nibabel numpy odil pkg-config pybind11 python-dateutil``

The compilation process follows the usual CMake workflow: 

- Specify which Python interpreter you use. It can be ``python``, ``python3``, or a more specific version, e.g. ``python3.10``. Store it in an environment variable, e.g. ``export PYTHON_EXECUTABLE=$(which python3)``
- Choose an install destination. It can be within the source directory, or in any other directory that you can write into. Store it in an environment variable, e.g. ``export DICOMIFIER=${HOME}/src/dicomifier/install``
- Create a ``build`` directory in the source directory.
- From the source directory, run ``cmake -DPYTHON_EXECUTABLE="${PYTHON_EXECUTABLE}" -DCMAKE_INSTALL_PREFIX="${DICOMIFIER}" -S . -B build`` to configure the build environment.
- Run ``cmake --build build --parallel`` to build Dicomifier.
- Finally, run ``cmake --install build`` to install Dicomifier to your specified location.

You may need to adjust your environment before you can use Dicomifier:

.. code:: bash
    
    export PATH="${DICOMIFIER}/bin:${PATH}"
    export LD_LIBRARY_PATH="${DICOMIFIER}/lib:${LD_LIBRARY_PATH}"
    PYTHONPREFIX=$(grep PYTHON_SITE_PACKAGES foo-build/CMakeCache.txt | cut -d= -f2)
    export PYTHONPATH="${DICOMIFIER}/${PYTHONPREFIX}:${PYTHONPATH}"

You may also refer to the `continuous integration scripts <https://github.com/lamyj/dicomifier/tree/master/.ci>`_ to see working examples.

Basic usage
-----------

Dicomifier has a single command line executable, called ``dicomifier``, which accepts :ref:`several commands <commands>`:

- List convertible data in a directory: ``dicomifier list my_directory``
- Convert Bruker data to DICOM: ``dicomifier to-dicom bruker_directory dicom_directory``
- Convert Bruker or DICOM data to NIfTI: ``dicomifier to-nifti bruker_or_dicom_directory nifti_directory``

To list all available commands, run ``dicomifier --help``; to get help about a specific command, run ``dicomifier some-command --help``.
