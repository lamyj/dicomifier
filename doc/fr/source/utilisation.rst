Utilisation de Dicomifier
=========================

Syntaxe
-------

dicomifier XmlFile

Format du fichier XML
---------------------

Balise Rule
^^^^^^^^^^^

.. code-block:: xml

	<Rule>
		<Condition />
		<Actions />
		<Inputs />
		<Outputs />
	</Rule>

Balise Condition
^^^^^^^^^^^^^^^^

Contient une condition. Valeurs possibles :

* True
* False
* Not
* All
* Any
* ElementMatch

Balise Actions
^^^^^^^^^^^^^^

Contient un ensemble d'actions. Valeurs possibles :

* None
* SetElement
* DeleteElement
* EmptyElement

Balise Inputs
^^^^^^^^^^^^^

Contient un ensemble de balises Input.

Balise Outputs
^^^^^^^^^^^^^^

Contient un ensemble de balises Output.

Balise Input
^^^^^^^^^^^^

.. code-block:: xml

	<Input type="" name="" value="" />

Balise Output
^^^^^^^^^^^^^

.. code-block:: xml

	<Output type="" name="" value="" />

Balise True
^^^^^^^^^^^

.. code-block:: xml

	<True />

Balise False
^^^^^^^^^^^^

.. code-block:: xml

	<False />

Balise Not
^^^^^^^^^^

Contient une condition. Valeurs possibles :

* True
* False
* Not
* All
* Any
* ElementMatch

Exemple :

.. code-block:: xml

	<Not>
		<True />
	</Not>

Balise Any
^^^^^^^^^^

Contient un ensemble de conditions.
La condition Any est vraie si au moins une des conditions est vraie.

Balise All
^^^^^^^^^^

Contient un ensemble de conditions.
La condition All est vraie si toutes les conditions sont vraies.

Balise ElementMatch
^^^^^^^^^^^^^^^^^^^

.. code-block:: xml

	<ElementMatch>
		<tag />
		<value />
		<VR />
		<dataset />
	</ElementMatch>

Balise None
^^^^^^^^^^^

.. code-block:: xml

	<None />

Balise SetElement
^^^^^^^^^^^^^^^^^

.. code-block:: xml

	<SetElement>
		<tag />
		<value />
		<VR />
		<dataset />
	</SetElement>

Balise DeleteElement
^^^^^^^^^^^^^^^^^^^^

.. code-block:: xml

	<DeleteElement>
		<tag />
		<dataset />
	</DeleteElement>

Balise EmptyElement
^^^^^^^^^^^^^^^^^^^

.. code-block:: xml

	<EmptyElement>
		<tag />
		<dataset />
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
