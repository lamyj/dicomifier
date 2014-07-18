/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleEmptyElement
#include <boost/test/unit_test.hpp>

#include <memory>

#include <dcmtk/dcmdata/dctk.h>

#include "dicom/actions/EmptyElement.h"

struct TestDataOK01
{
    DcmDataset * dataset;
 
    TestDataOK01()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1\\value2\\value3\\value4");
        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        item->putAndInsertOFStringArray(DCM_PatientID, "123\\456\\789");
        dataset->insertSequenceItem(DCM_OtherPatientIDsSequence, item);
    }
 
    ~TestDataOK01()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_Modality, dicomifier::Range(0,1)));
    
    auto testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
        
    DcmElement * element = NULL;
    OFCondition const element_ok = dataset->findAndGetElement(DCM_Modality, element);
    BOOST_CHECK_EQUAL(element_ok.good(), true);
    BOOST_CHECK_EQUAL(element != NULL, true);
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_Modality, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    
    BOOST_CHECK_EQUAL(str, "");
}

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK01)
{
    // check DCM_Modality in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientID, OFTrue), true);
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, dicomifier::Range(0,1)));
    vect.push_back(dicomifier::TagAndRange(DCM_PatientID, dicomifier::Range(0,std::numeric_limits<int>::max())));
    
    auto testdelete = dicomifier::actions::EmptyElement::New(dataset, vect);
    
    testdelete->run();
        
    // check DCM_Modality delete
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientID, OFTrue), true);
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PatientID, str, true);
    BOOST_CHECK_EQUAL(cond.good(), true);
    
    BOOST_CHECK_EQUAL(str, "");
}


BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK01)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PatientSex, dicomifier::Range(0,1)));
    
    auto testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
        
    DcmElement * element = NULL;
    OFCondition const element_ok = dataset->findAndGetElement(DCM_PatientSex, element);
    BOOST_CHECK_EQUAL(element_ok.good(), true);
    BOOST_CHECK_EQUAL(element != NULL, true);
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PatientSex, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    
    BOOST_CHECK_EQUAL(str, "");
}
