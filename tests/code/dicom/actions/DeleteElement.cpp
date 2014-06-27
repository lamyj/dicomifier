/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDeleteElement
#include <boost/test/unit_test.hpp>

#include <memory>

#include <dcmtk/dcmdata/dctk.h>

#include "core/Factory.h"
#include "dicom/actions/DeleteElement.h"

struct TestData
{
    DcmDataset * dataset;
 
    TestData()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1");
        dataset->putAndInsertOFStringArray(DCM_PatientWeight, "60.5");
    }
 
    ~TestData()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(DeleteExisting, TestData)
{
    // check DCM_Modality in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Modality), true);
    
    auto testaction = dicomifier::Factory::get_instance().create("DeleteElement");
    auto testdelete = std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(testaction);
    testdelete->set_dataset(dataset);
    testdelete->set_tag(DCM_Modality);
    testdelete->run();
        
    // check DCM_Modality delete
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Modality), false);
    
    // check Other tag already exist
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientWeight), true);
}

BOOST_FIXTURE_TEST_CASE(DeleteNotExisting, TestData)
{
    // check DCM_PatientSex not in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientSex), false);
    
    auto testaction = dicomifier::Factory::get_instance().create("DeleteElement");
    auto testdelete = std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(testaction);
    testdelete->set_dataset(dataset);
    testdelete->set_tag(DCM_PatientSex);
    testdelete->run();
        
    // check DCM_PatientSex not in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientSex), false);
}
