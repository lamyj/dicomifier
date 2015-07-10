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

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    // Test VR = SQ
    auto testfieldae = dicomifier::translator::DicomSequenceField::New();
    // Pointer exists
    BOOST_REQUIRE(testfieldae != NULL);
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (per frame)
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset dataset;
    // Test VR = SQ
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::
            DicomSequenceField::New(tagandrange, {}, true);
    testfieldSQ->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run Sequence with subtag (per frame)
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset dataset;
    // Test VR = SQ
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::DicomSequenceField::
            New(tagandrange, {dicomifier::translator::TestField::New()}, true);
    testfieldSQ->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (One Frame)
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset dataset;
    // Test VR = SQ
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::
            DicomSequenceField::New(tagandrange, {}, false);
    testfieldSQ->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run Sequence with subtag (per frame)
 */
BOOST_AUTO_TEST_CASE(TEST_OK_05)
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset dataset;
    // Test VR = SQ
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::DicomSequenceField::
            New(tagandrange, {dicomifier::translator::TestField::New()}, false);
    testfieldSQ->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Empty Dataset
 */
BOOST_AUTO_TEST_CASE(EmptyDataset)
{
    dicomifier::TagAndRange tagandrange;
    tagandrange._tag = DCM_SharedFunctionalGroupsSequence;
    auto testfieldSQ = dicomifier::translator::
            DicomSequenceField::New(tagandrange, {}, false);
    BOOST_REQUIRE_THROW(testfieldSQ->run(NULL,
                                         dicomifier::FrameIndexGenerator({}),
                                         NULL),
                        dicomifier::DicomifierException);
}
