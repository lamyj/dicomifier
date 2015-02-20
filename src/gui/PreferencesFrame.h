/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e3c36f6b_ae80_47c0_9a2f_226e659fd6d8
#define _e3c36f6b_ae80_47c0_9a2f_226e659fd6d8

#include "BaseFrame.h"
#include "components/PACSTreeView.h"
#include "PACSConfigurationFrame.h"

namespace dicomifier
{

namespace gui
{

namespace Ui {
class PreferencesFrame;
} // namespace Ui

/**
 * @brief The PreferencesFrame class
 */
class PreferencesFrame : public BaseFrame
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of PreferencesFrame
     * @param parent: widget containing the PreferencesFrame
     */
    explicit PreferencesFrame(QWidget *parent = 0);

    /// Destroy the instance of PreferencesFrame
    virtual ~PreferencesFrame();

    /// Initialize the instance of PreferencesFrame
    virtual void Initialize();

    /// Re-initialize the widget
    virtual void Reset();

    /// Save the preferences with QSettings
    void SavePreferences();

public slots:
    /// Event triggered when Preferences are modify
    virtual void onUpdate_Preferences();

    /**
     * @brief Event triggered when user click on TreeView
     * @param index: item clicked
     */
    void TreeViewClicked(QModelIndex index);

    /// Event triggered by clicking New Button
    void on_NewButton_clicked();

    /// Event triggered by clicking Edit Button
    void on_EditButton_clicked();

    /// Event triggered by clicking Delete Button
    void on_DeleteButton_clicked();

protected:
    /// Evaluate the value to set for Enabled property of Next Button
    virtual void modify_nextButton_enabled();

    /// Evaluate the value to set for Enabled property of Previous Button
    virtual void modify_previousButton_enabled();

    /// Request to repaint all or part of a widget
    void paintEvent(QPaintEvent *event);

private:
    /// User Interface
    Ui::PreferencesFrame * _ui;

    /// TreeView containing PACS information
    PACSTreeView * _treeView;

    PACSConfigurationFrame * _configFrame;

};

} // namespace gui

} // namespace dicomifier

#endif // _e3c36f6b_ae80_47c0_9a2f_226e659fd6d8
