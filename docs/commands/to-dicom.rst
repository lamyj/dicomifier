to-dicom
========

Convert Bruker data to DICOM (aliases: *dicom*, *dcm*).

**Usage**::
  
  dicomifier to-dicom [options] source [source ...] destination

Arguments
---------

.. option:: source
  
  Directories to scan for convertible data. This can be a top-level Bruker directory, or a sub-directory containing a single experiment or recontruction.

.. option:: destination
  
  Output directory

Options
-------

.. option:: --dicomdir, -d
  
  Creates a DICOMDIR in the *destination* directory

.. option:: --layout <layout>, -l <layout>
  
  Layout of the DICOM files on the disk, among
  
  - *flat*: all files are stored in the *destination* directory
  - *nested*: files are stored using a subject/study/series hierarchy in the *destination* directory (default)

.. option:: --multiframe, -m
  
  Save multiframe DICOM files (one file per serie) instead of the classic single-frame DICOM files (one file per slice)

.. option:: --transfer-syntax <syntax>, -t <syntax>
  
  Transfer syntax of the output files, among
  
  - *ImplicitVRLittleEndian* (default)
  - *ExplicitVRLittleEndian*

.. option:: -v <level>, --verbose <level>
  
  Verbosity level (*warning*, *info*, or *debug*)
