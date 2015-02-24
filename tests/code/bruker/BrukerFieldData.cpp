/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerFieldData
#include <boost/test/unit_test.hpp>

#include "bruker/BrukerFieldData.h"
#include "core/DicomifierException.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    auto field = dicomifier::bruker::BrukerFieldData::New();
    BOOST_CHECK_EQUAL(field != NULL, true);
    dicomifier::bruker::BrukerValue values = field->get_brukervalues();
    BOOST_CHECK_EQUAL(values.children.size(), 0);
    
    field = dicomifier::bruker::BrukerFieldData::New("value");
    BOOST_CHECK_EQUAL(field != NULL, true);
    values = field->get_brukervalues();
    BOOST_CHECK_EQUAL(values.children.size(), 1);
    BOOST_CHECK_EQUAL(boost::get<std::string>(values.children[0]), "value");
    
    values.children.clear();
    values.children.push_back("value1");
    values.children.push_back("value2");
    field = dicomifier::bruker::BrukerFieldData::New(values);
    BOOST_CHECK_EQUAL(field != NULL, true);
    values = field->get_brukervalues();
    BOOST_CHECK_EQUAL(values.children.size(), 2);
    BOOST_CHECK_EQUAL(boost::get<std::string>(values.children[0]), "value1");
    BOOST_CHECK_EQUAL(boost::get<std::string>(values.children[1]), "value2");
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Parse Header key (string value)
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    // Header key
    auto brukerfielddata = dicomifier::bruker::BrukerFieldData::New();
    brukerfielddata->Parse("##ORIGIN=Bruker BioSpin MRI GmbH");
    auto values = brukerfielddata->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(brukerfielddata->get_string(0), "Bruker BioSpin MRI GmbH");
    
    brukerfielddata = dicomifier::bruker::BrukerFieldData::New();
    brukerfielddata->Parse("##ORIGIN=text_sample 123456");
    values = brukerfielddata->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(brukerfielddata->get_string(0), "text_sample 123456");
    
    brukerfielddata = dicomifier::bruker::BrukerFieldData::New();
    brukerfielddata->Parse("##ORIGIN=<text_sample>");
    values = brukerfielddata->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(brukerfielddata->get_string(0), "<text_sample>");
    
    brukerfielddata = dicomifier::bruker::BrukerFieldData::New();
    brukerfielddata->Parse("##ORIGIN=(text_sample, 1234)");
    values = brukerfielddata->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(brukerfielddata->get_string(0), "(text_sample, 1234)");
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Parse String simple value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    // String simple value
    auto field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$SAMPLE=text_sample");
    auto values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_string(0), "text_sample");
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$SUBJECT_id=( 60 )\n<Rat>");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_string(0), "Rat");
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuUid=( 65 )\n<2.16.756.5.5.100.3611280983.9770.1256567574.1>");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_string(0), "2.16.756.5.5.100.3611280983.9770.1256567574.1");

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$SUBJECT_remarks=( 2048 )\n<>");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_string(0), "");
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$SUBJECT_id=( 60 )\n<Rat 469>");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_string(0), "Rat 469");
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$SUBJECT_id=( 60 )\n<123456>");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_string(0), "123456");
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$SUBJECT_id=( 60 )\n<(abcd)>");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_string(0), "(abcd)");
}
    
/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Parse Int simple value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    // Int simple value
    auto field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=19");
    auto values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_int(0), 19);

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=( 1 )\n19");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_int(0), 19);

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=( 1 )\n2147483647");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_int(0), 2147483647);

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=( 1 )\n-169419");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_int(0), -169419);

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=( 1 )\n0");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_int(0), 0);
}
    
/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Parse Double simple value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_05)
{
    // Double simple value
    auto field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=19.6");
    auto values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_double(0), 19.6);

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=( 1 )\n19.6");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_double(0), 19.6);

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=( 1 )\n19456789.6455948");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_double(0), 19456789.6455948);

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=( 1 )\n-94519.6546");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_double(0), -94519.6546);

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreFrameCount=( 1 )\n0.0");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_double(0), 0);
}
    
/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Parse String multiple value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_06)
{    
    // String multiple values
    auto field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreDimDesc=( 2 )\nghijkl abcdef");
    auto values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 2);
    BOOST_CHECK_EQUAL(field->get_string(0), "ghijkl");
    BOOST_CHECK_EQUAL(field->get_string(1), "abcdef");
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreUnits=( 2, 65 )\n<mm> <cm>");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 2);
    BOOST_CHECK_EQUAL(field->get_string(0), "mm");
    BOOST_CHECK_EQUAL(field->get_string(1), "cm");
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreUnits=( 2, 65 )\n<m m m> <> abcdef <156>");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 4);
    BOOST_CHECK_EQUAL(field->get_string(0), "m m m");
    BOOST_CHECK_EQUAL(field->get_string(1), "");
    BOOST_CHECK_EQUAL(field->get_string(2), "abcdef");
    BOOST_CHECK_EQUAL(field->get_string(3), "156");
}
    
/*************************** TEST OK 07 *******************************/
/**
 * Nominal test case: Parse Int multiple value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_07)
{    
    // Int multiple values
    auto field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreSize=( 2 )\n256 128");
    auto values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 2);
    BOOST_CHECK_EQUAL(field->get_int(0), 256);
    BOOST_CHECK_EQUAL(field->get_int(1), 128);
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreSize=( 6 )\n256 128 -15 +36 0 789456");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 6);
    BOOST_CHECK_EQUAL(field->get_int(0), 256);
    BOOST_CHECK_EQUAL(field->get_int(1), 128);
    BOOST_CHECK_EQUAL(field->get_int(2), -15);
    BOOST_CHECK_EQUAL(field->get_int(3), 36);
    BOOST_CHECK_EQUAL(field->get_int(4), 0);
    BOOST_CHECK_EQUAL(field->get_int(5), 789456);
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCoreSize=( 3, 2 )\n256 128 -15 +36 0 789456");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 2);
    BOOST_CHECK_EQUAL(values[0], 3);
    BOOST_CHECK_EQUAL(values[1], 2);
    BOOST_CHECK_EQUAL(field->get_int(0), 256);
    BOOST_CHECK_EQUAL(field->get_int(1), 128);
    BOOST_CHECK_EQUAL(field->get_int(2), -15);
    BOOST_CHECK_EQUAL(field->get_int(3), 36);
    BOOST_CHECK_EQUAL(field->get_int(4), 0);
    BOOST_CHECK_EQUAL(field->get_int(5), 789456);
}
    
/*************************** TEST OK 08 *******************************/
/**
 * Nominal test case: Parse Double multiple value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_08)
{    
    // Double multiple values
    auto field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCorePosition=( 4 )\n-14.9985581617522 +15.001441699668 0 12345.456789");
    auto values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 4);
    BOOST_CHECK_EQUAL(field->get_double(0), -14.9985581617522);
    BOOST_CHECK_EQUAL(field->get_double(1), 15.001441699668);
    BOOST_CHECK_EQUAL(field->get_double(2), 0);
    BOOST_CHECK_EQUAL(field->get_double(3), 12345.456789);
    
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuCorePosition=( 19, 3 )\n-14.9985581617522 -15.001441699668 -8 -14.9985581617522 -15.001441699668 -7 \n-14.9985581617522 -15.001441699668 -6 -14.9985581617522 -15.001441699668 -5 \n-14.9985581617522 -15.001441699668 -4 -14.9985581617522 -15.001441699668 -3 \n-14.9985581617522 -15.001441699668 -2 -14.9985581617522 -15.001441699668 -1 \n-14.9985581617522 -15.001441699668 0 -14.9985581617522 -15.001441699668 1 \n-14.9985581617522 -15.001441699668 2 -14.9985581617522 -15.001441699668 3 \n-14.9985581617522 -15.001441699668 4 -14.9985581617522 -15.001441699668 5 \n-14.9985581617522 -15.001441699668 6 -14.9985581617522 -15.001441699668 7 \n-14.9985581617522 -15.001441699668 8 -14.9985581617522 -15.001441699668 9 \n-14.9985581617522 -15.001441699668 10");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 2);
    BOOST_CHECK_EQUAL(values[0], 19);
    BOOST_CHECK_EQUAL(values[1], 3);
    BOOST_CHECK_EQUAL(field->get_double(0), -14.9985581617522);
    BOOST_CHECK_EQUAL(field->get_double(1), -15.001441699668);
    BOOST_CHECK_EQUAL(field->get_double(2), -8);
}
    
/*************************** TEST OK 09 *******************************/
/**
 * Nominal test case: Parse Simple Structure
 */
BOOST_AUTO_TEST_CASE(TEST_OK_09)
{
    // Struct simple value
    auto field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$SUBJECT_instance_creation_date=(1395234009, 239, 60)");
    auto values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_int(0), 1395234009);
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_int(1), 239);
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_int(2), 60);

    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$SUBJECT_name=(<Gustave>, <>)");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_string(0), "Gustave");
    
    // Struct multiple values
    field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$VisuGroupDepVals=( 2 )\n(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 1)");
    values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 2);
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_string(0), "VisuCoreOrientation");
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_int(1), 0);
    BOOST_CHECK_EQUAL(field->get_struct(1)->get_string(0), "VisuCorePosition");
    BOOST_CHECK_EQUAL(field->get_struct(1)->get_int(1), 1);
}
    
/*************************** TEST OK 10 *******************************/
/**
 * Nominal test case: Parse Complex Structure
 */
BOOST_AUTO_TEST_CASE(TEST_OK_10)
{
    // Struct simple value
    auto field = dicomifier::bruker::BrukerFieldData::New();
    field->Parse("##$SUBJECT_instance_creation_date=((abcd, <toto 123>, 14.5), <>, 35632)");
    auto values = field->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 1);
    values = field->get_struct(0)->get_dimensionNumbers();
    BOOST_CHECK_EQUAL(values.size(), 1);
    BOOST_CHECK_EQUAL(values[0], 3);
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_struct(0)->get_string(0), "abcd");
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_struct(0)->get_string(1), "toto 123");
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_struct(0)->get_double(2), 14.5);
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_string(1), "");
    BOOST_CHECK_EQUAL(field->get_struct(0)->get_int(2), 35632);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: No value
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto field = dicomifier::bruker::BrukerFieldData::New();
        
    BOOST_REQUIRE_THROW(field->get_string(0),   dicomifier::DicomifierException);
    
    BOOST_REQUIRE_THROW(field->get_int(0),      dicomifier::DicomifierException);
    
    BOOST_REQUIRE_THROW(field->get_double(0),   dicomifier::DicomifierException);
    
    BOOST_REQUIRE_THROW(field->get_struct(0),   dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Parsing error
 */
BOOST_AUTO_TEST_CASE(TEST_KO_02)
{
    auto field = dicomifier::bruker::BrukerFieldData::New();
    std::string str = "##$SUBJECT_instance=((abcd, 14.5), 35632 ";
    BOOST_REQUIRE_THROW(field->Parse(str), dicomifier::DicomifierException);
}
