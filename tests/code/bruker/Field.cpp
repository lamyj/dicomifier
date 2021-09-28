/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE Field
#include <boost/test/unit_test.hpp>

#include "bruker/Field.h"
#include "core/Exception.h"

BOOST_AUTO_TEST_CASE(DefaultConstructor)
{
    dicomifier::bruker::Field const field;
    BOOST_REQUIRE(field.name.empty());
    BOOST_REQUIRE(field.shape.empty());
    BOOST_REQUIRE(field.value.empty());
}

BOOST_AUTO_TEST_CASE(Constructor)
{
    dicomifier::bruker::Field const field("name", {1, 2}, {"foo", 3L});
    BOOST_REQUIRE_EQUAL(field.name, "name");
    BOOST_REQUIRE(field.shape == dicomifier::bruker::Field::Shape({1, 2}));
    BOOST_REQUIRE(field.value == dicomifier::bruker::Field::Value({"foo", 3L}));
}

BOOST_AUTO_TEST_CASE(String)
{
    dicomifier::bruker::Field const field("name", {}, {"foo"});
    BOOST_REQUIRE(field.is_string(0));
    BOOST_REQUIRE_EQUAL(field.get_string(0), "foo");
}

BOOST_AUTO_TEST_CASE(BadString)
{
    dicomifier::bruker::Field const field("name", {}, {123L});
    BOOST_REQUIRE_THROW(field.get_string(0), std::exception);
}

BOOST_AUTO_TEST_CASE(Int)
{
    dicomifier::bruker::Field const field("name", {}, {123L});
    BOOST_REQUIRE(field.is_int(0));
    BOOST_REQUIRE_EQUAL(field.get_int(0), 123);
}

BOOST_AUTO_TEST_CASE(BadInt)
{
    dicomifier::bruker::Field const field("name", {}, {1.23f});
    BOOST_REQUIRE_THROW(field.get_int(0), std::exception);
}

BOOST_AUTO_TEST_CASE(Real)
{
    dicomifier::bruker::Field const field("name", {}, {1.23f});
    BOOST_REQUIRE(field.is_real(0));
    BOOST_REQUIRE_CLOSE(field.get_real(0), 1.23, 1e-3);
}

BOOST_AUTO_TEST_CASE(Struct)
{
    dicomifier::bruker::Field::Value const item({1L, "foo"});
    dicomifier::bruker::Field const field(
        "name", {}, dicomifier::bruker::Field::Value({{item}}));
    BOOST_REQUIRE(field.is_struct(0));
    BOOST_REQUIRE(field.get_struct(0) == item);
}

BOOST_AUTO_TEST_CASE(BadStruct)
{
    dicomifier::bruker::Field const field("name", {}, {123L});
    BOOST_REQUIRE_THROW(field.get_struct(0), std::exception);
}

BOOST_AUTO_TEST_CASE(MixedTypes)
{
    dicomifier::bruker::Field::Value const item({1L, "foo"});
    dicomifier::bruker::Field const field("name", {}, {2L, "bar", -3.45f, item});

    BOOST_REQUIRE(field.is_int(0));
    BOOST_REQUIRE_EQUAL(field.get_int(0), 2);

    BOOST_REQUIRE(field.is_string(1));
    BOOST_REQUIRE_EQUAL(field.get_string(1), "bar");

    BOOST_REQUIRE(field.is_real(2));
    BOOST_REQUIRE_CLOSE(field.get_real(2), -3.45, 1e-3);

    BOOST_REQUIRE(field.is_struct(3));
    BOOST_REQUIRE(field.get_struct(3) == item);
}

BOOST_AUTO_TEST_CASE(Comparison)
{
    dicomifier::bruker::Field const field1("name", {1,2}, {"foo"});
    dicomifier::bruker::Field const field2("name", {1,2}, {"foo"});
    dicomifier::bruker::Field const field3("other_name", {1,2}, {"foo"});
    dicomifier::bruker::Field const field4("name", {3,4,5}, {"foo"});
    dicomifier::bruker::Field const field5("name", {1,2}, {"bar"});
    dicomifier::bruker::Field const field6("name", {1,2}, {42L});

    BOOST_REQUIRE(field1 == field2); BOOST_REQUIRE(!(field1 != field2));
    BOOST_REQUIRE(field1 != field3); BOOST_REQUIRE(!(field1 == field3));
    BOOST_REQUIRE(field1 != field4); BOOST_REQUIRE(!(field1 == field4));
    BOOST_REQUIRE(field1 != field5); BOOST_REQUIRE(!(field1 == field5));
    BOOST_REQUIRE(field1 != field6); BOOST_REQUIRE(!(field1 == field6));
}
