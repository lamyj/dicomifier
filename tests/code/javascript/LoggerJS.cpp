/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleLoggerVM
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <string>

#include <v8.h>

#include "core/Logger.h"
#include "javascript/JavascriptVM.h"
#include "javascript/LoggerJS.h"

struct TestDataLoggerJS
{
    std::stringstream streamlog;
    std::streambuf* OldBuf;

    TestDataLoggerJS()
    {
        // redirect standard output to stringstream
        OldBuf = std::cout.rdbuf(streamlog.rdbuf());

        dicomifier::InitializeLogger("DEBUG");
    }

    ~TestDataLoggerJS()
    {
        // set the default output
        std::cout.rdbuf(OldBuf);
    }
};

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Log error message from JavaScript code
 */
BOOST_FIXTURE_TEST_CASE(Logger_Error, TestDataLoggerJS)
{
    dicomifier::javascript::JavascriptVM vm;

    vm.run("log('My message', 'ERROR');", vm.get_context());

    BOOST_REQUIRE_NE(streamlog.str(), "");
    BOOST_CHECK(streamlog.str().find("ERROR") != std::string::npos);
    BOOST_CHECK(streamlog.str().find("My message") != std::string::npos);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Log error message from JavaScript code
 */
BOOST_FIXTURE_TEST_CASE(Logger_Info, TestDataLoggerJS)
{
    dicomifier::javascript::JavascriptVM vm;

    vm.run("log('My message');", vm.get_context());

    BOOST_REQUIRE_NE(streamlog.str(), "");
    BOOST_CHECK(streamlog.str().find("INFO") != std::string::npos);
    BOOST_CHECK(streamlog.str().find("My message") != std::string::npos);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Missing input
 */
BOOST_FIXTURE_TEST_CASE(Logger_missing_input, TestDataLoggerJS)
{
    dicomifier::javascript::JavascriptVM vm;

    vm.run("log();", vm.get_context());

    BOOST_REQUIRE_EQUAL(streamlog.str(), "");
}
