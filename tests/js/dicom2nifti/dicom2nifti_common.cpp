/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleJSDicom2nifti_Common
#include <boost/test/unit_test.hpp>

#include <sstream>

#include "../TestDataJS.h"

class TestData : public TestDataJS
{
public:
    TestData() : TestDataJS()
    {
        // include files
        std::string const include_("require(\"common.js\");\n"
                                   "require(\"dicom2nifti/common.js\");");
        jsvm.run(include_, jsvm.get_context());
    }

    virtual ~TestData()
    {
        // nothing to do
    }
};

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function getKeys
 */
BOOST_FIXTURE_TEST_CASE(getKeys, TestData)
{
    // all keys are present
    {
    std::stringstream script;
    script << "function testAll() {\n"
           << "var dataset = { '00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                 "'00180080': { 'VR': 'DS', 'Value': [ 100 ] }, "
           <<                 "'00180081': { 'VR': 'DS', 'Value': [ 3 ] }, "
           <<                 "'00180082': { 'VR': 'DS', 'Value': [ 5 ] } };\n"
           << "return dicomifier.dicom2nifti.getKeys(dataset);\n"
           << "}\n"
           << "JSON.stringify(testAll());";

    Json::Value const jsondataset = get_json_result(script.str());

    // check result
    BOOST_CHECK(jsondataset.isObject());
    BOOST_CHECK_EQUAL(jsondataset.size(), 4);
    // check array 00200037
    BOOST_CHECK(jsondataset.get("00200037", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("00200037", Json::Value()).size(), 6);
    // check array 00180080
    BOOST_CHECK(jsondataset.get("00180080", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("00180080", Json::Value()).size(), 1);
    BOOST_CHECK_EQUAL(jsondataset.get("00180080", Json::Value())[0].asInt(), 100);
    // check array 00180081
    BOOST_CHECK(jsondataset.get("00180081", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("00180081", Json::Value()).size(), 1);
    BOOST_CHECK_EQUAL(jsondataset.get("00180081", Json::Value())[0].asInt(), 3);
    // check array 00180082
    BOOST_CHECK(jsondataset.get("00180082", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("00180082", Json::Value()).size(), 1);
    BOOST_CHECK_EQUAL(jsondataset.get("00180082", Json::Value())[0].asInt(), 5);
    }

    // no key
    {
    std::stringstream script;
    script << "function testNoKey() {\n"
           << "var dataset = { '00080060': { 'VR': 'CS', 'Value': [ 'MR' ] } };\n"
           << "return dicomifier.dicom2nifti.getKeys(dataset);\n"
           << "}\n"
           << "JSON.stringify(testNoKey());";

    Json::Value const jsondataset = get_json_result(script.str());

    // check result
    BOOST_CHECK(jsondataset.isObject());
    BOOST_CHECK_EQUAL(jsondataset.size(), 0);
    }

    // Missing key
    {
    std::stringstream script;
    script << "function testMissingOne() {\n"
           << "var dataset = { '00080060': { 'VR': 'CS', 'Value': [ 'MR' ] }, "
           <<                 "'00180080': { 'VR': 'DS', 'Value': [ 100 ] }, "
           <<                 "'00180081': { 'VR': 'DS', 'Value': [ 3 ] }, "
           <<                 "'00180082': { 'VR': 'DS', 'Value': [ 5 ] } };\n"
           << "return dicomifier.dicom2nifti.getKeys(dataset);\n"
           << "}\n"
           << "JSON.stringify(testMissingOne());";

    Json::Value const jsondataset = get_json_result(script.str());

    // check result
    BOOST_CHECK(jsondataset.isObject());
    BOOST_CHECK_EQUAL(jsondataset.size(), 3);
    // check array 00180080
    BOOST_CHECK(jsondataset.get("00180080", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("00180080", Json::Value()).size(), 1);
    BOOST_CHECK_EQUAL(jsondataset.get("00180080", Json::Value())[0].asInt(), 100);
    // check array 00180081
    BOOST_CHECK(jsondataset.get("00180081", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("00180081", Json::Value()).size(), 1);
    BOOST_CHECK_EQUAL(jsondataset.get("00180081", Json::Value())[0].asInt(), 3);
    // check array 00180082
    BOOST_CHECK(jsondataset.get("00180082", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("00180082", Json::Value()).size(), 1);
    BOOST_CHECK_EQUAL(jsondataset.get("00180082", Json::Value())[0].asInt(), 5);
    }
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function closeEquals
 */
BOOST_FIXTURE_TEST_CASE(closeEquals, TestData)
{
    // Close equals
    {
    std::stringstream script;
    script << "function testClose() {\n"
           << "var vector1 = [ 1, 0, 0, 0, 1, 0 ];\n"
           << "var vector2 = [ 1, 0, 0.005, 0, 1, 0 ];\n"
           << "return closeEquals(vector1, vector2);\n"
           << "}\n"
           << "testClose();";

    auto const result = jsvm.run(script.str(), jsvm.get_context());

    BOOST_REQUIRE( result->ToBoolean()->Value() );
    }

    // Not close
    {
    std::stringstream script;
    script << "function testNotClose() {\n"
           << "var vector1 = [ 1, 0, 0, 0, 1, 0 ];\n"
           << "var vector2 = [ 1, 0, 5, 0, 1, 0 ];\n"
           << "return closeEquals(vector1, vector2);\n"
           << "}\n"
           << "testNotClose();";

    auto const result = jsvm.run(script.str(), jsvm.get_context());

    BOOST_REQUIRE( !result->ToBoolean()->Value() );
    }
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function findStack
 */
BOOST_FIXTURE_TEST_CASE(findStack, TestData)
{
    // No stack
    {
    std::stringstream script;
    script << "JSON.stringify(dicomifier.dicom2nifti.findStack({}, {}));";

    Json::Value const jsondataset = get_json_result(script.str());

    BOOST_REQUIRE(jsondataset.isNull());
    }

    // Not find
    {
    std::stringstream script;
    script << "function testNotFind() {\n"
           << "var dataset = { '00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                 "'00180080': { 'VR': 'DS', 'Value': [ 100 ] }, "
           <<                 "'00180081': { 'VR': 'DS', 'Value': [ 3 ] }, "
           <<                 "'00180082': { 'VR': 'DS', 'Value': [ 5 ] } };\n"
           << "var stack = [[{ '00200037': [ 1, 0, 0, 0, 1, 0 ], "
           <<                 "'00180080': [ 100 ], "
           <<                 "'00180081': [ 3 ], "
           <<                 "'00180082': [ 4 ] }, []]];\n"
           << "return dicomifier.dicom2nifti.findStack(stack, dataset);\n"
           << "}\n"
           << "JSON.stringify(testNotFind());";

    Json::Value const jsondataset = get_json_result(script.str());

    BOOST_REQUIRE(jsondataset.isNull());
    }

    // find
    {
    std::stringstream script;
    script << "function testFind() {\n"
           << "var dataset = { '00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                 "'00180080': { 'VR': 'DS', 'Value': [ 100 ] }, "
           <<                 "'00180081': { 'VR': 'DS', 'Value': [ 3 ] }, "
           <<                 "'00180082': { 'VR': 'DS', 'Value': [ 5 ] } };\n"
           << "var stack = [[{ '00200037': [ 1, 0, 0, 0, 1, 0 ], "
           <<                 "'00180080': [ 100 ], "
           <<                 "'00180081': [ 3 ], "
           <<                 "'00180082': [ 4 ] }, []], "
           <<              "[{ '00200037': [ 1, 0, 0, 0, 1, 0 ], "
           <<                 "'00180080': [ 100 ], "
           <<                 "'00180081': [ 3 ], "
           <<                 "'00180082': [ 5 ] }, []]];\n"
           << "return dicomifier.dicom2nifti.findStack(stack, dataset);\n"
           << "}\n"
           << "testFind();";

    auto const result = jsvm.run(script.str(), jsvm.get_context());

    BOOST_REQUIRE_EQUAL( result->ToInt32()->Value(), 1 );
    }
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function distance
 */
BOOST_FIXTURE_TEST_CASE(distance, TestData)
{
    std::stringstream script;
    script << "function testDistance() {\n"
           << "var position = [12, 12, 5];\n"
           << "var normal = [0, 0, 1];\n"
           << "return dicomifier.dicom2nifti.distance(position, normal);\n"
           << "}\n"
           << "testDistance();";

    auto const result = jsvm.run(script.str(), jsvm.get_context());

    BOOST_REQUIRE_EQUAL( result->ToInt32()->Value(), 5 );
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function sortStack
 */
BOOST_FIXTURE_TEST_CASE(sortStack, TestData)
{
    // Already sort
    {
    std::stringstream script;
    script << "function testSortAlready() {\n"
           << "var dataset1 = { '00200032': { 'VR': 'DS', 'Value': [ 10, 10, 0 ] }, "
           <<                  "'00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                  "'00200013': { 'VR': 'IS', 'Value': [ 1 ] }, "
           <<                  "'00180081': { 'VR': 'DS', 'Value': [ 3 ] } };\n"
           << "var dataset2 = { '00200032': { 'VR': 'DS', 'Value': [ 10, 10, 5 ] }, "
           <<                  "'00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                  "'00200013': { 'VR': 'IS', 'Value': [ 2 ] }, "
           <<                  "'00180081': { 'VR': 'DS', 'Value': [ 3 ] } };\n"
           << "var dataset3 = { '00200032': { 'VR': 'DS', 'Value': [ 10, 10, 10 ] }, "
           <<                  "'00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                  "'00200013': { 'VR': 'IS', 'Value': [ 3 ] }, "
           <<                  "'00180081': { 'VR': 'DS', 'Value': [ 3 ] } };\n"
           << "var datasets = [ dataset1, dataset2, dataset3 ];\n"
           << "return dicomifier.dicom2nifti.sortStack(datasets);\n"
           << "}\n"
           << "JSON.stringify(testSortAlready());";

    Json::Value const jsondataset = get_json_result(script.str());

    BOOST_REQUIRE(jsondataset.isArray());
    BOOST_REQUIRE_EQUAL(jsondataset.size(), 3);
    for (unsigned int i = 0; i < jsondataset.size(); ++i)
    {
        BOOST_REQUIRE_EQUAL(
            jsondataset[i].get("00200013",
                               Json::Value()).get("Value",
                                                  Json::Value())[0].asInt(),
            i+1);
    }
    }

    // not sort
    {
    std::stringstream script;
    script << "function testSort() {\n"
           << "var dataset1 = { '00200032': { 'VR': 'DS', 'Value': [ 10, 10, 0 ] }, "
           <<                  "'00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                  "'00200013': { 'VR': 'IS', 'Value': [ 1 ] }, "
           <<                  "'00180081': { 'VR': 'DS', 'Value': [ 3 ] } };\n"
           << "var dataset2 = { '00200032': { 'VR': 'DS', 'Value': [ 10, 10, 5 ] }, "
           <<                  "'00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                  "'00200013': { 'VR': 'IS', 'Value': [ 2 ] }, "
           <<                  "'00180081': { 'VR': 'DS', 'Value': [ 3 ] } };\n"
           << "var dataset3 = { '00200032': { 'VR': 'DS', 'Value': [ 10, 10, 10 ] }, "
           <<                  "'00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                  "'00200013': { 'VR': 'IS', 'Value': [ 3 ] }, "
           <<                  "'00180081': { 'VR': 'DS', 'Value': [ 3 ] } };\n"
           << "var datasets = [ dataset3, dataset2, dataset1 ];\n"
           << "return dicomifier.dicom2nifti.sortStack(datasets);\n"
           << "}\n"
           << "JSON.stringify(testSort());";

    Json::Value const jsondataset = get_json_result(script.str());

    BOOST_REQUIRE(jsondataset.isArray());
    BOOST_REQUIRE_EQUAL(jsondataset.size(), 3);
    for (unsigned int i = 0; i < jsondataset.size(); ++i)
    {
        BOOST_REQUIRE_EQUAL(
            jsondataset[i].get("00200013",
                               Json::Value()).get("Value",
                                                  Json::Value())[0].asInt(),
            i+1);
    }
    }
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Function mergeStack
 */
BOOST_FIXTURE_TEST_CASE(mergeStack, TestData)
{
    std::stringstream script;
    script << "function testSort() {\n"
           << "var dictionaryTagToName = {};\n"
           << "for (var key in dicomifier.dictionary) {\n"
           <<     "dictionaryTagToName[dicomifier.dictionary[key][1]] = key;\n"
           << "}\n"
           << "var dataset1 = { '00200032': { 'VR': 'DS', 'Value': [ 10, 10, 0 ] }, "
           <<                  "'00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                  "'00200013': { 'VR': 'IS', 'Value': [ 1 ] }, "
           <<                  "'00180081': { 'VR': 'DS', 'Value': [ 3 ] } };\n"
           << "var dataset2 = { '00200032': { 'VR': 'DS', 'Value': [ 10, 10, 5 ] }, "
           <<                  "'00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                  "'00200013': { 'VR': 'IS', 'Value': [ 2 ] }, "
           <<                  "'00180081': { 'VR': 'DS', 'Value': [ 3 ] } };\n"
           << "var dataset3 = { '00200032': { 'VR': 'DS', 'Value': [ 10, 10, 10 ] }, "
           <<                  "'00200037': { 'VR': 'DS', 'Value': [ 1, 0, 0, 0, 1, 0 ] }, "
           <<                  "'00200013': { 'VR': 'IS', 'Value': [ 3 ] }, "
           <<                  "'00180081': { 'VR': 'DS', 'Value': [ 3 ] } };\n"
           << "var datasets = [ dataset1, dataset2, dataset3 ];\n"
           << "return dicomifier.dicom2nifti.mergeStack(datasets, dictionaryTagToName);\n"
           << "}\n"
           << "JSON.stringify(testSort());";

    Json::Value const jsondataset = get_json_result(script.str());

    BOOST_REQUIRE(jsondataset.isObject());
    BOOST_REQUIRE_EQUAL(jsondataset.size(), 4);
    BOOST_CHECK(jsondataset.get("ImagePositionPatient", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("ImagePositionPatient", Json::Value()).size(), 3);
    BOOST_CHECK(jsondataset.get("ImageOrientationPatient", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("ImageOrientationPatient", Json::Value()).size(), 6);
    BOOST_CHECK(jsondataset.get("InstanceNumber", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("InstanceNumber", Json::Value()).size(), 3);
    BOOST_CHECK(jsondataset.get("EchoTime", Json::Value()).isArray());
    BOOST_CHECK_EQUAL(jsondataset.get("EchoTime", Json::Value()).size(), 1);
    BOOST_CHECK_EQUAL(jsondataset.get("EchoTime", Json::Value())[0].asInt(), 3);
}
