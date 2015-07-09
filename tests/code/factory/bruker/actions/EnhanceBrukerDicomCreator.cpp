/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleEnhanceBrukerDicomCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"
#include "bruker/actions/EnhanceBrukerDicom.h"
#include "factory/bruker/actions/EnhanceBrukerDicomCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestDataOK01()
    {
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.reconumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        emptynode.put("<xmlattr>.outputdirectory", "#outputdir");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));

        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("outputdir", boost::any(text)));
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    test->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = test->Create(v);
        
        dicomifier::actions::EnhanceBrukerDicom::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::EnhanceBrukerDicom>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/*************************** TEST KO 05 *******************************/
/**
 * Error test case: Bad brukerdir value
 */
struct TestDataKO05
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO05()
    {
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#badvalue");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.reconumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        emptynode.put("<xmlattr>.outputdirectory", ".");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestDataKO05()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_05, TestDataKO05)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 06 *******************************/
/**
 * Error test case: Missing brukerdir mandatory attribut
 */
struct TestDataKO06
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO06()
    {
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.reconumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        emptynode.put("<xmlattr>.outputdirectory", ".");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestDataKO06()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_06, TestDataKO06)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), std::runtime_error);
    }
}

/*************************** TEST KO 07 *******************************/
/**
 * Error test case: Missing reconumber mandatory attribut
 */
struct TestDataKO07
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO07()
    {
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.seriesnunmber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        emptynode.put("<xmlattr>.outputdirectory", ".");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestDataKO07()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_07, TestDataKO07)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), 
                            std::runtime_error);
    }
}

/*************************** TEST KO 08 *******************************/
/**
 * Error test case: Bad Reconstruction number value
 */
struct TestDataKO08
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO08()
    {
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.reconumber", "ABCD");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        emptynode.put("<xmlattr>.outputdirectory", ".");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestDataKO08()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_08, TestDataKO08)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), 
                            std::runtime_error);
    }
}

/*************************** TEST KO 09 *******************************/
/**
 * Error test case: Bad dataset value
 */
struct TestDataKO09
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;

    TestDataKO09()
    {
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.reconumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        emptynode.put("<xmlattr>.outputdirectory", "#badvalue");
        ptr.add_child("EnhanceBrukerDicom", emptynode);

        std::string text = "./temp";

        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));

        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("outputdir", boost::any(text)));
    }

    ~TestDataKO09()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_09, TestDataKO09)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    test->set_outputs(outputs);

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), dicomifier::DicomifierException);
    }
}
