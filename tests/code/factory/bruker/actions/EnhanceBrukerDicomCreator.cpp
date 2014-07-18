/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerDataset
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"
#include "bruker/actions/EnhanceBrukerDicom.h"
#include "factory/bruker/actions/EnhanceBrukerDicomCreator.h"

struct TestData
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestData()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Creation, TestData)
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
        emptynode.put("<xmlattr>.brukerdir", "#badvalue");
        emptynode.put("<xmlattr>.dataset", "#input");
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
        BOOST_REQUIRE_THROW(dicomifier::Object::Pointer object = test->Create(v), dicomifier::DicomifierException);
    }
}
