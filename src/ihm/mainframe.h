/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b6541ba8_6b89_4c08_95f1_69a3f8235a28
#define _b6541ba8_6b89_4c08_95f1_69a3f8235a28

#include "ProtocolsFrame.h"
#include "SubjectsFrame.h"

#include <QMainWindow>

#include <components/SubjectsTreeItemData.h>

namespace dicomifier
{

namespace ihm
{

namespace Ui
{
class MainFrame;
} // namespace Ui

enum DicomifierStep
{
    EDS_SelectSubject = 0,
    EDS_SelectProtocols,
    EDS_Generation,
    EDS_CountMax
};

class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    virtual ~MainFrame();

    void Initialize();

protected:
    void InitializeStep(DicomifierStep step);

    void ShowHide();

    void ChangeStep(bool nextstep);

private slots:
    void setEnabled_previousButton(bool enabled);

    void setEnabled_nextButton(bool enabled);

    void on_nextButton_clicked();

    void reset();

    void on_previousButton_clicked();

private:
    Ui::MainFrame * _ui;

    SubjectsFrame * _subjectsframe;

    ProtocolsFrame * _protocolsframe;

    DicomifierStep _currentStep;

};

} // namespace ihm

} // namespace dicomifier

#endif // _b6541ba8_6b89_4c08_95f1_69a3f8235a28
