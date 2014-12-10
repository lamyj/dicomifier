/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QProgressDialog>
#include <QSettings>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include <zlib.h>

#include "bruker/actions/EnhanceBrukerDicom.h"
#include "core/Logger.h"
#include "GenerationFrame.h"
#include "PreferencesFrame.h"
#include "ui_GenerationFrame.h"

namespace dicomifier
{

namespace gui
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
    // Create ProgressDialog
    QProgressDialog progress("Copying files...", "Cancel", 0, selectedItems.size(), this);
    progress.setWindowModality(Qt::WindowModal);
    QRect geom = progress.geometry();
    geom.setWidth(900);
    progress.setGeometry(geom);
    progress.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    progress.show();

    std::string format = "";
    if (this->_ui->formatMRIMultiple->isChecked())
    {
        format = "MRImageStorage";
    }
    else if (this->_ui->formatMRISingle->isChecked())
    {
        format = "EnhancedMRImageStorage";
    }

    int progressValue = 0;
    // Create DICOM files
    for (auto currentItem : selectedItems)
    {
        // Canceled => force stop
        if (progress.wasCanceled())
        {
            return;
        }

        // Update progressDialog
        progress.setValue(progressValue);
        ++progressValue;
        // Update ProgressDialog label
        std::stringstream progressLabel;
        progressLabel << "Create DICOM " << progressValue << " / " << selectedItems.size()
                      << " (Directory = " << currentItem->get_subjectDirectory() << ", "
                      << "Series=" << currentItem->get_seriesDirectory() << ", "
                      << "Reco=" << currentItem->get_recoDirectory() << ")";
        progress.setLabelText(QString(progressLabel.str().c_str()));

        int seriesnum = atoi(currentItem->get_seriesDirectory().c_str());
        int reconum = atoi(currentItem->get_recoDirectory().c_str());

        std::string mask = seriesnum < 10 ? "%01d%04d" : "%02d%04d";

        // Conversion: seriesnum (A) + reconum (B) => AABBBB
        char temp[7];
        memset(&temp[0], 0, 7);
        snprintf(&temp[0], 7, mask.c_str(), seriesnum, reconum);
        std::string seriesnumber(temp);

        // Create dataset
        DcmDataset* dataset = new DcmDataset();

        // Insert SeriesNumber => use to find Bruker data
        OFCondition ret = dataset->putAndInsertOFStringArray(DCM_SeriesNumber,
                                                            OFString(seriesnumber.c_str()));
        if (ret.bad())
        {
            // TODO do something
        }

        // create Rule
        auto rule = dicomifier::actions::EnhanceBrukerDicom::New(dataset,
                                                                 currentItem->get_directory(),
                                                                 format,
                                                                 this->_ui->outputDirectory->text().toStdString());

        if (rule == NULL)
        {
            // TODO do something
        }

        // Force to look if Cancel is called
        QApplication::processEvents( QEventLoop::AllEvents );

        try
        {
            // Execute
            rule->run();
        }
        catch (dicomifier::DicomifierException &exc)
        {
            dicomifier::loggerError() << exc.what();
        }
        catch (std::exception &e)
        {
            dicomifier::loggerError() << e.what();
        }

        delete dataset;
    }

    if (this->_ui->DicomdirCheckBox->isChecked())
    {
        // Create DICOMDIR file (One per Subject)

        // patient_extra_attributes
        std::vector<DcmTagKey> patient_extra_attributes_cpp =
        {
            // insert other DcmTagKey here
        };

        // study_extra_attributes
        std::vector<DcmTagKey> study_extra_attributes_cpp =
        {
            DCM_StudyDescription
            // insert other DcmTagKey here
        };

        // series_extra_attributes
        std::vector<DcmTagKey> series_extra_attributes_cpp =
        {
            DCM_SeriesDescription
            // insert other DcmTagKey here
        };

        boost::filesystem::directory_iterator it(this->_ui->outputDirectory->text().toStdString()),
                                              countdir(this->_ui->outputDirectory->text().toStdString()),
                                              it_end;

        int nbdir = 0;
        for(; countdir != it_end; ++countdir)
        {
            if( boost::filesystem::is_directory( (*countdir) ) )
            {
                ++nbdir;
            }
        }

        progressValue = 0;
        progress.setValue(progressValue);
        progress.setMaximum(nbdir);

        for(; it != it_end; ++it)
        {
            // Canceled => force stop
            if (progress.wasCanceled())
            {
                return;
            }

            if( boost::filesystem::is_directory( (*it) ) )
            {
                // Update progressDialog
                progress.setValue(progressValue);
                ++progressValue;
                // Update ProgressDialog label
                std::stringstream progressLabel;
                progressLabel << "Create DICOMDIR " << progressValue << " / " << nbdir
                              << " (Directory = " << std::string((*it).path().filename().c_str()) << ")";
                progress.setLabelText(QString(progressLabel.str().c_str()));

                std::string dir = this->_ui->outputDirectory->text().toStdString() +
                                  VALID_FILE_SEPARATOR +
                                  std::string((*it).path().filename().c_str());

                std::string dicomdirfile = dir + VALID_FILE_SEPARATOR + "DICOMDIR";

                if (boost::filesystem::exists(boost::filesystem::path(dicomdirfile.c_str())))
                {
                    // TODO log an error and continue
                    throw DicomifierException("DICOMDIR already exist: " + dicomdirfile);
                }

                // Create generator
                DicomDirGenerator generator;
                generator.enableMapFilenamesMode();
                // Create DICOMDIR object
                OFCondition ret = generator.createNewDicomDir(DicomDirGenerator::AP_GeneralPurpose,
                                            dicomdirfile.c_str());

                if (ret.bad())
                {
                    // TODO do something
                    continue;
                }

                // Configure DICOMDIR
                generator.setPatientExtraAttributes(patient_extra_attributes_cpp);
                generator.setStudyExtraAttributes(study_extra_attributes_cpp);
                generator.setSeriesExtraAttributes(series_extra_attributes_cpp);
                // Add files
                this->insertFilesForDicomdir(dir, &generator);
                // Write DICOMDIR
                ret = generator.writeDicomDir();

                if (ret.bad())
                {
                    // TODO do something
                }
            }
        }
    }

    if (this->_ui->ZIPCheckBox->isChecked())
    {
        boost::filesystem::directory_iterator it(this->_ui->outputDirectory->text().toStdString()),
                                              countdir(this->_ui->outputDirectory->text().toStdString()),
                                              it_end;

        int nbdir = 0;
        for(; countdir != it_end; ++countdir)
        {
            if( boost::filesystem::is_directory( (*countdir) ) )
            {
                ++nbdir;
            }
        }

        progressValue = 0;
        progress.setValue(progressValue);
        progress.setMaximum(nbdir);

        for(; it != it_end; ++it)
        {
            // Canceled => force stop
            if (progress.wasCanceled())
            {
                return;
            }

            if( boost::filesystem::is_directory( (*it) ) )
            {
                ++progressValue;
                // Update ProgressDialog label
                std::stringstream progressLabel;
                progressLabel << "Create ZIP Archive " << progressValue << " / " << nbdir
                              << " (Directory = " << std::string((*it).path().filename().c_str()) << ")";
                progress.setLabelText(QString(progressLabel.str().c_str()));

                std::string dir = this->_ui->outputDirectory->text().toStdString() +
                                  VALID_FILE_SEPARATOR +
                                  std::string((*it).path().filename().c_str());

                std::string zipfile = std::string((*it).path().filename().c_str());

                QDir directory(QString(dir.c_str()));

                // Create ZIP Archive (One per Subject)
                QString command = "zip";
                QStringList args;
                args << "-r" << QString(zipfile.c_str());
                args << directory.entryList();

                QProcess *myProcess = new QProcess(this);
                myProcess->setWorkingDirectory(QString(dir.c_str()));
                myProcess->start(command, args);

                myProcess->waitForFinished();

                // TODO look the process return

                // Update progressDialog
                progress.setValue(progressValue);
            }
        }
    }

    // Disabled Run button
    emit this->update_nextButton(false);

    // Terminate the progressDialog
    progress.setValue(progress.maximum());
}

void
GenerationFrame
::onUpdate_Preferences()
{
    QSettings settings;
    this->_ui->outputDirectory->setText(settings.value(CONF_GROUP_OUTPUT + "/" +
                                                       CONF_KEY_DIRECTORY,
                                                       QString("")).toString());

    int selectitem = settings.value(CONF_GROUP_OUTPUT + "/" +
                                    CONF_KEY_FORMAT,
                                    QString("")).toInt();
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
::insertFilesForDicomdir(const std::string &directory, DicomDirGenerator *dcmdirgenerator)
{
    boost::filesystem::directory_iterator it(directory), it_end;
    for(; it != it_end; ++it)
    {
        // if it is a directory
        if( boost::filesystem::is_directory( (*it) ) )
        {
            std::string const object = directory +
                                       VALID_FILE_SEPARATOR +
                                       std::string((*it).path().filename().c_str());
            // Recursive call
            this->insertFilesForDicomdir(object, dcmdirgenerator);
        }
        else
        {
            // add file
            OFCondition ret = dcmdirgenerator->addDicomFile((*it).path().filename().c_str(),
                                                            directory.c_str());

            if (ret.bad())
            {
                // TODO do something (error ?)
            }
        }
    }
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

} // namespace gui

} // namespace dicomifier
