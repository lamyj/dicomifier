#include "SubjectsFrame.h"
#include "ui_SubjectsFrame.h"

#include <QFileDialog>

SubjectsFrame::SubjectsFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubjectsFrame)
{
    ui->setupUi(this);
}

SubjectsFrame::~SubjectsFrame()
{
    delete ui;
}

void SubjectsFrame::on_dataDirectory_textChanged(const QString &arg1)
{

}

void SubjectsFrame::on_browserButton_clicked()
{
    // Create dialog
    QFileDialog dialog;
    // Look for Directory
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.setDirectory(this->ui->dataDirectory->text());

    if (dialog.exec())
    {
        QString directory = dialog.selectedFiles()[0];
        this->ui->dataDirectory->setText(directory);
    }
}
