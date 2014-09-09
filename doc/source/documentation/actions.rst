List of Actions
===============

.. _Balise_None:

Tag None
^^^^^^^^

Only used for testing.

Sample:

.. code-block:: xml

    <None />

.. _Balise_SetElement:

Tag SetElement
^^^^^^^^^^^^^^

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicity | Description                                                  |
+=================+===============+==============+==============================================================+
| dataset         | Mandatory     |       1      | Contains a link to an unique identifier defined by tag       |
|                 |               |              | :ref:`Input <Balise_Input>`                                  |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| private_creator | Optional      |       1      | Name of Private Dictionary if this attribut Group-Element    |
|                 |               |              | is defined in a Private Dictionary                           |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| tag             | Mandatory     |       1      | DICOM Tag or keyword of the element to be modified           |
|                 |               |              | Comment: it could be a composite tag like                    |
|                 |               |              | Sequence.SubSequence.Keyword                                 |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| value           | Mandatory     |       1      | New value for the given attribut                             |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| VR              | Mandatory     |       1      | Value Representation of given attribut                       |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Samples:

.. code-block:: xml

    <SetElement tag="PatientName" value="John" VR="PN" dataset="#identifiant" />
    <SetElement tag="0010,1002.0010,0020" value="123456789" VR="LO" dataset="#identifiant" />
    <SetElement tag="0023,xx01.0023,xx02" value="123456789" VR="LO" dataset="#identifiant" private_creator="MyPrivateDict" />

.. _Balise_DeleteElement:

Tag DeleteElement
^^^^^^^^^^^^^^^^^

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicity | Description                                                  |
+=================+===============+==============+==============================================================+
| dataset         | Mandatory     |       1      | Contains a link to an unique identifier defined by tag       |
|                 |               |              | :ref:`Input <Balise_Input>`                                  |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| private_creator | Optional      |       1      | Name of Private Dictionary if this attribut Group-Element    |
|                 |               |              | is defined in a Private Dictionary                           |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| tag             | Mandatory     |       1      | DICOM Tag or keyword of the element to be removed            |
|                 |               |              | Comment: it could be a composite tag like                    |
|                 |               |              | Sequence.SubSequence.Keyword                                 |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Samples:

.. code-block:: xml

    <DeleteElement tag="PatientName" dataset="#identifiant" />
    <DeleteElement tag="0010,1002.0010,0020" dataset="#identifiant" />
    <DeleteElement tag="0023,xx01.0023,xx02" dataset="#identifiant" private_creator="MyPrivateDict" />

.. _Balise_EmptyElement:

Tag EmptyElement
^^^^^^^^^^^^^^^^

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicity | Description                                                  |
+=================+===============+==============+==============================================================+
| dataset         | Mandatory     |       1      | Contains a link to an unique identifier defined by tag       |
|                 |               |              | :ref:`Input <Balise_Input>`                                  |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| private_creator | Optional      |       1      | Name of Private Dictionary if this attribut Group-Element    |
|                 |               |              | is defined in a Private Dictionary                           |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| tag             | Mandatory     |       1      | DICOM Tag or keyword of the element to be cleared            |
|                 |               |              | Comment: it could be a composite tag like                    |
|                 |               |              | Sequence.SubSequence.Keyword                                 |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Samples:

.. code-block:: xml

    <EmptyElement tag="PatientName" dataset="#identifiant" />
    <EmptyElement tag="0010,1002[:].0010,0020" dataset="#identifiant" />
    <EmptyElement tag="0023,xx01.0023,xx02" dataset="#identifiant" private_creator="MyPrivateDict" />

.. _Balise_SaveDataset:

Tag SaveDataset
^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Attributs     | Usage         | Multiplicity | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Mandatory     |       1      | Contains a link to an unique identifier defined by tag       |
|               |               |              | :ref:`Input <Balise_Input>`                                  |
+---------------+---------------+--------------+--------------------------------------------------------------+
| outputfile    | Mandatory     |       1      | Contains path to the file in which will be written the       |
|               |               |              | dataset, or a link to an unique identifier defined by tag    |
|               |               |              | :ref:`Output <Balise_Output>`                                |
+---------------+---------------+--------------+--------------------------------------------------------------+

Sample:

.. code-block:: xml

    <SaveDataset dataset="#identifiant" outputfile="#output_identifiant" />

.. _Balise_EnhanceBrukerDicom:

Tag EnhanceBrukerDicom
^^^^^^^^^^^^^^^^^^^^^^

+-------------------------+---------------+--------------+---------------------------------------------------------------+
| Attributs               | Usage         | Multiplicity | Description                                                   |
+=========================+===============+==============+===============================================================+
| dataset                 | Mandatory     |       1      | Contains a link to an unique identifier defined by tag        |
|                         |               |              | :ref:`Input <Balise_Input>`                                   |
+-------------------------+---------------+--------------+---------------------------------------------------------------+
| brukerdir               | Mandatory     |       1      | Contains path to directory in which are the Bruker data files |
|                         |               |              | or a link to an unique identifier defined by tag              |
|                         |               |              | :ref:`Input <Balise_Input>`                                   |
+-------------------------+---------------+--------------+---------------------------------------------------------------+
| seriesnumber            | Mandatory     |       1      | Contains number of the series to be process                   |
+-------------------------+---------------+--------------+---------------------------------------------------------------+
| studynumber             | Optional      |      0-1     | Contains number of the study to be process                    |
+-------------------------+---------------+--------------+---------------------------------------------------------------+
| brukertodicomdictionary | Optional      |      0-1     | Dictionary to translate Bruker data to DICOM field            |
+-------------------------+---------------+--------------+---------------------------------------------------------------+

See :ref:`Bruker to DICOM Dictionary <Balise_btodDico>` for more information about brukertodicomdictionary field.

Sample:

.. code-block:: xml

    <EnhanceBrukerDicom dataset="#dataset_identifiant" brukerdir="#bruker_identifiant" seriesnumber="1" studynumber="1" />

.. _Balise_StoreDataset:

Tag StoreDataset
^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Attributs     | Usage         | Multiplicity | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Mandatory     |       1      | Contains a link to an unique identifier defined by tag       |
|               |               |              | :ref:`Input <Balise_Input>`                                  |
+---------------+---------------+--------------+--------------------------------------------------------------+
| address       | Mandatory     |       1      | Contains IP address of the called SCP                        |
+---------------+---------------+--------------+--------------------------------------------------------------+
| port          | Mandatory     |       1      | Contains port number for connexion with the called SCP       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| aelocal       | Mandatory     |       1      | Contains calling AE Title                                    |
+---------------+---------------+--------------+--------------------------------------------------------------+
| aeremote      | Mandatory     |       1      | Contains called AE Title                                     |
+---------------+---------------+--------------+--------------------------------------------------------------+

Sample:

.. code-block:: xml

    <StoreDataset dataset="#identifiant" address="myaddress" port="11112" aelocal="LOCALNAME" aeremote="REMOTENAME" />

.. _Balise_PrintDataset:

Tag PrintDataset
^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Attributs     | Usage         | Multiplicity | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Mandatory     |       1      | Contains a link to an unique identifier defined by tag       |
|               |               |              | :ref:`Input <Balise_Input>`                                  |
+---------------+---------------+--------------+--------------------------------------------------------------+
| outputfile    | Optional      |       1      | Contains path to the file in which will be written the       |
|               |               |              | dataset, or a link to an unique identifier defined by tag    |
|               |               |              | :ref:`Output <Balise_Output>`                                |
|               |               |              | By default: Dataset is printed in the standard output (cout) |
+---------------+---------------+--------------+--------------------------------------------------------------+

Sample:

.. code-block:: xml

    <PrintDataset dataset="#identifiant" outputfile="#output_identifiant" />
