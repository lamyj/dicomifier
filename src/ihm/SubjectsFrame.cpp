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
    BaseFrame(parent),
    _ui(new Ui::SubjectsFrame), _treeView(NULL)
{
    this->_ui->setupUi(this);

    this->_treeView = new SubjectsTreeView(this->_ui->widget);
    this->_treeView->Initialize({});

    connect(this->_treeView, SIGNAL(itemsSelectionChanged()),
            this, SLOT(ontreeViewclicked()));

}

SubjectsFrame
::~SubjectsFrame()
{
    delete this->_ui;
}

void
SubjectsFrame
::Reset()
{
    this->_ui->dataDirectory->setText(QString(""));
    this->on_dataDirectory_editingFinished();
}

std::vector<TreeItem*>
SubjectsFrame
::get_selectedData() const
{
    std::vector<TreeItem*> returnvect;
    SubjectsTreeModel* model =
            dynamic_cast<SubjectsTreeModel*>(this->_treeView->model());

    if (model != NULL)
    {
        returnvect = model->get_item_selected();
    }

    return returnvect;
}

std::string
SubjectsFrame
::get_mainDirectory() const
{
    return this->_ui->dataDirectory->text().toStdString();
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
::set_list_enabled(bool enabled)
{
    this->_ui->radioButton->setEnabled(enabled);
    this->_ui->radioButton_2->setEnabled(enabled);
    this->_ui->lineEdit->setEnabled(enabled);
    this->_ui->lineEdit_2->setEnabled(enabled);
    this->_ui->label_2->setEnabled(enabled);
    this->_ui->label_3->setEnabled(enabled);
    this->_treeView->setEnabled(enabled);

    this->modify_nextButton_enabled();
}

void
SubjectsFrame
::on_dataDirectory_editingFinished()
{
    std::string const directory =
            this->_ui->dataDirectory->text().toUtf8().constData();

    if (directory == "" || !boost::filesystem::exists(boost::filesystem::path(directory)))
    {
        this->_treeView->Initialize({});
        this->set_list_enabled(false);
        return;
    }
    this->set_list_enabled(true);

    std::vector<TreeItem*> subjectsAndStudiesList;

    boost::filesystem::directory_iterator it(directory), it_end;
    for(; it != it_end; ++it)
    {
        // If we find a directory ( = subject )
        if( boost::filesystem::is_directory( (*it) ) )
        {
            std::string const dir = directory +
                                    VALID_FILE_SEPARATOR +
                                    std::string((*it).path().filename().c_str());
            std::string file = dir +
                               VALID_FILE_SEPARATOR +
                               "subject";

            if (!boost::filesystem::exists(boost::filesystem::path(file)))
            {
                continue;
            }

            dicomifier::bruker::BrukerDataset * dataset =
                    new dicomifier::bruker::BrukerDataset();

            dataset->LoadFile(file);

            TreeItem* treeitem = new TreeItem();
            treeitem->set_directory(dir);
            treeitem->fill_data(dataset);

            subjectsAndStudiesList.push_back(treeitem);

            delete dataset;
        }
        // else ignore files
    }

    this->_treeView->Initialize(subjectsAndStudiesList);
}

void
SubjectsFrame
::on_radioButton_toggled(bool checked)
{
    this->_treeView->set_displaySubject(checked);
}

void
SubjectsFrame
::ontreeViewclicked()
{
    this->modify_nextButton_enabled();
}

void
SubjectsFrame
::modify_nextButton_enabled()
{
    std::string const directory =
            this->_ui->dataDirectory->text().toUtf8().constData();

    // Directory is filled and available
    bool enabled = directory != "" &&
                   boost::filesystem::exists(boost::filesystem::path(directory));

    enabled &= this->_treeView->is_item_selected();

    emit this->update_nextButton(enabled);
}

void
SubjectsFrame
::modify_previousButton_enabled()
{
    // Nothing to do: always false
    emit this->update_previousButton(false);
}

} // namespace ihm

} // namespace dicomifier
