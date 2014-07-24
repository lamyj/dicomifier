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
 * Save dataset success
 */
struct TestDataOK01
{
    DcmDataset * dataset;
    std::string filename;
 
    TestDataOK01()
    {
        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1");
        dataset->putAndInsertOFStringArray(DCM_PatientWeight, "60.5");
        
        filename = "./test_SaveDataset_tempfile.dcm";
    }
 
    ~TestDataOK01()
    {
        delete dataset;
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto testsave = dicomifier::actions::SaveDataset::New();
    testsave->set_dataset(dataset);
    testsave->set_filename(filename);
    testsave->run();
    
    BOOST_CHECK_EQUAL(testsave->get_dataset() != NULL, true);
    BOOST_CHECK_EQUAL(testsave->get_filename() == filename, true);
        
    BOOST_CHECK_EQUAL(boost::filesystem::exists(filename), true);
}

/*************************** TEST KO 01 *******************************/
/**
 * Empty dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto testsave = dicomifier::actions::SaveDataset::New();
        
    BOOST_REQUIRE_THROW(testsave->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Bad output file name
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
    auto testsave = dicomifier::actions::SaveDataset::New();
    testsave->set_dataset(dataset);
    testsave->set_filename("");
        
    BOOST_REQUIRE_THROW(testsave->run(), dicomifier::DicomifierException);
}
