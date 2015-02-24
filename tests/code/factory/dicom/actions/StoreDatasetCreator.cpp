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

struct FixtureBase
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    FixtureBase()
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
};

/************************** No user identification ****************************/

struct NoUserIdFixture: public FixtureBase
{
    NoUserIdFixture()
    : FixtureBase()
    {
        // Do not modify user identification
    }
};

BOOST_FIXTURE_TEST_CASE(NoUserId, NoUserIdFixture)
{
    auto creator = dicomifier::factory::StoreDatasetCreator::New();
    creator->set_inputs(this->inputs);
    
    auto object = creator->Create(this->ptr.front());
    auto act = std::dynamic_pointer_cast<dicomifier::actions::StoreDataset>(object);
    
    BOOST_CHECK(act != NULL);
    
    BOOST_CHECK_EQUAL(act->get_address(), "myaddress");
    BOOST_CHECK_EQUAL(act->get_port(), 11112);
    BOOST_CHECK_EQUAL(act->get_AEremote(), "REMOTE");
    BOOST_CHECK_EQUAL(act->get_AElocal(), "LOCAL");
    BOOST_CHECK(act->get_user_identity_type() == 
        dicomifier::UserIdentityType::None);
    BOOST_CHECK_EQUAL(act->get_user_identity_primary_field(), "");
    BOOST_CHECK_EQUAL(act->get_user_identity_secondary_field(), "");
}

/************************** User name only ****************************/

struct UserNameOnlyFixture: public FixtureBase
{
    UserNameOnlyFixture()
    : FixtureBase()
    {
        ptr.put("StoreDataset.<xmlattr>.user", "georges.brouchard");
    }
};

BOOST_FIXTURE_TEST_CASE(UserNameOnly, UserNameOnlyFixture)
{
    auto creator = dicomifier::factory::StoreDatasetCreator::New();
    creator->set_inputs(this->inputs);
    
    auto object = creator->Create(this->ptr.front());
    auto act = std::dynamic_pointer_cast<dicomifier::actions::StoreDataset>(object);
    
    BOOST_CHECK(act != NULL);
    
    BOOST_CHECK_EQUAL(act->get_address(), "myaddress");
    BOOST_CHECK_EQUAL(act->get_port(), 11112);
    BOOST_CHECK_EQUAL(act->get_AEremote(), "REMOTE");
    BOOST_CHECK_EQUAL(act->get_AElocal(), "LOCAL");
    BOOST_CHECK(act->get_user_identity_type() == 
        dicomifier::UserIdentityType::Username);
    BOOST_CHECK_EQUAL(act->get_user_identity_primary_field(), 
        "georges.brouchard");
    BOOST_CHECK_EQUAL(act->get_user_identity_secondary_field(), "");
}

/************************** User name and password ****************************/

struct UserNameAndPasswordFixture: public FixtureBase
{
    UserNameAndPasswordFixture()
    : FixtureBase()
    {
        ptr.put("StoreDataset.<xmlattr>.user", "georges.brouchard");
        ptr.put("StoreDataset.<xmlattr>.password", "pAssw0rd!");
    }
};

BOOST_FIXTURE_TEST_CASE(UserNameAndPassword, UserNameAndPasswordFixture)
{
    auto creator = dicomifier::factory::StoreDatasetCreator::New();
    creator->set_inputs(this->inputs);
    
    auto object = creator->Create(this->ptr.front());
    auto act = std::dynamic_pointer_cast<dicomifier::actions::StoreDataset>(object);
    
    BOOST_CHECK(act != NULL);
    
    BOOST_CHECK_EQUAL(act->get_address(), "myaddress");
    BOOST_CHECK_EQUAL(act->get_port(), 11112);
    BOOST_CHECK_EQUAL(act->get_AEremote(), "REMOTE");
    BOOST_CHECK_EQUAL(act->get_AElocal(), "LOCAL");
    BOOST_CHECK(act->get_user_identity_type() == 
        dicomifier::UserIdentityType::UsernameAndPassword);
    BOOST_CHECK_EQUAL(act->get_user_identity_primary_field(), 
        "georges.brouchard");
    BOOST_CHECK_EQUAL(act->get_user_identity_secondary_field(), "pAssw0rd!");
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
        BOOST_REQUIRE_THROW(teststore->Create(v), dicomifier::DicomifierException);
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
        BOOST_REQUIRE_THROW(teststore->Create(v), dicomifier::DicomifierException);
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
        BOOST_REQUIRE_THROW(teststore->Create(v), dicomifier::DicomifierException);
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
        BOOST_REQUIRE_THROW(teststore->Create(v), dicomifier::DicomifierException);
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
