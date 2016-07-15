/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _35bea9c0_ca9a_4108_a701_3e11eee03779
#define _35bea9c0_ca9a_4108_a701_3e11eee03779

#include <vector>

#include <QtCore>
#include <QtGui>

#include "BaseFrame.h"
#include "components/SubjectsTreeView.h"
#include "components/TreeItem.h"

namespace dicomifier
{

namespace gui
{

namespace Ui
{
class SubjectsFrame;
} // namespace Ui

/// @brief Widget displaying the available subjects
class SubjectsFrame : public BaseFrame
{
    Q_OBJECT

public:
    /// @brief Constructor.
    explicit SubjectsFrame(QWidget *parent = 0);

    /// @brief Destructor.
    virtual ~SubjectsFrame();

    /// Initialize the instance of SubjectsFrame
    virtual void Initialize();

    /// Re-initialize the widget
    virtual void Reset();

    /// @brief Return all selected subjects.
    std::vector<TreeItem*> get_selected_data() const;

protected:
    /// Evaluate the value to set for Enabled property of Next Button
    virtual void modify_nextButton_enabled();

    /// Evaluate the value to set for Enabled property of Previous Button
    virtual void modify_previousButton_enabled();

    /// @brief Request to repaint all or part of a widget
    void paintEvent(QPaintEvent *event);

    /**
     * @brief Modify enabled property for all components in Subject/Study part
     * @param enabled: new value
     */
    void _set_list_enabled(bool enabled);

private:
    /// User Interface
    Ui::SubjectsFrame * _ui;

    /// TreeView containing all subjects/Studies
    SubjectsTreeView * _tree_view;

    /// Minimum date and time find in bruker data
    QDateTime _datetimemin;

private slots:
    void on_browserButton_clicked();

    void on_refreshButton_clicked();

    void on_dataDirectory_editingFinished();

    void on_sortedBySubjects_toggled(bool checked);



    /// Event triggered when Preferences are modify
    virtual void onUpdate_Preferences();

    void on_selectAllCheckBox_clicked();

    void on_filtersName_textEdited(const QString &arg1);

    void on_dateFilterBegin_dateTimeChanged(const QDateTime &dateTime);

    void on_dateFilterEnd_dateTimeChanged(const QDateTime &dateTime);

    void on_tree_view_clicked();
    void on_date_received(double date);

};

} // namespace gui

} // namespace dicomifier

#endif // _35bea9c0_ca9a_4108_a701_3e11eee03779
