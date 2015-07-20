/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE Modulejson_converter
#include <boost/test/unit_test.hpp>

#include <fstream>

#include <jsoncpp/json/json.h>

#include "bruker/Dataset.h"
#include "bruker/json_converter.h"

class TestData
{
public:
    std::string filepath;
    dicomifier::bruker::Dataset data_set;

    TestData() : filepath("./tmp_test_file_json_converter.txt")
    {
        // NOthing to do
    }

    virtual ~TestData()
    {
        remove(filepath.c_str());
    }
};

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Empty Dataset
 */
BOOST_AUTO_TEST_CASE(AsJSONEmpty)
{
    dicomifier::bruker::Dataset data_set;
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.empty());
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Convert a String field
 */
class TestDataStringValue : public TestData
{
public:
    TestDataStringValue() : TestData()
    {
        std::ofstream myfile;
        myfile.open(this->filepath);
        myfile << "##AttributeName=string value\n";
        myfile << "##END=\n";
        myfile.close();

        this->data_set.load(this->filepath);
    }

};

BOOST_FIXTURE_TEST_CASE(StringValue, TestDataStringValue)
{
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.isObject());
    BOOST_REQUIRE(json["AttributeName"].isArray());
    BOOST_REQUIRE(json["AttributeName"].get(Json::Value::ArrayIndex(0),
                                            Json::Value()).isString());
    BOOST_REQUIRE_EQUAL(json["AttributeName"].get(Json::Value::ArrayIndex(0),
                                                  Json::Value()).asString(),
                        "string value");
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Convert a Int field
 */
class TestDataIntValue : public TestData
{
public:
    TestDataIntValue() : TestData()
    {
        std::ofstream myfile;
        myfile.open(this->filepath);
        myfile << "##AttributeName=( 1 )\n";
        myfile << "12\n";
        myfile << "##END=\n";
        myfile.close();

        this->data_set.load(this->filepath);
    }

};

BOOST_FIXTURE_TEST_CASE(IntValue, TestDataIntValue)
{
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.isObject());
    BOOST_REQUIRE(json["AttributeName"].isArray());
    BOOST_REQUIRE(json["AttributeName"].get(Json::Value::ArrayIndex(0),
                                            Json::Value()).isInt());
    BOOST_REQUIRE_EQUAL(json["AttributeName"].get(Json::Value::ArrayIndex(0),
                                                  Json::Value()).asInt(),
                        12);
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Convert a Float field
 */
class TestDataFloatValue : public TestData
{
public:
    TestDataFloatValue() : TestData()
    {
        std::ofstream myfile;
        myfile.open(this->filepath);
        myfile << "##AttributeName=( 1 )\n";
        myfile << "12.56\n";
        myfile << "##END=\n";
        myfile.close();

        this->data_set.load(this->filepath);
    }

};

BOOST_FIXTURE_TEST_CASE(FloatValue, TestDataFloatValue)
{
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.isObject());
    BOOST_REQUIRE(json["AttributeName"].isArray());
    BOOST_REQUIRE(json["AttributeName"].get(Json::Value::ArrayIndex(0),
                                            Json::Value()).isDouble());
    BOOST_REQUIRE_CLOSE(json["AttributeName"].get(Json::Value::ArrayIndex(0),
                                                  Json::Value()).asDouble(),
                        12.56, 0.0001);
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Convert a multi-values field
 */
class TestDataMultiValue : public TestData
{
public:
    TestDataMultiValue() : TestData()
    {
        std::ofstream myfile;
        myfile.open(this->filepath);
        myfile << "##AttributeInt=( 3 )\n";
        myfile << "12 -5 42\n";
        myfile << "##AttributeFloat=( 3 )\n";
        myfile << "12.56 -5.74 42.15\n";
        myfile << "##AttributeString=( 3 )\n";
        myfile << "string1 string2 string3\n";
        myfile << "##END=\n";
        myfile.close();

        this->data_set.load(this->filepath);
    }

};

BOOST_FIXTURE_TEST_CASE(MultiValue, TestDataMultiValue)
{
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.isObject());

    BOOST_REQUIRE(json["AttributeInt"].isArray());
    BOOST_REQUIRE(json["AttributeInt"].get(Json::Value::ArrayIndex(0),
                                            Json::Value()).isInt());
    BOOST_REQUIRE(json["AttributeInt"].get(Json::Value::ArrayIndex(1),
                                            Json::Value()).isInt());
    BOOST_REQUIRE(json["AttributeInt"].get(Json::Value::ArrayIndex(2),
                                            Json::Value()).isInt());
    BOOST_REQUIRE_EQUAL(json["AttributeInt"].get(Json::Value::ArrayIndex(0),
                                                 Json::Value()).asInt(),
                        12);
    BOOST_REQUIRE_EQUAL(json["AttributeInt"].get(Json::Value::ArrayIndex(1),
                                                 Json::Value()).asInt(),
                        -5);
    BOOST_REQUIRE_EQUAL(json["AttributeInt"].get(Json::Value::ArrayIndex(2),
                                                 Json::Value()).asInt(),
                        42);

    BOOST_REQUIRE(json["AttributeFloat"].isArray());
    BOOST_REQUIRE(json["AttributeFloat"].get(Json::Value::ArrayIndex(0),
                                             Json::Value()).isDouble());
    BOOST_REQUIRE(json["AttributeFloat"].get(Json::Value::ArrayIndex(1),
                                             Json::Value()).isDouble());
    BOOST_REQUIRE(json["AttributeFloat"].get(Json::Value::ArrayIndex(2),
                                             Json::Value()).isDouble());
    BOOST_REQUIRE_CLOSE(json["AttributeFloat"].get(Json::Value::ArrayIndex(0),
                                                   Json::Value()).asDouble(),
                        12.56, 0.0001);
    BOOST_REQUIRE_CLOSE(json["AttributeFloat"].get(Json::Value::ArrayIndex(1),
                                                   Json::Value()).asDouble(),
                        -5.74, 0.0001);
    BOOST_REQUIRE_CLOSE(json["AttributeFloat"].get(Json::Value::ArrayIndex(2),
                                                   Json::Value()).asDouble(),
                        42.15, 0.0001);

    BOOST_REQUIRE(json["AttributeString"].isArray());
    BOOST_REQUIRE(json["AttributeString"].get(Json::Value::ArrayIndex(0),
                                              Json::Value()).isString());
    BOOST_REQUIRE(json["AttributeString"].get(Json::Value::ArrayIndex(1),
                                              Json::Value()).isString());
    BOOST_REQUIRE(json["AttributeString"].get(Json::Value::ArrayIndex(2),
                                              Json::Value()).isString());
    BOOST_REQUIRE_EQUAL(json["AttributeString"].get(Json::Value::ArrayIndex(0),
                                                    Json::Value()).asString(),
                        "string1");
    BOOST_REQUIRE_EQUAL(json["AttributeString"].get(Json::Value::ArrayIndex(1),
                                                    Json::Value()).asString(),
                        "string2");
    BOOST_REQUIRE_EQUAL(json["AttributeString"].get(Json::Value::ArrayIndex(2),
                                                    Json::Value()).asString(),
                        "string3");
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Convert a struct field
 */
class TestDataStructValue : public TestData
{
public:
    TestDataStructValue() : TestData()
    {
        std::ofstream myfile;
        myfile.open(this->filepath);
        myfile << "##AttributeStruct=( 1 )\n";
        myfile << "(1, <text>, <>, 0, 2)\n";
        myfile << "##END=\n";
        myfile.close();

        this->data_set.load(this->filepath);
    }

};

BOOST_FIXTURE_TEST_CASE(StructValue, TestDataStructValue)
{
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.isObject());

    BOOST_REQUIRE(json["AttributeStruct"].isArray());
    BOOST_REQUIRE(json["AttributeStruct"].get(Json::Value::ArrayIndex(0),
                                            Json::Value()).isArray());
    BOOST_REQUIRE_EQUAL(json["AttributeStruct"].get(Json::Value::ArrayIndex(0),
                                                    Json::Value()).
                                                get(Json::Value::ArrayIndex(0),
                                                    Json::Value()).asInt(),
                        1);
    BOOST_REQUIRE_EQUAL(json["AttributeStruct"].get(Json::Value::ArrayIndex(0),
                                                    Json::Value()).
                                                get(Json::Value::ArrayIndex(1),
                                                    Json::Value()).asString(),
                        "text");
    BOOST_REQUIRE_EQUAL(json["AttributeStruct"].get(Json::Value::ArrayIndex(0),
                                                    Json::Value()).
                                                get(Json::Value::ArrayIndex(2),
                                                    Json::Value()).asString(),
                        "");
    BOOST_REQUIRE_EQUAL(json["AttributeStruct"].get(Json::Value::ArrayIndex(0),
                                                    Json::Value()).
                                                get(Json::Value::ArrayIndex(3),
                                                    Json::Value()).asInt(),
                        0);
    BOOST_REQUIRE_EQUAL(json["AttributeStruct"].get(Json::Value::ArrayIndex(0),
                                                    Json::Value()).
                                                get(Json::Value::ArrayIndex(4),
                                                    Json::Value()).asInt(),
                        2);
}
