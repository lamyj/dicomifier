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
BOOST_AUTO_TEST_CASE(Constructor)
{
    auto eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::New();
    BOOST_REQUIRE(eltmatch != NULL);
    
    eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::
                                        New(NULL, {}, OFString(""));
    BOOST_REQUIRE(eltmatch != NULL);
    
    dicomifier::conditions::ElementMatch<EVR_AE>::ArrayType vect;
    eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::
                                                New(NULL, {}, vect);
    BOOST_REQUIRE(eltmatch != NULL);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(Accessors)
{
    auto eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::New();
    
    DcmDataset dataset;
    eltmatch->set_dataset(&dataset);
    BOOST_REQUIRE(eltmatch->get_dataset() != NULL);
    
    eltmatch->set_tags({dicomifier::TagAndRange()});
    BOOST_CHECK_EQUAL(eltmatch->get_tags().size(), 1);
    
    eltmatch = dicomifier::conditions::ElementMatch<EVR_AE>::
                New(&dataset, {dicomifier::TagAndRange()}, OFString(""));
    BOOST_CHECK(eltmatch->get_dataset() != NULL);
    BOOST_CHECK_EQUAL(eltmatch->get_tags().size(), 1);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Eval
 */
struct TestDataOK03
{
    DcmDataset dataset;
    std::vector<dicomifier::TagAndRange> vect;
 
    TestDataOK03()
    {
        // Test VR = AE
        OFCondition condition =
                dataset.putAndInsertOFStringArray(DCM_RetrieveAETitle,
                                                  "test_AE");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = AS
        condition = dataset.putAndInsertOFStringArray(DCM_PatientAge,
                                                      "test_AS");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = AT => Not implemented
        
        // Test VR = CS
        std::string test = "value1\\value2\\value3";
        condition = dataset.putAndInsertOFStringArray(DCM_Modality,
                                                      test.c_str());
        BOOST_REQUIRE(condition.good());
        
        // Test VR = DA
        condition = dataset.putAndInsertOFStringArray(DCM_PatientBirthDate,
                                                      "01/01/2001");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = DS
        condition = dataset.putAndInsertOFStringArray(DCM_PatientWeight,
                                                      "60.5");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = DT
        condition =
                dataset.putAndInsertOFStringArray(DCM_FrameAcquisitionDateTime,
                                                  "01/01/2001 09:09:09");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = FL
        condition = dataset.putAndInsertFloat32(
                        DCM_RecommendedDisplayFrameRateInFloat, 15.2);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = FD
        condition = dataset.putAndInsertFloat64(DCM_PupilSize, 42.5);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = IS
        condition = dataset.putAndInsertOFStringArray(DCM_StageNumber, "12");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = LO
        condition = dataset.putAndInsertOFStringArray(DCM_Manufacturer,
                                           "MyManufacturer");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = LT
        condition =
                dataset.putAndInsertOFStringArray(DCM_AdditionalPatientHistory,
                                                  "test_valueLT");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = OB => Not implemented
        // Test VR = OD => Not implemented
        // Test VR = OF => Not implemented
        // Test VR = OW => Not implemented
        
        // Test VR = PN
        condition = dataset.putAndInsertOFStringArray(DCM_PatientName,
                                                      "Doe^John");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = SH
        condition = dataset.putAndInsertOFStringArray(DCM_EthnicGroup,
                                                      "test_valueSH");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = SL
        condition = dataset.putAndInsertSint32(DCM_ReferencePixelX0, 10);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = SQ
        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        item->putAndInsertOFStringArray(DCM_PatientID, "123");
        condition = dataset.insertSequenceItem(DCM_OtherPatientIDsSequence,
                                               item);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = SS
        condition = dataset.putAndInsertSint16(DCM_TagAngleSecondAxis, 10);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = ST
        condition = dataset.putAndInsertOFStringArray(DCM_InstitutionAddress,
                                                      "MyAdress");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = TM
        condition = dataset.putAndInsertOFStringArray(DCM_InstanceCreationTime,
                                                      "08:08:08");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = UI
        condition = dataset.putAndInsertOFStringArray(DCM_SOPClassUID,
                                                      "1.2.3.4.5");
        BOOST_REQUIRE(condition.good());
        
        // Test VR = UL
        condition = dataset.putAndInsertUint32(DCM_SimpleFrameList, 11);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = UN => Not implemented
        
        // Test VR = US
        condition = dataset.putAndInsertUint16(DCM_FailureReason, 5);
        BOOST_REQUIRE(condition.good());
        
        // Test VR = UT
        condition = dataset.putAndInsertOFStringArray(DCM_PixelDataProviderURL,
                                                      "test_valueUT");
        BOOST_REQUIRE(condition.good());
    }
 
    ~TestDataOK03()
    {
        // Nothing to do
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    // Test VR = AE
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_RetrieveAETitle, 
                                           dicomifier::Range(0,1)));
    auto testmatchAE = dicomifier::conditions::ElementMatch<EVR_AE>::
                        New(&dataset, vect, "test_AE");
    BOOST_CHECK(testmatchAE->eval());
    
    // Test VR = AS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientAge, 
                                           dicomifier::Range(0,1)));
    auto testmatchAS = dicomifier::conditions::ElementMatch<EVR_AS>::
                        New(&dataset, vect, "test_AS");
    BOOST_CHECK(testmatchAS->eval());
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_Modality, 
                                           dicomifier::Range(0,1)));
    auto testmatchCS = dicomifier::conditions::ElementMatch<EVR_CS>::
                        New(&dataset, vect, {"value1", "value2", "value3"});
    BOOST_CHECK(testmatchCS->eval());
    
    // Test VR = DA
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientBirthDate, 
                                           dicomifier::Range(0,1)));
    auto testmatchDA = dicomifier::conditions::ElementMatch<EVR_DA>::
                        New(&dataset, vect, "01/01/2001");
    BOOST_CHECK(testmatchDA->eval());
    
    // Test VR = DS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientWeight, 
                                           dicomifier::Range(0,1)));
    auto testmatchDS = dicomifier::conditions::ElementMatch<EVR_DS>::
                        New(&dataset, vect, 60.5);
    BOOST_CHECK(testmatchDS->eval());
    
    // Test VR = DT
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_FrameAcquisitionDateTime, 
                                           dicomifier::Range(0,1)));
    auto testmatchDT = dicomifier::conditions::ElementMatch<EVR_DT>::
                        New(&dataset, vect, "01/01/2001 09:09:09");
    BOOST_CHECK(testmatchDT->eval());
    
    // Test VR = FL
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_RecommendedDisplayFrameRateInFloat, 
                                           dicomifier::Range(0,1)));
    auto testmatchFL = dicomifier::conditions::ElementMatch<EVR_FL>::
                        New(&dataset, vect, 15.2);
    BOOST_CHECK(testmatchFL->eval());
    
    // Test VR = FD
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PupilSize, 
                                           dicomifier::Range(0,1)));
    auto testmatchFD = dicomifier::conditions::ElementMatch<EVR_FD>::
                        New(&dataset, vect, 42.5);
    BOOST_CHECK(testmatchFD->eval());
    
    // Test VR = IS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_StageNumber, 
                                           dicomifier::Range(0,1)));
    auto testmatchIS = dicomifier::conditions::ElementMatch<EVR_IS>::
                        New(&dataset, vect, 12);
    BOOST_CHECK(testmatchIS->eval());
    
    // Test VR = LO
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_Manufacturer, 
                                           dicomifier::Range(0,1)));
    auto testmatchLO = dicomifier::conditions::ElementMatch<EVR_LO>::
                        New(&dataset, vect, "MyManufacturer");
    BOOST_CHECK(testmatchLO->eval());
    
    // Test VR = LT
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_AdditionalPatientHistory, 
                                           dicomifier::Range(0,1)));
    auto testmatchLT = dicomifier::conditions::ElementMatch<EVR_LT>::
                        New(&dataset, vect, "test_valueLT");
    BOOST_CHECK(testmatchLT->eval());
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, 
                                           dicomifier::Range(0,1)));
    auto testmatchPN = dicomifier::conditions::ElementMatch<EVR_PN>::
                        New(&dataset, vect, "Doe^John");
    BOOST_CHECK(testmatchPN->eval());
    
    // Test VR = SH
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_EthnicGroup, 
                                           dicomifier::Range(0,1)));
    auto testmatchSH = dicomifier::conditions::ElementMatch<EVR_SH>::
                        New(&dataset, vect, "test_valueSH");
    BOOST_CHECK(testmatchSH->eval());
    
    // Test VR = SL
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_ReferencePixelX0, 
                                           dicomifier::Range(0,1)));
    auto testmatchSL = dicomifier::conditions::ElementMatch<EVR_SL>::
                        New(&dataset, vect, 10);
    BOOST_CHECK(testmatchSL->eval());
    
    // Test VR = SQ (Test SubTag in sequence, not Sequence Tag)
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_OtherPatientIDsSequence, 
                                           dicomifier::Range(0,1)));
    vect.push_back(dicomifier::TagAndRange(DCM_PatientID, 
                                           dicomifier::Range(0,1)));
    auto testmatchSQ = dicomifier::conditions::ElementMatch<EVR_LO>::
                        New(&dataset, vect, "123");
    BOOST_CHECK(testmatchSQ->eval());
    
    // Test VR = SS
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_TagAngleSecondAxis, 
                                           dicomifier::Range(0,1)));
    auto testmatchSS = dicomifier::conditions::ElementMatch<EVR_SS>::
                        New(&dataset, vect, 10);
    BOOST_CHECK(testmatchSS->eval());
    
    // Test VR = ST
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_InstitutionAddress, 
                                           dicomifier::Range(0,1)));
    auto testmatchST = dicomifier::conditions::ElementMatch<EVR_ST>::
                        New(&dataset, vect, "MyAdress");
    BOOST_CHECK(testmatchST->eval());
    
    // Test VR = TM
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_InstanceCreationTime, 
                                           dicomifier::Range(0,1)));
    auto testmatchTM = dicomifier::conditions::ElementMatch<EVR_TM>::
                        New(&dataset, vect, "08:08:08");
    BOOST_CHECK(testmatchTM->eval());
    
    // Test VR = UI
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_SOPClassUID, 
                                           dicomifier::Range(0,1)));
    auto testmatchUI = dicomifier::conditions::ElementMatch<EVR_UI>::
                        New(&dataset, vect, "1.2.3.4.5");
    BOOST_CHECK(testmatchUI->eval());
    
    // Test VR = UL
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_SimpleFrameList, 
                                           dicomifier::Range(0,1)));
    auto testmatchUL = dicomifier::conditions::ElementMatch<EVR_UL>::
                        New(&dataset, vect, 11);
    BOOST_CHECK(testmatchUL->eval());
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_FailureReason, 
                                           dicomifier::Range(0,1)));
    auto testmatchUS = dicomifier::conditions::ElementMatch<EVR_US>::
                        New(&dataset, vect, 5);
    BOOST_CHECK(testmatchUS->eval());
    
    // Test VR = UT
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PixelDataProviderURL, 
                                           dicomifier::Range(0,1)));
    auto testmatchUT = dicomifier::conditions::ElementMatch<EVR_UT>::
                        New(&dataset, vect, "test_valueUT");
    BOOST_CHECK(testmatchUT->eval());
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
                        New(&dataset, vect, {"value1", "badValue", "value3"});
    BOOST_CHECK(!testmatch->eval());
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
                        New(&dataset, vect, {"value1", "value2", "value3"});
    BOOST_CHECK(!testmatch->eval());
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
                        New(&dataset, vect, "Doe^*");
    BOOST_CHECK(testmatch->eval());
    
    // Test 2
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, 
                                           dicomifier::Range(0,1)));
    testmatch = dicomifier::conditions::ElementMatch<EVR_PN>::
                        New(&dataset, vect, "Doe^Jo?n");
    BOOST_CHECK(testmatch->eval());
}

/*************************** TEST OK 07 *******************************/
/**
 * Nominal test case: Eval return false (different size)
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_07, TestDataOK03)
{
    vect.clear();
    vect.push_back(dicomifier::TagAndRange(DCM_Modality,
                                           dicomifier::Range(0,1)));
    auto testmatch = dicomifier::conditions::ElementMatch<EVR_CS>::
                        New(&dataset, vect, {"value1", "value2"});
    BOOST_CHECK(!testmatch->eval());
}

/*************************** TEST OK 08 *******************************/
/**
 * Error test case: Empty dataset
 */
BOOST_AUTO_TEST_CASE(Empty_Dataset_Eval)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_Modality,
                                           dicomifier::Range(0,1)));
    
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_CS>::New(NULL, 
                                                          vect,
                                                          "value1");
    BOOST_REQUIRE(!testmatch->eval());
}

/*************************** TEST OK 09 *******************************/
/**
 * Error test case: Empty dataset (matchItem)
 */
BOOST_AUTO_TEST_CASE(Empty_Dataset_MatchItem)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_Modality,
                                           dicomifier::Range(0,1)));

    auto testmatch =
        dicomifier::conditions::ElementMatch<EVR_CS>::New(NULL,
                                                          vect,
                                                          "value1");
    BOOST_REQUIRE(!testmatch->matchItem(0, NULL));
}
