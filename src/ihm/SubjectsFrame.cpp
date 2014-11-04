#include "SubjectsFrame.h"
#include "ui_SubjectsFrame.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QTreeView>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "bruker/BrukerDirectory.h"

SubjectsFrame
::SubjectsFrame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubjectsFrame), _treeView(NULL)
{
    ui->setupUi(this);

    this->_treeView = new SubjectsTreeView(this->ui->widget);
    this->_treeView->Initialize({});
}

SubjectsFrame
::~SubjectsFrame()
{
    delete ui;
}

void
SubjectsFrame
::on_dataDirectory_textChanged(const QString &arg1)
{

}

void
SubjectsFrame
::on_browserButton_clicked()
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

        this->on_dataDirectory_editingFinished();
    }
}

void
SubjectsFrame
::paintEvent(QPaintEvent *event)
{
    if (this->_treeView != NULL)
    {
        this->_treeView->resize(this->ui->widget->size());
    }
}

void
SubjectsFrame
::on_dataDirectory_editingFinished()
{
    std::string const directory = this->ui->dataDirectory->text().toUtf8().constData();

    if (directory == "")
        return;

    std::vector<SubjectsTreeItemData> subjectsAndStudiesList;

    boost::filesystem::directory_iterator it(directory), it_end;
    for(; it != it_end; ++it)
    {
        // If we find a directory ( = subject )
        if( boost::filesystem::is_directory( (*it) ) )
        {
            std::string file = directory +
                               VALID_FILE_SEPARATOR +
                               std::string((*it).path().filename().c_str()) +
                               VALID_FILE_SEPARATOR +
                               "subject";

            dicomifier::bruker::BrukerDataset * dataset = new dicomifier::bruker::BrukerDataset();

            dataset->LoadFile(file);

            subjectsAndStudiesList.push_back(SubjectsTreeItemData(dataset));

            delete dataset;
        }
        // else ignore files
    }

    this->_treeView->Initialize(subjectsAndStudiesList);
}
