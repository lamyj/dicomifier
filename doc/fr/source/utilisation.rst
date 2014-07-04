Utilisation de Dicomifier
=========================

Syntaxe
-------

Commande : ::

	dicomifier XmlFile

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
| :ref:`Inputs <Balise_Inputs>`         | Obligatoire    |       1        |
+---------------------------------------+----------------+----------------+
| :ref:`Outputs <Balise_Outputs>`       | Obligatoire    |       1        |
+---------------------------------------+----------------+----------------+

Exemple :

.. code-block:: xml

	<Rule>
		<Condition />
		<Actions />
		<Inputs />
		<Outputs />
	</Rule>

.. _Balise_Condition:

Balise Condition
^^^^^^^^^^^^^^^^

Contient une et une seule condition.

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

+---------------------------------------------+----------------+--------------+
| Balises                                     | Usage          | Multiplicité |
+=============================================+================+==============+
| :ref:`DeleteElement <Balise_DeleteElement>` | Optionnel      |      0-n     |
+---------------------------------------------+----------------+--------------+
| :ref:`EmptyElement <Balise_EmptyElement>`   | Optionnel      |      0-n     |
+---------------------------------------------+----------------+--------------+
| :ref:`None <Balise_None>`                   | Optionnel      |      0-n     |
+---------------------------------------------+----------------+--------------+
| :ref:`SetElement <Balise_SetElement>`       | Optionnel      |      0-n     |
+---------------------------------------------+----------------+--------------+

Exemple :

.. code-block:: xml

	<Actions>
		<None />
		<SetElement />
		<EmptyElement />
		<DeleteElement />
	</Actions>
	
.. _Balise_Inputs:

Balise Inputs
^^^^^^^^^^^^^

Contient un ensemble de balises :ref:`Input <Balise_Input>`.

+---------------------------------+----------------+--------------+
| Balises                         | Usage          | Multiplicité |
+=================================+================+==============+
| :ref:`Input <Balise_Input>`     | Optionnel      |      0-n     |
+---------------------------------+----------------+--------------+

Exemple :

.. code-block:: xml

	<Inputs>
		<Input />
		<Input />
		<Input />
	</Inputs>
	
.. _Balise_Outputs:

Balise Outputs
^^^^^^^^^^^^^^

Contient un ensemble de balises :ref:`Output <Balise_Output>`.

+---------------------------------+----------------+--------------+
| Balises                         | Usage          | Multiplicité |
+=================================+================+==============+
| :ref:`Output <Balise_Output>`   | Optionnel      |      0-n     |
+---------------------------------+----------------+--------------+

Exemple :

.. code-block:: xml

	<Outputs>
		<Output />
		<Output />
		<Output />
	</Outputs>
	
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
|                 |              | - dicomfile                        |
|                 |              | - bruker_dir                       |
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
|                 |              | - dicomfile                         |
|                 |              | - bruker_dir                        |
|                 |              | - directory                         |
|                 |              | - file                              |
|                 |              |                                     |
+-----------------+--------------+-------------------------------------+
| value           | Obligatoire  | Valeur de la donnée de sortie       |
+-----------------+--------------+-------------------------------------+

Exemple :

.. code-block:: xml

	<Output type="" name="" value="" />

.. _Balise_True:

Balise True
^^^^^^^^^^^

Utilisée uniquement pour les tests.

Exemple :

.. code-block:: xml

	<True />

.. _Balise_False:

Balise False
^^^^^^^^^^^^

Utilisée uniquement pour les tests.

Exemple :

.. code-block:: xml

	<False />

.. _Balise_Not:

Balise Not
^^^^^^^^^^

Contient une et une seule condition.

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

	<Not>
		<True />
	</Not>

.. _Balise_Any:

Balise Any
^^^^^^^^^^

Contient un ensemble de conditions.

+-------------------------------------------+-------------+--------------+
| Balises                                   | Usage       | Multiplicité |
+===========================================+=============+==============+
| :ref:`All <Balise_All>`                   | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`Any <Balise_Any>`                   | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`ElementMatch <Balise_ElementMatch>` | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`False <Balise_False>`               | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`Not <Balise_Not>`                   | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`True <Balise_True>`                 | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+

Exemple :

.. code-block:: xml

	<All>
		<True />
		<False />
		<True />
	</All>

.. _Balise_All:

Balise All
^^^^^^^^^^

Contient un ensemble de conditions.

+-------------------------------------------+-------------+--------------+
| Balises                                   | Usage       | Multiplicité |
+===========================================+=============+==============+
| :ref:`All <Balise_All>`                   | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`Any <Balise_Any>`                   | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`ElementMatch <Balise_ElementMatch>` | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`False <Balise_False>`               | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`Not <Balise_Not>`                   | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+
| :ref:`True <Balise_True>`                 | Optionnel   |      0-n     |
+-------------------------------------------+-------------+--------------+

Exemple :

.. code-block:: xml

	<Any>
		<True />
		<False />
		<True />
	</Any>

.. _Balise_ElementMatch:

Balise ElementMatch
^^^^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Balises       | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| tag           | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à comparer                 |
+---------------+---------------+--------------+--------------------------------------------------------------+
| value         | Obligatoire   |       1      | Valeur de l'élément à comparer                               |
+---------------+---------------+--------------+--------------------------------------------------------------+
| VR            | Obligatoire   |       1      | VR de l'élément à comparer                                   |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

	<ElementMatch>
		<tag>PatientName</tag>
		<value>John</value>
		<VR>PN</VR>
		<dataset>#identifiant</dataset>
	</ElementMatch>

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
| Balises       | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| tag           | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à modifier                 |
+---------------+---------------+--------------+--------------------------------------------------------------+
| value         | Obligatoire   |       1      | Nouvelle Valeur de l'élément                                 |
+---------------+---------------+--------------+--------------------------------------------------------------+
| VR            | Obligatoire   |       1      | VR de l'élément à modifier                                   |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

	<SetElement>
		<tag>PatientName</tag>
		<value>John</value>
		<VR>PN</VR>
		<dataset>#identifiant</dataset>
	</SetElement>

.. _Balise_DeleteElement:

Balise DeleteElement
^^^^^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Balises       | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| tag           | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à supprimer                |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

	<DeleteElement>
		<tag>PatientName</tag>
		<dataset>#identifiant</dataset>
	</DeleteElement>

.. _Balise_EmptyElement:

Balise EmptyElement
^^^^^^^^^^^^^^^^^^^

+---------------+---------------+--------------+--------------------------------------------------------------+
| Balises       | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| tag           | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à effacer                  |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

	<EmptyElement>
		<tag>PatientName</tag>
		<dataset>#identifiant</dataset>
	</EmptyElement>

Exemple de fichier XML
----------------------

.. code-block:: xml

	<Rule>
		<Condition>
			<All>
				<ElementMatch>
					<tag>PatientName</tag>
					<value>Doe^John</value>
					<VR>PN</VR>
					<dataset>#input_dataset</dataset>
				</ElementMatch>
				<Not>
					<ElementMatch>
						<tag>0010,0020</tag>
						<value>123456789</value>
						<VR>LO</VR>
						<dataset>#input_dataset</dataset>
					</ElementMatch>
				</Not>
			</All>
		</Condition>
		<Actions>
			<DeleteElement>
				<tag>PatientName</tag>
				<dataset>#input_dataset</dataset>
			</DeleteElement>
			<SetElement>
				<tag>PatientID</tag>
				<value>123456789</value>
				<VR>LO</VR>
				<dataset>#input_dataset</dataset>
			</SetElement>
		</Actions>
		<Inputs>
			<Input type="dicomfile" name="input_dataset" value="/home/dicomfile" />
		</Inputs>
		<Outputs />
	</Rule>
