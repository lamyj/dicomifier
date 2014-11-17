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

namespace ihm
{

namespace Ui
{
class SubjectsFrame;
}

class SubjectsFrame : public BaseFrame
{
    Q_OBJECT

public:
    explicit SubjectsFrame(QWidget *parent = 0);
    virtual ~SubjectsFrame();

    virtual void Initialize();

    virtual void Reset();

    std::vector<TreeItem*> get_selectedData() const;

    std::string get_mainDirectory() const;

public slots:
    void on_browserButton_clicked();

    void on_dataDirectory_editingFinished();

    void on_sortedBySubjects_toggled(bool checked);

    void ontreeViewclicked();

protected:
    virtual void modify_nextButton_enabled();

    virtual void modify_previousButton_enabled();

    void paintEvent(QPaintEvent *event);

    void set_list_enabled(bool enabled);

private slots:
    void on_selectAllCheckBox_clicked();

    void on_filtersName_textEdited(const QString &arg1);

    void ReceivedDate(double date);

    void on_dateFilterBegin_dateChanged(const QDate &date);

    void on_dateFilterEnd_dateChanged(const QDate &date);

private:
    Ui::SubjectsFrame * _ui;

    SubjectsTreeView * _treeView;

    QDate _datemin;

};

} // namespace ihm

} // namespace dicomifier

#endif // _35bea9c0_ca9a_4108_a701_3e11eee03779
