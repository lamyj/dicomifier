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

enum class DicomifierStep
{
    SelectSubject = 0,
    SelectProtocols,
    Generation,
    Results,
    CountMax,

    Preferences
};

class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    virtual ~MainFrame();

    void Initialize();

signals:
    void UpdatePreferences();

protected:
    void InitializeStep(DicomifierStep step);

    void InitializeWidget(BaseFrame* widget);

    void ShowHide(bool nextstep);

    void ChangeStep(bool nextstep);

private slots:
    void setEnabled_previousButton(bool enabled);

    void setEnabled_nextButton(bool enabled);

    void on_nextButton_clicked();

    void reset();

    void on_previousButton_clicked();

    void OpenPreferences();

private:
    Ui::MainFrame * _ui;

    SubjectsFrame * _subjectsframe;

    ProtocolsFrame * _protocolsframe;

    GenerationFrame * _generationframe;

    ResultsFrame * _resultsframe;

    PreferencesFrame * _preferencesframe;

    DicomifierStep _currentStep;

    DicomifierStep _previousStep;

    std::vector<TreeItem *> _itemsToProcess;

};

} // namespace gui

} // namespace dicomifier

#endif // _b6541ba8_6b89_4c08_95f1_69a3f8235a28
