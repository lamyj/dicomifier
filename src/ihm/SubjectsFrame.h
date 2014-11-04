#ifndef SUBJECTSFRAME_H
#define SUBJECTSFRAME_H

#include <QWidget>

#include <components/SubjectsTreeView.h>

namespace Ui {
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
    Ui::SubjectsFrame *ui;

    SubjectsTreeView * _treeView;

};

#endif // SUBJECTSFRAME_H
