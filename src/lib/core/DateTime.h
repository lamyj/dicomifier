/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _ef3b69e4_7472_48f2_9149_83e2517a5e9a
#define _ef3b69e4_7472_48f2_9149_83e2517a5e9a

#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>

namespace dicomifier
{

boost::local_time::local_date_time string_to_local_date_time(std::string const & datetime,
                                                             std::string & format);

std::string posix_time_to_string(
    boost::posix_time::ptime const & ptime, std::string const & format);


std::string local_date_time_to_string(boost::local_time::local_date_time const & ldt,
                                      std::string const & outputformat);

} // namespace dicomifier

#endif // _ef3b69e4_7472_48f2_9149_83e2517a5e9a
