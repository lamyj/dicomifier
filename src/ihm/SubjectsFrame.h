/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _35bea9c0_ca9a_4108_a701_3e11eee03779
#define _35bea9c0_ca9a_4108_a701_3e11eee03779

#include <QWidget>

#include <components/SubjectsTreeView.h>

namespace dicomifier
{

namespace ihm
{

namespace Ui
{
class SubjectsFrame;
}

class SubjectsFrame : public QWidget
{
    Q_OBJECT

public:
    explicit SubjectsFrame(QWidget *parent = 0);
    ~SubjectsFrame();

private slots:
    void on_dataDirectory_textChanged(const QString &arg1);

    void on_browserButton_clicked();

    void on_dataDirectory_editingFinished();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::SubjectsFrame * _ui;

    SubjectsTreeView * _treeView;

};

} // namespace ihm

} // namespace dicomifier

#endif // _35bea9c0_ca9a_4108_a701_3e11eee03779
