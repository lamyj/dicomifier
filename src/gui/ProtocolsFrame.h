/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d701c893_f5eb_43a4_bf29_271618b5489e
#define _d701c893_f5eb_43a4_bf29_271618b5489e

#include "BaseFrame.h"
#include "components/ProtocolsTreeView.h"

namespace dicomifier
{

namespace gui
{

namespace Ui {
class ProtocolsFrame;
} // namespace Ui

/**
 * @brief The ProtocolsFrame class
 */
class ProtocolsFrame : public BaseFrame
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of ProtocolsFrame
     * @param parent: widget containing the ProtocolsFrame
     */
    explicit ProtocolsFrame(QWidget *parent = 0);

    /// Destroy the instance of ProtocolsFrame
    virtual ~ProtocolsFrame();

    /**
     * @brief Initialize the instance of ProtocolsFrame
     * @param subjectslist: selected subjects
     */
    void InitializeWithData(std::vector<TreeItem*> subjectslist);

    /// Re-initialize the widget
    virtual void Reset();

    /**
     * @brief Return all selected items
     * @return selected items
     */
    std::vector<TreeItem*> get_selectedData() const;

public slots:
    /// Event triggered when user click on TreeView
    void ontreeViewclicked();

    /// Event triggered when Preferences are modify
    virtual void onUpdate_Preferences();

    /// Event triggered by clicking on Select All checkBox
    void on_selectAllCheckBox_clicked();

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
    Ui::ProtocolsFrame * _ui;

    /// TreeView containing all Series/Reconstruction
    ProtocolsTreeView * _treeView;

};

} // namespace gui

} // namespace dicomifier

#endif // _d701c893_f5eb_43a4_bf29_271618b5489e
