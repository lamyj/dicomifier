/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleSetElementCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"
#include "dicom/actions/SetElement.h"
#include "factory/dicom/actions/SetElementCreator.h"


struct TestDataCS
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataCS()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_PatientSex, OFString("M"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientSex");
        emptynode.put("<xmlattr>.value", "F");
        emptynode.put("<xmlattr>.VR", "CS");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("SetElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataCS()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationCS, TestDataCS)
{
    auto testset = dicomifier::factory::SetElementCreator::New();
    testset->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testset->Create(v);
        
        dicomifier::actions::SetElement<EVR_CS>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::actions::SetElement<EVR_CS>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

struct TestDataUT
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataUT()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("myFirstUnlimitedText");
        dataset->putAndInsertOFStringArray(DCM_PixelDataProviderURL, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PixelDataProviderURL");
        emptynode.put("<xmlattr>.value", "mySecondUnlimitedText");
        emptynode.put("<xmlattr>.VR", "UT");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("SetElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataUT()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationUT, TestDataUT)
{
    auto testset = dicomifier::factory::SetElementCreator::New();
    testset->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testset->Create(v);
        
        dicomifier::actions::SetElement<EVR_UT>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::actions::SetElement<EVR_UT>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

struct TestDataBadTag
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataBadTag()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "bad tag");
        emptynode.put("<xmlattr>.value", "Doe");
        emptynode.put("<xmlattr>.VR", "PN");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("SetElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataBadTag()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowBadTag, TestDataBadTag)
{
    auto testset = dicomifier::factory::SetElementCreator::New();
    testset->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testset->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataBadFile
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataBadFile()
    {        
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientName");
        emptynode.put("<xmlattr>.value", "John");
        emptynode.put("<xmlattr>.VR", "PN");
        emptynode.put("<xmlattr>.dataset", "#unknownfile");
        ptr.add_child("SetElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataBadFile()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowBadFile, TestDataBadFile)
{
    auto testset = dicomifier::factory::SetElementCreator::New();
    testset->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testset->Create(v), dicomifier::DicomifierException);
    }
}
