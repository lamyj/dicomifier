/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleElementMatchCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"
#include "dicom/conditions/ElementMatch.h"
#include "factory/dicom/conditions/ElementMatchCreator.h"

struct TestDataCS
{
    boost::property_tree::ptree ptr;
 
    TestDataCS()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_PatientSex, OFString("M"), true);
        dataset->saveFile("./tempfileCS", EXS_LittleEndianExplicit);
        delete dataset;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("tag", "PatientSex");
        emptynode.put("value", "M");
        emptynode.put("VR", "CS");
        emptynode.put("dataset", "./tempfileCS");
        ptr.add_child("ElementMatch", emptynode);
    }
 
    ~TestDataCS()
    {
        // Delete Test file
        remove("./tempfileCS");
    }
};

BOOST_FIXTURE_TEST_CASE(CreationCS, TestDataCS)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_CS>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_CS>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

struct TestDataPN
{
    boost::property_tree::ptree ptr;
 
    TestDataPN()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->saveFile("./tempfilePN", EXS_LittleEndianExplicit);
        delete dataset;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("tag", "0010,0010");
        emptynode.put("value", "John");
        emptynode.put("VR", "PN");
        emptynode.put("dataset", "./tempfilePN");
        ptr.add_child("ElementMatch", emptynode);
    }
 
    ~TestDataPN()
    {
        // Delete Test file
        remove("./tempfilePN");
    }
};

BOOST_FIXTURE_TEST_CASE(CreationPN, TestDataPN)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_PN>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_PN>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

struct TestDataUT
{
    boost::property_tree::ptree ptr;
 
    TestDataUT()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("myUnlimitedText");
        dataset->putAndInsertOFStringArray(DCM_PixelDataProviderURL, name, true);
        dataset->saveFile("./tempfileUT", EXS_LittleEndianExplicit);
        delete dataset;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("tag", "PixelDataProviderURL");
        emptynode.put("value", "myUnlimitedText");
        emptynode.put("VR", "UT");
        emptynode.put("dataset", "./tempfileUT");
        ptr.add_child("ElementMatch", emptynode);
    }
 
    ~TestDataUT()
    {
        // Delete Test file
        remove("./tempfileUT");
    }
};

BOOST_FIXTURE_TEST_CASE(CreationUT, TestDataUT)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_UT>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_UT>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

struct TestDataBadTag
{
    boost::property_tree::ptree ptr;
 
    TestDataBadTag()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        dataset->saveFile("./tempfilebadtag", EXS_LittleEndianExplicit);
        delete dataset;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("tag", "bad tag");
        emptynode.put("value", "John");
        emptynode.put("VR", "PN");
        emptynode.put("dataset", "./tempfilebadtag");
        ptr.add_child("ElementMatch", emptynode);
    }
 
    ~TestDataBadTag()
    {
        // Delete Test file
        remove("./tempfilebadtag");
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowBadTag, TestDataBadTag)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testmatch->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataBadFile
{
    boost::property_tree::ptree ptr;
 
    TestDataBadFile()
    {        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("tag", "PatientName");
        emptynode.put("value", "John");
        emptynode.put("VR", "PN");
        emptynode.put("dataset", "./unknownfile");
        ptr.add_child("ElementMatch", emptynode);
    }
 
    ~TestDataBadFile()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowBadFile, TestDataBadFile)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testmatch->Create(v), dicomifier::DicomifierException);
    }
}
