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

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = SQ
    auto testfieldae = dicomifier::translator::DicomSequenceField::New();
    // Pointer exists and class type is DicomSequenceField
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), 
                      dicomifier::translator::ECT_DicomSequenceField);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run
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
