/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleFrameIndexGeneratorJS
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "core/DicomifierException.h"
#include "../TestDataJS.h"

class TestDataFrameIndexGenerator : public TestDataJS
{
public:
    TestDataFrameIndexGenerator(): TestDataJS()
    {
        // include files

        std::stringstream streamscript;
        streamscript << "require('bruker2dicom/frame_index_generator.js');\n"
                     << "function createBrukerDataset() {\n"
                     << "return { "
                     <<         "\"VisuFGOrderDesc\":[[3,\"FG_SLICE\",\"\",0,2]], "
                     <<         "\"VisuFGOrderDescDim\":[\"1\"], "
                     <<         "\"VisuGroupDepVals\":[[\"VisuCoreOrientation\",0], "
                     <<                               "[\"VisuCorePosition\",0]] };\n"
                     << "}\n"
                     << "function createFrameGroups() {\n"
                     << "return dicomifier.bruker2dicom.getFrameGroups(createBrukerDataset()); \n"
                     << "}\n"
                     << "function createIndexGenerator() {\n"
                     << "return new dicomifier.bruker2dicom.FrameIndexGenerator(createFrameGroups()); \n"
                     << "}";

        jsvm.run(streamscript.str(), jsvm.get_context());
    }

    virtual ~TestDataFrameIndexGenerator()
    {
        // Nothing to do
    }
};

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Constructor / Destructor
 */
BOOST_FIXTURE_TEST_CASE(Constructor, TestDataFrameIndexGenerator)
{
    std::string const stream = "JSON.stringify(createIndexGenerator());";

    Json::Value const result = get_json_result(stream);

    BOOST_REQUIRE(result.isObject());
    BOOST_REQUIRE_EQUAL(result.size(), 5);
    // Members
    BOOST_REQUIRE(!result.get("frameGroups", Json::Value()).isNull());
    BOOST_REQUIRE(!result.get("indexMax", Json::Value()).isNull());
    BOOST_REQUIRE(!result.get("currentIndex", Json::Value()).isNull());
    BOOST_REQUIRE(!result.get("countMax", Json::Value()).isNull());
    BOOST_REQUIRE(!result.get("currentStep", Json::Value()).isNull());
    // Values frameGroups
    BOOST_REQUIRE_EQUAL(result.get("frameGroups", Json::Value()).size(), 1);
    BOOST_REQUIRE_EQUAL(result.get("frameGroups", Json::Value())[0].size(), 3);
    BOOST_CHECK_EQUAL(result.get("frameGroups", Json::Value())[0][0].asInt(), 3);
    BOOST_CHECK_EQUAL(std::string(
        result.get("frameGroups", Json::Value())[0][1].asCString()), "FG_SLICE");
    BOOST_REQUIRE(result.get("frameGroups", Json::Value())[0][2].isArray());
    BOOST_REQUIRE_EQUAL(
                result.get("frameGroups", Json::Value())[0][2].size(), 2);
    BOOST_CHECK_EQUAL(std::string(
            result.get("frameGroups", Json::Value())[0][2][0][0].asCString()),
            "VisuCoreOrientation");
    BOOST_CHECK_EQUAL(
            result.get("frameGroups", Json::Value())[0][2][0][1].asInt(),
            0);
    BOOST_CHECK_EQUAL(std::string(
            result.get("frameGroups", Json::Value())[0][2][1][0].asCString()),
            "VisuCorePosition");
    BOOST_CHECK_EQUAL(
            result.get("frameGroups", Json::Value())[0][2][1][1].asInt(),
            0);
    // Values indexMax
    BOOST_REQUIRE(result.get("indexMax", Json::Value()).isArray());
    BOOST_REQUIRE_EQUAL(result.get("indexMax", Json::Value()).size(), 1);
    BOOST_CHECK_EQUAL(result.get("indexMax", Json::Value())[0].asInt(), 3);
    // Values currentIndex
    BOOST_REQUIRE(result.get("currentIndex", Json::Value()).isArray());
    BOOST_REQUIRE_EQUAL(result.get("currentIndex", Json::Value()).size(), 1);
    BOOST_CHECK_EQUAL(result.get("currentIndex", Json::Value())[0].asInt(), 0);
    // Values countMax
    BOOST_REQUIRE(result.get("countMax", Json::Value()).isInt());
    BOOST_CHECK_EQUAL(result.get("countMax", Json::Value()).asInt(), 3);
    // Values currentStep
    BOOST_REQUIRE(result.get("currentStep", Json::Value()).isInt());
    BOOST_CHECK_EQUAL(result.get("currentStep", Json::Value()).asInt(), 0);
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function Done
 */
BOOST_FIXTURE_TEST_CASE(Done, TestDataFrameIndexGenerator)
{
    std::stringstream stream;
    stream << "var indexGenerator = createIndexGenerator();\n"
           << "indexGenerator.done();";

    auto const result = jsvm.run(stream.str(), jsvm.get_context());

    BOOST_REQUIRE( !result->ToBoolean()->Value() );
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function Next
 */
BOOST_FIXTURE_TEST_CASE(Next, TestDataFrameIndexGenerator)
{
    // initial State
    std::stringstream stream;
    stream << "var indexGenerator = createIndexGenerator();\n"
           << "indexGenerator.done();";
    auto const result = jsvm.run(stream.str(), jsvm.get_context());
    BOOST_REQUIRE( !result->ToBoolean()->Value() );

    // increase
    for (unsigned int i = 0; i < 3; ++i)
    {
        Json::Value const result = get_json_result("JSON.stringify(indexGenerator);");

        BOOST_REQUIRE(result.isObject());
        BOOST_REQUIRE_EQUAL(result.size(), 5);
        // Members
        BOOST_REQUIRE(!result.get("frameGroups", Json::Value()).isNull());
        BOOST_REQUIRE(!result.get("indexMax", Json::Value()).isNull());
        BOOST_REQUIRE(!result.get("currentIndex", Json::Value()).isNull());
        BOOST_REQUIRE(!result.get("countMax", Json::Value()).isNull());
        BOOST_REQUIRE(!result.get("currentStep", Json::Value()).isNull());
        // Values frameGroups
        BOOST_REQUIRE_EQUAL(result.get("frameGroups", Json::Value()).size(), 1);
        BOOST_REQUIRE_EQUAL(result.get("frameGroups", Json::Value())[0].size(), 3);
        BOOST_CHECK_EQUAL(result.get("frameGroups", Json::Value())[0][0].asInt(), 3);
        BOOST_CHECK_EQUAL(std::string(
            result.get("frameGroups", Json::Value())[0][1].asCString()), "FG_SLICE");
        BOOST_REQUIRE(result.get("frameGroups", Json::Value())[0][2].isArray());
        BOOST_REQUIRE_EQUAL(
                    result.get("frameGroups", Json::Value())[0][2].size(), 2);
        BOOST_CHECK_EQUAL(std::string(
                result.get("frameGroups", Json::Value())[0][2][0][0].asCString()),
                "VisuCoreOrientation");
        BOOST_CHECK_EQUAL(
                result.get("frameGroups", Json::Value())[0][2][0][1].asInt(),
                0);
        BOOST_CHECK_EQUAL(std::string(
                result.get("frameGroups", Json::Value())[0][2][1][0].asCString()),
                "VisuCorePosition");
        BOOST_CHECK_EQUAL(
                result.get("frameGroups", Json::Value())[0][2][1][1].asInt(),
                0);
        // Values indexMax
        BOOST_REQUIRE(result.get("indexMax", Json::Value()).isArray());
        BOOST_REQUIRE_EQUAL(result.get("indexMax", Json::Value()).size(), 1);
        BOOST_CHECK_EQUAL(result.get("indexMax", Json::Value())[0].asInt(), 3);
        // Values currentIndex
        BOOST_REQUIRE(result.get("currentIndex", Json::Value()).isArray());
        BOOST_REQUIRE_EQUAL(result.get("currentIndex", Json::Value()).size(), 1);
        BOOST_CHECK_EQUAL(result.get("currentIndex", Json::Value())[0].asInt(), i);
        // Values countMax
        BOOST_REQUIRE(result.get("countMax", Json::Value()).isInt());
        BOOST_CHECK_EQUAL(result.get("countMax", Json::Value()).asInt(), 3);
        // Values currentStep
        BOOST_REQUIRE(result.get("currentStep", Json::Value()).isInt());
        BOOST_CHECK_EQUAL(result.get("currentStep", Json::Value()).asInt(), i);

        jsvm.run("indexGenerator.next();", jsvm.get_context());
    }

    // Done == true
    {
        auto const result2 = jsvm.run("indexGenerator.done();", jsvm.get_context());
        BOOST_REQUIRE( result2->ToBoolean()->Value() );
    }
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Static Function GetFrameGroups
 */
BOOST_FIXTURE_TEST_CASE(GetFrameGroups, TestDataFrameIndexGenerator)
{
    std::string const stream = "JSON.stringify(createFrameGroups());";

    Json::Value const result = get_json_result(stream);

    BOOST_REQUIRE(result.isArray());
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0].size(), 3);
    BOOST_CHECK_EQUAL(result[0][0].asInt(), 3);
    BOOST_CHECK_EQUAL(std::string(result[0][1].asCString()), "FG_SLICE");
    BOOST_REQUIRE(result[0][2].isArray());
    BOOST_REQUIRE_EQUAL(result[0][2].size(), 2);
    BOOST_CHECK_EQUAL(std::string(
            result[0][2][0][0].asCString()), "VisuCoreOrientation");
    BOOST_CHECK_EQUAL(result[0][2][0][1].asInt(), 0);
    BOOST_CHECK_EQUAL(std::string(
            result[0][2][1][0].asCString()), "VisuCorePosition");
    BOOST_CHECK_EQUAL(result[0][2][1][1].asInt(), 0);
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Static Function getFrameGroupIndex
 */
BOOST_FIXTURE_TEST_CASE(getFrameGroupIndex, TestDataFrameIndexGenerator)
{
    std::stringstream stream;
    stream << "JSON.stringify("
           << "dicomifier.bruker2dicom.getFrameGroupIndex(createBrukerDataset(), "
           << "'VisuCoreOrientation'));";

    Json::Value const result = get_json_result(stream.str());

    BOOST_REQUIRE(result.isArray());
    BOOST_REQUIRE_EQUAL(result.size(), 2);
    BOOST_REQUIRE_EQUAL(result[0].asInt(), 0);
    BOOST_REQUIRE_EQUAL(result[1].asInt(), 0);
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Static Function getFrameGroupIndex
 *                    Empty BrukerField
 */
BOOST_FIXTURE_TEST_CASE(getFrameGroupIndex_EmptyBrukerField,
                        TestDataFrameIndexGenerator)
{
    std::stringstream stream;
    stream << "JSON.stringify("
           << "dicomifier.bruker2dicom.getFrameGroupIndex(createBrukerDataset(), "
           << "null));";

    Json::Value const result = get_json_result(stream.str());

    BOOST_REQUIRE(result.isNull());
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Static Function getFrameGroupIndex
 *                    BrukerField not found
 */
BOOST_FIXTURE_TEST_CASE(getFrameGroupIndex_BrukerFieldNotFound,
                        TestDataFrameIndexGenerator)
{
    std::stringstream stream;
    stream << "JSON.stringify("
           << "dicomifier.bruker2dicom.getFrameGroupIndex(createBrukerDataset(), "
           << "'NotAGoodField'));";

    Json::Value const result = get_json_result(stream.str());

    BOOST_REQUIRE(result.isNull());
}

/*************************** TEST Error *********************************/
/**
 * Error test case: Static Function GetFrameGroups
 *                  Empty Bruker Dataset
 */
BOOST_FIXTURE_TEST_CASE(GetFrameGroups_NoBrukerDataset,
                        TestDataFrameIndexGenerator)
{
    std::string const script("dicomifier.bruker2dicom.getFrameGroups(null);");
    BOOST_REQUIRE_THROW(jsvm.run(script, jsvm.get_context()),
                        dicomifier::DicomifierException);
}

/*************************** TEST Error *********************************/
/**
 * Error test case: Static Function getFrameGroupIndex
 *                  Empty Bruker Dataset
 */
BOOST_FIXTURE_TEST_CASE(getFrameGroupIndex_NoBrukerDataset,
                        TestDataFrameIndexGenerator)
{
    std::string script("dicomifier.bruker2dicom.getFrameGroupIndex(null);");
    BOOST_REQUIRE_THROW(jsvm.run(script, jsvm.get_context()),
                        dicomifier::DicomifierException);
}
