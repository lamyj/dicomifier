Utilisation de Dicomifier
=========================

Syntaxe
-------

Commande : ::

    dicomifier RulesFile.xml PrivateDictionary.xml

Format du fichier XML
---------------------

Le fichier est composé d'un ensemble de balise :ref:`Rule <Balise_Rule>`.

+-----------------------------+----------------+----------------+
| Balises                     | Usage          | Multiplicité   |
+=============================+================+================+
| :ref:`Rule <Balise_Rule>`   | Obligatoire    |      1-n       |
+-----------------------------+----------------+----------------+

.. _Balise_Rule:

Balise Rule
^^^^^^^^^^^

La balise :ref:`Rule <Balise_Rule>` est le noeud principal du fichier XML.
Il est composé des balises suivantes :

+---------------------------------------+----------------+----------------+
| Balises                               | Usage          | Multiplicité   |
+=======================================+================+================+
| :ref:`Actions <Balise_Actions>`       | Obligatoire    |       1        |
+---------------------------------------+----------------+----------------+
| :ref:`Condition <Balise_Condition>`   | Obligatoire    |       1        |
+---------------------------------------+----------------+----------------+
| :ref:`Input <Balise_Input>`           | Optionnel      |      0-n       |
+---------------------------------------+----------------+----------------+
| :ref:`Output <Balise_Output>`         | Optionnel      |      0-n       |
+---------------------------------------+----------------+----------------+

Exemple :

.. code-block:: xml

    <Rule>
        <Condition />
        <Actions />
        <Input />
        <Output />
    </Rule>

.. _Balise_Condition:

Balise Condition
^^^^^^^^^^^^^^^^

Contient une et une seule condition.

* :doc:`Liste des conditions <condition>`

+-------------------------------------------+----------------+--------------+
| Balises                                   | Usage          | Multiplicité |
+===========================================+================+==============+
| :ref:`All <Balise_All>`                   | Conditionnel   |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`Any <Balise_Any>`                   | Conditionnel   |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`ElementMatch <Balise_ElementMatch>` | Conditionnel   |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`False <Balise_False>`               | Conditionnel   |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`Not <Balise_Not>`                   | Conditionnel   |      0-1     |
+-------------------------------------------+----------------+--------------+
| :ref:`True <Balise_True>`                 | Conditionnel   |      0-1     |
+-------------------------------------------+----------------+--------------+

Pour chaque balise, celle-ci est présente à condition qu'aucune autre balise ne 
soit présente.

Exemple :

.. code-block:: xml

    <Condition>
        <True />
    </Condition>

.. _Balise_Actions:

Balise Actions
^^^^^^^^^^^^^^

Contient un ensemble d'actions.

* :doc:`Liste des actions <actions>`

+-------------------------------------------------------+----------------+--------------+
| Balises                                               | Usage          | Multiplicité |
+=======================================================+================+==============+
| :ref:`DeleteElement <Balise_DeleteElement>`           | Optionnel      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`EmptyElement <Balise_EmptyElement>`             | Optionnel      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`EnhanceBrukerDicom <Balise_EnhanceBrukerDicom>` | Optionnel      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`None <Balise_None>`                             | Optionnel      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`SaveDataset <Balise_SaveDataset>`               | Optionnel      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`SetElement <Balise_SetElement>`                 | Optionnel      |      0-n     |
+-------------------------------------------------------+----------------+--------------+
| :ref:`StoreDataset <Balise_StoreDataset>`             | Optionnel      |      0-n     |
+-------------------------------------------------------+----------------+--------------+

Exemple :

.. code-block:: xml

    <Actions>
        <None />
        <SetElement />
        <EmptyElement />
        <DeleteElement />
    </Actions>

.. _Balise_Input:

Balise Input
^^^^^^^^^^^^

+-----------------+--------------+------------------------------------+
| Attributs       | Usage        | Description                        |
+=================+==============+====================================+
| name            | Obligatoire  | Identifiant unique                 |
+-----------------+--------------+------------------------------------+
| type            | Obligatoire  | Type d'entrée. Valeurs possibles : |
|                 |              |                                    |
|                 |              | - dataset                          |
|                 |              | - directory                        |
|                 |              | - file                             |
|                 |              |                                    |
+-----------------+--------------+------------------------------------+
| value           | Obligatoire  | Valeur de la donnée d'entrée       |
+-----------------+--------------+------------------------------------+

Exemple :

.. code-block:: xml

    <Input type="" name="" value="" />

.. _Balise_Output:

Balise Output
^^^^^^^^^^^^^

+-----------------+--------------+-------------------------------------+
| Attributs       | Usage        | Description                         |
+=================+==============+=====================================+
| name            | Obligatoire  | Identifiant unique                  |
+-----------------+--------------+-------------------------------------+
| type            | Obligatoire  | Type de sortie. Valeurs possibles : |
|                 |              |                                     |
|                 |              | - dataset                           |
|                 |              | - directory                         |
|                 |              | - file                              |
|                 |              |                                     |
+-----------------+--------------+-------------------------------------+
| value           | Obligatoire  | Valeur de la donnée de sortie       |
+-----------------+--------------+-------------------------------------+

Exemple :

.. code-block:: xml

    <Output type="" name="" value="" />

Exemple de fichier XML
----------------------

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
