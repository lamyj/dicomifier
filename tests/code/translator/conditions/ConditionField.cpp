/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerFieldExist
#include <boost/test/unit_test.hpp>

#include "translator/conditions/ConditionField.h"
#include "translator/conditions/AlwaysTrue.h"
#include "translator/conditions/AlwaysFalse.h"
#include "translator/fields/ConstantField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::ConditionField<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldae != NULL, true);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::ConditionField<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldas != NULL, true);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ConditionField<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldcs != NULL, true);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::ConditionField<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldda != NULL, true);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::ConditionField<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldds != NULL, true);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::ConditionField<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfielddt != NULL, true);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::ConditionField<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfl != NULL, true);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::ConditionField<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfd != NULL, true);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::ConditionField<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldis != NULL, true);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::ConditionField<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlo != NULL, true);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::ConditionField<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlt != NULL, true);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::ConditionField<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldpn != NULL, true);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::ConditionField<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsh != NULL, true);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::ConditionField<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsl != NULL, true);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::ConditionField<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldss != NULL, true);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::ConditionField<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldst != NULL, true);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::ConditionField<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldtm != NULL, true);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::ConditionField<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldui != NULL, true);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::ConditionField<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldul != NULL, true);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::ConditionField<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldus != NULL, true);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::ConditionField<EVR_UT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldut != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run VR = AE
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_AE>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_AE>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_AE>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_AE>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_AE>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_AE>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run VR = AS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_AS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_AS>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_AS>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_AS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_AS>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_AS>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Run VR = CS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_CS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_CS>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_CS>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_CS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_CS>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_CS>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Run VR = DA
 */
BOOST_AUTO_TEST_CASE(TEST_OK_05)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_DA>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_DA>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_DA>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_DA>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_DA>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_DA>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Run VR = DS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_06)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_DS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_DS>::New(11.11),
            dicomifier::translator::ConstantField<EVR_DS>::New(22.22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Float64)11.11);
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_DS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_DS>::New(11.11),
            dicomifier::translator::ConstantField<EVR_DS>::New(22.22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Float64)22.22);
}

/*************************** TEST OK 07 *******************************/
/**
 * Nominal test case: Run VR = DT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_07)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_DT>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_DT>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_DT>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_DT>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_DT>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_DT>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 08 *******************************/
/**
 * Nominal test case: Run VR = FL
 */
BOOST_AUTO_TEST_CASE(TEST_OK_08)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_FL>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_FL>::New((Float32)11),
            dicomifier::translator::ConstantField<EVR_FL>::New((Float32)22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Float32)11);
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_FL>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_FL>::New((Float32)11),
            dicomifier::translator::ConstantField<EVR_FL>::New((Float32)22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Float32)22);
}

/*************************** TEST OK 09 *******************************/
/**
 * Nominal test case: Run VR = FD
 */
BOOST_AUTO_TEST_CASE(TEST_OK_09)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_FD>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_FD>::New(11.11),
            dicomifier::translator::ConstantField<EVR_FD>::New(22.22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Float64)11.11);
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_FD>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_FD>::New(11.11),
            dicomifier::translator::ConstantField<EVR_FD>::New(22.22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Float64)22.22);
}

/*************************** TEST OK 10 *******************************/
/**
 * Nominal test case: Run VR = IS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_10)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_IS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_IS>::New(11),
            dicomifier::translator::ConstantField<EVR_IS>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Sint32)11);
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_IS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_IS>::New(11),
            dicomifier::translator::ConstantField<EVR_IS>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Sint32)22);
}

/*************************** TEST OK 11 *******************************/
/**
 * Nominal test case: Run VR = LO
 */
BOOST_AUTO_TEST_CASE(TEST_OK_11)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_LO>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_LO>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_LO>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_LO>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_LO>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_LO>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 12 *******************************/
/**
 * Nominal test case: Run VR = LT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_12)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_LT>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_LT>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_LT>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_LT>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_LT>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_LT>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 13 *******************************/
/**
 * Nominal test case: Run VR = PN
 */
BOOST_AUTO_TEST_CASE(TEST_OK_13)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_PN>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_PN>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_PN>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_PN>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_PN>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_PN>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 14 *******************************/
/**
 * Nominal test case: Run VR = SH
 */
BOOST_AUTO_TEST_CASE(TEST_OK_14)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_SH>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_SH>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_SH>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_SH>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_SH>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_SH>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 15 *******************************/
/**
 * Nominal test case: Run VR = SL
 */
BOOST_AUTO_TEST_CASE(TEST_OK_15)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_SL>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_SL>::New(11),
            dicomifier::translator::ConstantField<EVR_SL>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Sint32)11);
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_SL>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_SL>::New(11),
            dicomifier::translator::ConstantField<EVR_SL>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Sint32)22);
}

/*************************** TEST OK 16 *******************************/
/**
 * Nominal test case: Run VR = SS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_16)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_SS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_SS>::New(11),
            dicomifier::translator::ConstantField<EVR_SS>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Sint16)11);
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_SS>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_SS>::New(11),
            dicomifier::translator::ConstantField<EVR_SS>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Sint16)22);
}

/*************************** TEST OK 17 *******************************/
/**
 * Nominal test case: Run VR = ST
 */
BOOST_AUTO_TEST_CASE(TEST_OK_17)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_ST>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_ST>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_ST>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_ST>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_ST>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_ST>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 18 *******************************/
/**
 * Nominal test case: Run VR = TM
 */
BOOST_AUTO_TEST_CASE(TEST_OK_18)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_TM>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_TM>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_TM>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_TM>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_TM>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_TM>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 19 *******************************/
/**
 * Nominal test case: Run VR = UI
 */
BOOST_AUTO_TEST_CASE(TEST_OK_19)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_UI>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_UI>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_UI>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_UI>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_UI>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_UI>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}

/*************************** TEST OK 20 *******************************/
/**
 * Nominal test case: Run VR = UL
 */
BOOST_AUTO_TEST_CASE(TEST_OK_20)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_UL>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_UL>::New(11),
            dicomifier::translator::ConstantField<EVR_UL>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Uint32)11);
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_UL>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_UL>::New(11),
            dicomifier::translator::ConstantField<EVR_UL>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Uint32)22);
}

/*************************** TEST OK 21 *******************************/
/**
 * Nominal test case: Run VR = US
 */
BOOST_AUTO_TEST_CASE(TEST_OK_21)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_US>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_US>::New(11),
            dicomifier::translator::ConstantField<EVR_US>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Uint16)11);
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_US>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_US>::New(11),
            dicomifier::translator::ConstantField<EVR_US>::New(22));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], (Uint16)22);
}

/*************************** TEST OK 22 *******************************/
/**
 * Nominal test case: Run VR = UT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_22)
{
    std::vector<dicomifier::translator::Tag::Pointer> vect;
    vect.push_back(dicomifier::translator::AlwaysTrue::New());
    
    auto conditionfieldae = dicomifier::translator::ConditionField<EVR_UT>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_UT>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_UT>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "Hello");
    
    vect.push_back(dicomifier::translator::AlwaysFalse::New());
    
    conditionfieldae = dicomifier::translator::ConditionField<EVR_UT>::
        New(vect,
            dicomifier::translator::ConstantField<EVR_UT>::New("Hello"),
            dicomifier::translator::ConstantField<EVR_UT>::New("World"));
            
    conditionfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = conditionfieldae->get_array();
    BOOST_CHECK_EQUAL(results[0], "World");
}
