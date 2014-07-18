Liste des conditions
====================

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

Les différentes balises possibles sont listées dans le paragraphe :ref:`Balise Condition <Balise_Condition>`.

Exemple :

.. code-block:: xml

    <Not>
        <True />
    </Not>

.. _Balise_Any:

Balise Any
^^^^^^^^^^

Contient un ensemble de conditions.

Les différentes balises possibles sont listées dans le paragraphe :ref:`Balise Condition <Balise_Condition>`.

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

Les différentes balises possibles sont listées dans le paragraphe :ref:`Balise Condition <Balise_Condition>`.

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
| Attributs     | Usage         | Multiplicité | Description                                                  |
+===============+===============+==============+==============================================================+
| dataset       | Obligatoire   |       1      | Contient une référence vers un identifiant unique défini par |
|               |               |              | une balise :ref:`Input <Balise_Input>`                       |
+---------------+---------------+--------------+--------------------------------------------------------------+
| tag           | Obligatoire   |       1      | Tag ou Keyword d'un élément DICOM à comparer                 |
|               |               |              | Remarque : il peut s'agir d'un tag composé du type           |
|               |               |              |            Sequence.SubSequence.Keyword                      |
+---------------+---------------+--------------+--------------------------------------------------------------+
| value         | Obligatoire   |       1      | Valeur de l'élément à comparer                               |
+---------------+---------------+--------------+--------------------------------------------------------------+
| VR            | Obligatoire   |       1      | VR de l'élément à comparer                                   |
+---------------+---------------+--------------+--------------------------------------------------------------+

Exemple :

.. code-block:: xml

    <ElementMatch tag="PatientName" value="John" VR="PN" dataset="#identifiant" />

