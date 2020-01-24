/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "DateTime.h"

#include <sstream>
#include <string>

#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

#include "core/Exception.h"

namespace dicomifier
{

boost::local_time::local_date_time
string_to_local_date_time(std::string const & datetime, std::string & format)
{
    std::string localdatetime = datetime;

    boost::replace_all(localdatetime, ",", ".");

    boost::local_time::local_date_time ldt(boost::local_time::not_a_date_time);

    // Try with ISO 8601 format: YYYY-MM-DDTHH:MM:SS,mmm+XXZZ
    if (ldt == boost::local_time::local_date_time(boost::local_time::not_a_date_time))
    {
        boost::local_time::local_time_input_facet *input_facet
            = new boost::local_time::local_time_input_facet("%Y-%m-%dT%H:%M:%S%f%q");

        // Set up the input datetime format.
        std::stringstream ss;
        ss.imbue(std::locale(ss.getloc(), input_facet));
        ss.str(localdatetime);

        // Read a time into ldt
        ss >> ldt;

        format = "%Y-%m-%dT%H:%M:%S%f%q";
    }
    // Try with ParaVision 5 format: HH:MM:SS DD Mon YYYY
    if (ldt == boost::local_time::local_date_time(boost::local_time::not_a_date_time))
    {
        boost::local_time::local_time_input_facet *input_facet
            = new boost::local_time::local_time_input_facet("%H:%M:%S %d %b %Y");

        // Set up the input datetime format.
        std::stringstream ss;
        ss.imbue(std::locale(ss.getloc(), input_facet));
        ss.str(localdatetime);

        // Read a time into ldt
        ss >> ldt;

        format = "%H:%M:%S %d %b %Y";
    }
    // ParaVision 5: Day could be write with only 1 digit...
    if (ldt == boost::local_time::local_date_time(boost::local_time::not_a_date_time) &&
        localdatetime.length() == 20)
    {
        localdatetime[9] = '0';
        boost::local_time::local_time_input_facet *input_facet
            = new boost::local_time::local_time_input_facet("%H:%M:%S %d %b %Y");

        // Set up the input datetime format.
        std::stringstream ss;
        ss.imbue(std::locale(ss.getloc(), input_facet));
        ss.str(localdatetime);

        // Read a time into ldt
        ss >> ldt;

        format = "%H:%M:%S %d %b %Y";
    }
    // Format not recognized
    if (ldt == boost::local_time::local_date_time(boost::local_time::not_a_date_time))
    {
        std::stringstream stream;
        stream << "Bad value for Date-Time: " << datetime;
        throw Exception(stream.str());
    }

    return ldt;
}

std::string
local_date_time_to_string(boost::local_time::local_date_time const & ldt,
                          std::string const & outputformat)
{
    boost::local_time::local_time_facet* output_facet =
            new boost::local_time::local_time_facet(outputformat.c_str());
    std::stringstream stream;
    stream.imbue(std::locale(std::locale::classic(), output_facet));
    stream << ldt;

    return stream.str();
}

} // namespace dicomifier
