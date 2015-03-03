/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleField
#include <boost/test/unit_test.hpp>

#include "bruker/Field.h"
#include "core/DicomifierException.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    dicomifier::bruker::Field field;
    BOOST_CHECK_EQUAL(field.name == "", true);
    BOOST_CHECK_EQUAL(field.shape.size(), 0);
    BOOST_CHECK_EQUAL(field.value.size(), 0);

    dicomifier::bruker::Field field2("myname", {}, {});
    BOOST_CHECK_EQUAL(field2.name == "myname", true);
    BOOST_CHECK_EQUAL(field2.shape.size(), 0);
    BOOST_CHECK_EQUAL(field2.value.size(), 0);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get values
 */
BOOST_AUTO_TEST_CASE(GetValues)
{
    dicomifier::bruker::Field::Value value;
    value.push_back("myvalue2");
    value.push_back((long)12);
    value.push_back((float)3.14);

    dicomifier::bruker::Field field("myname", {}, {});
    field.value.push_back("myvalue");
    field.value.push_back((long)42);
    field.value.push_back((float)37.1);
    field.value.push_back(value);

    BOOST_CHECK_EQUAL(field.get_string(0) == "myvalue", true);
    BOOST_CHECK_EQUAL(field.get_int(1), (long)42);
    BOOST_CHECK_EQUAL(field.get_float(2), (float)37.1);
    BOOST_CHECK_EQUAL(field.get_struct(3).size(), 3);

    BOOST_CHECK_EQUAL(boost::get<std::string>(field.get_struct(3)[0]) == "myvalue2", true);
    BOOST_CHECK_EQUAL(boost::get<long>(field.get_struct(3)[1]), (long)12);
    BOOST_CHECK_EQUAL(boost::get<float>(field.get_struct(3)[2]), (float)3.14);

    BOOST_CHECK_EQUAL(field.get<std::string>(0) == "myvalue", true);
    BOOST_CHECK_EQUAL(field.get<long>(1), (long)42);
    BOOST_CHECK_EQUAL(field.get<float>(2), (float)37.1);
    BOOST_CHECK_EQUAL(field.get<dicomifier::bruker::Field::Value>(3).size(), 3);
}
