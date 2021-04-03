# Dicomifier

[![Conda Version](https://img.shields.io/conda/v/conda-forge/dicomifier.svg)](https://anaconda.org/conda-forge/dicomifier) [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.4459178.svg)](https://doi.org/10.5281/zenodo.4459178)

Dicomifier is a set of tools to convert Bruker data to DICOM files, and DICOM files to NIfTI. It retains meta-data (e.g. MR parameters such as echo time or subject parameters such as weight or height) throughout the conversion process, and aligns the meta-data from Bruker on the DICOM dictionary for unified processing pipelines.

Getting started? Have a look at the [installation instructions and basic usage](https://dicomifier.readthedocs.io/en/latest/getting_started.html). If you're in a hurry and have [Miniconda](https://conda.io/en/master/miniconda.html) or [Anaconda](https://anaconda.org) installed, `conda install -c conda-forge dicomifier` should get you going.

Need to know more about your options and arguments? The [commands reference](https://dicomifier.readthedocs.io/en/latest/commands/index.html) is for you.

Want to find out how it works? The [API reference](https://dicomifier.readthedocs.io/en/latest/api_reference/index.html) is a good place to start, followed by the [source code](https://github.com/lamyj/dicomifier).

Interested in how the vendors store diffusion MRI meta-data? There is a [section](https://dicomifier.readthedocs.io/en/latest/diffusion/index.html) just for you.
