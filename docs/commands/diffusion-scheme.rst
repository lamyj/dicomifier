diffusion-scheme
================

Convert dMRI meta-data stored in JSON (aliases: *diffusion*, *diff*).

**Usage**::
  
  dicomifier diffusion-scheme [options] source format [destination ...]

Arguments
---------

.. option:: source
  
  Source JSON file

.. option:: format
  
  Output format, among:
  
  - *mrtrix*
  - *fsl*

.. option:: [destination ...]
  
  Output files, depends on the output format
  
  - *mrtrix*: single scheme file
  - *fsl*: the *bvecs* and *bvals* files, in that order

Options
-------

.. option:: -i <image>, --image <image>
  
  Image file for formats using image-based direction coordinates

.. option:: -v <level>, --verbose <level>
  
  Verbosity level (*warning*, *info*, or *debug*)
