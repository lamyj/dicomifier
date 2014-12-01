/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleStoreDataset
#include <boost/test/unit_test.hpp>

#include "core/DicomifierException.h"
#include "dicom/actions/StoreDataset.h"

#include "../DcmQrSCP.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    auto storeds = dicomifier::actions::StoreDataset::New();
    BOOST_CHECK_EQUAL(storeds != NULL, true);
    
    storeds = dicomifier::actions::StoreDataset::New(NULL, "", 0, "", "");
    BOOST_CHECK_EQUAL(storeds != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    DcmDataset * dataset = new DcmDataset();
    auto storeds = dicomifier::actions::StoreDataset::New();
    
    storeds->set_dataset(dataset);
    BOOST_CHECK_EQUAL(storeds->get_dataset() != NULL, true);
    
    storeds->set_address("MyAdress");
    BOOST_CHECK_EQUAL(storeds->get_address(), "MyAdress");
    
    storeds->set_port(11112);
    BOOST_CHECK_EQUAL(storeds->get_port(), 11112);
    
    storeds->set_AEremote("REMOTE");
    BOOST_CHECK_EQUAL(storeds->get_AEremote(), "REMOTE");
    
    storeds->set_AElocal("LOCAL");
    BOOST_CHECK_EQUAL(storeds->get_AElocal(), "LOCAL");
    
    storeds->set_user_identity_type(dicomifier::UserIdentityType::UsernameAndPassword);
    BOOST_CHECK_EQUAL(storeds->get_user_identity_type() == dicomifier::UserIdentityType::UsernameAndPassword, true);
    
    storeds->set_user_identity_primary_field("user");
    BOOST_CHECK_EQUAL(storeds->get_user_identity_primary_field(), "user");
    
    storeds->set_user_identity_secondary_field("password");
    BOOST_CHECK_EQUAL(storeds->get_user_identity_secondary_field(), "password");
    
    storeds = dicomifier::actions::StoreDataset::New(dataset, 
                                                     "MyAdress",
                                                     11112,
                                                     "REMOTE",
                                                     "LOCAL");
    BOOST_CHECK_EQUAL(storeds->get_dataset() != NULL, true);
    BOOST_CHECK_EQUAL(storeds->get_address(), "MyAdress");
    BOOST_CHECK_EQUAL(storeds->get_port(), 11112);
    BOOST_CHECK_EQUAL(storeds->get_AEremote(), "REMOTE");
    BOOST_CHECK_EQUAL(storeds->get_AElocal(), "LOCAL");
    
    delete dataset;
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Store dataset success
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_03, DcmQrSCP)
{
    DcmDataset * dataset = NULL;
    {
        std::stringstream filename;
        filename << data_directory << "/" << "image.dcm";
        
        DcmFileFormat file;
        OFCondition const condition = file.loadFile(filename.str().c_str());
        if(!condition.good())
        {
            BOOST_FAIL("Could not read " + filename.str());
        }
        dataset = file.getAndRemoveDataset();
        
        
        // generate unique SOP INSTANCE UID
        char uid_sop_instance[128];
        dcmGenerateUniqueIdentifier(uid_sop_instance, SITE_INSTANCE_UID_ROOT);
        
        dataset->putAndInsertOFStringArray(DCM_SOPInstanceUID, OFString(uid_sop_instance));
    }
    
    auto teststore = dicomifier::actions::StoreDataset::New();
    teststore->set_dataset(dataset);
    teststore->set_address(peer_host);
    teststore->set_port(peer_port);
    teststore->set_AElocal(calling_aet);
    teststore->set_AEremote(peer_aet);
    
    teststore->set_user_identity_type(dicomifier::UserIdentityType::UsernameAndPassword);
    teststore->set_user_identity_primary_field("user");
    teststore->set_user_identity_secondary_field("password");
    
    teststore->run();
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Empty dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto teststore = dicomifier::actions::StoreDataset::New();
        
    BOOST_REQUIRE_THROW(teststore->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Missing SOPClassUID attribut
 */
struct TestDataKO02
{
    DcmDataset * dataset;
 
    TestDataKO02()
    {
        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1");
    }
 
    ~TestDataKO02()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataKO02)
{
    auto teststore = dicomifier::actions::StoreDataset::New();
    teststore->set_dataset(dataset);
    
    BOOST_REQUIRE_THROW(teststore->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Bad Network address or port
 */
struct TestDataKO03
{
    DcmDataset * dataset;
 
    TestDataKO03()
    {
        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SOPClassUID, "1.2.840.10008.5.1.4.1.1.4"); // MRImageStorage
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1");
    }
 
    ~TestDataKO03()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataKO03)
{
    auto teststore = dicomifier::actions::StoreDataset::New();
    teststore->set_dataset(dataset);
    teststore->set_address("unknown");
    teststore->set_port(11112);

    BOOST_REQUIRE_THROW(teststore->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 04 *******************************/
/**
 * Error test case: Bad caller AE title
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_04, DcmQrSCP)
{
    DcmDataset * dataset = NULL;
    {
        std::stringstream filename;
        filename << data_directory << "/" << "image.dcm";
        
        DcmFileFormat file;
        OFCondition const condition = file.loadFile(filename.str().c_str());
        if(!condition.good())
        {
            BOOST_FAIL("Could not read " + filename.str());
        }
        dataset = file.getAndRemoveDataset();
        
        
        // generate unique SOP INSTANCE UID
        char uid_sop_instance[128];
        dcmGenerateUniqueIdentifier(uid_sop_instance, SITE_INSTANCE_UID_ROOT);
        
        dataset->putAndInsertOFStringArray(DCM_SOPInstanceUID, OFString(uid_sop_instance));
    }
    
    auto teststore = dicomifier::actions::StoreDataset::New();
    teststore->set_dataset(dataset);
    teststore->set_address(peer_host);
    teststore->set_port(peer_port);
    teststore->set_AElocal("BADVALUE");
    teststore->set_AEremote(peer_aet);
    
    teststore->set_user_identity_type(dicomifier::UserIdentityType::UsernameAndPassword);
    teststore->set_user_identity_primary_field("user");
    teststore->set_user_identity_secondary_field("password");
    
    BOOST_REQUIRE_THROW(teststore->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 05 *******************************/
/**
 * Error test case: Bad called AE title
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_05, DcmQrSCP)
{
    DcmDataset * dataset = NULL;
    {
        std::stringstream filename;
        filename << data_directory << "/" << "image.dcm";
        
        DcmFileFormat file;
        OFCondition const condition = file.loadFile(filename.str().c_str());
        if(!condition.good())
        {
            BOOST_FAIL("Could not read " + filename.str());
        }
        dataset = file.getAndRemoveDataset();
        
        
        // generate unique SOP INSTANCE UID
        char uid_sop_instance[128];
        dcmGenerateUniqueIdentifier(uid_sop_instance, SITE_INSTANCE_UID_ROOT);
        
        dataset->putAndInsertOFStringArray(DCM_SOPInstanceUID, OFString(uid_sop_instance));
    }
    
    auto teststore = dicomifier::actions::StoreDataset::New();
    teststore->set_dataset(dataset);
    teststore->set_address(peer_host);
    teststore->set_port(peer_port);
    teststore->set_AElocal(calling_aet);
    teststore->set_AEremote("BADVALUE");
    
    teststore->set_user_identity_type(dicomifier::UserIdentityType::UsernameAndPassword);
    teststore->set_user_identity_primary_field("user");
    teststore->set_user_identity_secondary_field("password");
    
    BOOST_REQUIRE_THROW(teststore->run(), dicomifier::DicomifierException);
}
