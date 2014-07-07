/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDeleteElementCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"
#include "dicom/actions/DeleteElement.h"
#include "factory/dicom/actions/DeleteElementCreator.h"

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
        emptynode.put("<xmlattr>.tag", "0010,0010");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Creation, TestData)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
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
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("EmptyElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataBadTag()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowBadTag, TestDataBadTag)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testdelete->Create(v), dicomifier::DicomifierException);
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
        emptynode.put("<xmlattr>.dataset", "#unknownfile");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataBadFile()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowBadFile, TestDataBadFile)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testdelete->Create(v), dicomifier::DicomifierException);
    }
}
