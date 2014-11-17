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
    _ui(new Ui::SubjectsFrame), _treeView(NULL), _datemin(QDate::currentDate())
{
    this->_ui->setupUi(this);

    this->_treeView = new SubjectsTreeView(this->_ui->widget);
    this->_treeView->Initialize({});

    connect(this->_treeView, SIGNAL(itemsSelectionChanged()),
            this, SLOT(ontreeViewclicked()));

    this->set_list_enabled(false);

    this->_ui->dateFilterBegin->setDisplayFormat(QString("dd/MM/yyyy"));
    this->_ui->dateFilterEnd->setDisplayFormat(QString("dd/MM/yyyy"));

    this->_ui->dateFilterBegin->setDate(this->_datemin);
    this->_ui->dateFilterEnd->setDate(QDate::currentDate());
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
    this->_ui->sortedBySubjects->setEnabled(enabled);
    this->_ui->sortedByStudies->setEnabled(enabled);
    this->_ui->filtersName->setEnabled(enabled);
    this->_ui->dateFilterBegin->setEnabled(enabled);
    this->_ui->dateFilterEnd->setEnabled(enabled);
    this->_ui->sortedTitle->setEnabled(enabled);
    this->_ui->filtersTitle->setEnabled(enabled);
    this->_ui->fromDateTitle->setEnabled(enabled);
    this->_ui->toDateTitle->setEnabled(enabled);
    this->_treeView->setEnabled(enabled);
    this->_ui->selectAllCheckBox->setEnabled(enabled);

    this->modify_nextButton_enabled();
}

void
SubjectsFrame
::on_dataDirectory_editingFinished()
{
    this->_datemin = QDate::currentDate();

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
            connect(treeitem, SIGNAL(SendDate(double)), this, SLOT(ReceivedDate(double)));
            treeitem->set_directory(dir);
            treeitem->fill_data(dataset);
            disconnect(treeitem, SIGNAL(SendDate(double)), this, SLOT(ReceivedDate(double)));

            subjectsAndStudiesList.push_back(treeitem);

            delete dataset;
        }
        // else ignore files
    }
    this->_ui->dateFilterBegin->setDate(this->_datemin);
    this->_treeView->filter_date(this->_datemin, QDate::currentDate(), false);

    this->_treeView->Initialize(subjectsAndStudiesList);
}

void
SubjectsFrame
::on_sortedBySubjects_toggled(bool checked)
{
    this->_treeView->set_displaySubject(checked);
}

void
SubjectsFrame
::ontreeViewclicked()
{
    this->_ui->selectAllCheckBox->setCheckState(this->_treeView->compute_selection());
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

    enabled &= (this->_ui->selectAllCheckBox->checkState() != Qt::Unchecked);

    emit this->update_nextButton(enabled);
}

void
SubjectsFrame
::modify_previousButton_enabled()
{
    // Nothing to do: always false
    emit this->update_previousButton(false);
}

void
SubjectsFrame
::on_selectAllCheckBox_clicked()
{
    if (this->_ui->selectAllCheckBox->checkState() == Qt::PartiallyChecked)
    {
        this->_ui->selectAllCheckBox->setCheckState(Qt::Checked);
    }
    this->_treeView->setCheckState_all(this->_ui->selectAllCheckBox->checkState());
    this->modify_nextButton_enabled();
}

void
SubjectsFrame
::on_filtersName_textEdited(const QString &arg1)
{
    this->_treeView->filter_name(arg1);
}

void
SubjectsFrame
::on_dateFilterBegin_dateChanged(const QDate &date)
{
    this->_treeView->filter_date(date, this->_ui->dateFilterEnd->date());
}

void
SubjectsFrame
::on_dateFilterEnd_dateChanged(const QDate &date)
{
    this->_treeView->filter_date(this->_datemin, date);
}

void
SubjectsFrame
::ReceivedDate(double date)
{
    std::time_t now = date;
    tm *ltm = localtime(&now);
    QDate datetemp(ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday);

    if (this->_datemin > datetemp)
    {
        this->_datemin = datetemp;
    }
}

} // namespace ihm

} // namespace dicomifier
