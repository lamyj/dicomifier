/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDateGenerator
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/generator/DateGenerator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::DateGenerator<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldae != NULL, true);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::DateGenerator<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldas != NULL, true);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::DateGenerator<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldcs != NULL, true);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::DateGenerator<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldda != NULL, true);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::DateGenerator<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldds != NULL, true);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::DateGenerator<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfielddt != NULL, true);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::DateGenerator<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfl != NULL, true);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::DateGenerator<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfd != NULL, true);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::DateGenerator<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldis != NULL, true);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::DateGenerator<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlo != NULL, true);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::DateGenerator<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlt != NULL, true);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::DateGenerator<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldpn != NULL, true);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::DateGenerator<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsh != NULL, true);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::DateGenerator<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsl != NULL, true);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::DateGenerator<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldss != NULL, true);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::DateGenerator<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldst != NULL, true);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::DateGenerator<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldtm != NULL, true);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::DateGenerator<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldui != NULL, true);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::DateGenerator<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldul != NULL, true);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::DateGenerator<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldus != NULL, true);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::DateGenerator<EVR_UT>::New();
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
    auto dategeneratorAE = dicomifier::translator::DateGenerator<EVR_AE>::
        New(dicomifier::translator::ConstantField<EVR_AE>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorAE->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsAE = dategeneratorAE->get_array();
    BOOST_CHECK_EQUAL(resultsAE[0], "20140201");
                        
    // Test VR = AS
    auto dategeneratorAS = dicomifier::translator::DateGenerator<EVR_AS>::
        New(dicomifier::translator::ConstantField<EVR_AS>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorAS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsAS = dategeneratorAS->get_array();
    BOOST_CHECK_EQUAL(resultsAS[0], "20140201");
                        
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto dategeneratorCS = dicomifier::translator::DateGenerator<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsCS = dategeneratorCS->get_array();
    BOOST_CHECK_EQUAL(resultsCS[0], "20140201");
    
    // Test VR = DA
    auto dategeneratorDA = dicomifier::translator::DateGenerator<EVR_DA>::
        New(dicomifier::translator::ConstantField<EVR_DA>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorDA->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDA = dategeneratorDA->get_array();
    BOOST_CHECK_EQUAL(resultsDA[0], "20140201");
                        
    // Test VR = DS
    /*auto dategeneratorDS = dicomifier::translator::DateGenerator<EVR_DS>::
        New(dicomifier::translator::ConstantField<EVR_DS>::New(123));
    dategeneratorDS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDS = dategeneratorDS->get_array();
    BOOST_CHECK_EQUAL(resultsDS[0], 123);*/
                        
    // Test VR = DT
    auto dategeneratorDT = dicomifier::translator::DateGenerator<EVR_DT>::
        New(dicomifier::translator::ConstantField<EVR_DT>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDT = dategeneratorDT->get_array();
    BOOST_CHECK_EQUAL(resultsDT[0], "20140201");
                        
    // Test VR = FL
    /*auto dategeneratorFL = dicomifier::translator::DateGenerator<EVR_FL>::
        New(dicomifier::translator::ConstantField<EVR_FL>::New(123));
    dategeneratorFL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsFL = dategeneratorFL->get_array();
    BOOST_CHECK_EQUAL(resultsFL[0], 123);*/
                        
    // Test VR = FD
    /*auto dategeneratorFD = dicomifier::translator::DateGenerator<EVR_FD>::
        New(dicomifier::translator::ConstantField<EVR_FD>::New(123));
    dategeneratorFD->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsFD = dategeneratorFD->get_array();
    BOOST_CHECK_EQUAL(resultsFD[0], 123);*/
                        
    // Test VR = IS
    /*auto dategeneratorIS = dicomifier::translator::DateGenerator<EVR_IS>::
        New(dicomifier::translator::ConstantField<EVR_IS>::New(123));
    dategeneratorIS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsIS = dategeneratorIS->get_array();
    BOOST_CHECK_EQUAL(resultsIS[0], 123);*/
                        
    // Test VR = LO
    auto dategeneratorLO = dicomifier::translator::DateGenerator<EVR_LO>::
        New(dicomifier::translator::ConstantField<EVR_LO>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorLO->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsLO = dategeneratorLO->get_array();
    BOOST_CHECK_EQUAL(resultsLO[0], "20140201");
                        
    // Test VR = LT
    auto dategeneratorLT = dicomifier::translator::DateGenerator<EVR_LT>::
        New(dicomifier::translator::ConstantField<EVR_LT>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorLT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsLT = dategeneratorLT->get_array();
    BOOST_CHECK_EQUAL(resultsLT[0], "20140201");
                        
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto dategeneratorPN = dicomifier::translator::DateGenerator<EVR_PN>::
        New(dicomifier::translator::ConstantField<EVR_PN>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorPN->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsPN = dategeneratorPN->get_array();
    BOOST_CHECK_EQUAL(resultsPN[0], "20140201");
                        
    // Test VR = SH
    auto dategeneratorSH = dicomifier::translator::DateGenerator<EVR_SH>::
        New(dicomifier::translator::ConstantField<EVR_SH>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorSH->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsSH = dategeneratorSH->get_array();
    BOOST_CHECK_EQUAL(resultsSH[0], "20140201");
                        
    // Test VR = SL
    /*auto dategeneratorSL = dicomifier::translator::DateGenerator<EVR_SL>::
        New(dicomifier::translator::ConstantField<EVR_SL>::New(123));
    dategeneratorSL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsSL = dategeneratorSL->get_array();
    BOOST_CHECK_EQUAL(resultsSL[0], 123);*/
                        
    // Test VR = SQ => Not implemented
                        
    // Test VR = SS
    /*auto dategeneratorSS = dicomifier::translator::DateGenerator<EVR_SS>::
        New(dicomifier::translator::ConstantField<EVR_SS>::New(123));
    dategeneratorSS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsSS = dategeneratorSS->get_array();
    BOOST_CHECK_EQUAL(resultsSS[0], 123);*/
                        
    // Test VR = ST
    auto dategeneratorST = dicomifier::translator::DateGenerator<EVR_ST>::
        New(dicomifier::translator::ConstantField<EVR_ST>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorST->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsST = dategeneratorST->get_array();
    BOOST_CHECK_EQUAL(resultsST[0], "20140201");
                        
    // Test VR = TM
    auto dategeneratorTM = dicomifier::translator::DateGenerator<EVR_TM>::
        New(dicomifier::translator::ConstantField<EVR_TM>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorTM->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsTM = dategeneratorTM->get_array();
    BOOST_CHECK_EQUAL(resultsTM[0], "20140201");
                        
    // Test VR = UI
    auto dategeneratorUI = dicomifier::translator::DateGenerator<EVR_UI>::
        New(dicomifier::translator::ConstantField<EVR_UI>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorUI->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUI = dategeneratorUI->get_array();
    BOOST_CHECK_EQUAL(resultsUI[0], "20140201");
                        
    // Test VR = UL
    /*auto dategeneratorUL = dicomifier::translator::DateGenerator<EVR_UL>::
        New(dicomifier::translator::ConstantField<EVR_UL>::New(123));
    dategeneratorUL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUL = dategeneratorUL->get_array();
    BOOST_CHECK_EQUAL(resultsUL[0], 123);*/
                        
    // Test VR = US
    /*auto dategeneratorUS = dicomifier::translator::DateGenerator<EVR_US>::
        New(dicomifier::translator::ConstantField<EVR_US>::New(123));
    dategeneratorUS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUS = dategeneratorUS->get_array();
    BOOST_CHECK_EQUAL(resultsUS[0], 123);*/
                        
    // Test VR = UT
    auto dategeneratorUT = dicomifier::translator::DateGenerator<EVR_UT>::
        New(dicomifier::translator::ConstantField<EVR_UT>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorUT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUT = dategeneratorUT->get_array();
    BOOST_CHECK_EQUAL(resultsUT[0], "20140201");
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run without input data
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    // Test VR = DA
    auto dategeneratorDA = dicomifier::translator::DateGenerator<EVR_DA>::New();
    dategeneratorDA->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDA = dategeneratorDA->get_array();
    BOOST_CHECK_EQUAL(resultsDA[0] != "", true);
}
