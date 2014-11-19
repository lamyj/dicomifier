/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <QApplication>

#include "dicom/Dictionaries.h"
#include "mainframe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Configure application
    QCoreApplication::setOrganizationName("Dicomifier");
    QCoreApplication::setApplicationName("dicomifier");

    // Load Private Dictionary
    dicomifier::Dictionaries::get_instance().ParsePrivateDictionary("./conf/private_dictionary.xml");

    // Create main frame
    dicomifier::ihm::MainFrame frame;
    frame.Initialize();
    frame.show();

    return a.exec();
}
