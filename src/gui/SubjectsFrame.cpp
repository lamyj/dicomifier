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

namespace gui
{

SubjectsFrame
::SubjectsFrame(QWidget *parent) :
    BaseFrame(parent),
    _ui(new Ui::SubjectsFrame), _treeView(NULL), _datetimemin(QDateTime::currentDateTime())
{
    this->_ui->setupUi(this);

    this->_treeView = new SubjectsTreeView(this->_ui->widget);
    this->_treeView->Initialize({});

    connect(this->_treeView, SIGNAL(itemsSelectionChanged()),
            this, SLOT(ontreeViewclicked()));

    this->set_list_enabled(false);

    this->_ui->dateFilterBegin->setDisplayFormat(QString("dd/MM/yyyy HH:mm:ss"));
    this->_ui->dateFilterEnd->setDisplayFormat(QString("dd/MM/yyyy HH:mm:ss"));

    this->_ui->dateFilterBegin->setDateTime(this->_datetimemin);
    this->_ui->dateFilterEnd->setDateTime(QDateTime::currentDateTime());

    QSettings settings;
    this->_ui->dataDirectory->setText(settings.value(CONF_GROUP_INPUT + "/" +
                                                     CONF_KEY_DIRECTORY,
                                                     QString("")).toString());
}

SubjectsFrame
::~SubjectsFrame()
{
    delete this->_ui;
}

void
SubjectsFrame
::Initialize()
{
    if (this->_ui->dataDirectory->text() != "")
    {
        on_dataDirectory_editingFinished();
    }
    ontreeViewclicked();
    BaseFrame::Initialize();
}

void
SubjectsFrame
::Reset()
{
    QSettings settings;
    this->_ui->dataDirectory->setText(settings.value(CONF_GROUP_INPUT + "/" +
                                                     CONF_KEY_DIRECTORY,
                                                     QString("")).toString());
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

        QSettings settings;

        settings.beginGroup(CONF_GROUP_INPUT);
        settings.setValue(CONF_KEY_DIRECTORY, directory);
        settings.endGroup();

        this->on_dataDirectory_editingFinished();
    }
}

void
SubjectsFrame
::on_refreshButton_clicked()
{
    this->on_dataDirectory_editingFinished();
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
    this->_datetimemin = QDateTime::currentDateTime();

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
            treeitem->set_subjectDirectory(std::string((*it).path().filename().c_str()));
            disconnect(treeitem, SIGNAL(SendDate(double)), this, SLOT(ReceivedDate(double)));

            subjectsAndStudiesList.push_back(treeitem);

            delete dataset;
        }
        // else ignore files
    }
    this->_ui->dateFilterBegin->setDateTime(this->_datetimemin);
    this->_treeView->filter_date(this->_datetimemin, QDateTime::currentDateTime(), false);

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
::onUpdate_Preferences()
{
    // Nothing to do
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
::on_dateFilterBegin_dateTimeChanged(const QDateTime &dateTime)
{
    this->_treeView->filter_date(dateTime, this->_ui->dateFilterEnd->dateTime());
}

void
SubjectsFrame
::on_dateFilterEnd_dateTimeChanged(const QDateTime &dateTime)
{
    this->_treeView->filter_date(this->_datetimemin, dateTime);
}

void
SubjectsFrame
::ReceivedDate(double date)
{
    std::time_t now = date;
    tm *ltm = localtime(&now);
    QDateTime datetemp(QDate(ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday),
                       QTime(ltm->tm_hour, ltm->tm_min, ltm->tm_sec));

    if (this->_datetimemin > datetemp)
    {
        this->_datetimemin = datetemp;
    }
}

} // namespace gui

} // namespace dicomifier
