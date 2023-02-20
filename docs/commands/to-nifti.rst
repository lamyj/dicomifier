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

.. option:: --layout <layout>, -l <layout>
  
  Set the layout of the destination directory. Values between braces are replaced by the value of the corresponding meta-data item. A set of pipe-separated items can be specified in the braces, in which case the first item present in the meta-data will be used. If no corresponding item is found in the meta-data, the empty string will be used

.. option:: --effective-b-values, -e
  
  Store effective b-values (i.e. accounting for imaging gradients) instead of ideal ones. This option should be enabled the imaging gradients add a non-trivial part of diffusion weighting (e.g. stimulated echoes). Note that the ideal b-values may still be stored in private data fields

.. option:: --diffusion-scheme <format>, -s <format>
  
  Save diffusion data in specified format (*mrtrix* or *fsl*), along with the NIfTI and JSON files

.. option:: -v <level>, --verbose <level>
  
  Verbosity level (*warning*, *info*, or *debug*)
