/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleLogger
#include <boost/test/unit_test.hpp>

#include "core/Logger.h"

struct TestDataLogger
{
    std::stringstream stream;
    std::streambuf* OldBuf;

    TestDataLogger()
    {
        // redirect standard output to stringstream
        OldBuf = std::cout.rdbuf(stream.rdbuf());
    }

    ~TestDataLogger()
    {
        // set the default output
        std::cout.rdbuf(OldBuf);
    }
};

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Logger not Initialize
 */
BOOST_FIXTURE_TEST_CASE(No_Initialization, TestDataLogger)
{
    // Test
    dicomifier::loggerError() << " test ";
    dicomifier::loggerWarning() << " test ";
    dicomifier::loggerInfo() << " test ";
    dicomifier::loggerDebug() << " test ";

    BOOST_CHECK_EQUAL(stream.str(), "");
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: InitializeLogger (ERROR)
 */
BOOST_FIXTURE_TEST_CASE(InitializeloggerError, TestDataLogger)
{
    // Initialize logger
    dicomifier::InitializeLogger("ERROR");

    // Test
    dicomifier::loggerError() << " test ";
    dicomifier::loggerWarning() << " test ";
    dicomifier::loggerInfo() << " test ";
    dicomifier::loggerDebug() << " test ";

    BOOST_REQUIRE(stream.str() != "");

    BOOST_CHECK(stream.str().find("ERROR") != std::string::npos);
    BOOST_CHECK(stream.str().find("WARN") == std::string::npos);
    BOOST_CHECK(stream.str().find("INFO") == std::string::npos);
    BOOST_CHECK(stream.str().find("DEBUG") == std::string::npos);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: InitializeLogger (WARNING)
 */
BOOST_FIXTURE_TEST_CASE(InitializeloggerWarning, TestDataLogger)
{
    // Initialize logger
    dicomifier::InitializeLogger("WARNING");

    // Test
    dicomifier::loggerError() << " test ";
    dicomifier::loggerWarning() << " test ";
    dicomifier::loggerInfo() << " test ";
    dicomifier::loggerDebug() << " test ";

    BOOST_REQUIRE(stream.str() != "");

    BOOST_CHECK(stream.str().find("ERROR") != std::string::npos);
    BOOST_CHECK(stream.str().find("WARN") != std::string::npos);
    BOOST_CHECK(stream.str().find("INFO") == std::string::npos);
    BOOST_CHECK(stream.str().find("DEBUG") == std::string::npos);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: InitializeLogger (INFO)
 */
BOOST_FIXTURE_TEST_CASE(InitializeloggerInfo, TestDataLogger)
{
    // Initialize logger
    dicomifier::InitializeLogger("INFO");

    // Test
    dicomifier::loggerError() << " test ";
    dicomifier::loggerWarning() << " test ";
    dicomifier::loggerInfo() << " test ";
    dicomifier::loggerDebug() << " test ";

    BOOST_REQUIRE(stream.str() != "");

    BOOST_CHECK(stream.str().find("ERROR") != std::string::npos);
    BOOST_CHECK(stream.str().find("WARN") != std::string::npos);
    BOOST_CHECK(stream.str().find("INFO") != std::string::npos);
    BOOST_CHECK(stream.str().find("DEBUG") == std::string::npos);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: InitializeLogger (DEBUG)
 */
BOOST_FIXTURE_TEST_CASE(InitializeloggerDebug, TestDataLogger)
{
    // Initialize logger
    dicomifier::InitializeLogger("DEBUG");

    // Test
    dicomifier::loggerError() << " test ";
    dicomifier::loggerWarning() << " test ";
    dicomifier::loggerInfo() << " test ";
    dicomifier::loggerDebug() << " test ";

    BOOST_REQUIRE(stream.str() != "");

    BOOST_CHECK(stream.str().find("ERROR") != std::string::npos);
    BOOST_CHECK(stream.str().find("WARN") != std::string::npos);
    BOOST_CHECK(stream.str().find("INFO") != std::string::npos);
    BOOST_CHECK(stream.str().find("DEBUG") != std::string::npos);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: InitializeLogger (DEFAULT)
 */
BOOST_FIXTURE_TEST_CASE(InitializeLogger_Default, TestDataLogger)
{
    // Initialize logger
    dicomifier::InitializeLogger("");

    // Test
    dicomifier::loggerError() << " test ";
    dicomifier::loggerWarning() << " test ";
    dicomifier::loggerInfo() << " test ";
    dicomifier::loggerDebug() << " test ";

    BOOST_REQUIRE(stream.str() != "");

    BOOST_CHECK(stream.str().find("ERROR") != std::string::npos);
    BOOST_CHECK(stream.str().find("WARN") != std::string::npos);
    BOOST_CHECK(stream.str().find("INFO") != std::string::npos);
    BOOST_CHECK(stream.str().find("DEBUG") != std::string::npos);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Get Logger
 */
BOOST_FIXTURE_TEST_CASE(GetLogger_DEBUG, TestDataLogger)
{
    // Initialize logger
    dicomifier::InitializeLogger("");

    // Test
    dicomifier::getLogger("ERROR") << " test ";
    dicomifier::getLogger("WARNING") << " test ";
    dicomifier::getLogger("INFO") << " test ";
    dicomifier::getLogger("DEBUG") << " test ";

    BOOST_REQUIRE(stream.str() != "");

    BOOST_CHECK(stream.str().find("ERROR") != std::string::npos);
    BOOST_CHECK(stream.str().find("WARN") != std::string::npos);
    BOOST_CHECK(stream.str().find("INFO") != std::string::npos);
    BOOST_CHECK(stream.str().find("DEBUG") != std::string::npos);
}
