.. _diffusion:

Diffusion meta-data
===================

For many other vendors, the diffusion-related meta data (b-values and direction of diffusion-encoding gradient) is barely specified in the official documentation, the two major problems being the unit in which the b-value is expressed and the coordinate system which defines the direction of the diffusion gradient. While the former is usually easy to determine (e.g. in neuro-imaging, a b-value of around :math:`1000\ s/mm^2` is customary), the latter is more complicated. An error in the frame of reference will remain unnoticed for some applications (e.g. a map of fractional anisotropy) but will yield radical changes in the output of direction-dependent metrics like tractography.

These documents attempt to describe how the diffusion-related meta data is stored in the files of various vendors.

.. toctree::
   :maxdepth: 2
   :caption: Contents:
   :titlesonly:

   Bruker <bruker/index.rst>
   GE <ge/index.rst>
   Siemens <siemens/index.rst>
