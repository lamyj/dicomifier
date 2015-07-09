/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDictionary
#include <boost/test/unit_test.hpp>

#include "core/DicomifierException.h"
#include "dicom/Dictionary.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor / Destructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    auto dictionary = dicomifier::Dictionary::New();
    
    BOOST_CHECK_EQUAL(dictionary != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: AddDictEntry / GetDictEntry
 */
struct TestDataOK02
{
    dicomifier::Dictionary::Pointer dictionary;
    
    TestDataOK02() : dictionary(dicomifier::Dictionary::New())
    {
        // Nothing to do
    }
    
    ~TestDataOK02()
    {
        // Nothing to do
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    BOOST_CHECK_EQUAL(dictionary->IsDictEntryFromName("PatientName"), false);
    
    DcmDictEntry* dictentry = 
            new DcmDictEntry(0x0010, 0x0010,
                             DcmVR("PN"),
                             "PatientName",
                             0, 1,
                             NULL, OFTrue,
                             "public");
                             
    dictionary->AddDictEntry(dictentry);
                             
    BOOST_CHECK_EQUAL(dictionary->IsDictEntryFromName("PatientName"), true);
    BOOST_CHECK(dictionary->GetEntryFromName("PatientName") != NULL);
    
    BOOST_CHECK_EQUAL(dictionary->IsDictEntryFromKey("0010,0020"), false);
    
    dictentry = 
            new DcmDictEntry(0x0010, 0x0020,
                             DcmVR("LO"),
                             "PatientID",
                             0, 1,
                             NULL, OFTrue,
                             "public");
                             
    dictionary->AddDictEntry(dictentry, "PatientID", "0010,0020");
                             
    BOOST_CHECK_EQUAL(dictionary->IsDictEntryFromKey("0010,0020"), true);
    BOOST_CHECK_EQUAL(dictionary->GetEntryFromKey("0010,0020") != NULL, true);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: GetEntryFromName Unknown name
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto dictionary = dicomifier::Dictionary::New();
    
    BOOST_REQUIRE_THROW(dictionary->GetEntryFromName("Unknown"), 
                        dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: GetEntryFromKey Unknown key
 */
BOOST_AUTO_TEST_CASE(TEST_KO_02)
{
    auto dictionary = dicomifier::Dictionary::New();
    
    BOOST_REQUIRE_THROW(dictionary->GetEntryFromKey("0000,0000"), 
                        dicomifier::DicomifierException);
}
