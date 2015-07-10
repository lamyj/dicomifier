/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleSaveDataset
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/test/unit_test.hpp>

#include "core/DicomifierException.h"
#include "dicom/actions/SaveDataset.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    auto saveds = dicomifier::actions::SaveDataset::New();
    BOOST_REQUIRE(saveds != NULL);
    
    saveds = dicomifier::actions::SaveDataset::New(NULL, "");
    BOOST_REQUIRE(saveds != NULL);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(Accessors)
{
    auto saveds = dicomifier::actions::SaveDataset::New();
    
    saveds->set_includeMetaInfoHeader(true);
    BOOST_CHECK(saveds->get_includeMetaInfoHeader());
    
    DcmDataset dataset;
    saveds->set_dataset(&dataset);
    BOOST_CHECK(saveds->get_dataset() != NULL);
    
    saveds->set_filename("test");
    BOOST_CHECK_EQUAL(saveds->get_filename(), "test");
    
    saveds = dicomifier::actions::SaveDataset::New(&dataset, "test", true);
    BOOST_CHECK(saveds->get_dataset() != NULL);
    BOOST_CHECK_EQUAL(saveds->get_filename(), "test");
    BOOST_CHECK(saveds->get_includeMetaInfoHeader());
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Save dataset without Meta information
 */
struct TestDataOK03
{
    DcmDataset dataset;
    std::string filename;
 
    TestDataOK03() : filename("./test_SaveDataset_tempfile.dcm")
    {
        dataset.putAndInsertOFStringArray(DCM_Modality, "value1");
        dataset.putAndInsertOFStringArray(DCM_PatientWeight, "60.5");
    }
 
    ~TestDataOK03()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    BOOST_REQUIRE(!boost::filesystem::exists(filename));
    
    auto testsave = dicomifier::actions::SaveDataset::New();
    testsave->set_dataset(&dataset);
    testsave->set_filename(filename);
    testsave->run();
        
    BOOST_CHECK(boost::filesystem::exists(filename));
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Save dataset with Meta information
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK03)
{
    BOOST_REQUIRE(!boost::filesystem::exists(filename));
    
    auto testsave = dicomifier::actions::SaveDataset::New();
    testsave->set_dataset(&dataset);
    testsave->set_filename(filename);
    testsave->set_includeMetaInfoHeader(true);
    testsave->run();
        
    BOOST_CHECK(boost::filesystem::exists(filename));
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Empty dataset
 */
BOOST_AUTO_TEST_CASE(EmptyDataset)
{
    auto testsave = dicomifier::actions::SaveDataset::New();
        
    BOOST_REQUIRE_THROW(testsave->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Bad output file name
 */
struct TestDataKO02
{
    DcmDataset dataset;
 
    TestDataKO02()
    {
        dataset.putAndInsertOFStringArray(DCM_Modality, "value1");
    }
 
    ~TestDataKO02()
    {
        // Nothing to do
    }
};

BOOST_FIXTURE_TEST_CASE(EmptyOutputFile, TestDataKO02)
{
    auto testsave = dicomifier::actions::SaveDataset::New();
    testsave->set_dataset(&dataset);
    testsave->set_filename("");
        
    BOOST_REQUIRE_THROW(testsave->run(), dicomifier::DicomifierException);
}
