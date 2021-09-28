search
======

Search for DICOM data matching the supplied search terms.

Search terms can be specified either as a tag name or tag number, and may be followed by a value. Value-less search terms match files where the tag is present, while valued search terms match elements following the DICOM rules (match any value in the element, ``?`` and ``*`` wildcards for strings).

**Usage**::

  dicomifier search [options] source [source ...]

Arguments
---------

.. option:: source

  DICOM file, directory or DICOMDIR.

Options
-------

.. option:: -m, --match

  Search criteria

.. option:: -p, --pipe

  Format data to be sent to ``dicomifier to-nifti``

.. option:: -v <level>, --verbose <level>

  Verbosity level (*warning*, *info*, or *debug*)
