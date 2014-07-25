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

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicité | Description                                                  |
+=================+===============+==============+==============================================================+
| dataset         | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|                 |               |              | une balise :ref:`Input <Balise_Input>`                       |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| private_creator | Optionnel     |       1      | Nom du dictionnaire privé si le tag correspond à un attribut |
|                 |               |              | d'un dictionnaire privé                                      |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| tag             | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à modifier                 |
|                 |               |              | Remarque : il peut s'agir d'un tag composé du type           |
|                 |               |              |            Sequence.SubSequence.Keyword                      |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| value           | Obligatoire   |       1      | Nouvelle Valeur de l'élément                                 |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| VR              | Obligatoire   |       1      | VR de l'élément à modifier                                   |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Exemples :

.. code-block:: xml

    <SetElement tag="PatientName" value="John" VR="PN" dataset="#identifiant" />
    <SetElement tag="0010,1002.0010,0020" value="123456789" VR="LO" dataset="#identifiant" />
    <SetElement tag="0023,xx01.0023,xx02" value="123456789" VR="LO" dataset="#identifiant" private_creator="MyPrivateDict" />

.. _Balise_DeleteElement:

Balise DeleteElement
^^^^^^^^^^^^^^^^^^^^

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicité | Description                                                  |
+=================+===============+==============+==============================================================+
| dataset         | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|                 |               |              | une balise :ref:`Input <Balise_Input>`                       |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| private_creator | Optionnel     |       1      | Nom du dictionnaire privé si le tag correspond à un attribut |
|                 |               |              | d'un dictionnaire privé                                      |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| tag             | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à supprimer                |
|                 |               |              | Remarque : il peut s'agir d'un tag composé du type           |
|                 |               |              |            Sequence.SubSequence.Keyword                      |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Exemples :

.. code-block:: xml

    <DeleteElement tag="PatientName" dataset="#identifiant" />
    <DeleteElement tag="0010,1002.0010,0020" dataset="#identifiant" />
    <DeleteElement tag="0023,xx01.0023,xx02" dataset="#identifiant" private_creator="MyPrivateDict" />

.. _Balise_EmptyElement:

Balise EmptyElement
^^^^^^^^^^^^^^^^^^^

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicité | Description                                                  |
+=================+===============+==============+==============================================================+
| dataset         | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|                 |               |              | une balise :ref:`Input <Balise_Input>`                       |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| private_creator | Optionnel     |       1      | Nom du dictionnaire privé si le tag correspond à un attribut |
|                 |               |              | d'un dictionnaire privé                                      |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| tag             | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à effacer                  |
|                 |               |              | Remarque : il peut s'agir d'un tag composé du type           |
|                 |               |              |            Sequence.SubSequence.Keyword                      |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Exemples :

.. code-block:: xml

    <EmptyElement tag="PatientName" dataset="#identifiant" />
    <EmptyElement tag="0010,1002[:].0010,0020" dataset="#identifiant" />
    <EmptyElement tag="0023,xx01.0023,xx02" dataset="#identifiant" private_creator="MyPrivateDict" />

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

.. _Balise_StoreDataset:

Balise StoreDataset
^^^^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Attributs     | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| address       | Obligatoire   |       1      | Contient l'adresse ip du scp à appeler                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| port          | Obligatoire   |       1      | Contient le port de connexion avec le scp                    |
+---------------+---------------+--------------+--------------------------------------------------------------+
| aelocal       | Obligatoire   |       1      | Contient l'AE title de la machine appelante                  |
+---------------+---------------+--------------+--------------------------------------------------------------+
| aeremote      | Obligatoire   |       1      | Contient l'AE title de la machine appelée                    |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

    <StoreDataset dataset="#identifiant" address="myaddress" port="11112" aelocal="LOCALNAME" aeremote="REMOTENAME" />
