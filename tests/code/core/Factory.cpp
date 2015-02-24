/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleFactory
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include "core/Factory.h"
#include "core/Object.h"
#include "factory/bruker/actions/EnhanceBrukerDicomCreator.h"
#include "factory/core/RuleCreator.h"
#include "factory/core/actions/NoneCreator.h"
#include "factory/core/conditions/AllCreator.h"
#include "factory/core/conditions/AnyCreator.h"
#include "factory/core/conditions/FalseCreator.h"
#include "factory/core/conditions/NotCreator.h"
#include "factory/core/conditions/TrueCreator.h"
#include "factory/dicom/actions/DeleteElementCreator.h"
#include "factory/dicom/actions/EmptyElementCreator.h"
#include "factory/dicom/actions/PrintDatasetCreator.h"
#include "factory/dicom/actions/SaveDatasetCreator.h"
#include "factory/dicom/actions/SetElementCreator.h"
#include "factory/dicom/actions/StoreDatasetCreator.h"
#include "factory/dicom/conditions/ElementMatchCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor / Destructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    dicomifier::Factory::get_instance();
    dicomifier::Factory::delete_instance();
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Register
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    dicomifier::Factory::delete_instance();
    dicomifier::Factory& factory_ = dicomifier::Factory::get_instance();
    
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::RuleCreator>(), 1);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::NoneCreator>(), 2);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::AllCreator>(), 3);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::AnyCreator>(), 4);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::FalseCreator>(), 5);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::NotCreator>(), 6);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::TrueCreator>(), 7);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::EnhanceBrukerDicomCreator>(), 8);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::DeleteElementCreator>(), 9);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::EmptyElementCreator>(), 10);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::PrintDatasetCreator>(), 11);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::SaveDatasetCreator>(), 12);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::SetElementCreator>(), 13);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::StoreDatasetCreator>(), 14);
    BOOST_CHECK_EQUAL(factory_.register_<dicomifier::factory::ElementMatchCreator>(), 15);
}
 
/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: can_create function
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    std::string const true_ = "True";
    BOOST_CHECK_EQUAL(dicomifier::Factory::get_instance().can_create(true_), true);
    std::string const badnode = "UnknownNode";
    BOOST_CHECK_EQUAL(dicomifier::Factory::get_instance().can_create(badnode), false);
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: create function
 */
struct TestDataOK04
{
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> outputs;
    boost::property_tree::ptree emptynode;
    
    boost::property_tree::ptree ptrRule;
    boost::property_tree::ptree ptrNone;
    boost::property_tree::ptree ptrAll;
    boost::property_tree::ptree ptrAny;
    boost::property_tree::ptree ptrFalse;
    boost::property_tree::ptree ptrNot;
    boost::property_tree::ptree ptrTrue;
    boost::property_tree::ptree ptrEnhanceBrukerDicom;
    boost::property_tree::ptree ptrDeleteElement;
    boost::property_tree::ptree ptrEmptyElement;
    boost::property_tree::ptree ptrPrintDataset;
    boost::property_tree::ptree ptrSaveDataset;
    boost::property_tree::ptree ptrSetElement;
    boost::property_tree::ptree ptrStoreDataset;
    boost::property_tree::ptree ptrElementMatch;
 
    TestDataOK04()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        
        std::string text = "/tmp/testfile.dcm";
        
        outputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        outputs->insert(std::pair<std::string, boost::any>("output", boost::any(text)));
        
        // Test RuleCreator
        boost::property_tree::ptree rulenode;
        rulenode.add_child("Condition", emptynode);
        rulenode.add_child("Actions", emptynode);
        ptrRule.add_child("Rule", rulenode);
        
        // Test NoneCreator
        ptrNone.add_child("None", emptynode);
        
        // Test AllCreator
        ptrAll.add_child("All", emptynode);
        
        // Test AnyCreator
        ptrAny.add_child("Any", emptynode);
        
        // Test FalseCreator
        ptrFalse.add_child("False", emptynode);
        
        // Test NotCreator
        boost::property_tree::ptree truenode;
        truenode.add_child("True", emptynode);
        ptrNot.add_child("Not", truenode);
        
        // Test TrueCreator
        ptrTrue.add_child("True", emptynode);
    
        // Test EnhanceBrukerDicomCreator
        // TODO RLA
        
        // Test DeleteElementCreator
        boost::property_tree::ptree attrDeleteElementnode;
        attrDeleteElementnode.put("<xmlattr>.tag", "0010,0010");
        attrDeleteElementnode.put("<xmlattr>.dataset", "#input");
        ptrDeleteElement.add_child("DeleteElement", attrDeleteElementnode);
        
        // Test EmptyElementCreator
        boost::property_tree::ptree attrEmptyElementnode;
        attrEmptyElementnode.put("<xmlattr>.tag", "0010,0010");
        attrEmptyElementnode.put("<xmlattr>.dataset", "#input");
        attrEmptyElementnode.put("<xmlattr>.VR", "PN");
        ptrEmptyElement.add_child("EmptyElement", attrEmptyElementnode);
        
        // Test PrintDatasetCreator
        boost::property_tree::ptree attrPrintDatasetnode;
        attrPrintDatasetnode.put("<xmlattr>.outputfile", "");
        attrPrintDatasetnode.put("<xmlattr>.dataset", "#input");
        ptrPrintDataset.add_child("PrintDataset", attrPrintDatasetnode);
        
        // Test SaveDatasetCreator
        boost::property_tree::ptree attrSaveDatasetnode;
        attrSaveDatasetnode.put("<xmlattr>.outputfile", "#output");
        attrSaveDatasetnode.put("<xmlattr>.dataset", "#input");
        ptrSaveDataset.add_child("SaveDataset", attrSaveDatasetnode);
        
        // Test SetElementCreator
        boost::property_tree::ptree attrSetElementnode;
        attrSetElementnode.put("<xmlattr>.tag", "PerformedStationAETitle");
        attrSetElementnode.put("<xmlattr>.value", "EFGH");
        attrSetElementnode.put("<xmlattr>.VR", "AE");
        attrSetElementnode.put("<xmlattr>.dataset", "#input");
        ptrSetElement.add_child("SetElement", attrSetElementnode);
        
        // Test StoreDatasetCreator
        boost::property_tree::ptree attrStoreDatasetnode;
        attrStoreDatasetnode.put("<xmlattr>.dataset", "#input");
        attrStoreDatasetnode.put("<xmlattr>.address", "myaddress");
        attrStoreDatasetnode.put("<xmlattr>.port", "11112");
        attrStoreDatasetnode.put("<xmlattr>.aeremote", "REMOTE");
        attrStoreDatasetnode.put("<xmlattr>.aelocal", "LOCAL");
        ptrStoreDataset.add_child("StoreDataset", attrStoreDatasetnode);
        
        // Test ElementMatchCreator
        boost::property_tree::ptree attrElementMatchnode;
        attrElementMatchnode.put("<xmlattr>.tag", "PerformedStationAETitle");
        attrElementMatchnode.put("<xmlattr>.value", "ABCD");
        attrElementMatchnode.put("<xmlattr>.VR", "AE");
        attrElementMatchnode.put("<xmlattr>.dataset", "#input");
        ptrElementMatch.add_child("ElementMatch", attrElementMatchnode);
    }
 
    ~TestDataOK04()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
{
    // Test RuleCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrRule)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, NULL, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test NoneCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrNone)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, NULL, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test AllCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrAll)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, NULL, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test AnyCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrAny)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, NULL, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test FalseCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrFalse)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, NULL, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test NotCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrNot)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, NULL, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test TrueCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrTrue)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, NULL, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test EnhanceBrukerDicomCreator
    
    // Test DeleteElementCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrDeleteElement)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, inputs, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test EmptyElementCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrEmptyElement)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, inputs, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test PrintDatasetCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrPrintDataset)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, inputs, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test SaveDatasetCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrSaveDataset)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, inputs, outputs);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test SetElementCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrSetElement)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, inputs, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test StoreDatasetCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrStoreDataset)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, inputs, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
    // Test ElementMatchCreator
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrElementMatch)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, inputs, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: create function
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    boost::property_tree::ptree emptynode;
    
    boost::property_tree::ptree ptrKO;
    ptrKO.add_child("UnknownNode", emptynode);
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v2, ptrKO)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v2, NULL, NULL);
        BOOST_CHECK_EQUAL(object == NULL, true);
    }
}
