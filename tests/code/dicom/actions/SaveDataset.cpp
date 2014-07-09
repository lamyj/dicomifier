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

#include "dicom/actions/SaveDataset.h"

struct TestData
{
    DcmDataset * dataset;
    std::string filename;
 
    TestData()
    {
        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1");
        dataset->putAndInsertOFStringArray(DCM_PatientWeight, "60.5");
        
        filename = "./test_SaveDataset_tempfile.dcm";
    }
 
    ~TestData()
    {
        delete dataset;
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(Save, TestData)
{
    auto testsave = dicomifier::actions::SaveDataset::New();
    testsave->set_dataset(dataset);
    testsave->set_filename(filename);
    testsave->run();
    
    BOOST_CHECK_EQUAL(testsave->get_dataset() != NULL, true);
    BOOST_CHECK_EQUAL(testsave->get_filename() == filename, true);
        
    BOOST_CHECK_EQUAL(boost::filesystem::exists(filename), true);
}
