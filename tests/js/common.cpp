/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleJSCommon
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include "core/DicomifierException.h"
#include "javascript/JavascriptVM.h"

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Exception class
 */
BOOST_AUTO_TEST_CASE(Exception)
{
    dicomifier::javascript::JavascriptVM jsvm;

    std::string const script("require(\"common.js\");\n"
                             "throw new dicomifier.Exception(\"HelloWorld\");");

    BOOST_REQUIRE_THROW(jsvm.run(script, jsvm.get_context()),
                        dicomifier::DicomifierException);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Object Equals
 */
BOOST_AUTO_TEST_CASE(Object_Equals)
{
    dicomifier::javascript::JavascriptVM jsvm;

    std::stringstream script;
    script << "require(\"common.js\");\n"
           << "function checkequals() {\n"
           << "var object1 = { \"first\": [ \"value\" ], \"second\": 12, "
           << "\"third\": { \"item1\": \"value\" } };\n"
           << "var object2 = { \"first\": [ \"value\" ], \"second\": 12, "
           << "\"third\": { \"item1\": \"value\" } };\n"
           << "return object1.equals(object2);\n"
           << "}\n"
           << "checkequals();";

    auto const result = jsvm.run(script.str(), jsvm.get_context());

    BOOST_REQUIRE( result->ToBoolean()->Value() );

    std::stringstream scriptnot;
    scriptnot << "require(\"common.js\");\n"
              << "function checknotequals() {\n"
              << "var object1 = { \"first\": [ \"value\" ], \"second\": 12, "
              <<                 "\"third\": { \"item1\": \"value\" } };\n"
              << "var object2 = { \"first\": [ \"value\" ], \"second\": 15, "
              <<                 "\"third\": { \"item1\": \"value\" } };\n"
              << "return object1.equals(object2);\n"
              << "}\n"
              << "checknotequals();";

    auto const resultnot = jsvm.run(scriptnot.str(), jsvm.get_context());

    BOOST_REQUIRE( !resultnot->ToBoolean()->Value() );
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Array Equals
 */
BOOST_AUTO_TEST_CASE(Array_Equals)
{
    dicomifier::javascript::JavascriptVM jsvm;

    std::stringstream script;
    script << "require(\"common.js\");\n"
           << "function checkequals() {\n"
           << "var array1 = [ [ \"value\" ], 12, { \"item1\": \"value\" } ];\n"
           << "var array2 = [ [ \"value\" ], 12, { \"item1\": \"value\" } ];\n"
           << "return array1.equals(array2);\n"
           << "}\n"
           << "checkequals();";

    auto const result = jsvm.run(script.str(), jsvm.get_context());

    BOOST_REQUIRE( result->ToBoolean()->Value() );

    std::stringstream scriptnot;
    scriptnot << "require(\"common.js\");\n"
              << "function checknotequals() {\n"
              << "var array1 = [ [ \"value\" ], 12, "
              <<                 "{ \"item1\": \"value\" } ];\n"
              << "var array2 = [ [ \"value\" ], 15, "
              <<                 "{ \"item1\": \"value\" } ];\n"
              << "return array1.equals(array2);\n"
              << "}\n"
              << "checknotequals();";

    auto const resultnot = jsvm.run(scriptnot.str(), jsvm.get_context());

    BOOST_REQUIRE( !resultnot->ToBoolean()->Value() );
}
