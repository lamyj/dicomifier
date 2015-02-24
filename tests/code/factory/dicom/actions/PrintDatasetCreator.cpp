/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModulePrintDatasetCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/Object.h"
#include "dicom/actions/PrintDataset.h"
#include "factory/dicom/actions/PrintDatasetCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    dicomifier::factory::PrintDatasetCreator::Pointer printdscreator = 
        dicomifier::factory::PrintDatasetCreator::New();
    BOOST_CHECK_EQUAL(printdscreator != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Creation (function create)
 */
struct TestDataOK02
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestDataOK02()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "#output");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("PrintDataset", emptynode);
        
        std::string text = "/tmp/testfile.dcm";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(text)));
    }
 
    ~TestDataOK02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    auto testprint = dicomifier::factory::PrintDatasetCreator::New();
    testprint->set_inputs(inputs);
    testprint->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testprint->Create(v);
        
        dicomifier::actions::PrintDataset::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::PrintDataset>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Missing 'dataset' XML attribut
 */
 struct TestDataKO01
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestDataKO01()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "#output");
        ptr.add_child("PrintDataset", emptynode);
        
        std::string text = "/tmp/testfile.dcm";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(text)));
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto testprint = dicomifier::factory::PrintDatasetCreator::New();
    testprint->set_inputs(inputs);
    testprint->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testprint->Create(v), std::runtime_error);
    }
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Missing 'outputfile' XML attribut
 */
 struct TestDataKO02
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestDataKO02()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("PrintDataset", emptynode);
        
        std::string text = "/tmp/testfile.dcm";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(text)));
    }
 
    ~TestDataKO02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataKO02)
{
    auto testprint = dicomifier::factory::PrintDatasetCreator::New();
    testprint->set_inputs(inputs);
    testprint->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testprint->Create(v), std::runtime_error);
    }
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Empty Dataset
 */
 struct TestDataKO03
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestDataKO03()
    {
        // Create Test file
        DcmDataset* dataset = NULL;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "#output");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("PrintDataset", emptynode);
        
        std::string text = "/tmp/testfile.dcm";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(text)));
    }
 
    ~TestDataKO03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataKO03)
{
    auto testprint = dicomifier::factory::PrintDatasetCreator::New();
    testprint->set_inputs(inputs);
    testprint->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testprint->Create(v), dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 04 *******************************/
/**
 * Error test case: Bad input Dataset Link
 */
 struct TestDataKO04
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestDataKO04()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "#output");
        emptynode.put("<xmlattr>.dataset", "badvalue");
        ptr.add_child("PrintDataset", emptynode);
        
        std::string text = "/tmp/testfile.dcm";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(text)));
    }
 
    ~TestDataKO04()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_04, TestDataKO04)
{
    auto testprint = dicomifier::factory::PrintDatasetCreator::New();
    testprint->set_inputs(inputs);
    testprint->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testprint->Create(v), dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 05 *******************************/
/**
 * Error test case: Unknown input Dataset Link
 */
 struct TestDataKO05
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestDataKO05()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "#output");
        emptynode.put("<xmlattr>.dataset", "#badvalue");
        ptr.add_child("PrintDataset", emptynode);
        
        std::string text = "/tmp/testfile.dcm";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(text)));
    }
 
    ~TestDataKO05()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_05, TestDataKO05)
{
    auto testprint = dicomifier::factory::PrintDatasetCreator::New();
    testprint->set_inputs(inputs);
    testprint->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testprint->Create(v), dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 06 *******************************/
/**
 * Error test case: Unknown output file Link
 */
 struct TestDataKO06
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
 
    TestDataKO06()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.outputfile", "#badvalue");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("PrintDataset", emptynode);
        
        std::string text = "/tmp/testfile.dcm";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(text)));
    }
 
    ~TestDataKO06()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_06, TestDataKO06)
{
    auto testprint = dicomifier::factory::PrintDatasetCreator::New();
    testprint->set_inputs(inputs);
    testprint->set_outputs(outputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testprint->Create(v), dicomifier::DicomifierException);
    }
}
