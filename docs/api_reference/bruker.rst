dicomifier.bruker
=================


.. py:module:: dicomifier.bruker


.. py:class:: Dataset
   :module: dicomifier.bruker

   A Bruker dataset. This objects implements part of the mapping 
   protocol: ``"foo" in d``, ``d["foo"]`` and ``for x in d``
   are valid constructs.


   .. py:method:: Dataset.get_field(self: dicomifier.bruker.Dataset, name: str) -> dicomifier::bruker::Field
      :module: dicomifier.bruker

      Return the field, throw an exception if field is missing.


   .. py:method:: Dataset.get_used_files(self: dicomifier.bruker.Dataset) -> List[str]
      :module: dicomifier.bruker

      Return a set of files used to create the dataset 
      (except the PixelData file)


   .. py:method:: Dataset.has_field(self: dicomifier.bruker.Dataset, name: str) -> bool
      :module: dicomifier.bruker

      Test if dataset contains a given field.


   .. py:method:: Dataset.items(self: dicomifier.bruker.Dataset) -> Iterator
      :module: dicomifier.bruker

      Iterate on fields


   .. py:method:: Dataset.load(self: dicomifier.bruker.Dataset, path: str) -> None
      :module: dicomifier.bruker

      Load dataset from file, update any existing field.


.. py:class:: Field
   :module: dicomifier.bruker

   A field (i.e. record in JCAMP-DX jargon) of a Bruker data set:
   container of named variant-typed items.


   .. py:class:: Field.Item
      :module: dicomifier.bruker


      .. py:method:: Field.Item.get_int(self: dicomifier.bruker.Field.Item) -> int
         :module: dicomifier.bruker

         Return a int-convertible item, throw an exception if not convertible.


      .. py:method:: Field.Item.get_real(self: dicomifier.bruker.Field.Item) -> float
         :module: dicomifier.bruker

         Return a real-convertible item, throw an exception if not convertible.


      .. py:method:: Field.Item.get_string(self: dicomifier.bruker.Field.Item) -> str
         :module: dicomifier.bruker

         Return a string item, throw an exception if not string-typed.


      .. py:method:: Field.Item.get_struct(self: dicomifier.bruker.Field.Item) -> List[dicomifier.bruker.Field.Item]
         :module: dicomifier.bruker

         Return a struct item, throw an exception if not struct-typed.


      .. py:method:: Field.Item.is_int(self: dicomifier.bruker.Field.Item) -> bool
         :module: dicomifier.bruker

         Test whether item is an int.


      .. py:method:: Field.Item.is_real(self: dicomifier.bruker.Field.Item) -> bool
         :module: dicomifier.bruker

         Test whether item is a real.


      .. py:method:: Field.Item.is_string(self: dicomifier.bruker.Field.Item) -> bool
         :module: dicomifier.bruker

         Test whether item is a string.


      .. py:method:: Field.Item.is_struct(self: dicomifier.bruker.Field.Item) -> bool
         :module: dicomifier.bruker

         Test whether item is a struct.


      .. py:property:: Field.Item.value
         :module: dicomifier.bruker


   .. py:method:: Field.get_int(self: dicomifier.bruker.Field, index: int) -> int
      :module: dicomifier.bruker

      Return a int-convertible item, throw an exception if not convertible.


   .. py:method:: Field.get_real(self: dicomifier.bruker.Field, index: int) -> float
      :module: dicomifier.bruker

      Return a real-convertible item, throw an exception if not convertible.


   .. py:method:: Field.get_string(self: dicomifier.bruker.Field, index: int) -> str
      :module: dicomifier.bruker

      Return a string item, throw an exception if not string-typed.


   .. py:method:: Field.get_struct(self: dicomifier.bruker.Field, index: int) -> List[boost::variant<boost::detail::variant::recursive_flag<long>, double, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, std::__1::vector<boost::recursive_variant_, std::__1::allocator<boost::recursive_variant_> > >]
      :module: dicomifier.bruker

      Return a struct item, throw an exception if not struct-typed.


   .. py:method:: Field.is_int(self: dicomifier.bruker.Field, index: int) -> bool
      :module: dicomifier.bruker

      Test whether item is an int.


   .. py:method:: Field.is_real(self: dicomifier.bruker.Field, index: int) -> bool
      :module: dicomifier.bruker

      Test whether item is a real.


   .. py:method:: Field.is_string(self: dicomifier.bruker.Field, index: int) -> bool
      :module: dicomifier.bruker

      Test whether item is a string.


   .. py:method:: Field.is_struct(self: dicomifier.bruker.Field, index: int) -> bool
      :module: dicomifier.bruker

      Test whether item is a struct.


   .. py:property:: Field.name
      :module: dicomifier.bruker

      Name of the field.


   .. py:property:: Field.shape
      :module: dicomifier.bruker

      Shape of the field.


   .. py:property:: Field.value
      :module: dicomifier.bruker

      Value of the field.
