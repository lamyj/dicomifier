/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE Dataset
#include <boost/test/unit_test.hpp>

#include <cstdio>
#include <fstream>

#include "bruker/Dataset.h"
#include "core/DicomifierException.h"

BOOST_AUTO_TEST_CASE(Constructor)
{
    dicomifier::bruker::Dataset data_set;
    BOOST_REQUIRE(!data_set.has_field("SomeField"));
}

struct LoadFixture
{
    std::string filepath;

    LoadFixture()
    : filepath("./test_Dataset_load.txt")
    {
        std::ofstream myfile;
        myfile.open(filepath);
        myfile << "##FieldName=Field Value\n";
        myfile << "##$OtherName=( 2, 60 )\n";
        myfile << "<Other> <Values>\n";
        myfile.close();
    }

    ~LoadFixture()
    {
        std::remove(filepath.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(Load, LoadFixture)
{
    dicomifier::bruker::Dataset data_set;
    data_set.load(filepath);

    BOOST_CHECK(data_set.has_field("FieldName"));
    BOOST_CHECK(
        data_set.get_field("FieldName").value ==
            dicomifier::bruker::Field::Value({"Field Value"}));

    BOOST_CHECK(data_set.has_field("OtherName"));
    BOOST_CHECK(
        data_set.get_field("OtherName").shape ==
            dicomifier::bruker::Field::Shape({2, 60}));
    BOOST_CHECK(
        data_set.get_field("OtherName").value ==
            dicomifier::bruker::Field::Value({"Other", "Values"}));
}

BOOST_AUTO_TEST_CASE(FieldAccess)
{
    dicomifier::bruker::Field const field("FieldName", {1, 2}, {"foo"});
    dicomifier::bruker::Dataset data_set;
    data_set.set_field(field);
    BOOST_REQUIRE(data_set.has_field("FieldName"));
    BOOST_REQUIRE(data_set.get_field("FieldName").name == "FieldName");
    BOOST_REQUIRE(
        data_set.get_field("FieldName").shape ==
            dicomifier::bruker::Field::Shape({1, 2}));
    BOOST_REQUIRE(
        data_set.get_field("FieldName").value ==
            dicomifier::bruker::Field::Value({"foo"}));
}

BOOST_AUTO_TEST_CASE(InvalidFieldAccess)
{
    dicomifier::bruker::Dataset data_set;
    BOOST_REQUIRE_THROW(
        data_set.get_field("FieldName"), dicomifier::DicomifierException);
}

BOOST_AUTO_TEST_CASE(Iterators)
{
    std::vector<dicomifier::bruker::Field> const fields({
        {"Bar", {3, 4}, {"bar"}},
        {"Foo", {1, 2}, {"foo"}}});

    dicomifier::bruker::Dataset data_set;
    data_set.set_field(fields[0]);
    data_set.set_field(fields[1]);

    int i=0;
    for(auto it=data_set.begin(); it!=data_set.end(); ++it, ++i)
    {
        BOOST_REQUIRE(i<fields.size());

        auto const & name = it->first;
        BOOST_REQUIRE_EQUAL(name, fields[i].name);

        auto const & field = it->second;
        BOOST_REQUIRE_EQUAL(field.name, fields[i].name);
        BOOST_REQUIRE(field.shape == fields[i].shape);
        BOOST_REQUIRE(field.value == fields[i].value);
    }
}
