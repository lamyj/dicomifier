/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE json_converter
#include <boost/test/unit_test.hpp>

#include <json/json.h>

#include "bruker/Dataset.h"
#include "bruker/Field.h"
#include "bruker/json_converter.h"

BOOST_AUTO_TEST_CASE(EmptyAsJSON)
{
    dicomifier::bruker::Dataset data_set;
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.empty());
}

BOOST_AUTO_TEST_CASE(StringAsJson)
{
    dicomifier::bruker::Dataset data_set;
    data_set.set_field(dicomifier::bruker::Field("Name", {}, {"value"}));
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.isObject());
    BOOST_REQUIRE(json["Name"].isArray());
    BOOST_REQUIRE_EQUAL(json["Name"].size(), 1);
    BOOST_REQUIRE(json["Name"][0].isString());
    BOOST_REQUIRE_EQUAL(json["Name"][0].asString(), "value");
}

BOOST_AUTO_TEST_CASE(IntAsJson)
{
    dicomifier::bruker::Dataset data_set;
    data_set.set_field(dicomifier::bruker::Field("Name", {}, {12L}));
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.isObject());
    BOOST_REQUIRE(json["Name"].isArray());
    BOOST_REQUIRE_EQUAL(json["Name"].size(), 1);
    BOOST_REQUIRE(json["Name"][0].isInt());
    BOOST_REQUIRE_EQUAL(json["Name"][0].asInt(), 12);
}

BOOST_AUTO_TEST_CASE(FloatAsJson)
{
    dicomifier::bruker::Dataset data_set;
    data_set.set_field(dicomifier::bruker::Field("Name", {}, {12.56f}));
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.isObject());
    BOOST_REQUIRE(json["Name"].isArray());
    BOOST_REQUIRE_EQUAL(json["Name"].size(), 1);
    BOOST_REQUIRE(json["Name"][0].isDouble());
    BOOST_REQUIRE_CLOSE(json["Name"][0].asDouble(), 12.56, 1e-3);
}

BOOST_AUTO_TEST_CASE(StructAsJson)
{
    dicomifier::bruker::Dataset data_set;
    data_set.set_field(
        dicomifier::bruker::Field("Name", {}, {-5L, 12.56f, "value"}));
    auto const json = dicomifier::bruker::as_json(data_set);
    BOOST_REQUIRE(json.isObject());
    BOOST_REQUIRE(json["Name"].isArray());
    BOOST_REQUIRE_EQUAL(json["Name"].size(), 3);

    BOOST_REQUIRE(json["Name"][0].isInt());
    BOOST_REQUIRE_EQUAL(json["Name"][0].asInt(), -5);

    BOOST_REQUIRE(json["Name"][1].isDouble());
    BOOST_REQUIRE_CLOSE(json["Name"][1].asDouble(), 12.56, 1e-3);

    BOOST_REQUIRE(json["Name"][2].isString());
    BOOST_REQUIRE_EQUAL(json["Name"][2].asString(), "value");
}

BOOST_AUTO_TEST_CASE(EmptyAsDataset)
{
    Json::Value json;
    auto const data_set = dicomifier::bruker::as_dataset(json);
    BOOST_REQUIRE(data_set.begin() == data_set.end());
}

BOOST_AUTO_TEST_CASE(IntAsDataset)
{
    Json::Value json;
    json["Name"].append(12);
    auto const data_set = dicomifier::bruker::as_dataset(json);
    BOOST_REQUIRE(data_set.has_field("Name"));

    auto const & field = data_set.get_field("Name");
    BOOST_REQUIRE_EQUAL(field.name, "Name");
    BOOST_REQUIRE(field.value == dicomifier::bruker::Field::Value({12L}));
}

BOOST_AUTO_TEST_CASE(FloatAsDataset)
{
    Json::Value json;
    json["Name"].append(12.56);
    auto const data_set = dicomifier::bruker::as_dataset(json);
    BOOST_REQUIRE(data_set.has_field("Name"));

    auto const & field = data_set.get_field("Name");
    BOOST_REQUIRE_EQUAL(field.name, "Name");
    BOOST_REQUIRE(field.value == dicomifier::bruker::Field::Value({12.56f}));
}

BOOST_AUTO_TEST_CASE(StringAsDataset)
{
    Json::Value json;
    json["Name"].append("foo");
    auto const data_set = dicomifier::bruker::as_dataset(json);
    BOOST_REQUIRE(data_set.has_field("Name"));

    auto const & field = data_set.get_field("Name");
    BOOST_REQUIRE_EQUAL(field.name, "Name");
    BOOST_REQUIRE(field.value == dicomifier::bruker::Field::Value({"foo"}));
}

BOOST_AUTO_TEST_CASE(StructAsDataset)
{
    Json::Value json_item;
    json_item.append(12);
    json_item.append(12.56);
    json_item.append("foo");

    Json::Value json;
    json["Name"].append(json_item);
    auto const data_set = dicomifier::bruker::as_dataset(json);
    BOOST_REQUIRE(data_set.has_field("Name"));

    auto const & field = data_set.get_field("Name");
    BOOST_REQUIRE_EQUAL(field.name, "Name");

    dicomifier::bruker::Field::Value const bruker_item({12L, 12.56f, "foo"});
    BOOST_REQUIRE(field.value == dicomifier::bruker::Field::Value({bruker_item}));
}
