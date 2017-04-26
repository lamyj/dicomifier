/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE grammar
#include <boost/test/unit_test.hpp>

#include <string>

#include "bruker/grammar.h"
#include "bruker/Field.h"
#include "core/DicomifierException.h"

std::vector<dicomifier::bruker::Field> parse(std::string const & value)
{
    auto begin = value.begin();
    auto const end = value.end();

    std::vector<dicomifier::bruker::Field> fields;
    dicomifier::bruker::grammar<std::string::const_iterator> g;
    auto const parsed = boost::spirit::qi::parse(begin, end, g, fields);

    // Make sure everything was parsed
    BOOST_REQUIRE(parsed);
    BOOST_REQUIRE(begin == end);

    return fields;
}

BOOST_AUTO_TEST_CASE(Comment)
{
    std::string const value = "$$Comment";
    auto const fields = parse(value);

    BOOST_REQUIRE(fields.empty());
}

BOOST_AUTO_TEST_CASE(UnquotedString)
{
    std::string const value = "##FieldName=A few words";
    auto const fields = parse(value);

    BOOST_REQUIRE_EQUAL(fields.size(), 1);
    BOOST_REQUIRE_EQUAL(fields[0].name, "FieldName");
    BOOST_REQUIRE(
        fields[0].value == dicomifier::bruker::Field::Value({"A few words"}));
}

BOOST_AUTO_TEST_CASE(QuotedStrings)
{
    std::string const value = "##FieldName=( 3, 5 )\n<foo> <bar>";
    auto const fields = parse(value);

    BOOST_REQUIRE_EQUAL(fields.size(), 1);
    BOOST_REQUIRE_EQUAL(fields[0].name, "FieldName");
    BOOST_REQUIRE(fields[0].shape == dicomifier::bruker::Field::Shape({3, 5}));
    BOOST_REQUIRE(
        fields[0].value == dicomifier::bruker::Field::Value({"foo", "bar"}));
}

BOOST_AUTO_TEST_CASE(Reals)
{
    std::string const value = "##FieldName=( 2 )\n1.23 -4.56";
    auto const fields = parse(value);

    BOOST_REQUIRE_EQUAL(fields.size(), 1);
    BOOST_REQUIRE_EQUAL(fields[0].name, "FieldName");
    BOOST_REQUIRE(fields[0].shape == dicomifier::bruker::Field::Shape({2}));
    BOOST_REQUIRE(
        fields[0].value == dicomifier::bruker::Field::Value({1.23f, -4.56f}));
}

BOOST_AUTO_TEST_CASE(Integers)
{
    std::string const value = "##FieldName=( 2 )\n123 -456";
    auto const fields = parse(value);

    BOOST_REQUIRE_EQUAL(fields.size(), 1);
    BOOST_REQUIRE_EQUAL(fields[0].name, "FieldName");
    BOOST_REQUIRE(fields[0].shape == dicomifier::bruker::Field::Shape({2}));
    BOOST_REQUIRE(
        fields[0].value == dicomifier::bruker::Field::Value({123L, -456L}));
}

BOOST_AUTO_TEST_CASE(Structure)
{
    std::string const value = "##FieldName=( 1 )\n(3, <Foo>)";
    auto const fields = parse(value);

    BOOST_REQUIRE_EQUAL(fields.size(), 1);
    BOOST_REQUIRE_EQUAL(fields[0].name, "FieldName");
    BOOST_REQUIRE(fields[0].shape == dicomifier::bruker::Field::Shape({1}));

    dicomifier::bruker::Field::Value const item({3L, "Foo"});
    BOOST_REQUIRE(
        fields[0].value == dicomifier::bruker::Field::Value({{item}}));
}
