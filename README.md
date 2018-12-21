# Dicomifier

[![Build Status (Travis)](https://travis-ci.org/lamyj/dicomifier.svg?branch=master)](https://travis-ci.org/lamyj/dicomifier)

Dicomifier is a set of tools to convert Bruker data to DICOM files, and DICOM files to NIfTI. It retains meta-data (e.g. MR parameters such as echo time or subject parameters such as weight or height) throughout the conversion process, storing them in [JSON](https://en.wikipedia.org/wiki/JSON) format, allowing easy access in multiple environments ([command-line](https://stedolan.github.io/jq/), [C++](https://github.com/open-source-parsers/jsoncpp), [MATLAB](http://iso2mesh.sourceforge.net/cgi-bin/index.cgi?jsonlab), [Python](https://docs.python.org/2/library/json.html)). The meta-data from Bruker is aligned on the DICOM dictionary for unified human and animal processing pipelines.

Dicomifier builds and runs on:
* Linux (Debian 8 and 9, Ubuntu 14.04 through 18.04, CentOS 7).
* OS X

A [Docker image](https://hub.docker.com/r/lamyj/dicomifier/) is also available.

## Installation

Unofficial packages are provided for the Debian and Ubuntu listed above. After following the [instructions to set up the unofficial repository](https://github.com/lamyj/packages), install the `dicomifier-cli` package with the usual tools provided by your distribution, e.g.:
* Debian/Ubuntu: `sudo apt-get install dicomifier-cli`
* CentOS: `sudo yum install dicomifier-cli`

If your distribution has no pre-compiled package available, you can either compile it from source (cf. documentation for [Linux](https://github.com/lamyj/dicomifier/wiki/Compiling-on-Debian-or-Ubuntu) and [macOS](https://github.com/lamyj/dicomifier/wiki/Compiling-on-OS-X)) or [ask for packaging](https://github.com/lamyj/dicomifier/issues).

## Conversion from Bruker to DICOM

Bruker-to-DICOM conversion is performed by `bruker2dicom`. This tool can use either uncompressed Bruker directories or `PvDataset` files and has been field-tested on different acquisitions types (anatomical, functional, diffusion) and different versions of Paravision (4, 5 and 6).

To list the series, use `bruker2dicom list`:
```console
computer:~ user$ bruker2dicom list lb_140721.Bq1/
1:1 - 1_Localizer (USER_MODE)
2:1 - T2_TurboRARE (USER_MODE)
3:1 - T2_TurboRARE (USER_MODE)
4:1 - T2_TurboRARE_3D (USER_MODE)
5:1 - (none) (USER_MODE)
6:1 - T2_TurboRARE (USER_MODE)
7:1 - T2_TurboRARE_3D (USER_MODE)
8:1 - T2_TurboRARE_3D (USER_MODE)
9:1 - T2map_MSME (USER_MODE)
10:1 - T2map_MSME (USER_MODE)
11:1 - T1map_RARE (USER_MODE)
11:2 - (none) (none)
```

To convert to DICOM, run `bruker2dicom convert`:
```console
computer:~ user$ bruker2dicom convert lb_140721.Bq1/ dicom/
WARNING - dicomifier: Skipping 11:2 - (none) (none): type is DERIVED_ISA
```

A single series/reconstruction can be targetted with the `-r` option: running `bruker2dicom convert -r 9:1 lb_140721.Bq1/ dicom/` will only convert the first *T2map_MSME* series. More information about the conversion process can be displayed using the `-v` option with different verbosity levels (`warning`, the default, `info` or `debug`):
```console
computer:~ user$ bruker2dicom convert -r 8:1 -v debug lb_140721.Bq1/ dicom
INFO - dicomifier: Converting 8:1
INFO - dicomifier: Found 8:1 - T2_TurboRARE_3D (USER_MODE)
```

Note that the tool will warn you about series that it cannot convert: some Bruker derived data (e.g. diffusion tensor) have no public specification available and are skipped.

The DICOM data will be stored with a subject/study/series/reconstruction hierarchy. This way, multiple exams of the same subject may be stored in the same directory. An index of the DICOM files (i.e. a *DICOMDIR* file) can be created at the top-level of the destination directory by using the `-d` option.

## Conversion from DICOM to NIfTI

DICOM-to-NIfTI conversion is performed by `dicom2nifti`. Its inputs are a set of either directories containing DICOM files or *DICOMDIR* files, and the destination directory of NIfTI data:
```console
computer:~ user$ dicom2nifti dicom/ nifti/`
```

The NIfTI data will be stored with a subject/study/series. Each series directory will contain all the reconstructions of the series, and each reconstruction will have two files: the NIfTI file itself, and the meta-data associated with it, in the JSON format. The subject, study and series directories will be named according to the information included in the DICOM file:
```console
computer:~ user$ tree -L 3 nifti/
nifti/
└── fantome-nouille
    └── 7_plateforme^18062016
        ├── 1114113_T2_TurboRARE
        ├── 1245185_B0Map-ADJ_B0MAP
        ├── 1966081_Perfusion_FAIR_RARE
        ├── 589825_T2map_MSME
        ├── 655361_T2map_MSME
        ├── 65537_1_Localizer
        └── 917505_Perfusion_FAIR_RARE
```

Compressed NIfTI files (*nii.gz*) can be created by passing the `-z` option, and more information about the conversion process can be displayed using the `-v` option with different verbosity levels (`warning`, the default, `info` or `debug`):
```console
computer:~ user$ dicom2nifti -z -v debug dicom/ nifti/
INFO - dicomifier: Splitting 62 DICOM files in series
INFO - dicomifier: 1 series found
INFO - dicomifier: Reading 62 DICOM files
INFO - dicomifier: Found 2 stacks
INFO - dicomifier: Converting 7-plateforme^18062016 / 589825-T2map_MSME
DEBUG - dicomifier: Converting 7-plateforme^18062016 / 589825-T2map_MSME (stack 1/2)
INFO - dicomifier: dtype deduced to be: <type 'numpy.float32'>
DEBUG - dicomifier: Converting 7-plateforme^18062016 / 589825-T2map_MSME (stack 2/2)
INFO - dicomifier: dtype deduced to be: <type 'numpy.float32'>
INFO - dicomifier: dtype deduced to be: <type 'numpy.float32'>
INFO - dicomifier: Merging 2 stacks
computer:~ user$ ls -l nifti/*/*/589825_T2map_MSME/
total 9944
-rw-rw----  1 user  group  2.4K 23 déc 12:29 1.json
-rw-rw----  1 user  group  4.9M 23 déc 12:29 1.nii.gz
```

## Getting meta-data from the JSON file

The meta-data is stored in the JSON file as a dictionary where the entries are the DICOM names, and the values are always stored as arrays, even for single-valued entries. Since the number of element in a value can vary between exams, this choice yields a uniform data storage and data access. For example, the echo time is stored in the *EchoTime* field and can be retrieved as such:
* Command-line, using [jq](https://stedolan.github.io/jq/):
  ```console
  computer:~/nifti user$ jq '.EchoTime[0]' 1.json 
  3
  ```
  or, for series with multiple echoes:
  ```console
  computer:~/nifti user$ jq '.EchoTime[][0]' 1.json 
  7.699999809265137
  15.39999961853027
  23.10000038146973
  30.79999923706055
  38.5
  46.20000076293945
  53.90000152587891
  ```
* Python, using the [standard module](https://docs.python.org/2/library/json.html)
  ```python
  import json
  meta_data = json.load(open("1.json"))
  # Single echo:
  echo_time = meta_data["EchoTime"][0]
  # 4D series, multiple echoes:
  echo_times = [x[0] for x in meta_data["EchoTime"]]
  ```

The complete specification of this JSON format, including 4D or higher series, is available [in the wiki](https://github.com/lamyj/dicomifier/wiki/JSON-format-of-NIfTI-meta-data).
