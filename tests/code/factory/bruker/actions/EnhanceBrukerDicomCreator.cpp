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
 
    TestDataOK01()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.studynumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = test->Create(v);
        
        dicomifier::actions::EnhanceBrukerDicom::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::EnhanceBrukerDicom>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Bad dataset value
 */
struct TestDataKO01
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO01()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.dataset", "#badvalue");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.studynumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Dataset not a reference
 */
struct TestDataKO02
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO02()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.dataset", "input");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.studynumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestDataKO02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataKO02)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Empty dataset
 */
struct TestDataKO03
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO03()
    {        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.studynumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        DcmDataset* dataset = NULL;
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestDataKO03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataKO03)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 04 *******************************/
/**
 * Error test case: Missing dataset mandatory attribut
 */
struct TestDataKO04
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO04()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.studynumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestDataKO04()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_04, TestDataKO04)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), 
                            dicomifier::DicomifierException);
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
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#badvalue");
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.studynumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
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
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.seriesnumber", "1");
        emptynode.put("<xmlattr>.studynumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
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
 * Error test case: Missing seriesnunmber mandatory attribut
 */
struct TestDataKO07
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO07()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.studynumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
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
 * Error test case: Bad Series number value
 */
struct TestDataKO08
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO08()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.seriesnumber", "ABCD");
        emptynode.put("<xmlattr>.studynumber", "1");
        emptynode.put("<xmlattr>.sopclassuid", "MR Image Storage");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
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
