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
#include "dicom/actions/PrintDataset.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    dicomifier::actions::PrintDataset::Pointer printds = 
        dicomifier::actions::PrintDataset::New();
    BOOST_CHECK_EQUAL(printds != NULL, true);
    
    printds = dicomifier::actions::PrintDataset::New(NULL, "");
    BOOST_CHECK_EQUAL(printds != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    dicomifier::actions::PrintDataset::Pointer printds = 
        dicomifier::actions::PrintDataset::New();
    
    DcmDataset * dataset = new DcmDataset();
    printds->set_dataset(dataset);
    BOOST_CHECK_EQUAL(printds->get_dataset() != NULL, true);
    delete dataset;
    
    printds->set_outputfile("test");
    BOOST_CHECK_EQUAL(printds->get_outputfile(), "test");
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Print in file (Run function)
 */
struct TestDataOK03
{
    DcmDataset * dataset;
    std::string filename;
 
    TestDataOK03()
    {
        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1");
        dataset->putAndInsertOFStringArray(DCM_PatientWeight, "60.5");
        
        filename = "./test_PrintDataset_tempfile.dcm";
    }
 
    ~TestDataOK03()
    {
        delete dataset;
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    auto testprint = dicomifier::actions::PrintDataset::New();
    testprint->set_dataset(dataset);
    testprint->set_outputfile(filename);
    testprint->run();
    
    BOOST_CHECK_EQUAL(boost::filesystem::exists(filename), true);
}

/*************************** TEST KO 01 *******************************/
/**
 * Nominal test case: Empty dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    dicomifier::actions::PrintDataset::Pointer printds = 
        dicomifier::actions::PrintDataset::New();
    BOOST_REQUIRE_THROW(printds->run(), dicomifier::DicomifierException);
}
