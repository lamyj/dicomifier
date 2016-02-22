/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDateTime
#include <boost/test/unit_test.hpp>

#include "core/DateTime.h"
#include "core/DicomifierException.h"

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: string_to_local_date_time
 */
BOOST_AUTO_TEST_CASE(String_To_Local_DateTime)
{
    // Try with ISO 8601 format: YYYY-MM-DDTHH:MM:SS,mmm+XXZZ
    {
    std::string format = "";
    boost::local_time::local_date_time const datetime =
            dicomifier::string_to_local_date_time("2015-02-19T10:07:11,018+0100",
                                                  format);

    BOOST_CHECK_EQUAL(datetime.to_string(), "2015-Feb-19 10:07:11.018000 UTC");
    BOOST_CHECK_EQUAL(format, "%Y-%m-%dT%H:%M:%S%f%q");
    }
    // Try with ParaVision 5 format: HH:MM:SS DD Mon YYYY
    {
    std::string format = "";
    boost::local_time::local_date_time const datetime =
            dicomifier::string_to_local_date_time("12:27:46 29 Apr 2013",
                                                  format);

    BOOST_CHECK_EQUAL(datetime.to_string(), "2013-Apr-29 12:27:46 UTC");
    BOOST_CHECK_EQUAL(format, "%H:%M:%S %d %b %Y");
    }
    // ParaVision 5: Day could be write with only 1 digit...
    {
    std::string format = "";
    boost::local_time::local_date_time const datetime =
            dicomifier::string_to_local_date_time("12:27:46  5 Apr 2013",
                                                  format);

    BOOST_CHECK_EQUAL(datetime.to_string(), "2013-Apr-05 12:27:46 UTC");
    BOOST_CHECK_EQUAL(format, "%H:%M:%S %d %b %Y");
    }
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: posix_time_to_string
 */
BOOST_AUTO_TEST_CASE(PosixTime_To_String)
{
    boost::posix_time::ptime time(boost::gregorian::date(2015, 05, 06));
    BOOST_CHECK_EQUAL(dicomifier::posix_time_to_string(time, "%d %b %Y"),
                      "06 May 2015");
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: local_date_time_to_string
 */
BOOST_AUTO_TEST_CASE(Local_DateTime_To_String)
{
    boost::local_time::local_time_input_facet *input_facet
        = new boost::local_time::local_time_input_facet("%H:%M:%S %d %b %Y");

    // Set up the input datetime format.
    std::stringstream ss;
    ss.imbue(std::locale(ss.getloc(), input_facet));
    ss.str("12:27:46 29 Apr 2013");

    // Read a time into ldt
    boost::local_time::local_date_time ldt(boost::local_time::not_a_date_time);
    ss >> ldt;

    BOOST_CHECK_EQUAL(
        dicomifier::local_date_time_to_string(ldt, "%Y-%m-%dT%H:%M:%S%f%q"),
        "2013-04-29T12:27:46000000Z");
}

/*************************** TEST Error *********************************/
/**
 * Error test case: Unknown format
 */
BOOST_AUTO_TEST_CASE(Unrecognize_format)
{
    std::string format = "";
    BOOST_REQUIRE_THROW(
        dicomifier::string_to_local_date_time("BAD_VALUE", format),
        dicomifier::DicomifierException);
}
