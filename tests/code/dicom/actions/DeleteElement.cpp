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

#include "dicom/actions/DeleteElement.h"

struct TestData
{
    DcmDataset * dataset;
 
    TestData()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1\\value2\\value3\\value4");
        dataset->putAndInsertOFStringArray(DCM_PatientWeight, "60.5");
        
        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        DcmItem* item2 = new DcmItem(DCM_OtherPatientIDsSequence);
        item2->putAndInsertOFStringArray(DCM_PatientID, "123\\456\\789");
        item2->putAndInsertOFStringArray(DCM_Modality, "123\\456\\789");
        
        item->insertSequenceItem(DCM_OtherPatientIDsSequence, item2);
        item->putAndInsertOFStringArray(DCM_Modality, "123\\456\\789");
        
        dataset->insertSequenceItem(DCM_OtherPatientIDsSequence, item);
        
        dataset->insertSequenceItem(DCM_OtherPatientIDsSequence, new DcmItem(DCM_PatientWeight));
        
        dataset->print(std::cout);
    }
 
    ~TestData()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(DeleteExisting, TestData)
{
    // check DCM_Modality in dataset
    //BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Modality), true);
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, dicomifier::Range(0,6)));
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, dicomifier::Range(0,1)));
    //vect.push_back(dicomifier::TagAndRange(DCM_PatientID, dicomifier::Range(0,2)));
    
    auto testdelete = dicomifier::actions::DeleteElement::New();
    testdelete->set_dataset(dataset);
    testdelete->set_tags(vect);
    testdelete->run();
    dataset->print(std::cout);
    //BOOST_CHECK_EQUAL(testdelete->get_dataset() != NULL, true);
    //BOOST_CHECK_EQUAL(testdelete->get_tag() == DCM_Modality, true);
        
    // check DCM_Modality delete
    //BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Modality), false);
    
    // check Other tag already exist
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientWeight), true);
}

/*BOOST_FIXTURE_TEST_CASE(DeleteNotExisting, TestData)
{
    // check DCM_PatientSex not in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientSex), false);
    
    auto testdelete = dicomifier::actions::DeleteElement::New();
    testdelete->set_dataset(dataset);
    //testdelete->set_tag(DCM_PatientSex);
    testdelete->run();
        
    // check DCM_PatientSex not in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientSex), false);
}*/
