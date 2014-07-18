Liste des actions
=================

.. _Balise_None:

Balise None
^^^^^^^^^^^

Utilisée uniquement pour les tests.

Exemple :

.. code-block:: xml

    <None />

.. _Balise_SetElement:

Balise SetElement
^^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Attributs     | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| tag           | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à modifier                 |
|               |               |              | Remarque : il peut s'agir d'un tag composé du type           |
|               |               |              |            Sequence.SubSequence.Keyword                      |
+---------------+---------------+--------------+--------------------------------------------------------------+
| value         | Obligatoire   |       1      | Nouvelle Valeur de l'élément                                 |
+---------------+---------------+--------------+--------------------------------------------------------------+
| VR            | Obligatoire   |       1      | VR de l'élément à modifier                                   |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

    <SetElement tag="PatientName" value="John" VR="PN" dataset="#identifiant" />

.. _Balise_DeleteElement:

Balise DeleteElement
^^^^^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Attributs     | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| tag           | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à supprimer                |
|               |               |              | Remarque : il peut s'agir d'un tag composé du type           |
|               |               |              |            Sequence.SubSequence.Keyword                      |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

    <DeleteElement tag="PatientName" dataset="#identifiant" />

.. _Balise_EmptyElement:

Balise EmptyElement
^^^^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Attributs     | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| tag           | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à effacer                  |
|               |               |              | Remarque : il peut s'agir d'un tag composé du type           |
|               |               |              |            Sequence.SubSequence.Keyword                      |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

    <EmptyElement tag="PatientName" dataset="#identifiant" />

.. _Balise_SaveDataset:

Balise SaveDataset
^^^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Attributs     | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| outputfile    | Obligatoire   |       1      | Contient le chemin du fichier dans lequel sera écrit le      |
|               |               |              | dataset, ou une référence vers un identifiant unique défini  |
|               |               |              | par une balise :ref:`Output <Balise_Output>`                 |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

    <SaveDataset dataset="#identifiant" outputfile="#output_identifiant" />

.. _Balise_EnhanceBrukerDicom:

Balise EnhanceBrukerDicom
^^^^^^^^^^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+---------------------------------------------------------------+
| Attributs     | Usage         | Multiplicité | Description                                                   |
+===============+===============+==============+===============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par  |
|               |               |              | une balise :ref:`Input <Balise_Input>`                        |
+---------------+---------------+--------------+---------------------------------------------------------------+
| brukerdir     | Obligatoire   |       1      | Contient le chemin du répertoire dans lequel se trouvent      |
|               |               |              | tous les fichiers Bruker ou une référence vers un identifiant |
|               |               |              | unique défini par une balise :ref:`Input <Balise_Input>`      |
+---------------+---------------+--------------+---------------------------------------------------------------+

Exemple :

.. code-block:: xml

    <EnhanceBrukerDicom dataset="#dataset_identifiant" brukerdir="#bruker_identifiant" />
