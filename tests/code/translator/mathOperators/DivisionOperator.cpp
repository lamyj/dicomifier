/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDivisionOperator
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/mathOperators/DivisionOperator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::DivisionOperator<EVR_AE>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::DivisionOperator<EVR_AS>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::DivisionOperator<EVR_CS>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::DivisionOperator<EVR_DA>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::DivisionOperator<EVR_DS>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::DivisionOperator<EVR_DT>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::DivisionOperator<EVR_FL>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::DivisionOperator<EVR_FD>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::DivisionOperator<EVR_IS>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::DivisionOperator<EVR_LO>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::DivisionOperator<EVR_LT>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::DivisionOperator<EVR_PN>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::DivisionOperator<EVR_SH>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::DivisionOperator<EVR_SL>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::DivisionOperator<EVR_SS>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::DivisionOperator<EVR_ST>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::DivisionOperator<EVR_TM>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::DivisionOperator<EVR_UI>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::DivisionOperator<EVR_UL>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::DivisionOperator<EVR_US>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::DivisionOperator<EVR_UT>::New();
    // Pointer exists and class type is DivisionOperator
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_DivisionOperator);
}
 
/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run VR = AE
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_AE>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_AE>::New("World"));
    
    auto divisionoperatorae = dicomifier::translator::DivisionOperator<EVR_AE>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorae->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run VR = AS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_AS>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_AS>::New("World"));
    
    auto divisionoperatoras = dicomifier::translator::DivisionOperator<EVR_AS>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatoras->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Run VR = CS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_CS>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_CS>::New("World"));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_CS>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Run VR = DA
 */
BOOST_AUTO_TEST_CASE(TEST_OK_05)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_DA>::New("01232014"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_DA>::New("01232014"));
    
    auto divisionoperatorda = dicomifier::translator::DivisionOperator<EVR_DA>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorda->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Run VR = DS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_06)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_DS>::New(2.5));
    vect.push_back(dicomifier::translator::ConstantField<EVR_DS>::New(2));
    
    auto divisionoperatords = dicomifier::translator::DivisionOperator<EVR_DS>::New(vect);
    divisionoperatords->run(NULL, {}, NULL);
    auto results = divisionoperatords->get_array();
    BOOST_CHECK_EQUAL(results[0], (Float64)(1.25));
}

/*************************** TEST OK 07 *******************************/
/**
 * Nominal test case: Run VR = DT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_07)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_DT>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_DT>::New("World"));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_DT>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 08 *******************************/
/**
 * Nominal test case: Run VR = FL
 */
BOOST_AUTO_TEST_CASE(TEST_OK_08)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_FL>::New((Float32)33));
    vect.push_back(dicomifier::translator::ConstantField<EVR_FL>::New((Float32)11));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_FL>::New(vect);
    divisionoperatorcs->run(NULL, {}, NULL);
    auto results = divisionoperatorcs->get_array();
    BOOST_CHECK_EQUAL(results[0], (Float32)(3));
}

/*************************** TEST OK 09 *******************************/
/**
 * Nominal test case: Run VR = FD
 */
BOOST_AUTO_TEST_CASE(TEST_OK_09)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_FD>::New(2.5));
    vect.push_back(dicomifier::translator::ConstantField<EVR_FD>::New(2));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_FD>::New(vect);
    divisionoperatorcs->run(NULL, {}, NULL);
    auto results = divisionoperatorcs->get_array();
    BOOST_CHECK_EQUAL(results[0], (Float64)1.25);
}

/*************************** TEST OK 10 *******************************/
/**
 * Nominal test case: Run VR = IS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_10)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_IS>::New(33));
    vect.push_back(dicomifier::translator::ConstantField<EVR_IS>::New(11));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_IS>::New(vect);
    divisionoperatorcs->run(NULL, {}, NULL);
    auto results = divisionoperatorcs->get_array();
    BOOST_CHECK_EQUAL(results[0], (Sint32)3);
}

/*************************** TEST OK 11 *******************************/
/**
 * Nominal test case: Run VR = LO
 */
BOOST_AUTO_TEST_CASE(TEST_OK_11)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_LO>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_LO>::New("World"));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_LO>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 12 *******************************/
/**
 * Nominal test case: Run VR = LT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_12)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_LT>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_LT>::New("World"));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_LT>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 13 *******************************/
/**
 * Nominal test case: Run VR = PN
 */
BOOST_AUTO_TEST_CASE(TEST_OK_13)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_PN>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_PN>::New("World"));
    
    auto divisionoperatorpn = dicomifier::translator::DivisionOperator<EVR_PN>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorpn->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 14 *******************************/
/**
 * Nominal test case: Run VR = SH
 */
BOOST_AUTO_TEST_CASE(TEST_OK_14)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_SH>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_SH>::New("World"));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_SH>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 15 *******************************/
/**
 * Nominal test case: Run VR = SL
 */
BOOST_AUTO_TEST_CASE(TEST_OK_15)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_SL>::New(33));
    vect.push_back(dicomifier::translator::ConstantField<EVR_SL>::New(11));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_SL>::New(vect);
    divisionoperatorcs->run(NULL, {}, NULL);
    auto results = divisionoperatorcs->get_array();
    BOOST_CHECK_EQUAL(results[0], (Sint32)3);
}

/*************************** TEST OK 16 *******************************/
/**
 * Nominal test case: Run VR = SS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_16)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_SS>::New(33));
    vect.push_back(dicomifier::translator::ConstantField<EVR_SS>::New(11));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_SS>::New(vect);
    divisionoperatorcs->run(NULL, {}, NULL);
    auto results = divisionoperatorcs->get_array();
    BOOST_CHECK_EQUAL(results[0], (Sint16)3);
}

/*************************** TEST OK 17 *******************************/
/**
 * Nominal test case: Run VR = ST
 */
BOOST_AUTO_TEST_CASE(TEST_OK_17)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_ST>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_ST>::New("World"));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_ST>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 18 *******************************/
/**
 * Nominal test case: Run VR = TM
 */
BOOST_AUTO_TEST_CASE(TEST_OK_18)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_TM>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_TM>::New("World"));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_TM>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 19 *******************************/
/**
 * Nominal test case: Run VR = UI
 */
BOOST_AUTO_TEST_CASE(TEST_OK_19)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_UI>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_UI>::New("World"));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_UI>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST OK 20 *******************************/
/**
 * Nominal test case: Run VR = UL
 */
BOOST_AUTO_TEST_CASE(TEST_OK_20)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_UL>::New(33));
    vect.push_back(dicomifier::translator::ConstantField<EVR_UL>::New(11));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_UL>::New(vect);
    divisionoperatorcs->run(NULL, {}, NULL);
    auto results = divisionoperatorcs->get_array();
    BOOST_CHECK_EQUAL(results[0], (Uint32)3);
}

/*************************** TEST OK 21 *******************************/
/**
 * Nominal test case: Run VR = US
 */
BOOST_AUTO_TEST_CASE(TEST_OK_21)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_US>::New(33));
    vect.push_back(dicomifier::translator::ConstantField<EVR_US>::New(11));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_US>::New(vect);
    divisionoperatorcs->run(NULL, {}, NULL);
    auto results = divisionoperatorcs->get_array();
    BOOST_CHECK_EQUAL(results[0], (Uint16)3);
}

/*************************** TEST OK 22 *******************************/
/**
 * Nominal test case: Run VR = UT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_22)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_UT>::New("Hello"));
    vect.push_back(dicomifier::translator::ConstantField<EVR_UT>::New("World"));
    
    auto divisionoperatorcs = dicomifier::translator::DivisionOperator<EVR_UT>::New(vect);
    BOOST_REQUIRE_THROW(divisionoperatorcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Differents size
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::ConstantField<EVR_DS>::New({11.11, 11.11}));
    vect.push_back(dicomifier::translator::ConstantField<EVR_DS>::New(22.22));
    
    auto divisionoperatords = dicomifier::translator::DivisionOperator<EVR_DS>::New(vect);
    
    BOOST_REQUIRE_THROW(divisionoperatords->run(NULL, {}, NULL), dicomifier::DicomifierException);
}
