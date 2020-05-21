dicomifier.bruker
=================

.. class:: dicomifier.bruker.Dataset
  
  A Bruker dataset. This objects implements part of the mapping protocol: ``"foo" in d``, ``d["foo"]`` and ``for x in d`` are valid constructs.
  
  .. method:: load(path)
    
    Load dataset from file, update any existing field.
  
  .. method:: has_field(name)
    
    Test if dataset contains a given field.
  
  .. method:: get_field(name)
    
    Return the field, throw an exception if field is missing.
  
  .. method:: get_used_files()
    
    Return a set of files used to create the dataset (except the PixelData file)
  
  .. method:: items()
    
    Iterates on fields.

.. class:: dicomifier.bruker.Field
  
  A field of a Bruker dataset. A field is a container of named variant-typed items.
  
  .. attribute:: name
    
    Name of the field.
  
  .. attribute:: shape
    
    Shape of the field.
  
  .. attribute:: value
    
    Value of the field.
  
  .. method:: get_string(index)
    
    Return a string item, throw an exception if not string-typed.
  
  .. method:: get_int(index)
    
    Return a int-convertible item, throw an exception if not convertible.
  
  .. method:: get_real(index)
    
    Return a real-convertible item, throw an exception if not convertible.
  
  .. method:: get_struct(index)
    
    Return a struct item, throw an exception if not struct-typed.
  
  .. method:: is_int(index)
    
    Test whether item is an int.
  
  .. method:: is_real(index)
    
    Test whether item is a real.
  
  .. method:: is_string(index)
    
    Test whether item is a string.
  
  .. method:: is_struct(index)
    
    Test whether item is a struct.
