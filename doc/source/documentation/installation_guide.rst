Installation Guide
==================

Requirements
------------

Softwares
*********

Following tools are usefull for install Dicomifier from Binary file:

Following tools are usefull for install Dicomifier from Source files:
- Mercurial (distributed revision control tool)
- CMake (software for managing the build process of software)
- Ninja (build system)

By Downloading Binary file
--------------------------

First, you should download a release version from the :ref:`Dowloading Page <Balise_ReleaseVersion>`.

TODO

.. _Balise_Checkout:

By Checking out Source files
----------------------------

Source files can be download at this address: https://medipy.u-strasbg.fr/scm/hg/fli-iam/dicomifier.

Compilation (UNIX)
******************

- Open a command prompt (ctrl+alt+t).

- Use Mercurial for getting Source code.

.. code-block:: sh
    
    hg clone https://medipy.u-strasbg.fr/scm/hg/fli-iam/dicomifier

- A new directory 'dicomifier/' is available, go inside:

.. code-block:: sh
    
    cd dicomifier/
    
- Create new directory 'build':

.. code-block:: sh
    
    mkdir build
    
- Go to the build directory:

.. code-block:: sh
    
    cd build

- Generate Makefile:

.. code-block:: sh
    
    cmake -G Ninja -D CMAKE_CXX_FLAGS="-std=c++0x" ../

- Compile Dicomifier project:

.. code-block:: sh
    
    ninja

A binary file 'dicomifier' is now available into the directory 'dicomifier/build/src/appli/'.
