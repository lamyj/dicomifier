/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <QFileDialog>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "bruker/BrukerDirectory.h"
#include "SubjectsFrame.h"
#include "ui_SubjectsFrame.h"

namespace dicomifier
{

namespace ihm
{

SubjectsFrame
::SubjectsFrame(QWidget *parent) :
    QWidget(parent),
    _ui(new Ui::SubjectsFrame), _treeView(NULL)
{
    this->_ui->setupUi(this);

    this->_treeView = new SubjectsTreeView(this->_ui->widget);
    this->_treeView->Initialize({});
}

SubjectsFrame
::~SubjectsFrame()
{
    delete this->_ui;
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
    dialog.setDirectory(this->_ui->dataDirectory->text());

    if (dialog.exec())
    {
        QString directory = dialog.selectedFiles()[0];
        this->_ui->dataDirectory->setText(directory);

        this->on_dataDirectory_editingFinished();
    }
}

void
SubjectsFrame
::paintEvent(QPaintEvent *event)
{
    if (this->_treeView != NULL)
    {
        this->_treeView->resize(this->_ui->widget->size());
    }
}

void
SubjectsFrame
::on_dataDirectory_editingFinished()
{
    std::string const directory =
            this->_ui->dataDirectory->text().toUtf8().constData();

    if (directory == "")
    {
        this->_treeView->Initialize({});
        return;
    }

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

            dicomifier::bruker::BrukerDataset * dataset =
                    new dicomifier::bruker::BrukerDataset();

            dataset->LoadFile(file);

            subjectsAndStudiesList.push_back(SubjectsTreeItemData(dataset));

            delete dataset;
        }
        // else ignore files
    }

    this->_treeView->Initialize(subjectsAndStudiesList);
}

} // namespace ihm

} // namespace dicomifier
