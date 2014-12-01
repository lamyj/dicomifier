/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#define BOOST_TEST_MODULE ModuleEmptyElement
#include <boost/test/unit_test.hpp>

#include <dcmtk/dcmdata/dctk.h>

#include "dicom/actions/EmptyElement.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    auto emptyelt = dicomifier::actions::EmptyElement::New();
    BOOST_CHECK_EQUAL(emptyelt != NULL, true);
    
    emptyelt = dicomifier::actions::EmptyElement::New(NULL, {});
    BOOST_CHECK_EQUAL(emptyelt != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto emptyelt = dicomifier::actions::EmptyElement::New();
    
    DcmDataset * dataset = new DcmDataset();
    emptyelt->set_dataset(dataset);
    BOOST_CHECK_EQUAL(emptyelt->get_dataset() != NULL, true);
    
    emptyelt->set_tags({dicomifier::TagAndRange()});
    BOOST_CHECK_EQUAL(emptyelt->get_tags().size(), 1);
    
    emptyelt = dicomifier::actions::EmptyElement::New(dataset, 
                                                       {dicomifier::TagAndRange()});
    BOOST_CHECK_EQUAL(emptyelt->get_dataset() != NULL, true);
    BOOST_CHECK_EQUAL(emptyelt->get_tags().size(), 1);
    
    delete dataset;
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run
 */
struct TestDataOK03
{
    DcmDataset * dataset;
    std::vector<dicomifier::TagAndRange> vect;
 
    TestDataOK03()
    {
        dataset = new DcmDataset();
        
        // Test VR = AE
        dataset->putAndInsertOFStringArray(DCM_PerformedStationAETitle, 
                                           OFString("ABCD"), true);
        
        // Test VR = AS
        dataset->putAndInsertOFStringArray(DCM_PatientAge, 
                                           OFString("20Y"), true);
        
        // Test VR = AT => Not implemented
        
        // Test VR = CS
        dataset->putAndInsertOFStringArray(DCM_PatientSex, 
                                           OFString("M"), true);
        
        // Test VR = DA
        dataset->putAndInsertOFStringArray(DCM_StudyDate, 
                                           OFString("02052014"), true);
        
        // Test VR = DS
        dataset->putAndInsertOFStringArray(DCM_PatientWeight, "60.5", true);
        
        // Test VR = DT
        dataset->putAndInsertOFStringArray(DCM_AcquisitionDateTime, 
                                           OFString("02153202062013"), 
                                           true);
        
        // Test VR = FL
        dataset->putAndInsertFloat32(DCM_StimulusArea, (Float32)15.2);
        
        // Test VR = FD
        dataset->putAndInsertFloat64(DCM_PupilSize, 42.5);
        
        // Test VR = IS
        dataset->putAndInsertOFStringArray(DCM_StageNumber, "12", true);
        
        // Test VR = LO
        dataset->putAndInsertOFStringArray(DCM_Manufacturer, 
                                           OFString("Machine1"), true);
        
        // Test VR = LT
        dataset->putAndInsertOFStringArray(DCM_AdditionalPatientHistory, 
                                           OFString("abc"), true);
        
        // Test VR = OB => Not implemented
        // Test VR = OD => Not implemented
        // Test VR = OF => Not implemented
        // Test VR = OW => Not implemented
        
        // Test VR = PN
        dataset->putAndInsertOFStringArray(DCM_PatientName, 
                                           OFString("John"), true);
        
        // Test VR = SH
        dataset->putAndInsertOFStringArray(DCM_AccessionNumber, 
                                           OFString("1234"), true);
        
        // Test VR = SL
        dataset->putAndInsertSint32(DCM_ReferencePixelX0, 123);
        
        // Test VR = SQ
        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        item->putAndInsertOFStringArray(DCM_PatientID, "123");
        dataset->insertSequenceItem(DCM_OtherPatientIDsSequence, item);
        
        // Test VR = SS
        dataset->putAndInsertSint16(DCM_TagAngleSecondAxis, 123);
        
        // Test VR = ST
        dataset->putAndInsertOFStringArray(DCM_InstitutionAddress, 
                                           OFString("ABC"), true);
        
        // Test VR = TM
        dataset->putAndInsertOFStringArray(DCM_StudyTime, 
                                           OFString("012345"), true);
        
        // Test VR = UI
        dataset->putAndInsertOFStringArray(DCM_SOPClassUID, 
                                           OFString("12345678"), true);
        
        // Test VR = UL
        dataset->putAndInsertUint32(DCM_RegionFlags, 123);
        
        // Test VR = UN => Not implemented
        
        // Test VR = US
        dataset->putAndInsertUint16(DCM_FailureReason, 123);
        
        // Test VR = UT
        OFString name("myUnlimitedText");
        dataset->putAndInsertOFStringArray(DCM_PixelDataProviderURL, 
                                           name, true);
    }
 
    ~TestDataOK03()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    dicomifier::actions::EmptyElement::Pointer testempty = NULL;
    
    // Test VR = AE
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PerformedStationAETitle), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PerformedStationAETitle, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PerformedStationAETitle), 
                      true);
    
    // Test VR = AS
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientAge), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientAge, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientAge), 
                      true);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientSex), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientSex, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientSex), 
                      true);
    
    // Test VR = DA
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_StudyDate), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StudyDate, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_StudyDate), 
                      true);
    
    // Test VR = DS
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientWeight), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientWeight, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientWeight), 
                      true);
    
    // Test VR = DT
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_AcquisitionDateTime), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_AcquisitionDateTime, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_AcquisitionDateTime), 
                      true);
    
    // Test VR = FL
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_StimulusArea), true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StimulusArea, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_StimulusArea), 
                      true);
    
    // Test VR = FD
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PupilSize), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PupilSize, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PupilSize), 
                      true);
    
    // Test VR = IS
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_StageNumber), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StageNumber, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_StageNumber), 
                      true);
    
    // Test VR = LO
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Manufacturer), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_Manufacturer, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Manufacturer), 
                      true);
    
    // Test VR = LT
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_AdditionalPatientHistory), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_AdditionalPatientHistory, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_AdditionalPatientHistory), 
                      true);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientName), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientName), 
                      true);
    
    // Test VR = SH
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_AccessionNumber), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_AccessionNumber, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_AccessionNumber), 
                      true);
    
    // Test VR = SL
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_ReferencePixelX0), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_ReferencePixelX0, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_ReferencePixelX0), 
                      true);
    
    // Test VR = SQ
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_OtherPatientIDsSequence), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_OtherPatientIDsSequence), 
                      true);
    
    // Test VR = SS
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_TagAngleSecondAxis), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_TagAngleSecondAxis, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_TagAngleSecondAxis), 
                      true);
    
    // Test VR = ST
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_InstitutionAddress), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_InstitutionAddress, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_InstitutionAddress), 
                      true);
    
    // Test VR = TM
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_StudyTime), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StudyTime, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_StudyTime), 
                      true);
    
    // Test VR = UI
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_SOPClassUID), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_SOPClassUID, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_SOPClassUID), 
                      true);
    
    // Test VR = UL
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_RegionFlags), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_RegionFlags, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_RegionFlags), 
                      true);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_FailureReason), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_FailureReason, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_FailureReason), 
                      true);
    
    // Test VR = UT
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PixelDataProviderURL), 
                      true);
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PixelDataProviderURL, 
                   dicomifier::Range(0,1)));
    testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PixelDataProviderURL), 
                      true);
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Empty public attribut (not in sequence)
 */
struct TestDataOK04
{
    DcmDataset * dataset;
 
    TestDataOK04()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1\\value2\\value3\\value4");
        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        item->putAndInsertOFStringArray(DCM_PatientID, "123\\456\\789");
        dataset->insertSequenceItem(DCM_OtherPatientIDsSequence, item);
    }
 
    ~TestDataOK04()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
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

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Empty public attribut (in sequence)
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_05, TestDataOK04)
{
    // check DCM_Modality in dataset
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientID, OFTrue), true);
    
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, dicomifier::Range(0,1)));
    vect.push_back(dicomifier::TagAndRange(DCM_PatientID, dicomifier::Range(0,std::numeric_limits<int>::max())));
    
    auto testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    
    testempty->run();
        
    // check DCM_Modality delete
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientID, OFTrue), true);
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PatientID, str, true);
    BOOST_CHECK_EQUAL(cond.good(), true);
    
    BOOST_CHECK_EQUAL(str, "");
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Add public attribut
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_06, TestDataOK04)
{
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientName), 
                      false);
                      
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, 
                   dicomifier::Range(0,1)));
    auto testempty = dicomifier::actions::EmptyElement::New(dataset, vect);
    testempty->run();
    
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_PatientName), 
                      true);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Empty dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto testempty = dicomifier::actions::EmptyElement::New();
        
    BOOST_REQUIRE_THROW(testempty->run(), dicomifier::DicomifierException);
}
