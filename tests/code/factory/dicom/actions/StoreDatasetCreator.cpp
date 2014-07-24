/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleStoreDatasetCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include "core/DicomifierException.h"
#include "dicom/actions/StoreDataset.h"
#include "factory/dicom/actions/StoreDatasetCreator.h"

/**************************** TEST OK 01 ******************************/
/**
 * StoreDataset Creation
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
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.address", "myaddress");
        emptynode.put("<xmlattr>.port", "11112");
        emptynode.put("<xmlattr>.aeremote", "REMOTE");
        emptynode.put("<xmlattr>.aelocal", "LOCAL");
        ptr.add_child("StoreDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto teststore = dicomifier::factory::StoreDatasetCreator::New();
    teststore->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = teststore->Create(v);
        
        dicomifier::actions::StoreDataset::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::StoreDataset>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST KO 01 ******************************/
/**
 * Missing 'aelocal' attribut
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
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.address", "myaddress");
        emptynode.put("<xmlattr>.port", "11112");
        emptynode.put("<xmlattr>.aeremote", "REMOTE");
        ptr.add_child("StoreDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto teststore = dicomifier::factory::StoreDatasetCreator::New();
    teststore->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {        
        BOOST_REQUIRE_THROW(teststore->Create(v), std::runtime_error);
    }
}

/**************************** TEST KO 02 ******************************/
/**
 * Missing 'aeremote' attribut
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
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.address", "myaddress");
        emptynode.put("<xmlattr>.port", "11112");
        emptynode.put("<xmlattr>.aelocal", "LOCAL");
        ptr.add_child("StoreDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataKO02)
{
    auto teststore = dicomifier::factory::StoreDatasetCreator::New();
    teststore->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {        
        BOOST_REQUIRE_THROW(teststore->Create(v), std::runtime_error);
    }
}

/**************************** TEST KO 03 ******************************/
/**
 * Missing 'port' attribut
 */
struct TestDataKO03
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO03()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.address", "myaddress");
        emptynode.put("<xmlattr>.aeremote", "REMOTE");
        emptynode.put("<xmlattr>.aelocal", "LOCAL");
        ptr.add_child("StoreDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataKO03)
{
    auto teststore = dicomifier::factory::StoreDatasetCreator::New();
    teststore->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {        
        BOOST_REQUIRE_THROW(teststore->Create(v), std::runtime_error);
    }
}

/**************************** TEST KO 04 ******************************/
/**
 * Missing 'address' attribut
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
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.port", "11112");
        emptynode.put("<xmlattr>.aeremote", "REMOTE");
        emptynode.put("<xmlattr>.aelocal", "LOCAL");
        ptr.add_child("StoreDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO04()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_04, TestDataKO04)
{
    auto teststore = dicomifier::factory::StoreDatasetCreator::New();
    teststore->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {        
        BOOST_REQUIRE_THROW(teststore->Create(v), std::runtime_error);
    }
}

/**************************** TEST KO 05 ******************************/
/**
 * DcmDataset == NULL
 */
struct TestDataKO05
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO05()
    {
        // Create Test file
        DcmDataset* dataset = NULL;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.address", "myaddress");
        emptynode.put("<xmlattr>.port", "11112");
        emptynode.put("<xmlattr>.aeremote", "REMOTE");
        emptynode.put("<xmlattr>.aelocal", "LOCAL");
        ptr.add_child("StoreDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO05()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_05, TestDataKO05)
{
    auto teststore = dicomifier::factory::StoreDatasetCreator::New();
    teststore->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {        
        BOOST_REQUIRE_THROW(teststore->Create(v), dicomifier::DicomifierException);
    }
}

/**************************** TEST KO 06 ******************************/
/**
 * wrong 'dataset' attribut
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
        emptynode.put("<xmlattr>.dataset", "input");
        emptynode.put("<xmlattr>.address", "myaddress");
        emptynode.put("<xmlattr>.port", "11112");
        emptynode.put("<xmlattr>.aeremote", "REMOTE");
        emptynode.put("<xmlattr>.aelocal", "LOCAL");
        ptr.add_child("StoreDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO06()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_06, TestDataKO06)
{
    auto teststore = dicomifier::factory::StoreDatasetCreator::New();
    teststore->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {        
        BOOST_REQUIRE_THROW(teststore->Create(v), dicomifier::DicomifierException);
    }
}

/**************************** TEST KO 07 ******************************/
/**
 * Dataset linked to unknown input
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
        emptynode.put("<xmlattr>.dataset", "#badvalue");
        emptynode.put("<xmlattr>.address", "myaddress");
        emptynode.put("<xmlattr>.port", "11112");
        emptynode.put("<xmlattr>.aeremote", "REMOTE");
        emptynode.put("<xmlattr>.aelocal", "LOCAL");
        ptr.add_child("StoreDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO07()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_07, TestDataKO07)
{
    auto teststore = dicomifier::factory::StoreDatasetCreator::New();
    teststore->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {        
        BOOST_REQUIRE_THROW(teststore->Create(v), dicomifier::DicomifierException);
    }
}