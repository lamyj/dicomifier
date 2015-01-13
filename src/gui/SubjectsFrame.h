/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _35bea9c0_ca9a_4108_a701_3e11eee03779
#define _35bea9c0_ca9a_4108_a701_3e11eee03779

#include "BaseFrame.h"
#include "components/SubjectsTreeView.h"

namespace dicomifier
{

namespace gui
{

namespace Ui
{
class SubjectsFrame;
} // namespace Ui

/**
 * @brief The SubjectsFrame class
 */
class SubjectsFrame : public BaseFrame
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of SubjectsFrame
     * @param parent: widget containing the SubjectsFrame
     */
    explicit SubjectsFrame(QWidget *parent = 0);

    /// Destroy the instance of SubjectsFrame
    virtual ~SubjectsFrame();

    /// Initialize the instance of SubjectsFrame
    virtual void Initialize();

    /// Re-initialize the widget
    virtual void Reset();

    /**
     * @brief Return all selected items
     * @return Selected treeItem
     */
    std::vector<TreeItem*> get_selectedData() const;

    /**
     * @brief Return the bruker data directory
     * @return selected input directory
     */
    std::string get_mainDirectory() const;

public slots:
    /// Event triggered by clicking on Browser button
    void on_browserButton_clicked();

    /// Event triggered by clicking on Refresh button
    void on_refreshButton_clicked();

    /// Event triggered by modifying input directory LineEdit
    void on_dataDirectory_editingFinished();

    /// Event triggered by clicking on Subject or Study RadioButton
    void on_sortedBySubjects_toggled(bool checked);

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

    /**
     * @brief Modify enabled property for all components in Subject/Study part
     * @param enabled: new value
     */
    void set_list_enabled(bool enabled);

private slots:
    /// Event triggered by clicking on Select All checkBox
    void on_selectAllCheckBox_clicked();

    /// Event triggered by modifying filter LineEdit
    void on_filtersName_textEdited(const QString &arg1);

    void ReceivedDate(double date);

    /// Event triggered by modifying filter begin DateTime
    void on_dateFilterBegin_dateTimeChanged(const QDateTime &dateTime);

    /// Event triggered by modifying filter end DateTime
    void on_dateFilterEnd_dateTimeChanged(const QDateTime &dateTime);

private:
    /// User Interface
    Ui::SubjectsFrame * _ui;

    /// TreeView containing all subjects/Studies
    SubjectsTreeView * _treeView;

    /// Minimum date and time find in bruker data
    QDateTime _datetimemin;

};

} // namespace gui

} // namespace dicomifier

#endif // _35bea9c0_ca9a_4108_a701_3e11eee03779
