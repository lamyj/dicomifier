to-nifti
========

Convert Bruker or DICOM data to NIfTI+JSON (aliases: *nifti*, *nii*).

**Usage**::
  
  dicomifier to-nifti [options] source [source ...] destination

All files are saved in the ``destination`` directory, with a user-definable layout based on DICOM tag names. If no layout is specified, a *Subject/Study/Series* hierarchy is used. A user-specific layout can e.g.g skip the subject and study levels and to only keep the series number and description: 

.. code:: bash
  
  dicomifier to-nifti -l {SeriesNumber}_{SeriesDescription} source_directory/ destination_directory

Fallback elements are also supported: to use the contents of *PatientName*, and, if missing, use the contents of *PatientID*, the call would be

.. code:: bash
  
  dicomifier to-nifti -l '{PatientName|PatientID}'/{SeriesNumber} source_directory/ destination_directory

In the leaf directory of the layout, NIfTI and JSON files will be saved with a incremental numeric name: since NIfTI can only accomodate one affine matrix per file, data sets with multiple image orientation (e.g. scout images) will be saved as ``1.nii``, ``2.nii``, etc.

The JSON file contains most of the fields present in the source DICOM data (Bruker data is implicitely converted to DICOM using :doc:`to-dicom`). The JSON data is a dictionary of the DICOM elements: elements with a public name (e.g. *PatientName*) will be recorded under this name, other elements (e.g. private elements) will be recorded using their numeric tag (e.g. *00291010*). The value of each entry will always be an array, in order to keep a consistent representation between single-valued items (e.g. *AcquisitionDate*) and multiple-valued items (e.g. *ImageType*). The dimension and the shape of the array depend on the organization of the image data:

- An *ImageType* element with value *["ORIGINAL", "PRIMARY"]* is a 1D array: it applies to the whole NIfTI data
- An *EchoTime* element with value *[[10], [20]]* is a 2D array: for a 4D NIfTI, each item of the top-level array (respectively *[10]* and *[20]*) applies to a 3D volume of the NIfTI data. The first volume will have an associated echo time of 10 ms, and the second volume an associated echo time of 20 ms.

More complex meta-data rarely happen, but follow the same rules: a 3D array accompanying a 4D NIfTI file describes slice-dependent data.

The semantics of the elements is driven by the DICOM standard: echo times are in milliseconds, flip angles in degrees, etc.

DICOM elements stored as part of the NIfTI header will not appear in the JSON file. This is the case for *Rows*, *Columns*, *ImageOrientationPatient*, *ImagePositionPatient*, *PixelSpacing*, *SliceLocation* , *PixelRepresentation*, *HighBit*, *BitsStored*, *BitsAllocated*, and *PixelData*.

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
