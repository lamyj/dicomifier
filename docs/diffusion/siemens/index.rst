Diffusion-related meta data in Siemens files
============================================

.. warning::

  This has been tested on Verio, Trio, Skyra and Prisma. Other models may or may not work.

.. warning::

  The coordinate system of diffusion gradient direction has not yet been determined.

Private element
---------------

The diffusion-related meta-data is stored in a vendor-specific, binary-encoded, element, called *CSA Image Header Info*. The element tag is *(0029,xx19)*, under the Private Creator value *SIEMENS CSA HEADER*. The DICOM Conformance Statements (e.g. for the `Prisma`_) only describe it as manufacturer model dependent information but its precise format can be found on various websites. A parser for this format has been `implemented in Dicomifier`_.

Fields in the private element
-----------------------------

Once parsed, the *CSA Image Header Info* has four fields obviously related to diffusion MRI: *B_value*, *DiffusionGradientDirection*, *DiffusionDirectionality*, and *B_matrix*, which match the terms of the `MR Diffusion module`_. Two examples are shown below, the first one for a diffusion-weighted image, the second one for a :math:`b=0\ s/mm^2` image (other fields have been removed for readability).


.. code:: python

    meta_data = [
        {
            'B_value': [0],
            'DiffusionGradientDirection': [],
            'B_matrix': [],
            'DiffusionDirectionality': [b'DIRECTIONAL\x00'] },
        {
            'B_value': [1000],
            'DiffusionGradientDirection': [0.1977423, 0.17195807, -0.96505374],
            'B_matrix': [39.0, 34.0, -191.0, 30.0, -166.0, 932.0],
            'DiffusionDirectionality': [b'DIRECTIONAL\x00'] },
        {
            'B_value': [1000],
            'DiffusionGradientDirection': [-0.32412839, -0.94072425, 0.09989204],
            'B_matrix': [105.0, 305.0, -32.0, 885.0, -94.0, 11.0],
            'DiffusionDirectionality': [b'DIRECTIONAL\x00'] },
        {
            'B_value': [1000],
            'DiffusionGradientDirection': [-0.97839409, -0.17072155, 0.11661573],
            'B_matrix': [957.0, 167.0, -114.0, 29.0, -20.0, 14.0],
            'DiffusionDirectionality': [b'DIRECTIONAL\x00'] }
    ]




The b-value is always present and expressed in :math:`s/mm^2`. It appears to be the ideal b-value, i.e. not modulated by the imaging gradients. The direction of the diffusion gradient is not specified for non diffusion-weighted images, and neither is the b-matrix; when specified, the direction has norm 1.

The b-matrix has only six elements, and can thus be assumed to be the upper or the lower triangular part of the full b-matrix. However, looking at eigensystem of the b-matrix for both hypotheses, it appears that both the eigenvalues and the dot-product of the principal eigenvector with the direction of the diffusion gradient only match for the upper-triangular matrix.


.. code:: python

    import numpy

    def from_upper(linear):
        return numpy.array([
            [linear[0], linear[1], linear[2]],
            [linear[1], linear[3], linear[4]],
            [linear[2], linear[4], linear[5]]])
    def from_lower(linear):
        return numpy.array([
            [linear[0], linear[1], linear[3]],
            [linear[1], linear[2], linear[4]],
            [linear[3], linear[4], linear[5]]])

    for item in meta_data:
        if not item["B_matrix"]:
            continue

        upper_eigensystem = numpy.linalg.eigh(from_upper(item["B_matrix"]))
        lower_eigensystem = numpy.linalg.eigh(from_lower(item["B_matrix"]))

        direction = item["DiffusionGradientDirection"]

        print(
            "Upper triangular matrix: ",
            upper_eigensystem[0].astype(int),
            numpy.dot(direction, upper_eigensystem[1][:,-1]),
            "\nLower triangular matrix: ",
            lower_eigensystem[0].astype(int),
            numpy.dot(direction, lower_eigensystem[1][:,-1]),
            "\n")


.. code::

    Upper triangular matrix:  [   0    0 1000] -1.0000001580676756
    Lower triangular matrix:  [-220   43  956] -0.9739920011521168

    Upper triangular matrix:  [   0    1 1000] 0.999999873698694
    Lower triangular matrix:  [-916   31  969] 0.3232097831549061

    Upper triangular matrix:  [  0   0 999] 1.0000000357323802
    Lower triangular matrix:  [-143   17  983] 0.9894968101548527




.. _implemented in Dicomifier: https://github.com/lamyj/dicomifier/blob/master/src/python/dicomifier/dicom_to_nifti/siemens.py
.. _MR Diffusion module: http://dicom.nema.org/medical/dicom/current/output/chtml/part03/sect_C.8.13.5.9.html
.. _Prisma: https://static.healthcare.siemens.com/siemens_hwem-hwem_ssxa_websites-context-root/wcm/idc/groups/public/@global/@services/documents/download/mda2/njux/~edisp/conformance_dc_ve11c-03636539.pdf
