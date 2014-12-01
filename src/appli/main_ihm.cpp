/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <QApplication>

#include <boost/filesystem.hpp>

#include "dicom/Dictionaries.h"
#include "mainframe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Configure application
    QCoreApplication::setOrganizationName("Dicomifier");
    QCoreApplication::setApplicationName("dicomifier");

    // Load Private Dictionary
    // if file exist locally
    if (boost::filesystem::exists(boost::filesystem::path("../configuration/private_dictionary.xml")))
    {
        dicomifier::Dictionaries::get_instance().ParsePrivateDictionary("../configuration/private_dictionary.xml");
    }
    // else use default file
    else
    {
        dicomifier::Dictionaries::get_instance().ParsePrivateDictionary("/etc/dicomifier/private_dictionary.xml");
    }

    // Create main frame
    dicomifier::ihm::MainFrame frame;
    frame.Initialize();
    frame.show();

    return a.exec();
}
