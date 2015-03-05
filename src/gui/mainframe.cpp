/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "mainframe.h"
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
    _subjectsframe(NULL), _protocolsframe(NULL),
    _generationframe(NULL), _resultsframe(NULL),
    _preferencesframe(NULL),
    _currentStep(DicomifierStep::CountMax),
    _previousStep(DicomifierStep::CountMax)
{
    this->_ui->setupUi(this);

    // Link menu item Quit
    this->_ui->actionQuit->setShortcuts(QKeySequence::Quit);
    this->_ui->actionQuit->setStatusTip(tr("Close the application"));
    connect(this->_ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    // Link menu item New
    this->_ui->actionNew->setShortcuts(QKeySequence::New);
    this->_ui->actionNew->setStatusTip(tr("New process"));
    connect(this->_ui->actionNew, SIGNAL(triggered()), this, SLOT(reset()));

    // Link menu item Preferences
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

    // Create Fourth Widget (Results information)
    this->_resultsframe = new ResultsFrame(this->_ui->stepWidget);
    this->InitializeWidget(this->_resultsframe);

    // Create Preferences Frame
    this->_preferencesframe = new PreferencesFrame(this->_ui->stepWidget);
    this->InitializeWidget(this->_preferencesframe);

    // Add specifics links
    connect(this->_generationframe, SIGNAL(CreateNewPACSConfiguration()),
            this, SLOT(CreateNewPACS()));
}

MainFrame
::~MainFrame()
{
    // Frames are destroyed by delete _ui

    delete this->_ui;
}

void
MainFrame
::Initialize(bool resize)
{
    if (resize)
    {
        // Window Position and Size
        this->setGeometry(0, 0, 1040, 768);
    }

    // Display first Frame
    this->ChangeStep(true);
}

void
MainFrame
::InitializeWidget(BaseFrame * widget)
{
    this->_ui->stepWidget->layout()->addWidget(widget);
    connect(this, SIGNAL(UpdatePreferences()),
            widget, SLOT(onUpdate_Preferences()));
    connect(widget, SIGNAL(cancelled()),
            this, SLOT(on_previousButton_clicked()));

    connect(widget, SIGNAL(update_previousButton(bool)),
            this->_ui->previousButton, SLOT(setEnabled(bool)));
    connect(widget, SIGNAL(update_nextButton(bool)),
            this->_ui->nextButton, SLOT(setEnabled(bool)));

}

void
MainFrame
::ShowHide(bool nextstep)
{
    // Show or Hide SubjectsFrame
    if (this->_currentStep == DicomifierStep::SelectSubject)
    {
        if (nextstep)
        {
            this->_subjectsframe->Initialize();
        }
        else
        {
            this->_subjectsframe->BaseFrame::Initialize();
        }
    }
    else
    {
        this->_subjectsframe->hide();
    }

    // Show or Hide ProtocolsFrame
    if (this->_currentStep == DicomifierStep::SelectProtocols)
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

    // Show or Hide GenerationFrame
    if (this->_currentStep == DicomifierStep::Generation)
    {
        this->_generationframe->Initialize();
    }
    else
    {
        this->_generationframe->hide();
    }

    // Show or Hide ResultsFrame
    if (this->_currentStep == DicomifierStep::Results)
    {
        if (nextstep)
        {
            this->_resultsframe->InitializeWithData(this->_itemsToProcess,
                                                    this->_generationframe->get_Results());
        }
        else
        {
            this->_resultsframe->Initialize();
        }
    }
    else
    {
        this->_resultsframe->hide();
    }

    // Show or Hide PreferencesFrame
    if (this->_currentStep == DicomifierStep::Preferences)
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
    // State Machine: select the next or previous Frame (depends on clicked button)
    switch (this->_currentStep)
    {
    case DicomifierStep::SelectSubject:
    {   // No previous step -> SubjectsFrame -> ProtocolsFrame
        this->_currentStep = nextstep ? DicomifierStep::SelectProtocols :
                                        DicomifierStep::SelectSubject;
        break;
    }
    case DicomifierStep::SelectProtocols:
    {   // SubjectsFrame -> ProtocolsFrame -> GenerationFrame
        this->_currentStep = nextstep ? DicomifierStep::Generation :
                                        DicomifierStep::SelectSubject;
        break;
    }
    case DicomifierStep::Generation:
    {   // ProtocolsFrame -> GenerationFrame -> ResultsFrame
        this->_currentStep = nextstep ? DicomifierStep::Results :
                                        DicomifierStep::SelectProtocols;

        if (nextstep)
        {
            _itemsToProcess = this->_protocolsframe->get_selectedData();
            this->_generationframe->RunDicomifier(_itemsToProcess);
        }
        break;
    }
    case DicomifierStep::Results:
    {   // New process (Re-initialize) -> ResultsFrame -> End (Close Dicomifier)
        if (nextstep)
        {
            this->close();
        }
        else
        {
            this->reset();
        }

        return;
    }
    case DicomifierStep::Preferences:
    {   // Display previous step
        this->_currentStep = this->_previousStep;
        this->_ui->stepNumberLabel->show();
        this->_ui->nextButton->setText(QString("Next"));
        this->_ui->previousButton->setText(QString("Previous"));
        if (nextstep)
        {
            this->_preferencesframe->SavePreferences();
            this->UpdatePreferences();
        }
        nextstep = false;
        break;
    }
    case DicomifierStep::CountMax:
    default:
    {   // Select First step by default
        this->_currentStep = DicomifierStep::SelectSubject;
        break;
    }
    }

    this->ShowHide(nextstep);

    this->ModifyComponentsText();
}

void
MainFrame
::on_nextButton_clicked()
{
    this->_ui->nextButton->setEnabled(false);
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
    // Already open
    if (this->_currentStep == DicomifierStep::Preferences)
        return;

    // Remember current Frame
    this->_previousStep = this->_currentStep;

    // Open PreferencesFrame
    this->_currentStep = DicomifierStep::Preferences;

    this->ModifyComponentsText();
    this->ShowHide(false);
}

void
MainFrame
::CreateNewPACS()
{
    this->OpenPreferences();
    this->_preferencesframe->on_NewButton_clicked();
}

void
MainFrame
::ModifyComponentsText()
{
    std::stringstream stream;
    stream << ((int)this->_currentStep + 1) << " / " << (int)DicomifierStep::Results;

    switch (this->_currentStep)
    {
    case DicomifierStep::Generation:
    {
        // Current Step Number => 1/3
        this->_ui->stepNumberLabel->setText(QString(stream.str().c_str()));
        this->_ui->stepNumberLabel->show();
        // Previous = Previous ; Next =  Run
        this->_ui->nextButton->setText(QString("Run"));
        this->_ui->previousButton->setText(QString("Previous"));
        break;
    }
    case DicomifierStep::Results:
    {
        // Current Step Number => None
        this->_ui->stepNumberLabel->setText("");
        this->_ui->stepNumberLabel->hide();
        // Previous = Close ; Next =  New
        this->_ui->nextButton->setText(QString("Close"));
        this->_ui->previousButton->setText(QString("New"));
        break;
    }
    case DicomifierStep::Preferences:
    {
        this->_ui->stepNumberLabel->setText("");
        this->_ui->stepNumberLabel->hide();

        this->_ui->nextButton->setText(QString("Validate"));
        this->_ui->previousButton->setText(QString("Cancel"));
        break;
    }
    case DicomifierStep::SelectSubject:
    case DicomifierStep::SelectProtocols:
    default:
    {
        // Step Number label
        this->_ui->stepNumberLabel->setText(QString(stream.str().c_str()));
        this->_ui->stepNumberLabel->show();
        // Buttons Previous and Next
        this->_ui->nextButton->setText(QString("Next"));
        this->_ui->previousButton->setText(QString("Previous"));
        break;
    }
    }
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
    this->_currentStep = DicomifierStep::CountMax;
    this->Initialize(false);
}

} // namespace gui

} // namespace dicomifier
