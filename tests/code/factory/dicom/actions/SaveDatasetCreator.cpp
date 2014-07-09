/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleSaveDatasetCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/Object.h"
#include "dicom/actions/SaveDataset.h"
#include "factory/dicom/actions/SaveDatasetCreator.h"

struct TestData
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestData()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "#output");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("SaveDataset", emptynode);
        
        std::string text = "/tmp/testfile.dcm";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(text)));
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Creation, TestData)
{
    auto testsave = dicomifier::factory::SaveDatasetCreator::New();
    testsave->set_inputs(inputs);
    testsave->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testsave->Create(v);
        
        dicomifier::actions::SaveDataset::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::SaveDataset>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

struct TestDataBadDataset
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataBadDataset()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "/tmp/testfile.dcm");
        emptynode.put("<xmlattr>.dataset", "bad_value");
        ptr.add_child("SaveDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataBadDataset()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Error01, TestDataBadDataset)
{
    auto testsave = dicomifier::factory::SaveDatasetCreator::New();
    testsave->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testsave->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataBadDataset02
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataBadDataset02()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "/tmp/testfile.dcm");
        emptynode.put("<xmlattr>.dataset", "#bad_value");
        ptr.add_child("SaveDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataBadDataset02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Error02, TestDataBadDataset02)
{
    auto testsave = dicomifier::factory::SaveDatasetCreator::New();
    testsave->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testsave->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataBadDataset03
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataBadDataset03()
    {
        // Create Test file
        DcmDataset* dataset = NULL;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "/tmp/testfile.dcm");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("SaveDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataBadDataset03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Error03, TestDataBadDataset03)
{
    auto testsave = dicomifier::factory::SaveDatasetCreator::New();
    testsave->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testsave->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataBadOutput
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestDataBadOutput()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "#bad_value");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("SaveDataset", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(std::string("/tmp/testfile.dcm"))));
    }
 
    ~TestDataBadOutput()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Error04, TestDataBadOutput)
{
    auto testsave = dicomifier::factory::SaveDatasetCreator::New();
    testsave->set_inputs(inputs);
    testsave->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testsave->Create(v), dicomifier::DicomifierException);
    }
}
