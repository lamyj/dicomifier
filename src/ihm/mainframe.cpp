/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SubjectsFrame.h"
#include "mainframe.h"
#include "ui_mainframe.h"

#include <QGridLayout>

namespace dicomifier
{

namespace ihm
{

MainFrame::MainFrame(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainFrame)
{
    this->_ui->setupUi(this);

    this->_ui->actionQuit->setShortcuts(QKeySequence::Quit);
    this->_ui->actionQuit->setStatusTip(tr("Close the application"));
    connect(this->_ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    this->_ui->actionNew->setShortcuts(QKeySequence::New);
    this->_ui->actionNew->setStatusTip(tr("New process"));
    //connect(this->_ui->actionNew, SIGNAL(triggered()), this, SLOT()); TODO

    this->_ui->actionPreferences->setShortcuts(QKeySequence::Preferences);
    this->_ui->actionPreferences->setStatusTip(tr("Modify Dicomifier Preferences"));
    //connect(this->_ui->actionPreferences, SIGNAL(triggered()), this, SLOT()); TODO
}

MainFrame::~MainFrame()
{
    delete this->_ui;
}

void MainFrame::Initialize()
{
    // Window Position and Size
    this->setGeometry(0, 0, 1024, 768);
}

} // namespace ihm

} // namespace dicomifier
