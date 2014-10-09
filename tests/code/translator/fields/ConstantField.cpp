/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleConstantField
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::ConstantField<EVR_AE>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::ConstantField<EVR_AS>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ConstantField<EVR_CS>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::ConstantField<EVR_DA>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::ConstantField<EVR_DS>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::ConstantField<EVR_DT>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::ConstantField<EVR_FL>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::ConstantField<EVR_FD>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::ConstantField<EVR_IS>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::ConstantField<EVR_LO>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::ConstantField<EVR_LT>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::ConstantField<EVR_PN>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::ConstantField<EVR_SH>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::ConstantField<EVR_SL>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::ConstantField<EVR_SS>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::ConstantField<EVR_ST>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::ConstantField<EVR_TM>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::ConstantField<EVR_UI>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::ConstantField<EVR_UL>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::ConstantField<EVR_US>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_ConstantField);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::ConstantField<EVR_UT>::New();
    // Pointer exists and class type is ConstantField
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_ConstantField);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run with single value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::ConstantField<EVR_AE>::New("AB");
    testfieldae->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldae->get_array().size(), 1);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::ConstantField<EVR_AS>::New("42Y");
    testfieldas->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldas->get_array().size(), 1);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ConstantField<EVR_CS>::New("MR");
    testfieldcs->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::ConstantField<EVR_DA>::New("12122012");
    testfieldda->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldda->get_array().size(), 1);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::ConstantField<EVR_DS>::New(75.57);
    testfieldds->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldds->get_array().size(), 1);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::ConstantField<EVR_DT>::New("01234501122012");
    testfielddt->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfielddt->get_array().size(), 1);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::ConstantField<EVR_FL>::New(1.23);
    testfieldfl->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldfl->get_array().size(), 1);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::ConstantField<EVR_FD>::New(1.23);
    testfieldfd->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldfd->get_array().size(), 1);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::ConstantField<EVR_IS>::New(123);
    testfieldis->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldis->get_array().size(), 1);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::ConstantField<EVR_LO>::New("BRUKER");
    testfieldlo->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldlo->get_array().size(), 1);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::ConstantField<EVR_LT>::New("ABCD");
    testfieldlt->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldlt->get_array().size(), 1);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::ConstantField<EVR_PN>::New("NAME");
    testfieldpn->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldpn->get_array().size(), 1);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::ConstantField<EVR_SH>::New("12345");
    testfieldsh->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldsh->get_array().size(), 1);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::ConstantField<EVR_SL>::New(-123456789);
    testfieldsl->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldsl->get_array().size(), 1);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::ConstantField<EVR_SS>::New(-123);
    testfieldss->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldss->get_array().size(), 1);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::ConstantField<EVR_ST>::New("abcde");
    testfieldst->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldst->get_array().size(), 1);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::ConstantField<EVR_TM>::New("012345");
    testfieldtm->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldtm->get_array().size(), 1);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::ConstantField<EVR_UI>::New("12345");
    testfieldui->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldui->get_array().size(), 1);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::ConstantField<EVR_UL>::New(1234567890);
    testfieldul->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldul->get_array().size(), 1);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::ConstantField<EVR_US>::New(456);
    testfieldus->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 1);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::ConstantField<EVR_UT>::New("abcde");
    testfieldut->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldut->get_array().size(), 1);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run with multiple values
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::ConstantField<EVR_AE>::New({"AB", "CD"});
    testfieldae->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldae->get_array().size(), 2);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::ConstantField<EVR_AS>::New({"AB", "CD"});
    testfieldas->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldas->get_array().size(), 2);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ConstantField<EVR_CS>::New({"AB", "CD"});
    testfieldcs->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 2);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::ConstantField<EVR_DA>::New({"12122012", "12122013"});
    testfieldda->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldda->get_array().size(), 2);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::ConstantField<EVR_DS>::New({1.23, -4.56});
    testfieldds->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldds->get_array().size(), 2);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::ConstantField<EVR_DT>::New({"01234501122012", "01234501122013"});
    testfielddt->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfielddt->get_array().size(), 2);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::ConstantField<EVR_FL>::New({(Float32)(1.23), (Float32)(-4.56)});
    testfieldfl->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldfl->get_array().size(), 2);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::ConstantField<EVR_FD>::New({1.23, -4.56});
    testfieldfd->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldfd->get_array().size(), 2);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::ConstantField<EVR_IS>::New({123, -456});
    testfieldis->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldis->get_array().size(), 2);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::ConstantField<EVR_LO>::New({"AB", "CD"});
    testfieldlo->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldlo->get_array().size(), 2);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::ConstantField<EVR_LT>::New({"AB", "CD"});
    testfieldlt->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldlt->get_array().size(), 2);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::ConstantField<EVR_PN>::New({"AB", "CD"});
    testfieldpn->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldpn->get_array().size(), 2);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::ConstantField<EVR_SH>::New({"1234", "5678"});
    testfieldsh->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldsh->get_array().size(), 2);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::ConstantField<EVR_SL>::New({-123456789, 12345678});
    testfieldsl->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldsl->get_array().size(), 2);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::ConstantField<EVR_SS>::New({-1, 2, -3});
    testfieldss->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldss->get_array().size(), 3);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::ConstantField<EVR_ST>::New({"abcde", "fghij"});
    testfieldst->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldst->get_array().size(), 2);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::ConstantField<EVR_TM>::New({"012345", "022345"});
    testfieldtm->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldtm->get_array().size(), 2);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::ConstantField<EVR_UI>::New({"1234", "5678"});
    testfieldui->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldui->get_array().size(), 2);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::ConstantField<EVR_UL>::New({1234567890, 1234567891});
    testfieldul->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldul->get_array().size(), 2);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::ConstantField<EVR_US>::New({456, 789});
    testfieldus->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 2);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::ConstantField<EVR_UT>::New({"abcde", "fghij"});
    testfieldut->run(NULL, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldut->get_array().size(), 2);
}
