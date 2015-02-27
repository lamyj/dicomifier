/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleTimeGenerator
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/generator/TimeGenerator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::TimeGenerator<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldae != NULL, true);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::TimeGenerator<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldas != NULL, true);
    
    // Test VR = AT
    auto testfieldat = dicomifier::translator::TimeGenerator<EVR_AT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldat != NULL, true);
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::TimeGenerator<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldcs != NULL, true);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::TimeGenerator<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldda != NULL, true);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::TimeGenerator<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldds != NULL, true);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::TimeGenerator<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfielddt != NULL, true);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::TimeGenerator<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfl != NULL, true);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::TimeGenerator<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfd != NULL, true);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::TimeGenerator<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldis != NULL, true);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::TimeGenerator<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlo != NULL, true);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::TimeGenerator<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlt != NULL, true);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::TimeGenerator<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldpn != NULL, true);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::TimeGenerator<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsh != NULL, true);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::TimeGenerator<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsl != NULL, true);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::TimeGenerator<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldss != NULL, true);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::TimeGenerator<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldst != NULL, true);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::TimeGenerator<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldtm != NULL, true);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::TimeGenerator<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldui != NULL, true);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::TimeGenerator<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldul != NULL, true);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::TimeGenerator<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldus != NULL, true);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::TimeGenerator<EVR_UT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldut != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    // Test VR = AE
    auto timegeneratorAE = dicomifier::translator::TimeGenerator<EVR_AE>::New();
    timegeneratorAE->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsAE = timegeneratorAE->get_array();
    BOOST_CHECK_EQUAL(resultsAE[0] != "", true);
                        
    // Test VR = AS
    auto timegeneratorAS = dicomifier::translator::TimeGenerator<EVR_AS>::New();
    timegeneratorAS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsAS = timegeneratorAS->get_array();
    BOOST_CHECK_EQUAL(resultsAS[0] != "", true);
                        
    // Test VR = AT
    auto timegeneratorAT = dicomifier::translator::TimeGenerator<EVR_AS>::New();
    timegeneratorAT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsAT = timegeneratorAT->get_array();
    BOOST_CHECK_EQUAL(resultsAT[0] != "", true);
    
    // Test VR = CS
    auto timegeneratorCS = dicomifier::translator::TimeGenerator<EVR_CS>::New();
    timegeneratorCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsCS = timegeneratorCS->get_array();
    BOOST_CHECK_EQUAL(resultsCS[0] != "", true);
    
    // Test VR = DA
    auto timegeneratorDA = dicomifier::translator::TimeGenerator<EVR_DA>::New();
    timegeneratorDA->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDA = timegeneratorDA->get_array();
    BOOST_CHECK_EQUAL(resultsDA[0] != "", true);
                        
    // Test VR = DS => See test error TEST_KO_01
                        
    // Test VR = DT
    auto timegeneratorDT = dicomifier::translator::TimeGenerator<EVR_DT>::New();
    timegeneratorDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDT = timegeneratorDT->get_array();
    BOOST_CHECK_EQUAL(resultsDT[0] != "", true);
                        
    // Test VR = FL => See test error TEST_KO_01
                        
    // Test VR = FD => See test error TEST_KO_01
                        
    // Test VR = IS => See test error TEST_KO_01
                        
    // Test VR = LO
    auto timegeneratorLO = dicomifier::translator::TimeGenerator<EVR_LO>::New();
    timegeneratorLO->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsLO = timegeneratorLO->get_array();
    BOOST_CHECK_EQUAL(resultsLO[0] != "", true);
                        
    // Test VR = LT
    auto timegeneratorLT = dicomifier::translator::TimeGenerator<EVR_LT>::New();
    timegeneratorLT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsLT = timegeneratorLT->get_array();
    BOOST_CHECK_EQUAL(resultsLT[0] != "", true);
                        
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto timegeneratorPN = dicomifier::translator::TimeGenerator<EVR_PN>::New();
    timegeneratorPN->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsPN = timegeneratorPN->get_array();
    BOOST_CHECK_EQUAL(resultsPN[0] != "", true);
                        
    // Test VR = SH
    auto timegeneratorSH = dicomifier::translator::TimeGenerator<EVR_SH>::New();
    timegeneratorSH->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsSH = timegeneratorSH->get_array();
    BOOST_CHECK_EQUAL(resultsSH[0] != "", true);
                        
    // Test VR = SL => See test error TEST_KO_01
                        
    // Test VR = SQ => Not implemented
                        
    // Test VR = SS => See test error TEST_KO_01
                        
    // Test VR = ST
    auto timegeneratorST = dicomifier::translator::TimeGenerator<EVR_ST>::New();
    timegeneratorST->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsST = timegeneratorST->get_array();
    BOOST_CHECK_EQUAL(resultsST[0] != "", true);
                        
    // Test VR = TM
    auto timegeneratorTM = dicomifier::translator::TimeGenerator<EVR_TM>::New();
    timegeneratorTM->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsTM = timegeneratorTM->get_array();
    BOOST_CHECK_EQUAL(resultsTM[0] != "", true);
                        
    // Test VR = UI
    auto timegeneratorUI = dicomifier::translator::TimeGenerator<EVR_UI>::New();
    timegeneratorUI->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUI = timegeneratorUI->get_array();
    BOOST_CHECK_EQUAL(resultsUI[0] != "", true);
                        
    // Test VR = UL => See test error TEST_KO_01
                        
    // Test VR = US => See test error TEST_KO_01
                        
    // Test VR = UT
    auto timegeneratorUT = dicomifier::translator::TimeGenerator<EVR_UT>::New();
    timegeneratorUT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUT = timegeneratorUT->get_array();
    BOOST_CHECK_EQUAL(resultsUT[0] != "", true);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Bad VR
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    // Test VR = DS
    auto timegeneratorDS = dicomifier::translator::TimeGenerator<EVR_DS>::New();
    BOOST_REQUIRE_THROW(timegeneratorDS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = FL
    auto timegeneratorFL = dicomifier::translator::TimeGenerator<EVR_FL>::New();
    BOOST_REQUIRE_THROW(timegeneratorFL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = FD
    auto timegeneratorFD = dicomifier::translator::TimeGenerator<EVR_FD>::New();
    BOOST_REQUIRE_THROW(timegeneratorFD->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = IS
    auto timegeneratorIS = dicomifier::translator::TimeGenerator<EVR_IS>::New();
    BOOST_REQUIRE_THROW(timegeneratorIS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = SL
    auto timegeneratorSL = dicomifier::translator::TimeGenerator<EVR_SL>::New();
    BOOST_REQUIRE_THROW(timegeneratorSL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = SS
    auto timegeneratorSS = dicomifier::translator::TimeGenerator<EVR_SS>::New();
    BOOST_REQUIRE_THROW(timegeneratorSS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = UL
    auto timegeneratorUL = dicomifier::translator::TimeGenerator<EVR_UL>::New();
    BOOST_REQUIRE_THROW(timegeneratorUL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = US
    auto timegeneratorUS = dicomifier::translator::TimeGenerator<EVR_US>::New();
    BOOST_REQUIRE_THROW(timegeneratorUS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);
}
