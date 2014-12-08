/*************************************************************************
 * Research_pacs - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Logger.h"

namespace dicomifier
{

void InitializeLogger(std::string const & priority)
{
    log4cpp::Appender *appender1 = new log4cpp::OstreamAppender("console", &std::cout);
    appender1->setLayout(new log4cpp::BasicLayout());

    log4cpp::Category& root = log4cpp::Category::getRoot();

    if (priority == "ERROR")
        root.setPriority(log4cpp::Priority::ERROR);
    else if (priority == "WARNING")
        root.setPriority(log4cpp::Priority::WARN);
    else if (priority == "INFO")
        root.setPriority(log4cpp::Priority::INFO);
    else
        root.setPriority(log4cpp::Priority::DEBUG);

    root.addAppender(appender1);
}

log4cpp::CategoryStream getLogger(const log4cpp::Priority::PriorityLevel &level)
{
    log4cpp::Category& root = log4cpp::Category::getRoot();

    return root << level;
}

log4cpp::CategoryStream loggerDebug()
{
    return getLogger(log4cpp::Priority::DEBUG);
}

log4cpp::CategoryStream loggerError()
{
    return getLogger(log4cpp::Priority::ERROR);
}

log4cpp::CategoryStream loggerInfo()
{
    return getLogger(log4cpp::Priority::INFO);
}

log4cpp::CategoryStream loggerWarning()
{
    return getLogger(log4cpp::Priority::WARN);
}

} // namespace dicomifier
