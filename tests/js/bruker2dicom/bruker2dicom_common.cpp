/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleJSBruker2dicom_Common
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "core/DicomifierException.h"
#include "../TestDataJS.h"

class TestData : public TestDataJS
{
public:
    TestData(): TestDataJS()
    {
        // include files
        std::string const include_("require(\"common.js\");\n"
                                   "require(\"bruker2dicom/common.js\");");
        jsvm.run(include_, jsvm.get_context());
    }

    virtual ~TestData()
    {
        // nothing to do
    }
};

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Function dictionaryMapper
 */
BOOST_FIXTURE_TEST_CASE(dictionaryMapper, TestData)
{
    std::stringstream script;
    script << "function dicoMapper() {\n"
           << "var functionMapper = dicomifier.bruker2dicom.dictionaryMapper({"
           <<       "'Head_Supine': 'HFS', 'Head_Prone': 'HFP',"
           <<       "'Head_Left' : 'HFDL', 'Head_Right': 'HFDR',"
           <<       "'Foot_Supine': 'FFS', 'Foot_Prone': 'FFP',"
           <<       "'Foot_Left': 'FFDL', 'Foot_Right': 'FFDR' });\n"
           << "return functionMapper('Foot_Supine');\n"
           << "}\n"
           << "dicoMapper();";

    auto const result = jsvm.run(script.str(), jsvm.get_context());

    BOOST_REQUIRE_EQUAL( std::string(*v8::String::Utf8Value(result)), "FFS" );
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Function dateTimeMapper
 */
BOOST_FIXTURE_TEST_CASE(dateTimeMapper, TestData)
{
    // Date
    {
    std::stringstream script;
    script << "function dicoMapperDate() {\n"
           << "var functionMapper = dicomifier.bruker2dicom.dateTimeMapper("
           <<       "'date');\n"
           << "return functionMapper('2015-02-19T10:18:16,448+0100');\n"
           << "}\n"
           << "dicoMapperDate();";

    auto const result = jsvm.run(script.str(), jsvm.get_context());

    BOOST_REQUIRE_EQUAL( std::string(*v8::String::Utf8Value(result)),
                         "20150219" );
    }

    // Time
    {
        std::stringstream script;
        script << "function dicoMapperTime() {\n"
               << "var functionMapper = dicomifier.bruker2dicom.dateTimeMapper("
               <<       "'time');\n"
               << "return functionMapper('2015-02-19T10:18:16,448+0100');\n"
               << "}\n"
               << "dicoMapperTime();";

        auto const result = jsvm.run(script.str(), jsvm.get_context());

        // time in UTC
        BOOST_REQUIRE_EQUAL( std::string(*v8::String::Utf8Value(result)),
                             "091816" );
    }
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Function toDicom
 */
BOOST_FIXTURE_TEST_CASE(toDicom, TestData)
{
    std::stringstream script;
    script << "function testToDicom() {\n"
           << "var brukerDataset = { "
           <<       "\"VisuAcqDate\":[\"2015-02-19T10:42:41,361+0100\"],"
           <<       "\"VisuAcqEchoSequenceType\":[\"Both\"],"
           <<       "\"VisuAcqEchoTime\":[7.354674339294434],"
           <<       "\"VisuAcqEchoTrainLength\":[\"1\"],"
           <<       "\"VisuAcqEncodingOrder\":[\"LinearEncoding\",\"LinearEncoding\"],"
           <<       "\"VisuAcqFlipAngle\":[\"90\"],"
           <<       "\"VisuAcqImagedNucleus\":[\"1H\"],"
           <<       "\"VisuAcqPhaseEncSteps\":[\"108\"],"
           <<       "\"VisuAcqPixelBandwidth\":[\"225.360576923077\"],"
           <<       "\"VisuAcqRepetitionTime\":[250.6052398681641,363.9815368652344,489.1980590820312,629.019287109375,787.3074951171875,969.6939086914062,1184.857177734375,1447.2158203125,1783.465454101562,2252.284912109375,3032.3662109375,6000],"
           <<       "\"VisuAcqSaturation\":[\"( 2 )(FovSaturation, 10, -0 -0 1, 0 0 -8.8612) (FovSaturation, 10, -0 -0 1, -0 -0 10.4269)\"],"
           <<       "\"VisuAcqSize\":[108,108],"
           <<       "\"VisuAcqSoftwareVersion\":[\"6.0\"],"
           <<       "\"VisuAcquisitionProtocol\":[\"T1_T2map_RARE\"],"
           <<       "\"VisuCoreByteOrder\":[\"littleEndian\"],"
           <<       "\"VisuCoreDim\":[\"2\"],"
           <<       "\"VisuCoreDimDesc\":[\"spatial\",\"spatial\"],"
           <<       "\"VisuCoreExtent\":[16,16],"
           <<       "\"VisuCoreFrameCount\":[\"108\"],"
           <<       "\"VisuCoreFrameThickness\":[0.800000011920929],"
           <<       "\"VisuCoreFrameType\":[\"MAGNITUDE_IMAGE\"],"
           <<       "\"VisuCoreOrientation\":[1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1],"
           <<       "\"VisuCorePosition\":[-7.359000205993652,-8.782999992370605,-2.34625506401062,-7.359000205993652,-8.782999992370605,-1.546254992485046,-7.359000205993652,-8.782999992370605,-0.7462549805641174,-7.359000205993652,-8.782999992370605,0.05374499782919884,-7.359000205993652,-8.782999992370605,0.8537449836730957,-7.359000205993652,-8.782999992370605,1.653745055198669,-7.359000205993652,-8.782999992370605,2.453744888305664,-7.359000205993652,-8.782999992370605,3.253745079040527,-7.359000205993652,-8.782999992370605,4.053744792938232],"
           <<       "\"VisuCoreSize\":[128,128],"
           <<       "\"VisuCoreUnits\":[\"mm\",\"mm\"],"
           <<       "\"VisuCoreWordType\":[\"_16BIT_SGN_INT\"],"
           <<       "\"VisuCreationDate\":[\"2015-02-19T11:17:33,343+0100\"],"
           <<       "\"VisuCreator\":[\"ParaVision\"],"
           <<       "\"VisuCreatorVersion\":[\"6.0\"],"
           <<       "\"VisuExperimentNumber\":[\"8\"],"
           <<       "\"VisuFGElemComment\":[\"VTR=   250.6ms\",\"VTR=   364.0ms\",\"VTR=   489.2ms\",\"VTR=   629.0ms\",\"VTR=   787.3ms\",\"VTR=   969.7ms\",\"VTR=  1184.9ms\",\"VTR=  1447.2ms\",\"VTR=  1783.5ms\",\"VTR=  2252.3ms\",\"VTR=  3032.4ms\",\"VTR=  6000.0ms\"],"
           <<       "\"VisuFGOrderDesc\":[[9,\"FG_SLICE\",\"\",0,2],[12,\"FG_MOVIE\",\"vtr\",2,2]],"
           <<       "\"VisuFGOrderDescDim\":[\"2\"],"
           <<       "\"VisuGroupDepVals\":[[\"VisuCoreOrientation\",0],[\"VisuCorePosition\",0],[\"VisuFGElemComment\",0],[\"VisuAcqRepetitionTime\",0]],"
           <<       "\"VisuInstanceModality\":[\"MR\"],"
           <<       "\"VisuInstitution\":[\"ICUDE Strasbourg\"],"
           <<       "\"VisuManufacturer\":[\"Bruker BioSpin MRI GmbH\"],"
           <<       "\"VisuSeriesDate\":[\"2015-02-19T11:17:33,343+0100\"],"
           <<       "\"VisuSeriesTypeId\":[\"ACQ_BRUKER_PVM\"],"
           <<       "\"VisuStation\":[\"Biospec \"],"
           <<       "\"VisuStudyDate\":[\"2015-02-19T09:30:02,093+0100\"],"
           <<       "\"VisuStudyDescription\":[\"PROTOCOLE_TOUT\"],"
           <<       "\"VisuStudyId\":[\"FLIIAM^19022015\"],"
           <<       "\"VisuStudyNumber\":[\"1\"],"
           <<       "\"VisuStudyReferringPhysician\":[\"fli_iam\"],"
           <<       "\"VisuStudyUid\":[\"2.16.756.5.5.100.1333920868.19866.1424334602.23\"],"
           <<       "\"VisuSubjectBirthDate\":[\"20150219\"],"
           <<       "\"VisuSubjectId\":[\"FLIIAM^S15-01\"],"
           <<       "\"VisuSubjectInstanceCreationDate\":[[1424334602,92,60]],"
           <<       "\"VisuSubjectName\":[\"S15-01\"],"
           <<       "\"VisuSubjectPosition\":[\"Head_Supine\"],"
           <<       "\"VisuSubjectSex\":[\"MALE\"],"
           <<       "\"VisuSubjectType\":[\"Quadruped\"],"
           <<       "\"VisuSubjectUid\":[\"2.16.756.5.5.100.1333920868.19866.1424334602.22\"],"
           <<       "\"VisuSubjectWeight\":[\"0.001\"],"
           <<       "\"VisuUid\":[\"2.16.756.5.5.100.1333920868.3876.1424341053.1\"],"
           <<       "\"VisuVersion\":[\"3\"] "
           << "};\n"
           << "var frameGroups = dicomifier.bruker2dicom.getFrameGroups(brukerDataset);\n"
           << "var indexGenerator = new dicomifier.bruker2dicom.FrameIndexGenerator(frameGroups);\n"
           << "var dicomDataset = {};\n"
         // Simple matching
           << "dicomifier.bruker2dicom.toDicom("
           <<       "indexGenerator, dicomDataset, 'SeriesInstanceUID', brukerDataset, 'VisuUid', 1);\n"
         // With Setter
           << "dicomifier.bruker2dicom.toDicom("
           <<       "indexGenerator, dicomDataset, 'SeriesDate', brukerDataset, 'VisuSeriesDate', 2, dicomifier.bruker2dicom.dateTimeMapper('date'));\n"
         // With Getter
           << "dicomifier.bruker2dicom.toDicom("
           <<       "indexGenerator, dicomDataset, 'SeriesNumber', brukerDataset, null, 2, parseInt, function(brukerDataset) { return [brukerDataset.VisuExperimentNumber || brukerDataset.VisuSeriesNumber ]; });\n"
           << "return dicomDataset;\n"
           << "}\n"
           << "JSON.stringify(testToDicom());";

    Json::Value const jsondataset = get_json_result(script.str());

    BOOST_REQUIRE(jsondataset.isObject());
    BOOST_REQUIRE_EQUAL(std::string(
        jsondataset.get("0020000e", Json::Value()).
                    get("Value", Json::Value())[0].asCString()),
        "2.16.756.5.5.100.1333920868.3876.1424341053.1");
    BOOST_REQUIRE_EQUAL(std::string(
        jsondataset.get("0020000e", Json::Value()).
                    get("vr", Json::Value()).asCString()),
        "UI");
    BOOST_REQUIRE_EQUAL(std::string(
        jsondataset.get("00080021", Json::Value()).
                    get("Value", Json::Value())[0].asCString()),
        "20150219");
    BOOST_REQUIRE_EQUAL(std::string(
        jsondataset.get("00080021", Json::Value()).
                    get("vr", Json::Value()).asCString()),
        "DA");
    BOOST_REQUIRE_EQUAL(
        jsondataset.get("00200011", Json::Value()).
                    get("Value", Json::Value())[0].asInt(),
        8);
    BOOST_REQUIRE_EQUAL(std::string(
        jsondataset.get("00200011", Json::Value()).
                    get("vr", Json::Value()).asCString()),
        "IS");
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Function dictionaryMapper
 *                  Value not mapped
 */
BOOST_FIXTURE_TEST_CASE(dictionaryMapper_notFind, TestData)
{
    std::stringstream script;
    script << "function dicoMapperNotfind() {\n"
           << "var functionMapper = dicomifier.bruker2dicom.dictionaryMapper({"
           <<       "'Head_Supine': 'HFS', 'Head_Prone': 'HFP',"
           <<       "'Head_Left' : 'HFDL', 'Head_Right': 'HFDR',"
           <<       "'Foot_Supine': 'FFS', 'Foot_Prone': 'FFP',"
           <<       "'Foot_Left': 'FFDL', 'Foot_Right': 'FFDR' });\n"
           << "return functionMapper('bad_value');\n"
           << "}\n"
           << "dicoMapperNotfind();";

    BOOST_REQUIRE_THROW(jsvm.run(script.str(), jsvm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Function dateTimeMapper
 *                  Value not mapped
 */
BOOST_FIXTURE_TEST_CASE(dateTimeMapper_notFind, TestData)
{
    std::stringstream script;
    script << "function dicoMapperTime() {\n"
           << "var functionMapper = dicomifier.bruker2dicom.dateTimeMapper("
           <<       "'bad_value');\n"
           << "return functionMapper('2015-02-19T10:18:16,448+0100');\n"
           << "}\n"
           << "dicoMapperTime();";

    BOOST_REQUIRE_THROW(jsvm.run(script.str(), jsvm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Function dateTimeMapper
 *                  Value not date
 */
BOOST_FIXTURE_TEST_CASE(dateTimeMapper_NotADate, TestData)
{
    std::stringstream script;
    script << "function dicoMapperTime() {\n"
           << "var functionMapper = dicomifier.bruker2dicom.dateTimeMapper("
           <<       "'time');\n"
           << "return functionMapper('aa2015-02-19T10:18:16,448+0100');\n"
           << "}\n"
           << "dicoMapperTime();";

    BOOST_REQUIRE_THROW(jsvm.run(script.str(), jsvm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Function toDicom
 *                  Unknown DICOM element
 */
BOOST_FIXTURE_TEST_CASE(toDicom_UnknownElement, TestData)
{
    std::stringstream script;
    script << "function toDicom() {\n"
           << "return dicomifier.bruker2dicom.toDicom("
           <<       "null, null, 'badElement', null, null);\n"
           << "}\n"
           << "toDicom();";

    BOOST_REQUIRE_THROW(jsvm.run(script.str(), jsvm.get_context()),
                        dicomifier::DicomifierException);
}
