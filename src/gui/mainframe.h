/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b6541ba8_6b89_4c08_95f1_69a3f8235a28
#define _b6541ba8_6b89_4c08_95f1_69a3f8235a28

#include <QMainWindow>

#include "GenerationFrame.h"
#include "PreferencesFrame.h"
#include "ProtocolsFrame.h"
#include "ResultsFrame.h"
#include "SubjectsFrame.h"

namespace dicomifier
{

namespace gui
{

namespace Ui
{
class MainFrame;
} // namespace Ui

/**
 * @brief The DicomifierStep enum
 */
enum class DicomifierStep
{
    SelectSubject = 0,  /// SubjectsFrame
    SelectProtocols,    /// ProtocolsFrame
    Generation,         /// GenerationFrame
    Results,            /// ResultsFrame
    CountMax,

    Preferences         /// PreferencesFrame
};

/**
 * @brief The MainFrame class
 */
class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of MainFrame
     * @param parent: widget containing the MainFrame
     */
    explicit MainFrame(QWidget *parent = 0);

    /// Destroy the instance of MainFrame
    virtual ~MainFrame();

    /**
     * @brief Initialize the MainFrame
     */
    void Initialize(bool resize = true);

signals:
    /**
     * @brief Signal emit after Preferences validation
     */
    void UpdatePreferences();

protected:
    /**
     * @brief Initialize a given BaseFrame widget
     * @param widget: widget to initialize
     */
    void InitializeWidget(BaseFrame* widget);

    /**
     * @brief Show the current Widget (Frame) and hide the others
     * @param nextstep: true if Next Button was clicked, false otherwise
     */
    void ShowHide(bool nextstep);

    /**
     * @brief Select the good frame to display
     * @param nextstep: true if Next Button was clicked, false otherwise
     */
    void ChangeStep(bool nextstep);

private slots:
    /// Event triggered by a click on Next Button
    void on_nextButton_clicked();

    /// Event triggered by a click on Previous Button
    void on_previousButton_clicked();

    /// Re-initialize the instance of MainFrame
    void reset();

    /// Show the Preferences Frame
    void OpenPreferences();

    /// Event triggered by a click on New button (GenerationFrame)
    void CreateNewPACS();

private:
    void ModifyComponentsText();

    /// User Interface
    Ui::MainFrame * _ui;

    /// Widget SubjectFrame
    SubjectsFrame * _subjectsframe;

    /// Widget ProtocolsFrame
    ProtocolsFrame * _protocolsframe;

    /// Widget GenerationFrame
    GenerationFrame * _generationframe;

    /// Widget ResultsFrame
    ResultsFrame * _resultsframe;

    /// Widget PreferencesFrame
    PreferencesFrame * _preferencesframe;

    /// Identify the widget currently displayed
    DicomifierStep _currentStep;

    /// Identify the widget previously displayed (only if Preferences frame is displayed)
    DicomifierStep _previousStep;

    /// Selected items
    std::vector<TreeItem *> _itemsToProcess;

};

} // namespace gui

} // namespace dicomifier

#endif // _b6541ba8_6b89_4c08_95f1_69a3f8235a28
