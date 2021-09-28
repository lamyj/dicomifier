to-nifti
========

Convert Bruker or DICOM data to NIfTI (aliases: *nifti*, *nii*).

**Usage**::

  dicomifier to-nifti [options] source [source ...] destination

Arguments
---------

.. option:: source

  Directories to scan for convertible data. This can be a Bruker directory, DICOM files or directories or DICOMDIR, or ``-``. In the latter case, a NUL-separated list of file names is read from the standard input.

.. option:: destination

  Output directory

Options
-------

.. option:: --dtype <dtype>, -d <dtype>

  Pixel type

.. option:: --zip, -z

  Compress NIfTI files

.. option:: -v <level>, --verbose <level>

  Verbosity level (*warning*, *info*, or *debug*)
