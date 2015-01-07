/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ResultsFrame.h"
#include "ui_ResultsFrame.h"

namespace dicomifier
{

namespace gui
{

ResultsFrame
::ResultsFrame(QWidget *parent) :
    BaseFrame(parent),
    _ui(new Ui::ResultsFrame)
{
    this->_ui->setupUi(this);

    this->_treeView = new ResultsTreeView(this->_ui->widget);
    this->_treeView->Initialize({});

    connect(this->_treeView, SIGNAL(itemsSelectionChanged()),
            this, SLOT(ontreeViewclicked()));
}

ResultsFrame
::~ResultsFrame()
{
    delete this->_ui;
}

void
ResultsFrame
::Reset()
{
    // Nothing to do
}

void
ResultsFrame
::InitializeWithData(std::vector<TreeItem *> subjectslist,
                     std::map<std::string, GenerationResultItem> results)
{
    this->Initialize();
    this->_treeView->set_results(results);
    this->_treeView->Initialize(subjectslist);
}

void
ResultsFrame
::ontreeViewclicked()
{
    // TODO
}

void
ResultsFrame
::onUpdate_Preferences()
{
    // Nothing to do
}

void
ResultsFrame
::modify_nextButton_enabled()
{
    // "Next button" is "Close Button" for this Frame

    // always true
    emit this->update_nextButton(true);
}

void
ResultsFrame
::modify_previousButton_enabled()
{
    // "Previous button" is "New Button" for this Frame

    // always true
    emit this->update_previousButton(true);
}

void ResultsFrame::paintEvent(QPaintEvent *event)
{
    if (this->_treeView != NULL)
    {
        this->_treeView->resize(this->_ui->widget->size());
    }

    QWidget::paintEvent(event);
}

} // namespace gui

} // namespace dicomifier
