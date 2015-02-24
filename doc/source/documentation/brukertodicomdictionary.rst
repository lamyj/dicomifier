Bruker to DICOM Dictionary
==========================

.. _Balise_btodDico:

Bruker to DICOM Dictionary is an XML file and contains an unique tag Dictionary.

Tag Dictionary
^^^^^^^^^^^^^^

Tag Dicitonary contains a set of DICOM fields.

+------------------------------------------+---------------+----------------+
| Tags                                     | Usage         | Multiplicity   |
+==========================================+===============+================+
| :ref:`DicomField <Balise_DicomField>`    | Mandatory     |       1-n      |
+------------------------------------------+---------------+----------------+

Sample:

.. code-block:: xml

    <Dictionary>
        <DicomField>...</DicomField>
        <DicomField>...</DicomField>
    </Dictionary>
    
.. _Balise_DicomField:

Tag DicomField
^^^^^^^^^^^^^^

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicity | Description                                                  |
+=================+===============+==============+==============================================================+
| tag             | Mandatory     |       1      | Contains Group-Element of the DICOM field                    |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| keyword         | Optional      |       1      | Contains keyword of the DICOM field                          |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| vr              | Mandatory     |       1      | Contains Value Representation of the DICOM field             |
+-----------------+---------------+--------------+--------------------------------------------------------------+
| private_creator | Optional      |       1      | Name of Private Dictionary if this attribut Group-Element    |
|                 |               |              | is defined in a Private Dictionary                           |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Tag DicomField contains an unique tag available in the following board:

+---------------------------------------------------------------+---------------+----------------+
| Tags                                                          | Usage         | Multiplicity   |
+===============================================================+===============+================+
| :ref:`AdditionOperator <Balise_AdditionOperator>`             | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`BrukerField <Balise_BrukerField>`                       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConditionField <Balise_ConditionField>`                 | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConstantField <Balise_ConstantField>`                   | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`DivisionOperator <Balise_DivisionOperator>`             | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`MultiplicationOperator <Balise_MultiplicationOperator>` | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`RegExFilter <Balise_RegExFilter>`                       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`SubtractionOperator <Balise_SubtractionOperator>`       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+

Remark: 
 - DivisionOperator and MultiplicationOperator are not available for string VR (AE, AS, CS, ...).
 - AdditionOperator performs mathematical addition for numeral VR and concatenate string VR.
 - SubtractionOperator performs mathematical subtraction for numeral VR and remove all pattern for string VR.

Sample:

.. code-block:: xml

    <DicomField tag="0010,0010" keyword="PatientName" vr="PN">
        <ConstantField values="My_Name" />
    </DicomField>
    
.. _Balise_AdditionOperator:

Tag AdditionOperator
^^^^^^^^^^^^^^^^^^^^

Tag AdditionOperator contains one or more tags availables in the following board:

+---------------------------------------------------------------+---------------+----------------+
| Tags                                                          | Usage         | Multiplicity   |
+===============================================================+===============+================+
| :ref:`AdditionOperator <Balise_AdditionOperator>`             | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`BrukerField <Balise_BrukerField>`                       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConditionField <Balise_ConditionField>`                 | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConstantField <Balise_ConstantField>`                   | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`DivisionOperator <Balise_DivisionOperator>`             | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`MultiplicationOperator <Balise_MultiplicationOperator>` | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`RegExFilter <Balise_RegExFilter>`                       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`SubtractionOperator <Balise_SubtractionOperator>`       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+

Sample:

.. code-block:: xml

    <AdditionOperator>
        <ConstantField values="1\2" />
        <ConstantField values="4\5" />
    </AdditionOperator>
    
.. _Balise_BrukerField:

Tag BrukerField
^^^^^^^^^^^^^^^

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicity | Description                                                  |
+=================+===============+==============+==============================================================+
| name            | Mandatory     |       1      | Contains name of the Bruker data field                       |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Sample:

.. code-block:: xml

    <BrukerField name="VisuSubjectId" />
    
.. _Balise_ConditionField:

Tag ConditionField
^^^^^^^^^^^^^^^^^^

Tag ConditionField contains the following tags:

+-------------------------------+---------------+---------------+
| Tags                          | Usage         | Multiplicity  |
+===============================+===============+===============+
| :ref:`If <Balise_If>`         | Mandatory     |       1       |
+-------------------------------+---------------+---------------+
| :ref:`Then <Balise_Then>`     | Mandatory     |       1       |
+-------------------------------+---------------+---------------+
| :ref:`Else <Balise_Else>`     | Mandatory     |       1       |
+-------------------------------+---------------+---------------+

Sample:

.. code-block:: xml

    <ConditionField>
        <If>...</If>
        <Then>...</Then>
        <Else>...</Else>
    </ConditionField>
    
.. _Balise_If:

Tag If
------

Tag If contains the following tags:

+---------------------------------------------------+---------------+---------------+
| Tags                                              | Usage         | Multiplicity  |
+===================================================+===============+===============+
| :ref:`AlwaysFalse <Balise_AlwaysFalse>`           | Optional      |      0-n      |
+---------------------------------------------------+---------------+---------------+
| :ref:`AlwaysTrue <Balise_AlwaysTrue>`             | Optional      |      0-n      |
+---------------------------------------------------+---------------+---------------+
| :ref:`BrukerFieldExist <Balise_BrukerFieldExist>` | Optional      |      0-n      |
+---------------------------------------------------+---------------+---------------+

Sample:

.. code-block:: xml

    <If>
        <BrukerFieldExist name="field_name_01" />
        <BrukerFieldExist name="field_name_02" />
    </If>
    
.. _Balise_AlwaysFalse:

Tag AlwaysFalse
_______________

Only used for testing.

Sample:

.. code-block:: xml

    <AlwaysFalse />
    
.. _Balise_AlwaysTrue:

Tag AlwaysTrue
______________

Only used for testing.

Sample:

.. code-block:: xml

    <AlwaysTrue />
    
.. _Balise_BrukerFieldExist:

Tag BrukerFieldExist
____________________

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicity | Description                                                  |
+=================+===============+==============+==============================================================+
| name            | Mandatory     |       1      | Contains name of the Bruker data field                       |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Sample:

.. code-block:: xml

    <BrukerFieldExist name="VisuSubjectId" />
    
.. _Balise_Then:

Tag Then
--------

Tag Then contains an unique tag available in the following board:

+---------------------------------------------------------------+---------------+----------------+
| Tags                                                          | Usage         | Multiplicity   |
+===============================================================+===============+================+
| :ref:`AdditionOperator <Balise_AdditionOperator>`             | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`BrukerField <Balise_BrukerField>`                       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConditionField <Balise_ConditionField>`                 | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConstantField <Balise_ConstantField>`                   | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`DivisionOperator <Balise_DivisionOperator>`             | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`MultiplicationOperator <Balise_MultiplicationOperator>` | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`RegExFilter <Balise_RegExFilter>`                       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`SubtractionOperator <Balise_SubtractionOperator>`       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+

Sample:

.. code-block:: xml

    <Then>
        <BrukerField name="field_name" />
    </Then>
    
.. _Balise_Else:

Tag Else
--------

Tag Else contains an unique tag available in the following board:

+---------------------------------------------------------------+---------------+----------------+
| Tags                                                          | Usage         | Multiplicity   |
+===============================================================+===============+================+
| :ref:`AdditionOperator <Balise_AdditionOperator>`             | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`BrukerField <Balise_BrukerField>`                       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConditionField <Balise_ConditionField>`                 | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConstantField <Balise_ConstantField>`                   | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`DivisionOperator <Balise_DivisionOperator>`             | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`MultiplicationOperator <Balise_MultiplicationOperator>` | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`RegExFilter <Balise_RegExFilter>`                       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`SubtractionOperator <Balise_SubtractionOperator>`       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+

Sample:

.. code-block:: xml

    <Else>
        <BrukerField name="field_name" />
    </Else>
    
.. _Balise_ConstantField:

Tag ConstantField
^^^^^^^^^^^^^^^^^

+-----------------+---------------+--------------+--------------------------------------------------------------+
| Attributs       | Usage         | Multiplicity | Description                                                  |
+=================+===============+==============+==============================================================+
| values          | Mandatory     |       1      | List of Values                                               |
+-----------------+---------------+--------------+--------------------------------------------------------------+

Sample:

.. code-block:: xml

    <ConstantField values="Value1\Value2\Value3" />
    
.. _Balise_DivisionOperator:

Tag DivisionOperator
^^^^^^^^^^^^^^^^^^^^

Tag DivisionOperator contains one or more tags availables in the following board:

+---------------------------------------------------------------+---------------+----------------+
| Tags                                                          | Usage         | Multiplicity   |
+===============================================================+===============+================+
| :ref:`AdditionOperator <Balise_AdditionOperator>`             | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`BrukerField <Balise_BrukerField>`                       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConditionField <Balise_ConditionField>`                 | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConstantField <Balise_ConstantField>`                   | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`DivisionOperator <Balise_DivisionOperator>`             | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`MultiplicationOperator <Balise_MultiplicationOperator>` | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`RegExFilter <Balise_RegExFilter>`                       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`SubtractionOperator <Balise_SubtractionOperator>`       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+

Sample:

.. code-block:: xml

    <DivisionOperator>
        <ConstantField values="12\4" />
        <ConstantField values="4\1" />
    </DivisionOperator>
    
.. _Balise_MultiplicationOperator:

Tag MultiplicationOperator
^^^^^^^^^^^^^^^^^^^^^^^^^^

Tag MultiplicationOperator contains one or more tags availables in the following board:

+---------------------------------------------------------------+---------------+----------------+
| Tags                                                          | Usage         | Multiplicity   |
+===============================================================+===============+================+
| :ref:`AdditionOperator <Balise_AdditionOperator>`             | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`BrukerField <Balise_BrukerField>`                       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConditionField <Balise_ConditionField>`                 | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConstantField <Balise_ConstantField>`                   | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`DivisionOperator <Balise_DivisionOperator>`             | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`MultiplicationOperator <Balise_MultiplicationOperator>` | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`RegExFilter <Balise_RegExFilter>`                       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`SubtractionOperator <Balise_SubtractionOperator>`       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+

Sample:

.. code-block:: xml

    <MultiplicationOperator>
        <ConstantField values="12\4" />
        <ConstantField values="4\1" />
    </MultiplicationOperator>
    
.. _Balise_RegExFilter:

Tag RegExFilter
^^^^^^^^^^^^^^^

Tag RegExFilter contains an unique tag available in the following board:

+---------------------------------------------------------------+---------------+----------------+
| Tags                                                          | Usage         | Multiplicity   |
+===============================================================+===============+================+
| :ref:`AdditionOperator <Balise_AdditionOperator>`             | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`BrukerField <Balise_BrukerField>`                       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConditionField <Balise_ConditionField>`                 | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConstantField <Balise_ConstantField>`                   | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`DivisionOperator <Balise_DivisionOperator>`             | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`MultiplicationOperator <Balise_MultiplicationOperator>` | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`RegExFilter <Balise_RegExFilter>`                       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`SubtractionOperator <Balise_SubtractionOperator>`       | Optional      |       0-1      |
+---------------------------------------------------------------+---------------+----------------+

Sample:

.. code-block:: xml

    <RegExFilter expression="^([0-9]{2}):{1}([0-9]{2}):{1}([0-9]{2}).*">
        <ConstantField values="10:10:10 abcd" />
    </RegExFilter>
    
.. _Balise_SubtractionOperator:

Tag SubtractionOperator
^^^^^^^^^^^^^^^^^^^^^^^

Tag SubtractionOperator contains one or more tags availables in the following board:

+---------------------------------------------------------------+---------------+----------------+
| Tags                                                          | Usage         | Multiplicity   |
+===============================================================+===============+================+
| :ref:`AdditionOperator <Balise_AdditionOperator>`             | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`BrukerField <Balise_BrukerField>`                       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConditionField <Balise_ConditionField>`                 | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`ConstantField <Balise_ConstantField>`                   | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`DivisionOperator <Balise_DivisionOperator>`             | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`MultiplicationOperator <Balise_MultiplicationOperator>` | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`RegExFilter <Balise_RegExFilter>`                       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+
| :ref:`SubtractionOperator <Balise_SubtractionOperator>`       | Optional      |       0-n      |
+---------------------------------------------------------------+---------------+----------------+

Sample:

.. code-block:: xml

    <SubtractionOperator>
        <ConstantField values="12\4" />
        <ConstantField values="4\1" />
    </SubtractionOperator>
    
