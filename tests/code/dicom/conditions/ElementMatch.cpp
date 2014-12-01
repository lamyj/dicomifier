/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleElementMatch
#include <boost/test/unit_test.hpp>

#include "dicom/conditions/ElementMatch.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    auto eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::New();
    BOOST_CHECK_EQUAL(eltmatch != NULL, true);
    
    eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::
                                        New(NULL, {}, OFString(""));
    BOOST_CHECK_EQUAL(eltmatch != NULL, true);
    
    dicomifier::conditions::ElementMatch<EVR_AE>::ArrayType vect;
    eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::
                                                New(NULL, {}, vect);
    BOOST_CHECK_EQUAL(eltmatch != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::New();
    
    DcmDataset * dataset = new DcmDataset();
    eltmatch->set_dataset(dataset);
    BOOST_CHECK_EQUAL(eltmatch->get_dataset() != NULL, true);
    
    eltmatch->set_tags({dicomifier::TagAndRange()});
    BOOST_CHECK_EQUAL(eltmatch->get_tags().size(), 1);
    
    eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::
                New(dataset, {dicomifier::TagAndRange()}, OFString(""));
    BOOST_CHECK_EQUAL(eltmatch->get_dataset() != NULL, true);
    BOOST_CHECK_EQUAL(eltmatch->get_tags().size(), 1);
    
    delete dataset;
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Eval
 */
struct TestDataOK03
{
    DcmDataset * dataset;
    std::vector<dicomifier::TagAndRange> vect;
 
    TestDataOK03()
    {
        dataset = new DcmDataset();
        
        // Test VR = AE
        dataset->putAndInsertOFStringArray(DCM_RetrieveAETitle, 
                                           "test_AE");
        
        // Test VR = AS
        dataset->putAndInsertOFStringArray(DCM_PatientAge, "test_AS");
        
        // Test VR = AT => Not implemented
        
        // Test VR = CS
        std::string test = "value1\\value2\\value3";
        dataset->putAndInsertOFStringArray(DCM_Modality, test.c_str());
        
        // Test VR = DA
        dataset->putAndInsertOFStringArray(DCM_PatientBirthDate, 
                                           "01/01/2001");
        
        // Test VR = DS
        dataset->putAndInsertOFStringArray(DCM_PatientWeight, "60.5");
        
        // Test VR = DT
        dataset->putAndInsertOFStringArray(DCM_FrameAcquisitionDateTime, 
                                           "01/01/2001 09:09:09");
        
        // Test VR = FL
        dataset->putAndInsertFloat32(DCM_RecommendedDisplayFrameRateInFloat, 
                                     15.2);
        
        // Test VR = FD
        dataset->putAndInsertFloat64(DCM_PupilSize, 42.5);
        
        // Test VR = IS
        dataset->putAndInsertOFStringArray(DCM_StageNumber, "12");
        
        // Test VR = LO
        dataset->putAndInsertOFStringArray(DCM_Manufacturer, 
                                           "MyManufacturer");
        
        // Test VR = LT
        dataset->putAndInsertOFStringArray(DCM_AdditionalPatientHistory, 
                                           "test_valueLT");
        
        // Test VR = OB => Not implemented
        // Test VR = OD => Not implemented
        // Test VR = OF => Not implemented
        // Test VR = OW => Not implemented
        
        // Test VR = PN
        dataset->putAndInsertOFStringArray(DCM_PatientName, "Doe^John");
        
        // Test VR = SH
        dataset->putAndInsertOFStringArray(DCM_EthnicGroup, 
                                           "test_valueSH");
        
        // Test VR = SL
        dataset->putAndInsertSint32(DCM_ReferencePixelX0, 10);
        
        // Test VR = SQ
        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        item->putAndInsertOFStringArray(DCM_PatientID, "123");
        dataset->insertSequenceItem(DCM_OtherPatientIDsSequence, item);
        
        // Test VR = SS
        dataset->putAndInsertSint16(DCM_TagAngleSecondAxis, 10);
        
        // Test VR = ST
        dataset->putAndInsertOFStringArray(DCM_InstitutionAddress, 
                                           "MyAdress");
        
        // Test VR = TM
        dataset->putAndInsertOFStringArray(DCM_InstanceCreationTime, 
                                           "08:08:08");
        
        // Test VR = UI
        dataset->putAndInsertOFStringArray(DCM_SOPClassUID, "1.2.3.4.5");
        
        // Test VR = UL
        dataset->putAndInsertUint32(DCM_SimpleFrameList, 11);
        
        // Test VR = UN => Not implemented
        
        // Test VR = US
        dataset->putAndInsertUint16(DCM_FailureReason, 5);
        
        // Test VR = UT
        dataset->putAndInsertOFStringArray(DCM_PixelDataProviderURL, 
                                           "test_valueUT");
    }
 
    ~TestDataOK03()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    // Test VR = AE
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_RetrieveAETitle, 
                                           dicomifier::Range(0,1)));
    auto testmatchAE = dicomifier::conditions::ElementMatch<EVR_AE>::
                        New(dataset, vect, "test_AE");
    BOOST_CHECK_EQUAL(testmatchAE->eval(), true);
    
    // Test VR = AS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientAge, 
                                           dicomifier::Range(0,1)));
    auto testmatchAS = dicomifier::conditions::ElementMatch<EVR_AS>::
                        New(dataset, vect, "test_AS");
    BOOST_CHECK_EQUAL(testmatchAS->eval(), true);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_Modality, 
                                           dicomifier::Range(0,1)));
    auto testmatchCS = dicomifier::conditions::ElementMatch<EVR_CS>::
                        New(dataset, vect, {"value1", "value2", "value3"});
    BOOST_CHECK_EQUAL(testmatchCS->eval(), true);
    
    // Test VR = DA
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientBirthDate, 
                                           dicomifier::Range(0,1)));
    auto testmatchDA = dicomifier::conditions::ElementMatch<EVR_DA>::
                        New(dataset, vect, "01/01/2001");
    BOOST_CHECK_EQUAL(testmatchDA->eval(), true);
    
    // Test VR = DS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientWeight, 
                                           dicomifier::Range(0,1)));
    auto testmatchDS = dicomifier::conditions::ElementMatch<EVR_DS>::
                        New(dataset, vect, 60.5);
    BOOST_CHECK_EQUAL(testmatchDS->eval(), true);
    
    // Test VR = DT
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_FrameAcquisitionDateTime, 
                                           dicomifier::Range(0,1)));
    auto testmatchDT = dicomifier::conditions::ElementMatch<EVR_DT>::
                        New(dataset, vect, "01/01/2001 09:09:09");
    BOOST_CHECK_EQUAL(testmatchDT->eval(), true);
    
    // Test VR = FL
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_RecommendedDisplayFrameRateInFloat, 
                                           dicomifier::Range(0,1)));
    auto testmatchFL = dicomifier::conditions::ElementMatch<EVR_FL>::
                        New(dataset, vect, 15.2);
    BOOST_CHECK_EQUAL(testmatchFL->eval(), true);
    
    // Test VR = FD
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PupilSize, 
                                           dicomifier::Range(0,1)));
    auto testmatchFD = dicomifier::conditions::ElementMatch<EVR_FD>::
                        New(dataset, vect, 42.5);
    BOOST_CHECK_EQUAL(testmatchFD->eval(), true);
    
    // Test VR = IS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StageNumber, 
                                           dicomifier::Range(0,1)));
    auto testmatchIS = dicomifier::conditions::ElementMatch<EVR_IS>::
                        New(dataset, vect, 12);
    BOOST_CHECK_EQUAL(testmatchIS->eval(), true);
    
    // Test VR = LO
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_Manufacturer, 
                                           dicomifier::Range(0,1)));
    auto testmatchLO = dicomifier::conditions::ElementMatch<EVR_LO>::
                        New(dataset, vect, "MyManufacturer");
    BOOST_CHECK_EQUAL(testmatchLO->eval(), true);
    
    // Test VR = LT
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_AdditionalPatientHistory, 
                                           dicomifier::Range(0,1)));
    auto testmatchLT = dicomifier::conditions::ElementMatch<EVR_LT>::
                        New(dataset, vect, "test_valueLT");
    BOOST_CHECK_EQUAL(testmatchLT->eval(), true);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, 
                                           dicomifier::Range(0,1)));
    auto testmatchPN = dicomifier::conditions::ElementMatch<EVR_PN>::
                        New(dataset, vect, "Doe^John");
    BOOST_CHECK_EQUAL(testmatchPN->eval(), true);
    
    // Test VR = SH
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_EthnicGroup, 
                                           dicomifier::Range(0,1)));
    auto testmatchSH = dicomifier::conditions::ElementMatch<EVR_SH>::
                        New(dataset, vect, "test_valueSH");
    BOOST_CHECK_EQUAL(testmatchSH->eval(), true);
    
    // Test VR = SL
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_ReferencePixelX0, 
                                           dicomifier::Range(0,1)));
    auto testmatchSL = dicomifier::conditions::ElementMatch<EVR_SL>::
                        New(dataset, vect, 10);
    BOOST_CHECK_EQUAL(testmatchSL->eval(), true);
    
    // Test VR = SQ (Test SubTag in sequence, not Sequence Tag)
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, 
                                           dicomifier::Range(0,1)));
    vect.push_back(dicomifier::TagAndRange(DCM_PatientID, 
                                           dicomifier::Range(0,1)));
    auto testmatchSQ = dicomifier::conditions::ElementMatch<EVR_LO>::
                        New(dataset, vect, "123");
    BOOST_CHECK_EQUAL(testmatchSQ->eval(), true);
    
    // Test VR = SS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_TagAngleSecondAxis, 
                                           dicomifier::Range(0,1)));
    auto testmatchSS = dicomifier::conditions::ElementMatch<EVR_SS>::
                        New(dataset, vect, 10);
    BOOST_CHECK_EQUAL(testmatchSS->eval(), true);
    
    // Test VR = ST
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_InstitutionAddress, 
                                           dicomifier::Range(0,1)));
    auto testmatchST = dicomifier::conditions::ElementMatch<EVR_ST>::
                        New(dataset, vect, "MyAdress");
    BOOST_CHECK_EQUAL(testmatchST->eval(), true);
    
    // Test VR = TM
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_InstanceCreationTime, 
                                           dicomifier::Range(0,1)));
    auto testmatchTM = dicomifier::conditions::ElementMatch<EVR_TM>::
                        New(dataset, vect, "08:08:08");
    BOOST_CHECK_EQUAL(testmatchTM->eval(), true);
    
    // Test VR = UI
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_SOPClassUID, 
                                           dicomifier::Range(0,1)));
    auto testmatchUI = dicomifier::conditions::ElementMatch<EVR_UI>::
                        New(dataset, vect, "1.2.3.4.5");
    BOOST_CHECK_EQUAL(testmatchUI->eval(), true);
    
    // Test VR = UL
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_SimpleFrameList, 
                                           dicomifier::Range(0,1)));
    auto testmatchUL = dicomifier::conditions::ElementMatch<EVR_UL>::
                        New(dataset, vect, 11);
    BOOST_CHECK_EQUAL(testmatchUL->eval(), true);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_FailureReason, 
                                           dicomifier::Range(0,1)));
    auto testmatchUS = dicomifier::conditions::ElementMatch<EVR_US>::
                        New(dataset, vect, 5);
    BOOST_CHECK_EQUAL(testmatchUS->eval(), true);
    
    // Test VR = UT
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PixelDataProviderURL, 
                                           dicomifier::Range(0,1)));
    auto testmatchUT = dicomifier::conditions::ElementMatch<EVR_UT>::
                        New(dataset, vect, "test_valueUT");
    BOOST_CHECK_EQUAL(testmatchUT->eval(), true);
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Eval return false (bad value)
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK03)
{
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_Modality, 
                                           dicomifier::Range(0,1)));
    auto testmatch = dicomifier::conditions::ElementMatch<EVR_CS>::
                        New(dataset, vect, {"value1", "badValue", "value3"});
    BOOST_CHECK_EQUAL(testmatch->eval(), false);
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Eval return false (tag not find)
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_05, TestDataOK03)
{
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientSex, 
                                           dicomifier::Range(0,1)));
    auto testmatch = dicomifier::conditions::ElementMatch<EVR_CS>::
                        New(dataset, vect, {"value1", "value2", "value3"});
    BOOST_CHECK_EQUAL(testmatch->eval(), false);
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Eval Match with regex
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_06, TestDataOK03)
{
    // Test 1
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, 
                                           dicomifier::Range(0,1)));
    
    auto testmatch = dicomifier::conditions::ElementMatch<EVR_PN>::
                        New(dataset, vect, "Doe^*");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
    
    // Test 2
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, 
                                           dicomifier::Range(0,1)));
    testmatch = dicomifier::conditions::ElementMatch<EVR_PN>::
                        New(dataset, vect, "Doe^Jo?n");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Empty dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_Modality, dicomifier::Range(0,1)));
    
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_CS>::New(NULL, 
                                                      vect, 
                                                      "value1");
    BOOST_CHECK_EQUAL(testmatch->eval(), false);
}
