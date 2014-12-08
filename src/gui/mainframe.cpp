/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "mainframe.h"
#include "ProtocolsFrame.h"
#include "SubjectsFrame.h"
#include "ui_mainframe.h"

#include <QGridLayout>

namespace dicomifier
{

namespace gui
{

MainFrame
::MainFrame(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainFrame),
    _subjectsframe(NULL),
    _protocolsframe(NULL),
    _generationframe(NULL),
    _preferencesframe(NULL),
    _currentStep(EDS_CountMax),
    _previousStep(EDS_CountMax)
{
    this->_ui->setupUi(this);

    this->_ui->actionQuit->setShortcuts(QKeySequence::Quit);
    this->_ui->actionQuit->setStatusTip(tr("Close the application"));
    connect(this->_ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    this->_ui->actionNew->setShortcuts(QKeySequence::New);
    this->_ui->actionNew->setStatusTip(tr("New process"));
    connect(this->_ui->actionNew, SIGNAL(triggered()), this, SLOT(reset()));

    this->_ui->actionPreferences->setShortcuts(QKeySequence::Preferences);
    this->_ui->actionPreferences->setStatusTip(tr("Modify Dicomifier Preferences"));
    connect(this->_ui->actionPreferences, SIGNAL(triggered()), this, SLOT(OpenPreferences()));

    // Create first Widget (Subect Selection)
    this->_subjectsframe = new SubjectsFrame(this->_ui->stepWidget);
    this->InitializeWidget(this->_subjectsframe);

    // Create second Widget (Protocols Selection)
    this->_protocolsframe = new ProtocolsFrame(this->_ui->stepWidget);
    this->InitializeWidget(this->_protocolsframe);

    // Create third Widget (Generation Parameters)
    this->_generationframe = new GenerationFrame(this->_ui->stepWidget);
    this->InitializeWidget(this->_generationframe);

    // Create Preferences Frame
    this->_preferencesframe = new PreferencesFrame(this->_ui->stepWidget);
    this->InitializeWidget(this->_preferencesframe);
}

MainFrame
::~MainFrame()
{
    delete this->_ui;
}

void
MainFrame
::Initialize()
{
    // Window Position and Size
    this->setGeometry(0, 0, 1040, 768);

    this->ChangeStep(false);
}

void
MainFrame
::InitializeWidget(BaseFrame * widget)
{
    this->_ui->stepWidget->layout()->addWidget(widget);
    connect(widget, SIGNAL(update_nextButton(bool)),
            this, SLOT(setEnabled_nextButton(bool)));
    connect(widget, SIGNAL(update_previousButton(bool)),
            this, SLOT(setEnabled_previousButton(bool)));
    connect(this, SIGNAL(UpdatePreferences()),
            widget, SLOT(onUpdate_Preferences()));
}

void
MainFrame
::ShowHide(bool nextstep)
{
    if (this->_currentStep == EDS_SelectSubject)
    {
        this->_subjectsframe->Initialize();
    }
    else
    {
        this->_subjectsframe->hide();
    }

    if (this->_currentStep == EDS_SelectProtocols)
    {
        if (nextstep)
        {
            this->_protocolsframe->InitializeWithData(this->_subjectsframe->get_selectedData());
        }
        else
        {
            this->_protocolsframe->Initialize();
        }
    }
    else
    {
        this->_protocolsframe->hide();
    }

    if (this->_currentStep == EDS_Generation)
    {
        this->_generationframe->Initialize();
    }
    else
    {
        this->_generationframe->hide();
    }

    if (this->_currentStep == EDS_Preferences)
    {
        this->_preferencesframe->Initialize();
    }
    else
    {
        this->_preferencesframe->hide();
    }
}

void
MainFrame
::ChangeStep(bool nextstep)
{
    switch (this->_currentStep)
    {
    case EDS_SelectSubject:
    {
        this->_currentStep = nextstep ? EDS_SelectProtocols : EDS_SelectSubject;
        break;
    }
    case EDS_SelectProtocols:
    {
        this->_currentStep = nextstep ? EDS_Generation : EDS_SelectSubject;
        break;
    }
    case EDS_Generation:
    {
        this->_currentStep = nextstep ? EDS_Generation : EDS_SelectProtocols;

        if (nextstep)
        {
            this->_generationframe->RunDicomifier(this->_protocolsframe->get_selectedData());
        }
        break;
    }
    case EDS_Preferences:
    {
        this->_currentStep = this->_previousStep;
        this->_ui->stepNumberLabel->show();
        this->_ui->nextButton->setText(QString("Next"));
        this->_ui->previousButton->setText(QString("Previous"));
        if (nextstep)
        {
            this->_preferencesframe->SavePreferences();
            emit this->UpdatePreferences();
        }
        nextstep = false;
        break;
    }
    case EDS_CountMax:
    default:
    {
        this->_currentStep = EDS_SelectSubject;
        break;
    }
    }

    this->ShowHide(nextstep);

    std::stringstream stream;
    stream << (this->_currentStep + 1) << " / " << EDS_CountMax;
    this->_ui->stepNumberLabel->setText(QString(stream.str().c_str()));

    this->_ui->nextButton->setText(this->_currentStep + 1 == EDS_CountMax ? QString("Run") :
                                                                            QString("Next"));
}

void
MainFrame
::setEnabled_previousButton(bool enabled)
{
    this->_ui->previousButton->setEnabled(enabled);
}

void
MainFrame
::setEnabled_nextButton(bool enabled)
{
    this->_ui->nextButton->setEnabled(enabled);
}

void
MainFrame
::on_nextButton_clicked()
{
    this->setEnabled_nextButton(false);
    this->ChangeStep(true);
}

void
MainFrame
::on_previousButton_clicked()
{
    this->ChangeStep(false);
}

void
MainFrame
::OpenPreferences()
{
    if (this->_currentStep == EDS_Preferences)
        return;

    this->_previousStep = this->_currentStep;
    this->_currentStep = EDS_Preferences;
    this->_ui->stepNumberLabel->hide();

    this->_ui->nextButton->setText(QString("Validate"));
    this->_ui->previousButton->setText(QString("Cancel"));

    this->ShowHide(false);
}

void
MainFrame
::reset()
{
    // reset data
    this->_subjectsframe->Reset();
    this->_protocolsframe->Reset();
    this->_generationframe->Reset();

    // Initialize window
    this->_currentStep = EDS_CountMax;
    this->ChangeStep(false);
}

} // namespace gui

} // namespace dicomifier
