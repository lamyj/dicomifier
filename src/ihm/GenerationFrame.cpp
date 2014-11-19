/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <QFileDialog>
#include <QSettings>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "bruker/actions/EnhanceBrukerDicom.h"
#include "GenerationFrame.h"
#include "PreferencesFrame.h"
#include "ui_GenerationFrame.h"

namespace dicomifier
{

namespace ihm
{

GenerationFrame
::GenerationFrame(QWidget *parent) :
    BaseFrame(parent),
    _ui(new Ui::GenerationFrame)
{
    this->_ui->setupUi(this);

    onUpdate_Preferences();
}

GenerationFrame
::~GenerationFrame()
{
    delete this->_ui;
}

void
GenerationFrame
::Reset()
{
    onUpdate_Preferences();
    this->_ui->DicomdirCheckBox->setChecked(false);
    this->_ui->ZIPCheckBox->setChecked(false);
}

void
GenerationFrame
::RunDicomifier(std::vector<TreeItem *> selectedItems)
{
    std::string format = "";
    if (this->_ui->formatMRIMultiple->isChecked())
    {
        format = "MRImageStorage";
    }
    else if (this->_ui->formatMRISingle->isChecked())
    {
        format = "EnhancedMRImageStorage";
    }

    for (auto currentItem : selectedItems)
    {
        int seriesnum = atoi(currentItem->get_seriesDirectory().c_str());
        int reconum = atoi(currentItem->get_recoDirectory().c_str());

        // Conversion: seriesnum (A) + reconum (B) => ABBBB
        char temp[6];
        memset(&temp[0], 0, 6);
        snprintf(&temp[0], 6, "%01d%04d", seriesnum, reconum);
        std::string seriesnumber(temp);

        // Create dataset
        DcmDataset* dataset = new DcmDataset();

        // Insert SeriesNumber => use to find Bruker data
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString(seriesnumber.c_str()));

        // create Rule
        auto rule = dicomifier::actions::EnhanceBrukerDicom::New(dataset,
                                                                 currentItem->get_directory(),
                                                                 format,
                                                                 this->_ui->outputDirectory->text().toStdString());

        // Execute
        rule->run();

        delete dataset;
    }
}

void
GenerationFrame
::onUpdate_Preferences()
{
    QSettings settings;
    this->_ui->outputDirectory->setText(settings.value(CONF_GROUP_OUTPUT + "/" + CONF_KEY_DIRECTORY,
                                                       QString("")).toString());

    int selectitem = settings.value(CONF_GROUP_OUTPUT + "/" + CONF_KEY_FORMAT, QString("")).toInt();
    if (selectitem == 0)
    {
        this->_ui->formatMRIMultiple->setChecked(true);
    }
    else if (selectitem == 1)
    {
        this->_ui->formatMRISingle->setChecked(true);
    }
}

void
GenerationFrame
::modify_nextButton_enabled()
{
    // "Next button" is "Run Button" for this Frame

    std::string const directory =
            this->_ui->outputDirectory->text().toUtf8().constData();

    // Directory is filled and available
    bool enabled = this->_ui->saveCheckBox->checkState() == Qt::Checked &&
                   directory != "" &&
                   boost::filesystem::exists(boost::filesystem::path(directory));

    emit this->update_nextButton(enabled);
}

void
GenerationFrame
::modify_previousButton_enabled()
{
    // always true
    emit this->update_previousButton(true);
}

void
GenerationFrame
::on_saveCheckBox_clicked()
{
    this->modify_nextButton_enabled();
}

void
GenerationFrame
::on_outputDirBrowseButton_clicked()
{
    // Create dialog
    QFileDialog dialog;
    // Look for Directory
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.setDirectory(this->_ui->outputDirectory->text());

    if (dialog.exec())
    {
        QString directory = dialog.selectedFiles()[0];
        this->_ui->outputDirectory->setText(directory);

        this->on_outputDirectory_editingFinished();
    }
}

void
GenerationFrame
::on_outputDirectory_textEdited(const QString &arg1)
{
    this->modify_nextButton_enabled();
}

void
GenerationFrame
::on_outputDirectory_editingFinished()
{
    this->modify_nextButton_enabled();
}

} // namespace ihm

} // namespace dicomifier
