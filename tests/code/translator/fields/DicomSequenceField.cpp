/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDicomSequenceField
#include <boost/test/unit_test.hpp>

#include "translator/fields/DicomSequenceField.h"
#include "translator/fields/TestField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = SQ
    auto testfieldae = dicomifier::translator::DicomSequenceField::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldae != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run (per frame)
 */
struct TestDataOK02
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset* dataset;
 
    TestDataOK02()
    {
        dataset = new DcmDataset();
    }
 
    ~TestDataOK02()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    // Test VR = SQ
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::
            DicomSequenceField::New(tagandrange, {}, true);
    testfieldSQ->run(NULL, dicomifier::FrameIndexGenerator({}), dataset);
    BOOST_CHECK_EQUAL(dataset->tagExists(tagandrange._tag), true);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run Sequence with subtag (per frame)
 */
struct TestDataOK03
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset* dataset;

    TestDataOK03()
    {
        dataset = new DcmDataset();
    }

    ~TestDataOK03()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    // Test VR = SQ
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::
            DicomSequenceField::New(tagandrange, {dicomifier::translator::TestField::New()}, true);
    testfieldSQ->run(NULL, dicomifier::FrameIndexGenerator({}), dataset);
    BOOST_CHECK_EQUAL(dataset->tagExists(tagandrange._tag), true);
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Run (One Frame)
 */
struct TestDataOK04
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset* dataset;

    TestDataOK04()
    {
        dataset = new DcmDataset();
    }

    ~TestDataOK04()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
{
    // Test VR = SQ
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::
            DicomSequenceField::New(tagandrange, {}, false);
    testfieldSQ->run(NULL, dicomifier::FrameIndexGenerator({}), dataset);
    BOOST_CHECK_EQUAL(dataset->tagExists(tagandrange._tag), true);
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Run Sequence with subtag (per frame)
 */
struct TestDataOK05
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset* dataset;

    TestDataOK05()
    {
        dataset = new DcmDataset();
    }

    ~TestDataOK05()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_05, TestDataOK05)
{
    // Test VR = SQ
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::
            DicomSequenceField::New(tagandrange, {dicomifier::translator::TestField::New()}, false);
    testfieldSQ->run(NULL, dicomifier::FrameIndexGenerator({}), dataset);
    BOOST_CHECK_EQUAL(dataset->tagExists(tagandrange._tag), true);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Empty Dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    dicomifier::TagAndRange tagandrange;
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::
            DicomSequenceField::New(tagandrange, {}, false);
    BOOST_REQUIRE_THROW(testfieldSQ->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
}
