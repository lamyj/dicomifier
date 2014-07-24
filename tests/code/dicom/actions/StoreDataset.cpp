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

/*************************** TEST OK 01 *******************************/
/**
 * Store dataset success
 */
// TODO

/*************************** TEST KO 01 *******************************/
/**
 * Empty dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto teststore = dicomifier::actions::StoreDataset::New();
        
    BOOST_REQUIRE_THROW(teststore->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Missing SOPClassUID attribut
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
 * Bad Network address or port
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
 * Bad caller AE title
 */
// TODO

/*************************** TEST KO 05 *******************************/
/**
 * Bad called AE title
 */
// TODO
