/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleUpperCaseGenerator
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/generator/UpperCaseGenerator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::UpperCaseGenerator<EVR_AE>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::UpperCaseGenerator<EVR_AS>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::UpperCaseGenerator<EVR_CS>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::UpperCaseGenerator<EVR_DA>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::UpperCaseGenerator<EVR_DS>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::UpperCaseGenerator<EVR_DT>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::UpperCaseGenerator<EVR_FL>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::UpperCaseGenerator<EVR_FD>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::UpperCaseGenerator<EVR_IS>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::UpperCaseGenerator<EVR_LO>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::UpperCaseGenerator<EVR_LT>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::UpperCaseGenerator<EVR_PN>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::UpperCaseGenerator<EVR_SH>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::UpperCaseGenerator<EVR_SL>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::UpperCaseGenerator<EVR_SS>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::UpperCaseGenerator<EVR_ST>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::UpperCaseGenerator<EVR_TM>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::UpperCaseGenerator<EVR_UI>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::UpperCaseGenerator<EVR_UL>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::UpperCaseGenerator<EVR_US>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::UpperCaseGenerator<EVR_UT>::New();
    // Pointer exists and class type is UpperCaseGenerator
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_UpperCaseGenerator);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    // Test VR = AE
    auto uppercasegeneratorAE = dicomifier::translator::UpperCaseGenerator<EVR_AE>::
        New(dicomifier::translator::ConstantField<EVR_AE>::New("AbCd123"));
    uppercasegeneratorAE->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsAE = uppercasegeneratorAE->get_array();
    BOOST_CHECK_EQUAL(resultsAE[0], "ABCD123");
                        
    // Test VR = AS
    auto uppercasegeneratorAS = dicomifier::translator::UpperCaseGenerator<EVR_AS>::
        New(dicomifier::translator::ConstantField<EVR_AS>::New("AbCd123"));
    uppercasegeneratorAS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsAS = uppercasegeneratorAS->get_array();
    BOOST_CHECK_EQUAL(resultsAS[0], "ABCD123");
                        
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto uppercasegeneratorCS = dicomifier::translator::UpperCaseGenerator<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("AbCd123"));
    uppercasegeneratorCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsCS = uppercasegeneratorCS->get_array();
    BOOST_CHECK_EQUAL(resultsCS[0], "ABCD123");
    
    // Test VR = DA
    auto uppercasegeneratorDA = dicomifier::translator::UpperCaseGenerator<EVR_DA>::
        New(dicomifier::translator::ConstantField<EVR_DA>::New("AbCd123"));
    uppercasegeneratorDA->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDA = uppercasegeneratorDA->get_array();
    BOOST_CHECK_EQUAL(resultsDA[0], "ABCD123");
                        
    // Test VR = DS
    /*auto uppercasegeneratorDS = dicomifier::translator::UpperCaseGenerator<EVR_DS>::
        New(dicomifier::translator::ConstantField<EVR_DS>::New(123));
    uppercasegeneratorDS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDS = uppercasegeneratorDS->get_array();
    BOOST_CHECK_EQUAL(resultsDS[0], 123);*/
                        
    // Test VR = DT
    auto uppercasegeneratorDT = dicomifier::translator::UpperCaseGenerator<EVR_DT>::
        New(dicomifier::translator::ConstantField<EVR_DT>::New("AbCd123"));
    uppercasegeneratorDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDT = uppercasegeneratorDT->get_array();
    BOOST_CHECK_EQUAL(resultsDT[0], "ABCD123");
                        
    // Test VR = FL
    /*auto uppercasegeneratorFL = dicomifier::translator::UpperCaseGenerator<EVR_FL>::
        New(dicomifier::translator::ConstantField<EVR_FL>::New(123));
    uppercasegeneratorFL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsFL = uppercasegeneratorFL->get_array();
    BOOST_CHECK_EQUAL(resultsFL[0], 123);*/
                        
    // Test VR = FD
    /*auto uppercasegeneratorFD = dicomifier::translator::UpperCaseGenerator<EVR_FD>::
        New(dicomifier::translator::ConstantField<EVR_FD>::New(123));
    uppercasegeneratorFD->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsFD = uppercasegeneratorFD->get_array();
    BOOST_CHECK_EQUAL(resultsFD[0], 123);*/
                        
    // Test VR = IS
    /*auto uppercasegeneratorIS = dicomifier::translator::UpperCaseGenerator<EVR_IS>::
        New(dicomifier::translator::ConstantField<EVR_IS>::New(123));
    uppercasegeneratorIS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsIS = uppercasegeneratorIS->get_array();
    BOOST_CHECK_EQUAL(resultsIS[0], 123);*/
                        
    // Test VR = LO
    auto uppercasegeneratorLO = dicomifier::translator::UpperCaseGenerator<EVR_LO>::
        New(dicomifier::translator::ConstantField<EVR_LO>::New("AbCd123"));
    uppercasegeneratorLO->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsLO = uppercasegeneratorLO->get_array();
    BOOST_CHECK_EQUAL(resultsLO[0], "ABCD123");
                        
    // Test VR = LT
    auto uppercasegeneratorLT = dicomifier::translator::UpperCaseGenerator<EVR_LT>::
        New(dicomifier::translator::ConstantField<EVR_LT>::New("AbCd123"));
    uppercasegeneratorLT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsLT = uppercasegeneratorLT->get_array();
    BOOST_CHECK_EQUAL(resultsLT[0], "ABCD123");
                        
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto uppercasegeneratorPN = dicomifier::translator::UpperCaseGenerator<EVR_PN>::
        New(dicomifier::translator::ConstantField<EVR_PN>::New("AbCd123"));
    uppercasegeneratorPN->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsPN = uppercasegeneratorPN->get_array();
    BOOST_CHECK_EQUAL(resultsPN[0], "ABCD123");
                        
    // Test VR = SH
    auto uppercasegeneratorSH = dicomifier::translator::UpperCaseGenerator<EVR_SH>::
        New(dicomifier::translator::ConstantField<EVR_SH>::New("AbCd123"));
    uppercasegeneratorSH->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsSH = uppercasegeneratorSH->get_array();
    BOOST_CHECK_EQUAL(resultsSH[0], "ABCD123");
                        
    // Test VR = SL
    /*auto uppercasegeneratorSL = dicomifier::translator::UpperCaseGenerator<EVR_SL>::
        New(dicomifier::translator::ConstantField<EVR_SL>::New(123));
    uppercasegeneratorSL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsSL = uppercasegeneratorSL->get_array();
    BOOST_CHECK_EQUAL(resultsSL[0], 123);*/
                        
    // Test VR = SQ => Not implemented
                        
    // Test VR = SS
    /*auto uppercasegeneratorSS = dicomifier::translator::UpperCaseGenerator<EVR_SS>::
        New(dicomifier::translator::ConstantField<EVR_SS>::New(123));
    uppercasegeneratorSS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsSS = uppercasegeneratorSS->get_array();
    BOOST_CHECK_EQUAL(resultsSS[0], 123);*/
                        
    // Test VR = ST
    auto uppercasegeneratorST = dicomifier::translator::UpperCaseGenerator<EVR_ST>::
        New(dicomifier::translator::ConstantField<EVR_ST>::New("AbCd123"));
    uppercasegeneratorST->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsST = uppercasegeneratorST->get_array();
    BOOST_CHECK_EQUAL(resultsST[0], "ABCD123");
                        
    // Test VR = TM
    auto uppercasegeneratorTM = dicomifier::translator::UpperCaseGenerator<EVR_TM>::
        New(dicomifier::translator::ConstantField<EVR_TM>::New("AbCd123"));
    uppercasegeneratorTM->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsTM = uppercasegeneratorTM->get_array();
    BOOST_CHECK_EQUAL(resultsTM[0], "ABCD123");
                        
    // Test VR = UI
    auto uppercasegeneratorUI = dicomifier::translator::UpperCaseGenerator<EVR_UI>::
        New(dicomifier::translator::ConstantField<EVR_UI>::New("AbCd123"));
    uppercasegeneratorUI->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUI = uppercasegeneratorUI->get_array();
    BOOST_CHECK_EQUAL(resultsUI[0], "ABCD123");
                        
    // Test VR = UL
    /*auto uppercasegeneratorUL = dicomifier::translator::UpperCaseGenerator<EVR_UL>::
        New(dicomifier::translator::ConstantField<EVR_UL>::New(123));
    uppercasegeneratorUL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUL = uppercasegeneratorUL->get_array();
    BOOST_CHECK_EQUAL(resultsUL[0], 123);*/
                        
    // Test VR = US
    /*auto uppercasegeneratorUS = dicomifier::translator::UpperCaseGenerator<EVR_US>::
        New(dicomifier::translator::ConstantField<EVR_US>::New(123));
    uppercasegeneratorUS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUS = uppercasegeneratorUS->get_array();
    BOOST_CHECK_EQUAL(resultsUS[0], 123);*/
                        
    // Test VR = UT
    auto uppercasegeneratorUT = dicomifier::translator::UpperCaseGenerator<EVR_UT>::
        New(dicomifier::translator::ConstantField<EVR_UT>::New("AbCd123"));
    uppercasegeneratorUT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUT = uppercasegeneratorUT->get_array();
    BOOST_CHECK_EQUAL(resultsUT[0], "ABCD123");
}
