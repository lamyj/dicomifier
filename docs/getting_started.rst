.. _getting-started:

Getting started
===============

Installing pre-compiled packages
--------------------------------

If you are using a Conda-like environment (e.g. `Anaconda <https://anaconda.org>`_, `Miniconda <https://docs.conda.io/projects/miniconda>`_, `Micromamba <https://mamba.readthedocs.io/>`_), a pre-built package is available on `conda-forge <https://conda-forge.org/>`_: running ``conda install -c conda-forge dicomifier`` will install the latest stable version.

Compiling from source
---------------------

If you need to compile Dicomifier from scratch, you will need

- A build environment with a C++11 compiler and Python ≥ 3.6
- `CMake <https://cmake.org>`_ ≥ 3.5
- The `Boost libraries <https://boost.org>`_ ≥ 1.58
- `Pybind11 <https://pybind11.readthedocs.io>`_ ≥ 2.0.1
- `Odil <https://odil.readthedocs.io>`_ ≥ 0.12.2
- The `dateutil <https://pypi.org/project/py-dateutil/>`_, `nibabel <https://nipy.org/nibabel/>`_ and `numpy <https://numpy.org/>`_ Python modules

If using Conda, all dependencies can be installed by ``conda install --yes -c conda-forge boost cmake nibabel numpy odil pkg-config pybind11 python-dateutil``

The compilation process follows the usual CMake workflow: 

- Specify which Python interpreter you use. It can be ``python``, ``python3``, or a more specific version, e.g. ``python3.10``. Store it in an environment variable, e.g. ``export PYTHON_EXECUTABLE=$(which python3)``
- Choose an install directory. It can be within the source directory, or in any other directory that you can write into. Store it in an environment variable, e.g. ``export DICOMIFIER=${HOME}/src/dicomifier/install``
- Create a ``build`` directory in the source directory.
- From the source directory, run ``cmake -DPYTHON_EXECUTABLE="${PYTHON_EXECUTABLE}" -DCMAKE_INSTALL_PREFIX="${DICOMIFIER}" -S . -B build`` to configure the build environment.
- Run ``cmake --build build --parallel`` to build Dicomifier.
- Finally, run ``cmake --install build`` to install Dicomifier to your specified location.

You may need to adjust your environment (e.g. by modifying your *.bashrc* file) before you can use Dicomifier:

- From the build directory, run ``grep PYTHON_SITE_PACKAGES CMakeCache.txt | cut -d= -f2`` to determine the path to the Python files within the install directory
- Modify the search paths so that they include the install directory. In the following code sample, the first line must match the install directory, and in the last line, the ``lib/python3.11/site-packages`` part must match the output of the previous command
    
    .. code:: bash
        
        export DICOMIFIER=${HOME}/src/dicomifier/install
        export PATH="${DICOMIFIER}/bin:${PATH}"
        export LD_LIBRARY_PATH="${DICOMIFIER}/lib:${LD_LIBRARY_PATH}"
        export PYTHONPATH="${DICOMIFIER}/lib/python3.11/site-packages:${PYTHONPATH}"

You may also refer to the `continuous integration scripts <https://github.com/lamyj/dicomifier/tree/master/.ci>`_ to see working examples.

Basic usage
-----------

Dicomifier has a single command line executable, called ``dicomifier``, which accepts :ref:`several commands <commands>`:

- List convertible data in a directory: ``dicomifier list my_directory``
- Convert Bruker data to DICOM: ``dicomifier to-dicom bruker_directory dicom_directory``
- Convert Bruker or DICOM data to NIfTI: ``dicomifier to-nifti bruker_or_dicom_directory nifti_directory``

To list all available commands, run ``dicomifier --help``; to get help about a specific command, run ``dicomifier some-command --help``.
