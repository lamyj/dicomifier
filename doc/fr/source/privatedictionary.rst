Dictionnaire privé
==================

.. _Balise_PrivateDict:

Contenu
-------

Le dictionnaire privé contient un ensemble d'éléments respectant le standard DICOM.

Le nom du dictionnaire privé est contenu par la balise "title". Ce nom sera celui utilisé dans les actions et conditions 'dicomifier'.

Exemple de dictionnaire
-----------------------

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
