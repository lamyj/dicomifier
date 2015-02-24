Developer Guide
===============

API Dicomifier
--------------

Dicomifier is primarily a library. A simple 'main' has been created to generate a binary launcher.

If you want used it in your software, you should get the source code by 
checking out source file (see :ref:`Installation Guide <Balise_Checkout>`).

Parsing Private Dictionary
^^^^^^^^^^^^^^^^^^^^^^^^^^

Dicomifier Library contains a singleton named Dictionaries and defined in lib/dicom/Dictionaries.h.
With it, you can add many private dictionary (each dictionary should have an unique name).

- Create and get the Dictionaries instance:

.. code-block:: c++
    
    dicomifier.Dictionaries& instance = dicomifier.Dictionaries::get_instance();
    
- Add a new dictionary:

.. code-block:: c++
    
    std::string filepath = "./my_private_dictionary.xml";
    instance.ParsePrivateDictionary(filepath);
    
By default, Dictionaries contains the DICOM public dictionary (named 'public').

- Retrieve dictionary data:

    * GetTagFromName: Return the DcmTag of a given key name (and optional dictionary name)

    .. code-block:: c++
        
        DcmTag myTag = instance.GetTagFromName("PatientName");
        // or
        DcmTag myTag = instance.GetTagFromName("MyPrivateTag", "MyPrivateDictionary");
    
    * GetTagFromKey: Return the DcmTag of a given key (and optional dictionary name)

    .. code-block:: c++
        
        DcmTag myTag = instance.GetTagFromKey("0010,0010");
        // or
        DcmTag myTag = instance.GetTagFromKey("0023,xx01", "MyPrivateDictionary");
    
- Retrieve number associated to private dictionary, for a given dataset:

.. code-block:: c++
    
    Uint16 privateDictNumber = instance.FindCreatorElementNumber("MyPrivateDictionary", myDataset);
    
    
Parsing Bruker files
^^^^^^^^^^^^^^^^^^^^

Todo

Parsing XML rule files
^^^^^^^^^^^^^^^^^^^^^^

Dicomifier Library contains two static functions to parse XML files and generate a list of Rule objects.

You should first include the header file:

.. code-block:: c++
    
    #include XmlToRules.h

- Parsing XML file:

.. code-block:: c++
    
    std::vector<dicomifier.Object::Pointer> ruleObjects;
    ruleObjects = dicomifier.XmlToRules::Convert("./my_rules_file.xml");
    
- Parsing XML Node:

.. code-block:: c++
    
    boost::property_tree::ptree myXmlNode;
    // create your xml node object
    
    std::vector<dicomifier.Object::Pointer> ruleObjects;
    ruleObjects = dicomifier.XmlToRules::Convert(myXmlNode);

Comment: XML rule file or node should respect the rule syntax describe in chapter :ref:`Format of rule XML files <Balise_RuleFormat>`.
    
Adding new Actions
^^^^^^^^^^^^^^^^^^

You can add your owned actions in Dicomifier. To do this, you should create 2 classes (4 C++ files), for example: 
* MyAction.h
* MyAction.cpp
* MyActionCreator.h
* MyActionCreator.cpp

Class MyAction do all your action job. Class MyActionCreator is just a creator 
called by a factory which automatically creates an object 'MyAction' when parsing an XML file.

First, create header for MyAction class.

- Create a new class MyAction:

.. code-block:: c++

    // MyAction.h
    
    // include base class (from dicomifier library)
    #include "core/actions/Action.h"
    
    // inherit from Actions
    class MyAction: public Action
    {
    public:
        // Define new type
        typedef MyAction Self;
        typedef std::shared_ptr<Self> Pointer;
    };
    
- Add constructor / desctructor

.. code-block:: c++

    class MyAction: public Action
    {
    public:
        ...
        
        // Static constructor
        static Pointer New() { return Pointer(new Self()); }
        
        // Virtual Destructor
        virtual ~MyAction();
        
    private:
        // Private constructor: force used of New function
        MyAction();
        ...
    };
    
- Overload virtual pure functions:

.. code-block:: c++

    class MyAction: public Action
    {
    public:
        ...
        
        virtual void run() const;
    };
    
- Now you can implement MyAction class. The 'run' function is the main function called when Dicomifier is execute.

Then create header file for MyActionCreator class:

- Create a new class MyActionCreator:

.. code-block:: c++

    // MyActionCreator.h
    
    // include base class (from dicomifier library)
    #include "factory/core/CreatorBase.h"
    
    // inherit from CreatorBase
    class MyActionCreator: public CreatorBase
    {
    public:
        // Define new type
        typedef MyActionCreator Self;
        typedef std::shared_ptr<Self> Pointer;
    };
    
- Add constructor / desctructor

.. code-block:: c++

    class MyActionCreator: public CreatorBase
    {
    public:
        ...
        
        // Static constructor
        static Pointer New() { return Pointer(new Self()); }
        
        // Virtual Destructor
        virtual ~MyActionCreator();
        
    private:
        // Private constructor: force used of New function
        MyActionCreator();
        ...
    };
    
- Overload virtual pure functions:

.. code-block:: c++

    class MyActionCreator: public CreatorBase
    {
    public:
        ...
        
        virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);
    };
    
- Add a name to your class, this name is use by the factory:

.. code-block:: c++

    class MyActionCreator: public CreatorBase
    {
    public:
        ...
        
        static std::string get_class_name() { return "MyAction"; }
    };

- Now you can implement MyActionCreator class. The 'Create' function is the main function, automatically called when Dicomifier parse XML input file.

.. code-block:: c++

    // MyCreationCreator.cpp
    
    // Declared your class in Factory
    static unsigned int const registration = Factory::get_instance().register_<MyActionCreator>();
    
Now you can compile your project and try running the new Action.
    
Adding new Conditions
^^^^^^^^^^^^^^^^^^^^^

You can add your owned conditions in Dicomifier. To do this, you should create 2 classes (4 C++ files), for example: 
* MyCondition.h
* MyCondition.cpp
* MyConditionCreator.h
* MyConditionCreator.cpp

Class MyCondition do all your condition job and return a boolean. Class MyConditionCreator is just a creator 
called by a factory which automatically creates an object 'MyCondition' when parsing an XML file.

First, create header for MyCondition class.

- Create a new class MyCondition:

.. code-block:: c++

    // MyCondition.h
    
    // include base class (from dicomifier library)
    #include "core/conditions/Condition.h"
    
    // inherit from Actions
    class MyCondition: public Condition
    {
    public:
        // Define new type
        typedef MyCondition Self;
        typedef std::shared_ptr<Self> Pointer;
    };
    
- Add constructor / desctructor

.. code-block:: c++

    class MyCondition: public Condition
    {
    public:
        ...
        
        // Static constructor
        static Pointer New() { return Pointer(new Self()); }
        
        // Virtual Destructor
        virtual ~MyCondition();
        
    private:
        // Private constructor: force used of New function
        MyCondition();
        ...
    };
    
- Overload virtual pure functions:

.. code-block:: c++

    class MyCondition: public Condition
    {
    public:
        ...
        
        virtual bool eval() const;
    };
    
- Now you can implement MyCondition class. The 'eval' function is the main function called when Dicomifier is execute.

Then create header file for MyConditionCreator class:

- Create a new class MyConditionCreator:

.. code-block:: c++

    // MyConditionCreator.h
    
    // include base class (from dicomifier library)
    #include "factory/core/CreatorBase.h"
    
    // inherit from CreatorBase
    class MyConditionCreator: public CreatorBase
    {
    public:
        // Define new type
        typedef MyConditionCreator Self;
        typedef std::shared_ptr<Self> Pointer;
    };
    
- Add constructor / desctructor

.. code-block:: c++

    class MyConditionCreator: public CreatorBase
    {
    public:
        ...
        
        // Static constructor
        static Pointer New() { return Pointer(new Self()); }
        
        // Virtual Destructor
        virtual ~MyConditionCreator();
        
    private:
        // Private constructor: force used of New function
        MyConditionCreator();
        ...
    };
    
- Overload virtual pure functions:

.. code-block:: c++

    class MyConditionCreator: public CreatorBase
    {
    public:
        ...
        
        virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);
    };
    
- Add a name to your class, this name is use by the factory:

.. code-block:: c++

    class MyConditionCreator: public CreatorBase
    {
    public:
        ...
        
        static std::string get_class_name() { return "MyCondition"; }
    };

- Now you can implement MyConditionCreator class. The 'Create' function is the main function, automatically called when Dicomifier parse XML input file.

.. code-block:: c++

    // MyConditionCreator.cpp
    
    // Declared your class in Factory
    static unsigned int const registration = Factory::get_instance().register_<MyConditionCreator>();
    
Now you can compile your project and try running the new Condition.
    
Dicomifier Exception
^^^^^^^^^^^^^^^^^^^^

There is a class to raise and catch exception in Dicomifier: DicomifierException.
This base class inherit from std::exception class.

To raise an exception use the base constructor:

.. code-block:: c++
    
    throw dicomifier.DicomifierException("any comment");
    
To catch and display error message:

.. code-block:: c++
    
    try
    {
        throw dicomifier.DicomifierException("any comment");
    }
    catch (dicomifier.DicomifierException exception)
    {
        std::cout << exception.what() << std::endl;
    }
    
You can inherit from this base class to manage exception in your software.
Simply create your exception.h:

.. code-block:: c++
    
    #include DicomifierException.h
    
    class MyException: public dicomifier.DicomifierException
    {
        // your class definition
    };

Python Wrapper
--------------

A Python Wrapper has been created and works like the binary launcher.
To use Dicomifier in your Python Code:

- Include python file dicomifier.py

.. code-block:: python
    
    import dicomifier
    
- Call function execute

.. code-block:: python
    
    dicomifier.execute(rulesXML, privateDictionary)


Only the DicomifierException class is wrapped. You can catch Dicomifier Exception.

.. code-block:: python
    
    try:
        dicomifier.execute(rulesXML, privateDictionary)
    except dicomifier.DicomifierException as e:
        print e

Generate Documentation
----------------------

Documentation is generated by Sphinx (See http://sphinx-doc.org/).

After checking out the source code, you can find a repository 'dicomifier/doc/'.
It contains this documentation.

You can add your owned pages or add a new language.

Build the documentation
^^^^^^^^^^^^^^^^^^^^^^^

- Go to the directory 'dicomifier/doc':

.. code-block:: sh
    
    cd dicomifier/doc/
    
- Create a map with all documentation texts:

.. code-block:: sh
    
    make gettext
    
As a result, many pot files are generated under _build/locale directory.

- Defined what languages you want for the documentation:

.. code-block:: sh
    
    export SPHINXINTL_LANGUAGE=en,fr
    
Now you are creating documentation in English and French.

- Go to 'source' directory:

.. code-block:: sh
    
    cd source/

- Generate the translation files:

.. code-block:: sh
    
    sphinx-intl update -p _build/locale
    
You got these directories that contain po files:

    * ./language/en/LC_MESSAGES/
    * ./language/fr/LC_MESSAGES/
    
- Translate your po files.

- Compile translation files:

.. code-block:: sh
    
    sphinx-intl build
    
- Return to previous directory ('doc'):

.. code-block:: sh
    
    cd ..
    
- Generate the documentation in french:

.. code-block:: sh
    
    make -e SPHINXOPTS="-D language='fr'" html
    
Done. Documentation is now available under build/html directory.
Open the html main page 'index.html' with a web browser (like Google Chrome).
