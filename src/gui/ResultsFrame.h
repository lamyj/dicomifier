/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _508febdb_0508_40bd_8395_726fad7b436e
#define _508febdb_0508_40bd_8395_726fad7b436e

#include "BaseFrame.h"
#include "components/GenerationResultItem.h"
#include "components/ResultsTreeView.h"

namespace dicomifier
{

namespace gui
{

namespace Ui {
class ResultsFrame;
} // namespace Ui

/**
 * @brief The ResultsFrame class
 */
class ResultsFrame : public BaseFrame
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of ResultsFrame
     * @param parent: widget containing the ResultsFrame
     */
    explicit ResultsFrame(QWidget *parent = 0);

    /// Destroy the instance of ResultsFrame
    ~ResultsFrame();

    /// Re-initialize the widget
    virtual void Reset();

    /**
     * @brief Initialize the instance of ResultsFrame
     * @param subjectslist: Selected subjects
     * @param results: process results
     */
    void InitializeWithData(std::vector<TreeItem*> subjectslist,
                            std::map<std::string, GenerationResultItem> results);

public slots:
    /// Event triggered when user click on TreeView
    void ontreeViewclicked();

    /// Event triggered when Preferences are modify
    virtual void onUpdate_Preferences();

protected:
    /// Evaluate the value to set for Enabled property of Next Button
    virtual void modify_nextButton_enabled();

    /// Evaluate the value to set for Enabled property of Previous Button
    virtual void modify_previousButton_enabled();

    /**
     * @brief Request to repaint all or part of a widget
     * @param event: paint event
     */
    void paintEvent(QPaintEvent *event);

private:
    /// User Interface
    Ui::ResultsFrame * _ui;

    /// TreeView containing all results
    ResultsTreeView * _treeView;

};

} // namespace gui

} // namespace dicomifier

#endif // _508febdb_0508_40bd_8395_726fad7b436e
