/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _db1e5e46_6fd6_4a1c_ba95_d9525001652e
#define _db1e5e46_6fd6_4a1c_ba95_d9525001652e

#include "log4cpp/Appender.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Category.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Priority.hh"

namespace dicomifier
{

static std::map<std::string, log4cpp::Priority::PriorityLevel> level_dictionary =
{
    { "", log4cpp::Priority::DEBUG },       // Default
    { "ERROR", log4cpp::Priority::ERROR },
    { "WARNING", log4cpp::Priority::WARN },
    { "INFO", log4cpp::Priority::INFO },
    { "DEBUG", log4cpp::Priority::DEBUG }
};

void InitializeLogger(std::string const & priority);

log4cpp::CategoryStream getLogger(log4cpp::Priority::PriorityLevel const & level);

log4cpp::CategoryStream getLogger(std::string const & priority);

log4cpp::CategoryStream loggerDebug();

log4cpp::CategoryStream loggerError();

log4cpp::CategoryStream loggerInfo();

log4cpp::CategoryStream loggerWarning();

} // namespace dicomifier

#endif // _db1e5e46_6fd6_4a1c_ba95_d9525001652e
