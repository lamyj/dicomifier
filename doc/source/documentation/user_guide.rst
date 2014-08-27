User Guide
==========

Launch
------

Dicomifier is a binary file. You can use a command prompt to launch him.

.. code-block:: sh
    
    ./dicomifier <Rule file> [<Private dictionary>]
    
As you can see, Dicomifier takes one mandatory option (Rule file) and one optional (Private dictionary).
Both correspond to XML files and are described in the next sections.

.. _Balise_RuleFormat:

Format of rule XML files
------------------------

File contains a list of XML tag :ref:`Rule <Balise_Rule>`.

+-----------------------------+----------------+----------------+
| Tags                        | Usage          | Multiplicity   |
+=============================+================+================+
| :ref:`Rule <Balise_Rule>`   | Mandatory      |      1-n       |
+-----------------------------+----------------+----------------+

.. _Balise_Rule:

Tag Rule
^^^^^^^^

Tag :ref:`Rule <Balise_Rule>` is the main tag of the XML file.
It contains the followings tags:

+---------------------------------------+----------------+----------------+
| Tags                                  | Usage          | Multiplicity   |
+=======================================+================+================+
| :ref:`Actions <Balise_Actions>`       | Mandatory      |       1        |
+---------------------------------------+----------------+----------------+
| :ref:`Condition <Balise_Condition>`   | Mandatory      |       1        |
+---------------------------------------+----------------+----------------+
| :ref:`Input <Balise_Input>`           | Optionnal      |      0-n       |
+---------------------------------------+----------------+----------------+
| :ref:`Output <Balise_Output>`         | Optionnal      |      0-n       |
+---------------------------------------+----------------+----------------+

Sample:

.. code-block:: xml

    <Rule>
        <Condition />
        <Actions />
        <Input />
        <Output />
    </Rule>

.. _Balise_Condition:

Tag Condition
^^^^^^^^^^^^^

Condition contains only one of the following tags:

* :doc:`Avalaible Conditions list <condition>`

+-------------------------------------------+----------------+--------------+
| Tags                                      | Usage          | Multiplicity |
+===========================================+================+==============+
| :ref:`All <Balise_All>`                   | Conditional    |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`Any <Balise_Any>`                   | Conditional    |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`ElementMatch <Balise_ElementMatch>` | Conditional    |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`False <Balise_False>`               | Conditional    |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`Not <Balise_Not>`                   | Conditional    |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`True <Balise_True>`                 | Conditional    |      0-1     |
+-------------------------------------------+----------------+--------------+

For each tag, it is present if no other tag is present.

Sample:

.. code-block:: xml

    <Condition>
        <True />
    </Condition>

.. _Balise_Actions:

Tag Actions
^^^^^^^^^^^

Actions contains a list of action.

* :doc:`Avalaible Actions list <actions>`

+-------------------------------------------------------+----------------+--------------+
| Tags                                                  | Usage          | Multiplicity |
+=======================================================+================+==============+
| :ref:`DeleteElement <Balise_DeleteElement>`           | Optionnal      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`EmptyElement <Balise_EmptyElement>`             | Optionnal      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`EnhanceBrukerDicom <Balise_EnhanceBrukerDicom>` | Optionnal      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`None <Balise_None>`                             | Optionnal      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`SaveDataset <Balise_SaveDataset>`               | Optionnal      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`SetElement <Balise_SetElement>`                 | Optionnal      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`StoreDataset <Balise_StoreDataset>`             | Optionnal      |      0-n     |
+-------------------------------------------------------+----------------+--------------+

Sample:

.. code-block:: xml

    <Actions>
        <None />
        <SetElement />
        <EmptyElement />
        <DeleteElement />
    </Actions>

.. _Balise_Input:

Tag Input
^^^^^^^^^

+-----------------+--------------+------------------------------------+
| Attributs       | Usage        | Description                        |
+=================+==============+====================================+
| name            | Mandatory    | Unique identifier                  |
+-----------------+--------------+------------------------------------+
| type            | Mandatory    | Input type. Available values:      |
|                 |              |                                    |
|                 |              | - dataset                          |
|                 |              | - directory                        |
|                 |              | - file                             |
|                 |              |                                    |
+-----------------+--------------+------------------------------------+
| value           | Mandatory    | Value of input data                |
+-----------------+--------------+------------------------------------+

Sample:

.. code-block:: xml

    <Input type="" name="" value="" />

.. _Balise_Output:

Tag Output
^^^^^^^^^^

+-----------------+--------------+-------------------------------------+
| Attributs       | Usage        | Description                         |
+=================+==============+=====================================+
| name            | Mandatory    | Unique identifier                   |
+-----------------+--------------+-------------------------------------+
| type            | Mandatory    | Output type. Available values:      |
|                 |              |                                     |
|                 |              | - dataset                           |
|                 |              | - directory                         |
|                 |              | - file                              |
|                 |              |                                     |
+-----------------+--------------+-------------------------------------+
| value           | Mandatory    | Value of output data                |
+-----------------+--------------+-------------------------------------+

Sample:

.. code-block:: xml

    <Output type="" name="" value="" />

Sample XML file
^^^^^^^^^^^^^^^

.. code-block:: xml

    <Rule>
        <Condition>
            <All>
                <ElementMatch tag="PatientName" value="Doe^John" VR="PN" dataset="#input_dataset" />
                <Not>
                    <ElementMatch tag="0010,0020" value="123456789" VR="LO" dataset="#input_dataset" />
                    <ElementMatch tag="0023,xx02" value="MyValue" VR="CS" dataset="#input_dataset" private_creator="MyPrivateDict" />
                </Not>
            </All>
        </Condition>
        <Actions>
            <DeleteElement tag="PatientName" dataset="#input_dataset" />
            <SetElement tag="PatientID" value="123456789" VR="LO" dataset="#input_dataset" />
            <SetElement tag="0010,1002[0:3].PatientID[4]" value="123456789" VR="LO" dataset="#input_dataset" />
            <SaveDataset dataset="#input_dataset" outputfile="#output_dataset" />
        </Actions>
        <Input type="dataset" name="input_dataset" value="/home/dicomfile" />
        <Output type="file" name="output_dataset" value="/home/fichier_sortie.dcm" />
    </Rule>

Format of Private Dictionary
----------------------------

.. _Balise_PrivateDict:

Description
^^^^^^^^^^^

Private Dictionary contains a set of elements based on DICOM Standard.

Title tag is mandatory and contains dictionary name used by Dicomifier.

Sample of Private Dictionary
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: xml

    <?xml version="1.0" encoding="utf-8" standalone="no"?>
    <book xmlns="http://docbook.org/ns/docbook" xmlns:xl="http://www.w3.org/1999/xlink" xml:id="PS3.6-FLI-IAM" label="PS3.6-FLI-IAM" version="1.0">
      <title>FLI-IAM</title>
      <subtitle>Private Data Dictionary</subtitle>
      <info>
        <author>
          <orgname>FLI</orgname>
        </author>
        <copyright>
          <year>2014</year>
          <holder>FLI</holder>
        </copyright>
      </info>
      <chapter xml:id="chapter_1" label="1" status="1">
        <title>Registry of private DICOM Data Elements</title>
        <table rules="all" frame="box" xml:id="table_1-1-FLI-IAM" label="1-1">
          <caption>Registry of private DICOM Data Elements</caption>
          <thead>
            <tr valign="top">
              <th align="center" colspan="1" rowspan="1">
                <para>
                  <emphasis role="bold">Tag</emphasis>
                </para>
              </th>
              <th align="center" colspan="1" rowspan="1">
                <para>
                  <emphasis role="bold">Name</emphasis>
                </para>
              </th>
              <th align="center" colspan="1" rowspan="1">
                <para>
                  <emphasis role="bold">Keyword</emphasis>
                </para>
              </th>
              <th align="center" colspan="1" rowspan="1">
                <para>
                  <emphasis role="bold">VR</emphasis>
                </para>
              </th>
              <th align="center" colspan="1" rowspan="1">
                <para>
                  <emphasis role="bold">VM</emphasis>
                </para>
              </th>
              <td align="center" colspan="1" rowspan="1">
                <para/>
              </td>
            </tr>
          </thead>
          <tbody>
            <tr valign="top">
              <td align="center" colspan="1" rowspan="1">
                <para>(0023,xx01)</para>
              </td>
              <td align="left" colspan="1" rowspan="1">
                <para>Subject Category</para>
              </td>
              <td align="left" colspan="1" rowspan="1">
                <para>SubjectCategory</para>
              </td>
              <td align="center" colspan="1" rowspan="1">
                <para>CS</para>
              </td>
              <td align="center" colspan="1" rowspan="1">
                <para>1</para>
              </td>
              <td align="center" colspan="1" rowspan="1">
                <para/>
              </td>
            </tr>
            <tr valign="top">
              <td align="center" colspan="1" rowspan="1">
                <para>(0023,xx02)</para>
              </td>
              <td align="left" colspan="1" rowspan="1">
                <para>Provider Name</para>
              </td>
              <td align="left" colspan="1" rowspan="1">
                <para>ProviderName</para>
              </td>
              <td align="center" colspan="1" rowspan="1">
                <para>LO</para>
              </td>
              <td align="center" colspan="1" rowspan="1">
                <para>1</para>
              </td>
              <td align="center" colspan="1" rowspan="1">
                <para/>
              </td>
            </tr>
          </tbody>
        </table>
      </chapter>
    </book>

