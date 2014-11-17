/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <QApplication>

#include "mainframe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Dicomifier");
    QCoreApplication::setApplicationName("dicomifier");

    dicomifier::ihm::MainFrame frame;

    frame.Initialize();

    frame.show();

    return a.exec();
}
