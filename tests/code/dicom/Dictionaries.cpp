/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDictionaries
#include <boost/test/unit_test.hpp>

#include "core/DicomifierException.h"
#include "dicom/Dictionaries.h"

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Constructor / Destructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    dicomifier::Dictionaries::get_instance();
    dicomifier::Dictionaries::delete_instance();
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Parse Private Dictionary
 */
struct TestDataOK02
{
    std::string filepath;
    
    TestDataOK02() : filepath("./temp_test_ModuleDictionaries.xml")
    {
        std::ofstream myfile;
        myfile.open(filepath);
        myfile << "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"no\"?>\n";
        myfile << "<book xmlns=\"http://docbook.org/ns/docbook\" xmlns:xl=\"http://www.w3.org/1999/xlink\" xml:id=\"PS3.6-FLI-IAM\" label=\"PS3.6-FLI-IAM\" version=\"1.0\">\n";
        myfile << "  <title>FLI-IAM</title>\n";
        myfile << "  <subtitle>Private Data Dictionary</subtitle>\n";
        myfile << "  <chapter xml:id=\"chapter_1\" label=\"1\" status=\"1\">\n";
        myfile << "    <title>Registry of private DICOM Data Elements</title>\n";
        myfile << "    <table rules=\"all\" frame=\"box\" xml:id=\"table_1-1-FLI-IAM\" label=\"1-1\">\n";
        myfile << "      <caption>Registry of private DICOM Data Elements</caption>\n";
        myfile << "      <thead>\n";
        myfile << "        <tr valign=\"top\">\n";
        myfile << "          <th align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>\n";
        myfile << "              <emphasis role=\"bold\">Tag</emphasis>\n";
        myfile << "            </para>\n";
        myfile << "          </th>\n";
        myfile << "          <th align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>\n";
        myfile << "              <emphasis role=\"bold\">Name</emphasis>\n";
        myfile << "            </para>\n";
        myfile << "          </th>\n";
        myfile << "          <th align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>\n";
        myfile << "              <emphasis role=\"bold\">Keyword</emphasis>\n";
        myfile << "            </para>\n";
        myfile << "          </th>\n";
        myfile << "          <th align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>\n";
        myfile << "              <emphasis role=\"bold\">VR</emphasis>\n";
        myfile << "            </para>\n";
        myfile << "          </th>\n";
        myfile << "          <th align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>\n";
        myfile << "              <emphasis role=\"bold\">VM</emphasis>\n";
        myfile << "            </para>\n";
        myfile << "          </th>\n";
        myfile << "          <td align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para/>\n";
        myfile << "          </td>\n";
        myfile << "        </tr>\n";
        myfile << "      </thead>\n";
        myfile << "      <tbody>\n";
        myfile << "        <tr valign=\"top\">\n";
        myfile << "          <td align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>(0023,xx01)</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"left\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>Subject Category</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"left\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>SubjectCategory</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>CS</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>1-2</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para/>\n";
        myfile << "          </td>\n";
        myfile << "        </tr>\n";
        myfile << "        <tr valign=\"top\">\n";
        myfile << "          <td align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>(0023,xx02)</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"left\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>Provider Name</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"left\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>ProviderName</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>LO</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para>1-n</para>\n";
        myfile << "          </td>\n";
        myfile << "          <td align=\"center\" colspan=\"1\" rowspan=\"1\">\n";
        myfile << "            <para/>\n";
        myfile << "          </td>\n";
        myfile << "        </tr>\n";
        myfile << "      </tbody>\n";
        myfile << "    </table>\n";
        myfile << "  </chapter>\n";
        myfile << "</book>\n";
        myfile.close();
    }
    
    ~TestDataOK02()
    {
        remove(filepath.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    dicomifier::Dictionaries& dictionaries =
            dicomifier::Dictionaries::get_instance();
    
    dictionaries.ParsePrivateDictionary(filepath);
    
    BOOST_CHECK_EQUAL(dictionaries.FindCreatorElementNumber("FLI-IAM", 
                                                            new DcmDataset()), 
                      0x0010);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Get Creator num
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK02)
{
    dicomifier::Dictionaries& dictionaries =
            dicomifier::Dictionaries::get_instance();
    
    dictionaries.ParsePrivateDictionary(filepath);
    
    DcmDataset* dataset = new DcmDataset();
    dataset->putAndInsertString(DcmTag(0x0023, 0x0011), "FLI-IAM");
    
    BOOST_CHECK_EQUAL(dictionaries.FindCreatorElementNumber("FLI-IAM", 
                                                            dataset), 
                      0x0011);

    BOOST_CHECK_EQUAL(dictionaries.FindCreatorElementNumber("public",
                                                            dataset),
                      0x00FF);

    delete dataset;
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: GetTagFromName
 */
BOOST_FIXTURE_TEST_CASE(GetTagFromName, TestDataOK02)
{
    dicomifier::Dictionaries& dictionaries =
            dicomifier::Dictionaries::get_instance();

    dictionaries.ParsePrivateDictionary(filepath);

    bool public_;
    DcmTag tag1 = dictionaries.GetTagFromName("PatientName", "public", public_);
    BOOST_CHECK_EQUAL(tag1.getTagName(), "PatientName");
    BOOST_CHECK(!public_);

    DcmTag tag2 = dictionaries.GetTagFromName("PatientName", "FLI-IAM", public_);
    BOOST_CHECK_EQUAL(tag2.getTagName(), "PatientName");
    BOOST_CHECK(public_);

    DcmTag tag3 = dictionaries.GetTagFromName("SubjectCategory",
                                              "FLI-IAM", public_);
    BOOST_CHECK_EQUAL(tag3.getGroup(), 35);
    BOOST_CHECK_EQUAL(tag3.getElement(), 1);
    BOOST_CHECK(!public_);

    dicomifier::Dictionaries::delete_instance();
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: GetTagFromKey
 */
BOOST_FIXTURE_TEST_CASE(GetTagFromKey, TestDataOK02)
{
    dicomifier::Dictionaries& dictionaries =
            dicomifier::Dictionaries::get_instance();

    dictionaries.ParsePrivateDictionary(filepath);

    bool public_;
    DcmTag tag1 = dictionaries.GetTagFromKey("0010,0010", "public", public_);
    BOOST_CHECK_EQUAL(tag1.getTagName(), "PatientName");
    BOOST_CHECK(!public_);

    DcmTag tag2 = dictionaries.GetTagFromKey("0010,0010", "FLI-IAM", public_);
    BOOST_CHECK_EQUAL(tag2.getTagName(), "PatientName");
    BOOST_CHECK(public_);

    DcmTag tag3 = dictionaries.GetTagFromKey("0023,xx01",
                                             "FLI-IAM", public_);
    BOOST_CHECK_EQUAL(tag3.getGroup(), 35);
    BOOST_CHECK_EQUAL(tag3.getElement(), 1);
    BOOST_CHECK(!public_);

    dicomifier::Dictionaries::delete_instance();
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: public_dictionary_as_json
 */
BOOST_AUTO_TEST_CASE(PublicDictionaryAsJSON)
{
    BOOST_REQUIRE(dicomifier::Dictionaries::public_dictionary_as_json() != "");
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Unkown Dictionary file
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    BOOST_REQUIRE_THROW(dicomifier::Dictionaries::get_instance().
                            ParsePrivateDictionary("./unknownfile.xml"),
                        std::runtime_error);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: GetTagFromName Unkown dictionary
 */
BOOST_AUTO_TEST_CASE(TEST_KO_02)
{
    dicomifier::Dictionaries& dictionaries =
            dicomifier::Dictionaries::get_instance();
    
    bool testvalue = false;
    BOOST_REQUIRE_THROW(dictionaries.GetTagFromName("MyTagName",
                                                    "badDictionary", testvalue),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: GetTagFromKey Unkown dictionary
 */
BOOST_AUTO_TEST_CASE(TEST_KO_03)
{
    dicomifier::Dictionaries& dictionaries =
            dicomifier::Dictionaries::get_instance();
    
    bool testvalue = false;
    BOOST_REQUIRE_THROW(dictionaries.GetTagFromKey("0023,xx99",
                                                   "badDictionary", testvalue),
                        dicomifier::DicomifierException);
}
