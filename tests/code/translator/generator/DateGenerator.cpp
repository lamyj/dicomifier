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
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::DateGenerator<EVR_AS>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::DateGenerator<EVR_CS>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::DateGenerator<EVR_DA>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::DateGenerator<EVR_DS>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::DateGenerator<EVR_DT>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::DateGenerator<EVR_FL>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::DateGenerator<EVR_FD>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::DateGenerator<EVR_IS>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::DateGenerator<EVR_LO>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::DateGenerator<EVR_LT>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::DateGenerator<EVR_PN>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::DateGenerator<EVR_SH>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::DateGenerator<EVR_SL>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::DateGenerator<EVR_SS>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::DateGenerator<EVR_ST>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::DateGenerator<EVR_TM>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::DateGenerator<EVR_UI>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::DateGenerator<EVR_UL>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::DateGenerator<EVR_US>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_DateGenerator);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::DateGenerator<EVR_UT>::New();
    // Pointer exists and class type is DateGenerator
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_DateGenerator);
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
    dategeneratorAE->run(NULL, NULL);
    auto resultsAE = dategeneratorAE->get_array();
    BOOST_CHECK_EQUAL(resultsAE[0], "20140201");
                        
    // Test VR = AS
    auto dategeneratorAS = dicomifier::translator::DateGenerator<EVR_AS>::
        New(dicomifier::translator::ConstantField<EVR_AS>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorAS->run(NULL, NULL);
    auto resultsAS = dategeneratorAS->get_array();
    BOOST_CHECK_EQUAL(resultsAS[0], "20140201");
                        
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto dategeneratorCS = dicomifier::translator::DateGenerator<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorCS->run(NULL, NULL);
    auto resultsCS = dategeneratorCS->get_array();
    BOOST_CHECK_EQUAL(resultsCS[0], "20140201");
    
    // Test VR = DA
    auto dategeneratorDA = dicomifier::translator::DateGenerator<EVR_DA>::
        New(dicomifier::translator::ConstantField<EVR_DA>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorDA->run(NULL, NULL);
    auto resultsDA = dategeneratorDA->get_array();
    BOOST_CHECK_EQUAL(resultsDA[0], "20140201");
                        
    // Test VR = DS
    /*auto dategeneratorDS = dicomifier::translator::DateGenerator<EVR_DS>::
        New(dicomifier::translator::ConstantField<EVR_DS>::New(123));
    dategeneratorDS->run(NULL, NULL);
    auto resultsDS = dategeneratorDS->get_array();
    BOOST_CHECK_EQUAL(resultsDS[0], 123);*/
                        
    // Test VR = DT
    auto dategeneratorDT = dicomifier::translator::DateGenerator<EVR_DT>::
        New(dicomifier::translator::ConstantField<EVR_DT>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorDT->run(NULL, NULL);
    auto resultsDT = dategeneratorDT->get_array();
    BOOST_CHECK_EQUAL(resultsDT[0], "20140201");
                        
    // Test VR = FL
    /*auto dategeneratorFL = dicomifier::translator::DateGenerator<EVR_FL>::
        New(dicomifier::translator::ConstantField<EVR_FL>::New(123));
    dategeneratorFL->run(NULL, NULL);
    auto resultsFL = dategeneratorFL->get_array();
    BOOST_CHECK_EQUAL(resultsFL[0], 123);*/
                        
    // Test VR = FD
    /*auto dategeneratorFD = dicomifier::translator::DateGenerator<EVR_FD>::
        New(dicomifier::translator::ConstantField<EVR_FD>::New(123));
    dategeneratorFD->run(NULL, NULL);
    auto resultsFD = dategeneratorFD->get_array();
    BOOST_CHECK_EQUAL(resultsFD[0], 123);*/
                        
    // Test VR = IS
    /*auto dategeneratorIS = dicomifier::translator::DateGenerator<EVR_IS>::
        New(dicomifier::translator::ConstantField<EVR_IS>::New(123));
    dategeneratorIS->run(NULL, NULL);
    auto resultsIS = dategeneratorIS->get_array();
    BOOST_CHECK_EQUAL(resultsIS[0], 123);*/
                        
    // Test VR = LO
    auto dategeneratorLO = dicomifier::translator::DateGenerator<EVR_LO>::
        New(dicomifier::translator::ConstantField<EVR_LO>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorLO->run(NULL, NULL);
    auto resultsLO = dategeneratorLO->get_array();
    BOOST_CHECK_EQUAL(resultsLO[0], "20140201");
                        
    // Test VR = LT
    auto dategeneratorLT = dicomifier::translator::DateGenerator<EVR_LT>::
        New(dicomifier::translator::ConstantField<EVR_LT>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorLT->run(NULL, NULL);
    auto resultsLT = dategeneratorLT->get_array();
    BOOST_CHECK_EQUAL(resultsLT[0], "20140201");
                        
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto dategeneratorPN = dicomifier::translator::DateGenerator<EVR_PN>::
        New(dicomifier::translator::ConstantField<EVR_PN>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorPN->run(NULL, NULL);
    auto resultsPN = dategeneratorPN->get_array();
    BOOST_CHECK_EQUAL(resultsPN[0], "20140201");
                        
    // Test VR = SH
    auto dategeneratorSH = dicomifier::translator::DateGenerator<EVR_SH>::
        New(dicomifier::translator::ConstantField<EVR_SH>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorSH->run(NULL, NULL);
    auto resultsSH = dategeneratorSH->get_array();
    BOOST_CHECK_EQUAL(resultsSH[0], "20140201");
                        
    // Test VR = SL
    /*auto dategeneratorSL = dicomifier::translator::DateGenerator<EVR_SL>::
        New(dicomifier::translator::ConstantField<EVR_SL>::New(123));
    dategeneratorSL->run(NULL, NULL);
    auto resultsSL = dategeneratorSL->get_array();
    BOOST_CHECK_EQUAL(resultsSL[0], 123);*/
                        
    // Test VR = SQ => Not implemented
                        
    // Test VR = SS
    /*auto dategeneratorSS = dicomifier::translator::DateGenerator<EVR_SS>::
        New(dicomifier::translator::ConstantField<EVR_SS>::New(123));
    dategeneratorSS->run(NULL, NULL);
    auto resultsSS = dategeneratorSS->get_array();
    BOOST_CHECK_EQUAL(resultsSS[0], 123);*/
                        
    // Test VR = ST
    auto dategeneratorST = dicomifier::translator::DateGenerator<EVR_ST>::
        New(dicomifier::translator::ConstantField<EVR_ST>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorST->run(NULL, NULL);
    auto resultsST = dategeneratorST->get_array();
    BOOST_CHECK_EQUAL(resultsST[0], "20140201");
                        
    // Test VR = TM
    auto dategeneratorTM = dicomifier::translator::DateGenerator<EVR_TM>::
        New(dicomifier::translator::ConstantField<EVR_TM>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorTM->run(NULL, NULL);
    auto resultsTM = dategeneratorTM->get_array();
    BOOST_CHECK_EQUAL(resultsTM[0], "20140201");
                        
    // Test VR = UI
    auto dategeneratorUI = dicomifier::translator::DateGenerator<EVR_UI>::
        New(dicomifier::translator::ConstantField<EVR_UI>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorUI->run(NULL, NULL);
    auto resultsUI = dategeneratorUI->get_array();
    BOOST_CHECK_EQUAL(resultsUI[0], "20140201");
                        
    // Test VR = UL
    /*auto dategeneratorUL = dicomifier::translator::DateGenerator<EVR_UL>::
        New(dicomifier::translator::ConstantField<EVR_UL>::New(123));
    dategeneratorUL->run(NULL, NULL);
    auto resultsUL = dategeneratorUL->get_array();
    BOOST_CHECK_EQUAL(resultsUL[0], 123);*/
                        
    // Test VR = US
    /*auto dategeneratorUS = dicomifier::translator::DateGenerator<EVR_US>::
        New(dicomifier::translator::ConstantField<EVR_US>::New(123));
    dategeneratorUS->run(NULL, NULL);
    auto resultsUS = dategeneratorUS->get_array();
    BOOST_CHECK_EQUAL(resultsUS[0], 123);*/
                        
    // Test VR = UT
    auto dategeneratorUT = dicomifier::translator::DateGenerator<EVR_UT>::
        New(dicomifier::translator::ConstantField<EVR_UT>::New("01/02/2014"), "%d/%m/%Y", "%Y%m%d");
    dategeneratorUT->run(NULL, NULL);
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
    dategeneratorDA->run(NULL, NULL);
    auto resultsDA = dategeneratorDA->get_array();
    BOOST_CHECK_EQUAL(resultsDA[0] != "", true);
}
