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
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::TimeGenerator<EVR_AS>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::TimeGenerator<EVR_CS>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::TimeGenerator<EVR_DA>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::TimeGenerator<EVR_DS>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::TimeGenerator<EVR_DT>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::TimeGenerator<EVR_FL>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::TimeGenerator<EVR_FD>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::TimeGenerator<EVR_IS>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::TimeGenerator<EVR_LO>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::TimeGenerator<EVR_LT>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::TimeGenerator<EVR_PN>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::TimeGenerator<EVR_SH>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::TimeGenerator<EVR_SL>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::TimeGenerator<EVR_SS>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::TimeGenerator<EVR_ST>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::TimeGenerator<EVR_TM>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::TimeGenerator<EVR_UI>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::TimeGenerator<EVR_UL>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::TimeGenerator<EVR_US>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::TimeGenerator<EVR_UT>::New();
    // Pointer exists and class type is TimeGenerator
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_TimeGenerator);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    // Test VR = AE
    auto timegeneratorAE = dicomifier::translator::TimeGenerator<EVR_AE>::New();
    timegeneratorAE->run(NULL, NULL);
    auto resultsAE = timegeneratorAE->get_array();
    BOOST_CHECK_EQUAL(resultsAE[0] != "", true);
                        
    // Test VR = AS
    auto timegeneratorAS = dicomifier::translator::TimeGenerator<EVR_AS>::New();
    timegeneratorAS->run(NULL, NULL);
    auto resultsAS = timegeneratorAS->get_array();
    BOOST_CHECK_EQUAL(resultsAS[0] != "", true);
                        
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto timegeneratorCS = dicomifier::translator::TimeGenerator<EVR_CS>::New();
    timegeneratorCS->run(NULL, NULL);
    auto resultsCS = timegeneratorCS->get_array();
    BOOST_CHECK_EQUAL(resultsCS[0] != "", true);
    
    // Test VR = DA
    auto timegeneratorDA = dicomifier::translator::TimeGenerator<EVR_DA>::New();
    timegeneratorDA->run(NULL, NULL);
    auto resultsDA = timegeneratorDA->get_array();
    BOOST_CHECK_EQUAL(resultsDA[0] != "", true);
                        
    // Test VR = DS => Not tested
                        
    // Test VR = DT
    auto timegeneratorDT = dicomifier::translator::TimeGenerator<EVR_DT>::New();
    timegeneratorDT->run(NULL, NULL);
    auto resultsDT = timegeneratorDT->get_array();
    BOOST_CHECK_EQUAL(resultsDT[0] != "", true);
                        
    // Test VR = FL => Not tested
                        
    // Test VR = FD => Not tested
                        
    // Test VR = IS => Not tested
                        
    // Test VR = LO
    auto timegeneratorLO = dicomifier::translator::TimeGenerator<EVR_LO>::New();
    timegeneratorLO->run(NULL, NULL);
    auto resultsLO = timegeneratorLO->get_array();
    BOOST_CHECK_EQUAL(resultsLO[0] != "", true);
                        
    // Test VR = LT
    auto timegeneratorLT = dicomifier::translator::TimeGenerator<EVR_LT>::New();
    timegeneratorLT->run(NULL, NULL);
    auto resultsLT = timegeneratorLT->get_array();
    BOOST_CHECK_EQUAL(resultsLT[0] != "", true);
                        
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto timegeneratorPN = dicomifier::translator::TimeGenerator<EVR_PN>::New();
    timegeneratorPN->run(NULL, NULL);
    auto resultsPN = timegeneratorPN->get_array();
    BOOST_CHECK_EQUAL(resultsPN[0] != "", true);
                        
    // Test VR = SH
    auto timegeneratorSH = dicomifier::translator::TimeGenerator<EVR_SH>::New();
    timegeneratorSH->run(NULL, NULL);
    auto resultsSH = timegeneratorSH->get_array();
    BOOST_CHECK_EQUAL(resultsSH[0] != "", true);
                        
    // Test VR = SL => Not tested
                        
    // Test VR = SQ => Not implemented
                        
    // Test VR = SS => Not tested
                        
    // Test VR = ST
    auto timegeneratorST = dicomifier::translator::TimeGenerator<EVR_ST>::New();
    timegeneratorST->run(NULL, NULL);
    auto resultsST = timegeneratorST->get_array();
    BOOST_CHECK_EQUAL(resultsST[0] != "", true);
                        
    // Test VR = TM
    auto timegeneratorTM = dicomifier::translator::TimeGenerator<EVR_TM>::New();
    timegeneratorTM->run(NULL, NULL);
    auto resultsTM = timegeneratorTM->get_array();
    BOOST_CHECK_EQUAL(resultsTM[0] != "", true);
                        
    // Test VR = UI
    auto timegeneratorUI = dicomifier::translator::TimeGenerator<EVR_UI>::New();
    timegeneratorUI->run(NULL, NULL);
    auto resultsUI = timegeneratorUI->get_array();
    BOOST_CHECK_EQUAL(resultsUI[0] != "", true);
                        
    // Test VR = UL => Not tested
                        
    // Test VR = US => Not tested
                        
    // Test VR = UT
    auto timegeneratorUT = dicomifier::translator::TimeGenerator<EVR_UT>::New();
    timegeneratorUT->run(NULL, NULL);
    auto resultsUT = timegeneratorUT->get_array();
    BOOST_CHECK_EQUAL(resultsUT[0] != "", true);
}
