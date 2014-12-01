/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleRegExFilter
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/filters/RegExFilter.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::RegExFilter<EVR_AE>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::RegExFilter<EVR_AS>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::RegExFilter<EVR_CS>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::RegExFilter<EVR_DA>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::RegExFilter<EVR_DS>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::RegExFilter<EVR_DT>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::RegExFilter<EVR_FL>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::RegExFilter<EVR_FD>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::RegExFilter<EVR_IS>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::RegExFilter<EVR_LO>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::RegExFilter<EVR_LT>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::RegExFilter<EVR_PN>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::RegExFilter<EVR_SH>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::RegExFilter<EVR_SL>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::RegExFilter<EVR_SS>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::RegExFilter<EVR_ST>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::RegExFilter<EVR_TM>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::RegExFilter<EVR_UI>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::RegExFilter<EVR_UL>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::RegExFilter<EVR_US>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_RegExFilter);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::RegExFilter<EVR_UT>::New();
    // Pointer exists and class type is RegExFilter
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_RegExFilter);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run VR = AE
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto regexfilterAE = dicomifier::translator::
        RegExFilter<EVR_AE>::New(dicomifier::translator::
                                 ConstantField<EVR_AE>::New("MY_AETITLE_TEST"), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterAE->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterAE->get_array();
    BOOST_CHECK_EQUAL(results[0], "AETITLE");
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run VR = AS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    auto regexfilterAS = dicomifier::translator::
        RegExFilter<EVR_AS>::New(dicomifier::translator::
                                 ConstantField<EVR_AS>::New("42Y"), 
                                                            "^([0-9]+).*");
    regexfilterAS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterAS->get_array();
    BOOST_CHECK_EQUAL(results[0], "42");
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Run VR = CS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    auto regexfilterCS = dicomifier::translator::
        RegExFilter<EVR_CS>::New(dicomifier::translator::
                                 ConstantField<EVR_CS>::New("10:11:12 21062014"), 
                                                            "^([0-9]{2}):{1}([0-9]{2}):{1}([0-9]{2}).*");
    regexfilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "101112");
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Run VR = DA
 */
BOOST_AUTO_TEST_CASE(TEST_OK_05)
{
    auto regexfilterDA = dicomifier::translator::
        RegExFilter<EVR_DA>::New(dicomifier::translator::
                                 ConstantField<EVR_DA>::New("10:11:12 21/06/2014"), 
                                                            "^.*([0-9]{2})/{1}([0-9]{2})/{1}([0-9]{4}).*");
    regexfilterDA->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterDA->get_array();
    BOOST_CHECK_EQUAL(results[0], "21062014");
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Run VR = DS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_06)
{
    auto regexfilterDS = dicomifier::translator::
        RegExFilter<EVR_DS>::New(dicomifier::translator::
                                 ConstantField<EVR_DS>::New(25), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterDS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterDS->get_array();
    BOOST_CHECK_EQUAL(results[0], 25);
}

/*************************** TEST OK 07 *******************************/
/**
 * Nominal test case: Run VR = DT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_07)
{
    auto regexfilterDT = dicomifier::translator::
        RegExFilter<EVR_DT>::New(dicomifier::translator::
                                 ConstantField<EVR_DT>::New("10:11:12 21062014"), 
                                                            "^([0-9]{2}):{1}([0-9]{2}):{1}([0-9]{2}).*");
    regexfilterDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterDT->get_array();
    BOOST_CHECK_EQUAL(results[0], "101112");
}

/*************************** TEST OK 08 *******************************/
/**
 * Nominal test case: Run VR = FL
 */
BOOST_AUTO_TEST_CASE(TEST_OK_08)
{
    auto regexfilterFL = dicomifier::translator::
        RegExFilter<EVR_FL>::New(dicomifier::translator::
                                 ConstantField<EVR_FL>::New(25), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterFL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterFL->get_array();
    BOOST_CHECK_EQUAL(results[0], 25);
}

/*************************** TEST OK 09 *******************************/
/**
 * Nominal test case: Run VR = FD
 */
BOOST_AUTO_TEST_CASE(TEST_OK_09)
{
    auto regexfilterFD = dicomifier::translator::
        RegExFilter<EVR_FD>::New(dicomifier::translator::
                                 ConstantField<EVR_FD>::New(25), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterFD->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterFD->get_array();
    BOOST_CHECK_EQUAL(results[0], 25);
}

/*************************** TEST OK 10 *******************************/
/**
 * Nominal test case: Run VR = IS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_10)
{
    auto regexfilterIS = dicomifier::translator::
        RegExFilter<EVR_IS>::New(dicomifier::translator::
                                 ConstantField<EVR_IS>::New(25), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterIS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterIS->get_array();
    BOOST_CHECK_EQUAL(results[0], 25);
}

/*************************** TEST OK 11 *******************************/
/**
 * Nominal test case: Run VR = LO
 */
BOOST_AUTO_TEST_CASE(TEST_OK_11)
{
    auto regexfilterLO = dicomifier::translator::
        RegExFilter<EVR_LO>::New(dicomifier::translator::
                                 ConstantField<EVR_LO>::New("MY_LOTITLE_TEST"), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterLO->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterLO->get_array();
    BOOST_CHECK_EQUAL(results[0], "LOTITLE");
}

/*************************** TEST OK 12 *******************************/
/**
 * Nominal test case: Run VR = LT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_12)
{
    auto regexfilterLT = dicomifier::translator::
        RegExFilter<EVR_LT>::New(dicomifier::translator::
                                 ConstantField<EVR_LT>::New("MY_LTTITLE_TEST"), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterLT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterLT->get_array();
    BOOST_CHECK_EQUAL(results[0], "LTTITLE");
}

/*************************** TEST OK 13 *******************************/
/**
 * Nominal test case: Run VR = PN
 */
BOOST_AUTO_TEST_CASE(TEST_OK_13)
{
    auto regexfilterPN = dicomifier::translator::
        RegExFilter<EVR_PN>::New(dicomifier::translator::
                                 ConstantField<EVR_PN>::New("MY_PNTITLE_TEST"), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterPN->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterPN->get_array();
    BOOST_CHECK_EQUAL(results[0], "PNTITLE");
}

/*************************** TEST OK 14 *******************************/
/**
 * Nominal test case: Run VR = SH
 */
BOOST_AUTO_TEST_CASE(TEST_OK_14)
{
    auto regexfilterSH = dicomifier::translator::
        RegExFilter<EVR_SH>::New(dicomifier::translator::
                                 ConstantField<EVR_SH>::New("MY_SHTITLE_TEST"), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterSH->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterSH->get_array();
    BOOST_CHECK_EQUAL(results[0], "SHTITLE");
}

/*************************** TEST OK 15 *******************************/
/**
 * Nominal test case: Run VR = SL
 */
BOOST_AUTO_TEST_CASE(TEST_OK_15)
{
    auto regexfilterSL = dicomifier::translator::
        RegExFilter<EVR_SL>::New(dicomifier::translator::
                                 ConstantField<EVR_SL>::New(25), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterSL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterSL->get_array();
    BOOST_CHECK_EQUAL(results[0], 25);
}

/*************************** TEST OK 16 *******************************/
/**
 * Nominal test case: Run VR = SS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_16)
{
    auto regexfilterSS = dicomifier::translator::
        RegExFilter<EVR_SS>::New(dicomifier::translator::
                                 ConstantField<EVR_SS>::New(25), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterSS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterSS->get_array();
    BOOST_CHECK_EQUAL(results[0], 25);
}

/*************************** TEST OK 17 *******************************/
/**
 * Nominal test case: Run VR = ST
 */
BOOST_AUTO_TEST_CASE(TEST_OK_17)
{
    auto regexfilterST = dicomifier::translator::
        RegExFilter<EVR_ST>::New(dicomifier::translator::
                                 ConstantField<EVR_ST>::New("MY_STTITLE_TEST"), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterST->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterST->get_array();
    BOOST_CHECK_EQUAL(results[0], "STTITLE");
}

/*************************** TEST OK 18 *******************************/
/**
 * Nominal test case: Run VR = TM
 */
BOOST_AUTO_TEST_CASE(TEST_OK_18)
{
    auto regexfilterTM = dicomifier::translator::
        RegExFilter<EVR_TM>::New(dicomifier::translator::
                                 ConstantField<EVR_TM>::New("MY_TMTITLE_TEST"), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterTM->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterTM->get_array();
    BOOST_CHECK_EQUAL(results[0], "TMTITLE");
}

/*************************** TEST OK 19 *******************************/
/**
 * Nominal test case: Run VR = UI
 */
BOOST_AUTO_TEST_CASE(TEST_OK_19)
{
    auto regexfilterUI = dicomifier::translator::
        RegExFilter<EVR_UI>::New(dicomifier::translator::
                                 ConstantField<EVR_UI>::New("MY_UITITLE_TEST"), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterUI->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterUI->get_array();
    BOOST_CHECK_EQUAL(results[0], "UITITLE");
}

/*************************** TEST OK 20 *******************************/
/**
 * Nominal test case: Run VR = UL
 */
BOOST_AUTO_TEST_CASE(TEST_OK_20)
{
    auto regexfilterUL = dicomifier::translator::
        RegExFilter<EVR_UL>::New(dicomifier::translator::
                                 ConstantField<EVR_UL>::New(25), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterUL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterUL->get_array();
    BOOST_CHECK_EQUAL(results[0], 25);
}

/*************************** TEST OK 21 *******************************/
/**
 * Nominal test case: Run VR = US
 */
BOOST_AUTO_TEST_CASE(TEST_OK_21)
{
    auto regexfilterUS = dicomifier::translator::
        RegExFilter<EVR_US>::New(dicomifier::translator::
                                 ConstantField<EVR_US>::New(25), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterUS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterUS->get_array();
    BOOST_CHECK_EQUAL(results[0], 25);
}

/*************************** TEST OK 22 *******************************/
/**
 * Nominal test case: Run VR = UT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_22)
{
    auto regexfilterUT = dicomifier::translator::
        RegExFilter<EVR_UT>::New(dicomifier::translator::
                                 ConstantField<EVR_UT>::New("MY_UTTITLE_TEST"), 
                                                            "^.*_{1}(.*)_{1}.*");
    regexfilterUT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = regexfilterUT->get_array();
    BOOST_CHECK_EQUAL(results[0], "UTTITLE");
}
