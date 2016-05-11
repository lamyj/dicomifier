/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <cstdlib>

#include <QApplication>

#include <boost/filesystem.hpp>

#include "core/Logger.h"
#include "mainframe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Configure application
    QCoreApplication::setOrganizationName("Dicomifier");
    QCoreApplication::setApplicationName("dicomifier");

    char* mode = getenv("DICOMIFIER_LOGGER");
    std::string logmode = mode != NULL ? std::string(mode): "ERROR";
    dicomifier::InitializeLogger(logmode);

    // Create main frame
    dicomifier::gui::MainFrame frame;
    frame.Initialize();
    frame.show();

    return a.exec();
}
