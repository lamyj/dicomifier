/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#define BOOST_TEST_MODULE ModuleDeleteElement
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "dicom/actions/DeleteElement.h"
#include "dicom/ElementTraits.h"

/*************************** TEST OK 01 *******************************/
/**
 * Delete public attribut (not in sequence)
 */
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
    // check DCM_Modality in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Modality), true);
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_Modality, dicomifier::Range(0,std::numeric_limits<int>::max())));
    
    auto testdelete = dicomifier::actions::DeleteElement::New(dataset, vect);
    
    testdelete->run();
        
    // check DCM_Modality delete
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Modality), false);
    
    // check Other tag already exist
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_OtherPatientIDsSequence), true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Delete specific value in public attribut (not in sequence)
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK01)
{
    // check DCM_Modality in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Modality), true);
    
    DcmElement* dcmelement = NULL;
    dataset->findAndGetElement(DCM_Modality, dcmelement);
    BOOST_CHECK_EQUAL(dcmelement->getVM(), 4);
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_Modality, dicomifier::Range(1,3)));
    
    auto testdelete = dicomifier::actions::DeleteElement::New(dataset, vect);
    
    testdelete->run();
        
    // check DCM_Modality still present
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Modality), true);
    
    dcmelement = NULL;
    dataset->findAndGetElement(DCM_Modality, dcmelement);
    BOOST_CHECK_EQUAL(dcmelement->getVM(), 2);
    auto const array = dicomifier::ElementTraits<EVR_CS>::array_getter(dcmelement);
    BOOST_CHECK_EQUAL(array[0], OFString("value1"));
    BOOST_CHECK_EQUAL(array[1], OFString("value4"));
}

/*************************** TEST OK 03 *******************************/
/**
 * Delete public attribut (in sequence)
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK01)
{
    // check DCM_Modality in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientID, OFTrue), true);
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, dicomifier::Range(0,1)));
    vect.push_back(dicomifier::TagAndRange(DCM_PatientID, dicomifier::Range(0,std::numeric_limits<int>::max())));
    
    auto testdelete = dicomifier::actions::DeleteElement::New(dataset, vect);
    
    testdelete->run();
        
    // check DCM_Modality delete
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientID, OFTrue), false);
    
    // check Other tag already exist
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_OtherPatientIDsSequence), true);
}

/*************************** TEST OK 04 *******************************/
/**
 * Delete specific value in public attribut (in sequence)
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK01)
{
    // check DCM_Modality in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientID, OFTrue), true);
    
    DcmElement* dcmelement = NULL;
    dataset->findAndGetElement(DCM_Modality, dcmelement);
    BOOST_CHECK_EQUAL(dcmelement->getVM(), 4);
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, 
                                            dicomifier::Range(0,1)));
    vect.push_back(dicomifier::TagAndRange(DCM_PatientID, dicomifier::Range(0,2)));
    
    auto testdelete = dicomifier::actions::DeleteElement::New(dataset, vect);
    
    testdelete->run();
        
    // check DCM_Modality still present
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientID, OFTrue), true);
    
    dcmelement = NULL;
    dataset->findAndGetElement(DCM_PatientID, dcmelement, OFTrue);
    BOOST_CHECK_EQUAL(dcmelement->getVM(), 1);
    auto const array = dicomifier::ElementTraits<EVR_LO>::array_getter(dcmelement);
    BOOST_CHECK_EQUAL(array[0], OFString("789"));
}

/*************************** TEST OK 05 *******************************/
/**
 * Delete public attribut (sequence attribut)
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_05, TestDataOK01)
{
    // check DCM_Modality in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_OtherPatientIDsSequence, OFTrue), true);
    
    DcmElement* dcmelement = NULL;
    dataset->findAndGetElement(DCM_Modality, dcmelement);
    BOOST_CHECK_EQUAL(dcmelement->getVM(), 4);
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, 
                                            dicomifier::Range(0,1)));
    
    auto testdelete = dicomifier::actions::DeleteElement::New(dataset, vect);
    
    testdelete->run();
        
    // check DCM_Modality still present
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_OtherPatientIDsSequence, OFTrue), false);
}

/*************************** TEST OK 06 *******************************/
/**
 * Delete attribut not present in dataset
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_06, TestDataOK01)
{
    // check DCM_PatientSex not in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientSex), false);
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PatientSex, 
                                    dicomifier::Range(0,std::numeric_limits<int>::max())));
    
    auto testdelete = dicomifier::actions::DeleteElement::New(dataset, vect);
    testdelete->run();
        
    // check DCM_PatientSex not in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientSex), false);
}

/*************************** TEST KO 01 *******************************/
/**
 * Empty dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto testdelete = dicomifier::actions::DeleteElement::New();
        
    BOOST_REQUIRE_THROW(testdelete->run(), dicomifier::DicomifierException);
}
