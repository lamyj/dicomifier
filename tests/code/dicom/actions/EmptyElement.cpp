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

BOOST_FIXTURE_TEST_CASE(EmptyExisting, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, dicomifier::Range(0,6)));
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, dicomifier::Range(0,1)));
    //vect.push_back(dicomifier::TagAndRange(DCM_PatientID, dicomifier::Range(0,2)));
    
    auto testempty = dicomifier::actions::EmptyElement::New();
    testempty->set_dataset(dataset);
    testempty->set_tags(vect);
    testempty->run();
    dataset->print(std::cout);
    
    
    /*auto testempty = dicomifier::actions::EmptyElement::New();
    testempty->set_dataset(dataset);
    //testempty->set_tag(DCM_Modality);
    testempty->run();
    
    BOOST_CHECK_EQUAL(testempty->get_dataset() != NULL, true);
    //BOOST_CHECK_EQUAL(testempty->get_tag() == DCM_Modality, true);
        
    DcmElement * element = NULL;
    OFCondition const element_ok = dataset->findAndGetElement(DCM_Modality, element);
    BOOST_CHECK_EQUAL(element_ok.good(), true);
    BOOST_CHECK_EQUAL(element != NULL, true);*/
    
    OFString str;
    //OFCondition cond = dataset->findAndGetOFStringArray(DCM_Modality, str);
    //BOOST_CHECK_EQUAL(cond.good(), true);
    
    BOOST_CHECK_EQUAL(str, "");
}

/*
BOOST_FIXTURE_TEST_CASE(EmptyNotExisting, TestData)
{
    auto testempty = dicomifier::actions::EmptyElement::New();
    testempty->set_dataset(dataset);
    //testempty->set_tag(DCM_PatientSex);
    testempty->run();
        
    DcmElement * element = NULL;
    OFCondition const element_ok = dataset->findAndGetElement(DCM_PatientSex, element);
    BOOST_CHECK_EQUAL(element_ok.good(), true);
    BOOST_CHECK_EQUAL(element != NULL, true);
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PatientSex, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    
    BOOST_CHECK_EQUAL(str, "");
}*/
