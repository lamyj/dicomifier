/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDateTimeFilter
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/filters/DateTimeFilter.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::DateTimeFilter<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldae != NULL, true);

    // Test VR = AS
    auto testfieldas = dicomifier::translator::DateTimeFilter<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldas != NULL, true);

    // Test VR = AT
    auto testfieldat = dicomifier::translator::DateTimeFilter<EVR_AT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldat != NULL, true);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::DateTimeFilter<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldcs != NULL, true);

    // Test VR = DA
    auto testfieldda = dicomifier::translator::DateTimeFilter<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldda != NULL, true);

    // Test VR = DS
    auto testfieldds = dicomifier::translator::DateTimeFilter<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldds != NULL, true);

    // Test VR = DT
    auto testfielddt = dicomifier::translator::DateTimeFilter<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfielddt != NULL, true);

    // Test VR = FL
    auto testfieldfl = dicomifier::translator::DateTimeFilter<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfl != NULL, true);

    // Test VR = FD
    auto testfieldfd = dicomifier::translator::DateTimeFilter<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfd != NULL, true);

    // Test VR = IS
    auto testfieldis = dicomifier::translator::DateTimeFilter<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldis != NULL, true);

    // Test VR = LO
    auto testfieldlo = dicomifier::translator::DateTimeFilter<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlo != NULL, true);

    // Test VR = LT
    auto testfieldlt = dicomifier::translator::DateTimeFilter<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlt != NULL, true);

    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented

    // Test VR = PN
    auto testfieldpn = dicomifier::translator::DateTimeFilter<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldpn != NULL, true);

    // Test VR = SH
    auto testfieldsh = dicomifier::translator::DateTimeFilter<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsh != NULL, true);

    // Test VR = SL
    auto testfieldsl = dicomifier::translator::DateTimeFilter<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsl != NULL, true);

    // Test VR = SQ => Not implemented

    // Test VR = SS
    auto testfieldss = dicomifier::translator::DateTimeFilter<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldss != NULL, true);

    // Test VR = ST
    auto testfieldst = dicomifier::translator::DateTimeFilter<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldst != NULL, true);

    // Test VR = TM
    auto testfieldtm = dicomifier::translator::DateTimeFilter<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldtm != NULL, true);

    // Test VR = UI
    auto testfieldui = dicomifier::translator::DateTimeFilter<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldui != NULL, true);

    // Test VR = UL
    auto testfieldul = dicomifier::translator::DateTimeFilter<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldul != NULL, true);

    // Test VR = UN => Not implemented

    // Test VR = US
    auto testfieldus = dicomifier::translator::DateTimeFilter<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldus != NULL, true);

    // Test VR = UT
    auto testfieldut = dicomifier::translator::DateTimeFilter<EVR_UT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldut != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run VR = AE
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto datetimefilterAE = dicomifier::translator::
        DateTimeFilter<EVR_AE>::New(dicomifier::translator::
                                 ConstantField<EVR_AE>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%H%M%S");
    datetimefilterAE->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterAE->get_array();
    BOOST_CHECK_EQUAL(results[0], "140912");
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run VR = AS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    auto datetimefilterAS = dicomifier::translator::
        DateTimeFilter<EVR_AS>::New(dicomifier::translator::
                                    ConstantField<EVR_AS>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%H%M");
    datetimefilterAS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterAS->get_array();
    BOOST_CHECK_EQUAL(results[0], "1409");
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Run VR = CS
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    auto datetimefilterCS = dicomifier::translator::
        DateTimeFilter<EVR_CS>::New(dicomifier::translator::
                                    ConstantField<EVR_CS>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%H%M%S");
    datetimefilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "140912");
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Run VR = DA
 */
BOOST_AUTO_TEST_CASE(TEST_OK_05)
{
    auto datetimefilterDA = dicomifier::translator::
        DateTimeFilter<EVR_DA>::New(dicomifier::translator::
                                    ConstantField<EVR_DA>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%Y%m%d");
    datetimefilterDA->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterDA->get_array();
    BOOST_CHECK_EQUAL(results[0], "20150115");
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Run VR = DT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_06)
{
    auto datetimefilterDT = dicomifier::translator::
        DateTimeFilter<EVR_DT>::New(dicomifier::translator::
                                    ConstantField<EVR_DT>::New("2015-01-15T14:09:12,490+0100"),
                                                               "%Y%m%d%H%M%S");
    datetimefilterDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterDT->get_array();
    BOOST_CHECK_EQUAL(results[0], "20150115140912");

    datetimefilterDT = dicomifier::translator::
        DateTimeFilter<EVR_DT>::New(dicomifier::translator::
                                    ConstantField<EVR_DT>::New("14:09:12 15 Jan 2015"),
                                                               "%Y%m%d%H%M%S");
    datetimefilterDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = datetimefilterDT->get_array();
    BOOST_CHECK_EQUAL(results[0], "20150115140912");

    datetimefilterDT = dicomifier::translator::
        DateTimeFilter<EVR_DT>::New(dicomifier::translator::
                                    ConstantField<EVR_DT>::New("14:09:12  6 Jan 2015"),
                                                               "%Y%m%d%H%M%S");
    datetimefilterDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = datetimefilterDT->get_array();
    BOOST_CHECK_EQUAL(results[0], "20150106140912");
}

/*************************** TEST OK 07 *******************************/
/**
 * Nominal test case: Run VR = LO
 */
BOOST_AUTO_TEST_CASE(TEST_OK_07)
{
    auto datetimefilterLO = dicomifier::translator::
        DateTimeFilter<EVR_LO>::New(dicomifier::translator::
                                 ConstantField<EVR_LO>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%Y%m");
    datetimefilterLO->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterLO->get_array();
    BOOST_CHECK_EQUAL(results[0], "201501");
}

/*************************** TEST OK 08 *******************************/
/**
 * Nominal test case: Run VR = LT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_08)
{
    auto datetimefilterLT = dicomifier::translator::
        DateTimeFilter<EVR_LT>::New(dicomifier::translator::
                                 ConstantField<EVR_LT>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%Y%m%d %H:%M:%S");
    datetimefilterLT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterLT->get_array();
    BOOST_CHECK_EQUAL(results[0], "20150115 14:09:12");
}

/*************************** TEST OK 09 *******************************/
/**
 * Nominal test case: Run VR = PN
 */
BOOST_AUTO_TEST_CASE(TEST_OK_09)
{
    auto datetimefilterPN = dicomifier::translator::
        DateTimeFilter<EVR_PN>::New(dicomifier::translator::
                                 ConstantField<EVR_PN>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%Y^%m");
    datetimefilterPN->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterPN->get_array();
    BOOST_CHECK_EQUAL(results[0], "2015^01");
}

/*************************** TEST OK 10 *******************************/
/**
 * Nominal test case: Run VR = SH
 */
BOOST_AUTO_TEST_CASE(TEST_OK_10)
{
    auto datetimefilterSH = dicomifier::translator::
        DateTimeFilter<EVR_SH>::New(dicomifier::translator::
                                 ConstantField<EVR_SH>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%Y-%m-%d");
    datetimefilterSH->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterSH->get_array();
    BOOST_CHECK_EQUAL(results[0], "2015-01-15");
}

/*************************** TEST OK 11 *******************************/
/**
 * Nominal test case: Run VR = ST
 */
BOOST_AUTO_TEST_CASE(TEST_OK_11)
{
    auto datetimefilterST = dicomifier::translator::
        DateTimeFilter<EVR_ST>::New(dicomifier::translator::
                                 ConstantField<EVR_ST>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%Y%m%d");
    datetimefilterST->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterST->get_array();
    BOOST_CHECK_EQUAL(results[0], "20150115");
}

/*************************** TEST OK 12 *******************************/
/**
 * Nominal test case: Run VR = TM
 */
BOOST_AUTO_TEST_CASE(TEST_OK_12)
{
    auto datetimefilterTM = dicomifier::translator::
        DateTimeFilter<EVR_TM>::New(dicomifier::translator::
                                 ConstantField<EVR_TM>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%H%M%S");
    datetimefilterTM->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterTM->get_array();
    BOOST_CHECK_EQUAL(results[0], "140912");
}

/*************************** TEST OK 13 *******************************/
/**
 * Nominal test case: Run VR = UI
 */
BOOST_AUTO_TEST_CASE(TEST_OK_13)
{
    auto datetimefilterUI = dicomifier::translator::
        DateTimeFilter<EVR_UI>::New(dicomifier::translator::
                                 ConstantField<EVR_UI>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%H.%M.%S");
    datetimefilterUI->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterUI->get_array();
    BOOST_CHECK_EQUAL(results[0], "14.09.12");
}

/*************************** TEST OK 14 *******************************/
/**
 * Nominal test case: Run VR = UT
 */
BOOST_AUTO_TEST_CASE(TEST_OK_14)
{
    auto datetimefilterUT = dicomifier::translator::
        DateTimeFilter<EVR_UT>::New(dicomifier::translator::
                                 ConstantField<EVR_UT>::New("2015-01-15T14:09:12,490+0100"),
                                                            "%Y-%H");
    datetimefilterUT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = datetimefilterUT->get_array();
    BOOST_CHECK_EQUAL(results[0], "2015-14");
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: No subtag
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto datetimefilterDT = dicomifier::translator::
        DateTimeFilter<EVR_DT>::New(NULL, "%Y%m%d%H%M%S");
    BOOST_REQUIRE_THROW(datetimefilterDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Unrecognized input format
 */
BOOST_AUTO_TEST_CASE(TEST_KO_02)
{
    auto datetimefilterDT = dicomifier::translator::
        DateTimeFilter<EVR_DT>::New(dicomifier::translator::
                                    ConstantField<EVR_DT>::New("2015...01...15"),
                                    "%Y%m%d%");
    BOOST_REQUIRE_THROW(datetimefilterDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: VR not allowed
 */
BOOST_AUTO_TEST_CASE(TEST_KO_03)
{
    // Test VR = DS
    auto datetimefilterDS = dicomifier::translator::
            DateTimeFilter<EVR_DS>::New(NULL, "%Y%m%d%H%M%S");
    BOOST_REQUIRE_THROW(datetimefilterDS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = FL
    auto datetimefilterFL = dicomifier::translator::
            DateTimeFilter<EVR_FL>::New(NULL, "%Y%m%d%H%M%S");
    BOOST_REQUIRE_THROW(datetimefilterFL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = FD
    auto datetimefilterFD = dicomifier::translator::
            DateTimeFilter<EVR_FD>::New(NULL, "%Y%m%d%H%M%S");
    BOOST_REQUIRE_THROW(datetimefilterFD->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = IS
    auto datetimefilterIS = dicomifier::translator::
            DateTimeFilter<EVR_IS>::New(NULL, "%Y%m%d%H%M%S");
    BOOST_REQUIRE_THROW(datetimefilterIS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = SL
    auto datetimefilterSL = dicomifier::translator::
            DateTimeFilter<EVR_SL>::New(NULL, "%Y%m%d%H%M%S");
    BOOST_REQUIRE_THROW(datetimefilterSL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = SS
    auto datetimefilterSS = dicomifier::translator::
            DateTimeFilter<EVR_SS>::New(NULL, "%Y%m%d%H%M%S");
    BOOST_REQUIRE_THROW(datetimefilterSS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = SQ => Not implemented

    // Test VR = UL
    auto datetimefilterUL = dicomifier::translator::
            DateTimeFilter<EVR_UL>::New(NULL, "%Y%m%d%H%M%S");
    BOOST_REQUIRE_THROW(datetimefilterUL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);

    // Test VR = US
    auto datetimefilterUS = dicomifier::translator::
            DateTimeFilter<EVR_US>::New(NULL, "%Y%m%d%H%M%S");
    BOOST_REQUIRE_THROW(datetimefilterUS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL),
                        dicomifier::DicomifierException);
}
