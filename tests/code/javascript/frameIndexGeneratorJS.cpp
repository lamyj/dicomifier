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
#include <string>

#include "core/DicomifierException.h"
#include "javascript/JavascriptVM.h"

struct TestDataFrameIndexGenerator
{
    dicomifier::javascript::JavascriptVM vm;
    std::stringstream streamscript;

    TestDataFrameIndexGenerator()
    {
        streamscript << "require('bruker2dicom/frame_index_generator.js');"
                     << "var brukerDataset = { "
                     <<         "\"VisuFGOrderDesc\":[[3,\"FG_SLICE\",\"\",0,2]], "
                     <<         "\"VisuFGOrderDescDim\":[\"1\"], "
                     <<         "\"VisuGroupDepVals\":[[\"VisuCoreOrientation\",0], "
                     <<                               "[\"VisuCorePosition\",0]] };"
                     << "var frameGroups = "
                     <<     "dicomifier.bruker2dicom.getFrameGroups(brukerDataset); "
                     << "var indexGenerator = "
                     <<     "new dicomifier.bruker2dicom.FrameIndexGenerator(frameGroups); ";
    }

    ~TestDataFrameIndexGenerator()
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
    std::stringstream stream;
    stream << streamscript.str()
           << "JSON.stringify(indexGenerator);";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream outputstream;
    outputstream << *utf8;

    BOOST_REQUIRE_EQUAL(
     outputstream.str(),
     "{\"indexMax\":[3],\"currentIndex\":[0],\"countMax\":3,\"currentStep\":0}");
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function Done
 */
BOOST_FIXTURE_TEST_CASE(Done, TestDataFrameIndexGenerator)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "String(indexGenerator.done());";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream outputstream;
    outputstream << *utf8;

    BOOST_REQUIRE_EQUAL(outputstream.str(), "false");
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function Next
 */
BOOST_FIXTURE_TEST_CASE(Next, TestDataFrameIndexGenerator)
{
    // initial State
    vm.run(streamscript.str(), vm.get_context());

    // increase
    for (unsigned int i = 0; i < 3; ++i)
    {
        auto result = vm.run("JSON.stringify(indexGenerator);", vm.get_context());
        v8::String::Utf8Value utf8(result);

        std::stringstream outputstream;
        outputstream << *utf8;

        std::stringstream expectedresult;
        expectedresult << "{\"indexMax\":[3],\"currentIndex\":[" << i
                       << "],\"countMax\":3,\"currentStep\":" << i << "}";
        BOOST_REQUIRE_EQUAL(outputstream.str(), expectedresult.str());

        vm.run("indexGenerator.next();", vm.get_context());
    }

    // Done == true
    {
        auto result = vm.run("String(indexGenerator.done());", vm.get_context());
        v8::String::Utf8Value utf8(result);

        std::stringstream outputstream;
        outputstream << *utf8;

        BOOST_REQUIRE_EQUAL(outputstream.str(), "true");
    }
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Static Function GetFrameGroups
 */
BOOST_FIXTURE_TEST_CASE(GetFrameGroups, TestDataFrameIndexGenerator)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "JSON.stringify(frameGroups);";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream outputstream;
    outputstream << *utf8;

    std::stringstream expectedresult;
    expectedresult << "[[3,\"FG_SLICE\",[[\"VisuCoreOrientation\",0],"
                   <<                   "[\"VisuCorePosition\",0]]]]";
    BOOST_REQUIRE_EQUAL(outputstream.str(), expectedresult.str());
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Static Function getFrameGroupIndex
 */
BOOST_FIXTURE_TEST_CASE(getFrameGroupIndex, TestDataFrameIndexGenerator)
{
    std::stringstream stream;
    stream << streamscript.str()
           << "JSON.stringify(dicomifier.bruker2dicom.getFrameGroupIndex(brukerDataset, "
           << "'VisuCoreOrientation'));";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream outputstream;
    outputstream << *utf8;

    BOOST_REQUIRE_EQUAL(outputstream.str(), "[0,0]");
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
    stream << streamscript.str()
           << "JSON.stringify(dicomifier.bruker2dicom.getFrameGroupIndex(brukerDataset, "
           << "null));";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream outputstream;
    outputstream << *utf8;

    BOOST_REQUIRE_EQUAL(outputstream.str(), "null");
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
    stream << streamscript.str()
           << "JSON.stringify(dicomifier.bruker2dicom.getFrameGroupIndex(brukerDataset, "
           << "'NotAGoodField'));";

    auto result = vm.run(stream.str(), vm.get_context());
    v8::String::Utf8Value utf8(result);

    std::stringstream outputstream;
    outputstream << *utf8;

    BOOST_REQUIRE_EQUAL(outputstream.str(), "null");
}

/*************************** TEST Error *********************************/
/**
 * Error test case: Static Function GetFrameGroups
 *                  Empty Bruker Dataset
 */
BOOST_FIXTURE_TEST_CASE(GetFrameGroups_NoBrukerDataset,
                        TestDataFrameIndexGenerator)
{
    std::string script("var frameGroups = dicomifier.bruker2dicom.getFrameGroups(null);");
    BOOST_REQUIRE_THROW(
        vm.run(script, vm.get_context()),
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
    BOOST_REQUIRE_THROW(
        vm.run(script, vm.get_context()),
        dicomifier::DicomifierException);
}
