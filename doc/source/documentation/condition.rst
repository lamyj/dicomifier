List of conditions
==================

.. _Balise_True:

Tag True
^^^^^^^^

Only used for testing.

Sample:

.. code-block:: xml

    <True />

.. _Balise_False:

Tag False
^^^^^^^^^

Only used for testing.

Sample:

.. code-block:: xml

    <False />

.. _Balise_Not:

Tag Not
^^^^^^^

Contains only one condition.

Available tags are listed in chapter :ref:`Tag Condition <Balise_Condition>`.

Sample:

.. code-block:: xml

    <Not>
        <True />
    </Not>

.. _Balise_Any:

Tag Any
^^^^^^^

Contains a set of Conditions.

Available tags are listed in chapter :ref:`Tag Condition <Balise_Condition>`.

Sample:

.. code-block:: xml

    <All>
        <True />
        <False />
        <True />
    </All>

.. _Balise_All:

Tag All
^^^^^^^

Contains a set of Conditions.

Available tags are listed in chapter :ref:`Tag Condition <Balise_Condition>`.

Sample:

.. code-block:: xml

    <Any>
        <True />
        <False />
        <True />
    </Any>

.. _Balise_ElementMatch:

Tag ElementMatch
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
| tag             | Mandatory     |       1      | DICOM Tag or keyword of the element to be compared           |
|                 |               |              | Comment: it could be a composite tag like                    |
|                 |               |              | Sequence.SubSequence.Keyword                                 |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| value           | Mandatory     |       1      | Value of compared element                                    |
|                 |               |              | Comment: it is possible to use regular expressions with      |
|                 |               |              | following characters: '*' et '?'.                            |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| VR              | Mandatory     |       1      | Value Representation of compared attribut                    |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Samples:

.. code-block:: xml

    <ElementMatch tag="PatientName" value="John" VR="PN" dataset="#identifiant" />
    <ElementMatch tag="PatientName" value="Doe^*" VR="PN" dataset="#identifiant" />
    <ElementMatch tag="PatientName" value="Doe^J?hn" VR="PN" dataset="#identifiant" />
    <ElementMatch tag="0010,1002[0:3].PatientID[4]" value="123456789" VR="LO" dataset="#identifiant" />
    <ElementMatch tag="0023,xx02" value="John" VR="PN" dataset="#identifiant" private_creator="MyPrivateDict" />

