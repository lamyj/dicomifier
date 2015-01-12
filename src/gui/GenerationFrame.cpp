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
#include "dicom/actions/StoreDataset.h"
#include "GenerationFrame.h"
#include "components/PACSTreeItem.h"
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
}

GenerationFrame
::~GenerationFrame()
{
    delete this->_ui;
}

void
GenerationFrame
::Initialize()
{
    QSettings settings;

    // Set Output Directory
    this->_ui->outputDirectory->setText(settings.value(CONF_GROUP_OUTPUT + "/" +
                                                       CONF_KEY_DIRECTORY,
                                                       QString("")).toString());

    // Set Output Format File
    QString selectitem = settings.value(CONF_GROUP_OUTPUT + "/" +
                                    CONF_KEY_FORMAT,
                                    QString("")).toString();
    if (selectitem.toStdString() == "MRImageStorage")
    {
        this->_ui->formatMRIMultiple->setChecked(true);
    }
    else if (selectitem.toStdString() == "EnhancedMRImageStorage")
    {
        this->_ui->formatMRISingle->setChecked(true);
    }

    // Set DICOMDIR Creation
    Qt::CheckState checkstate =
            (Qt::CheckState)settings.value(CONF_GROUP_OUTPUT + "/" + CONF_KEY_DICOMDIR,
                                           Qt::CheckState::Unchecked).toInt();
    this->_ui->DicomdirCheckBox->setCheckState(checkstate);

    // Set ZIP Creation
    checkstate =
            (Qt::CheckState)settings.value(CONF_GROUP_OUTPUT + "/" + CONF_KEY_ZIP,
                                           Qt::CheckState::Unchecked).toInt();
    this->_ui->ZIPCheckBox->setCheckState(checkstate);

    // Set Save Option
    checkstate =
            (Qt::CheckState)settings.value(CONF_GROUP_OUTPUT + "/" + CONF_KEY_SAVE,
                                           Qt::CheckState::Unchecked).toInt();
    this->_ui->saveCheckBox->setCheckState(checkstate);

    // Set Store Option
    checkstate =
            (Qt::CheckState)settings.value(CONF_GROUP_OUTPUT + "/" + CONF_KEY_STORE,
                                           Qt::CheckState::Unchecked).toInt();
    this->_ui->StoreCheckBox->setCheckState(checkstate);

    // Set PACS name
    this->_ui->PACSComboBox->clear();
    int number = settings.value(CONF_GROUP_PACS + "/" + CONF_KEY_NUMBER, 0).toInt();
    QStringList itemslist;
    for (unsigned int i = 0 ; i < number ; ++i)
    {
        std::stringstream stream;
        stream << CONF_GROUP_PACS.toStdString() << "/"
               << CONF_GROUP_PACS.toStdString() << i << "_";

        std::stringstream streamname;
        streamname << stream.str() << CONF_KEY_NAME.toStdString();

        itemslist << settings.value(streamname.str().c_str(), QString("")).toString();
    }
    this->_ui->PACSComboBox->addItems(itemslist);

    BaseFrame::Initialize();
}

void
GenerationFrame
::Reset()
{
    this->Initialize();
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

    // Save preferences
    QSettings settings;
    settings.beginGroup(CONF_GROUP_OUTPUT);
    settings.setValue(CONF_KEY_FORMAT, QString(format.c_str()));
    settings.setValue(CONF_KEY_DICOMDIR, this->_ui->DicomdirCheckBox->checkState());
    settings.setValue(CONF_KEY_ZIP, this->_ui->ZIPCheckBox->checkState());
    settings.setValue(CONF_KEY_SAVE, this->_ui->saveCheckBox->checkState());
    settings.setValue(CONF_KEY_STORE, this->_ui->StoreCheckBox->checkState());
    settings.endGroup();

    std::map<std::string, std::string> mapHascodeToSubject;

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

        if (mapHascodeToSubject.find(currentItem->get_destinationDirectory()) == mapHascodeToSubject.end())
        {
            mapHascodeToSubject[currentItem->get_destinationDirectory()] = currentItem->get_name();
        }

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
            delete dataset;
            currentItem->set_DicomErrorMsg(ret.text());
            continue;
        }

        std::string outputdir = this->_ui->outputDirectory->text().toStdString();
        if (this->_ui->saveCheckBox->isChecked() == false)
        {
            // Create temporary directory
            boost::filesystem::path uniquepath = boost::filesystem::unique_path();
            boost::filesystem::path temp = boost::filesystem::temp_directory_path();

            outputdir = boost::filesystem::canonical(temp).string() + "/" + uniquepath.filename().string();
            boost::filesystem::create_directories(boost::filesystem::path(outputdir.c_str()));
        }

        // create Rule
        auto rule = dicomifier::actions::EnhanceBrukerDicom::New(dataset,
                                                                 currentItem->get_directory(),
                                                                 format,
                                                                 outputdir);

        if (rule == NULL)
        {
            delete dataset;
            currentItem->set_DicomErrorMsg("Cannot create conversion rule");
            continue;
        }

        // Force to look if Cancel is called
        QApplication::processEvents( QEventLoop::AllEvents );

        try
        {
            // Execute Save
            rule->run();

            currentItem->set_DicomErrorMsg("OK");
        }
        catch (dicomifier::DicomifierException &exc)
        {
            dicomifier::loggerError() << exc.what();
            currentItem->set_DicomErrorMsg(exc.what());
        }
        catch (std::exception &e)
        {
            dicomifier::loggerError() << e.what();
            currentItem->set_DicomErrorMsg(e.what());
        }

        if (this->_ui->StoreCheckBox->isChecked() &&
            currentItem->get_DicomErrorMsg() == "OK")
        {
            try
            {
                this->storeFilesIntoPACS(outputdir);

                currentItem->set_StoreErrorMsg("OK"); // TODO
            }
            catch (dicomifier::DicomifierException &exc)
            {
                dicomifier::loggerError() << exc.what();
                currentItem->set_StoreErrorMsg(exc.what());
            }
            catch (std::exception &e)
            {
                dicomifier::loggerError() << e.what();
                currentItem->set_StoreErrorMsg(e.what());
            }
        }

        if (this->_ui->saveCheckBox->isChecked() == false)
        {
            // Remove temporary directory
            boost::filesystem::remove_all(boost::filesystem::path(outputdir.c_str()));
        }

        delete dataset;
    }

    this->_Results.clear();
    for (auto iter = mapHascodeToSubject.begin();
         iter != mapHascodeToSubject.end();
         iter++)
    {
        this->_Results[iter->second] = GenerationResultItem();
    }

    if (this->_ui->saveCheckBox->isChecked() &&
        this->_ui->DicomdirCheckBox->isChecked())
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
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_dicomdirCreation(GenerationResultItem::Result::Fail);
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_DicomdirErrorMsg("DICOMDIR already exist: " + dicomdirfile);
                    continue;
                }

                // Create generator
                DicomDirGenerator generator;
                generator.enableMapFilenamesMode();
                // Create DICOMDIR object
                OFCondition ret = generator.createNewDicomDir(DicomDirGenerator::AP_GeneralPurpose,
                                            dicomdirfile.c_str());

                if (ret.bad())
                {
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_dicomdirCreation(GenerationResultItem::Result::Fail);
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_DicomdirErrorMsg(ret.text());
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
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_dicomdirCreation(GenerationResultItem::Result::Fail);
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_DicomdirErrorMsg(ret.text());
                }
                else
                {
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_dicomdirCreation(GenerationResultItem::Result::OK);
                }
            }
        }
    }

    if (this->_ui->saveCheckBox->isChecked() &&
        this->_ui->ZIPCheckBox->isChecked())
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

                if (myProcess->exitCode() == EXIT_SUCCESS)
                {
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_zipCreation(GenerationResultItem::Result::OK);
                }
                else
                {
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_zipCreation(GenerationResultItem::Result::Fail);
                    this->_Results[mapHascodeToSubject[std::string((*it).path().filename().c_str())]].set_ZipErrorMsg(myProcess->errorString().toStdString());
                }

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

    // Set PACS name
    this->_ui->PACSComboBox->clear();
    int number = settings.value(CONF_GROUP_PACS + "/" + CONF_KEY_NUMBER, 0).toInt();
    QStringList itemslist;
    for (unsigned int i = 0 ; i < number ; ++i)
    {
        std::stringstream stream;
        stream << CONF_GROUP_PACS.toStdString() << "/"
               << CONF_GROUP_PACS.toStdString() << i << "_";

        std::stringstream streamname;
        streamname << stream.str() << CONF_KEY_NAME.toStdString();

        itemslist << settings.value(streamname.str().c_str(), QString("")).toString();
    }
    this->_ui->PACSComboBox->addItems(itemslist);
}

void
GenerationFrame
::modify_nextButton_enabled()
{
    // "Next button" is "Run Button" for this Frame

    std::string const directory =
            this->_ui->outputDirectory->text().toUtf8().constData();

    // Directory is filled and available
    bool enabled = (this->_ui->saveCheckBox->checkState() == Qt::Checked &&
                   directory != "" &&
                   boost::filesystem::exists(boost::filesystem::path(directory))) ||

                   (this->_ui->StoreCheckBox->checkState() == Qt::Checked);

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
::storeFilesIntoPACS(std::string const & directory)
{
    std::string address = "";
    std::string port = "";
    std::string called = "";
    std::string caller = "";
    UserIdentityType idType = UserIdentityType::None;
    std::string first = "";
    std::string second = "";

    // Search PACS information
    QSettings settings;
    int number = settings.value(CONF_GROUP_PACS + "/" + CONF_KEY_NUMBER, 0).toInt();
    QStringList itemslist;
    for (unsigned int i = 0 ; i < number ; ++i)
    {
        std::stringstream stream;
        stream << CONF_GROUP_PACS.toStdString() << "/"
               << CONF_GROUP_PACS.toStdString() << i << "_";

        std::stringstream streamname;
        streamname << stream.str() << CONF_KEY_NAME.toStdString();

        if (settings.value(streamname.str().c_str(), QString("")).toString() ==
                this->_ui->PACSComboBox->currentText())
        {
            std::stringstream streamaddress;
            streamaddress << stream.str() << CONF_KEY_ADDRESS.toStdString();
            address = settings.value(streamaddress.str().c_str(), QString("")).toString().toStdString();

            std::stringstream streamport;
            streamport << stream.str() << CONF_KEY_PORT.toStdString();
            port = settings.value(streamport.str().c_str(), QString("")).toString().toStdString();

            std::stringstream streamcalled;
            streamcalled << stream.str() << CONF_KEY_CALLED.toStdString();
            called = settings.value(streamcalled.str().c_str(), QString("")).toString().toStdString();

            std::stringstream streamcaller;
            streamcaller << stream.str() << CONF_KEY_CALLER.toStdString();
            caller = settings.value(streamcaller.str().c_str(), QString("")).toString().toStdString();

            std::stringstream streamidentity;
            streamidentity << stream.str() << CONF_KEY_IDENTITY.toStdString();
            idType = (UserIdentityType)settings.value(streamidentity.str().c_str(), 0).toInt();

            std::stringstream streamfirst;
            streamfirst << stream.str() << CONF_KEY_FIRST.toStdString();
            first = settings.value(streamfirst.str().c_str(), QString("")).toString().toStdString();

            std::stringstream streamsecond;
            streamsecond << stream.str() << CONF_KEY_SECOND.toStdString();
            second = settings.value(streamsecond.str().c_str(), QString("")).toString().toStdString();

            break;
        }
    }

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
            this->storeFilesIntoPACS(object);
        }
        else
        {
            DcmFileFormat fileformat;
            fileformat.loadFile(boost::filesystem::canonical(*it).string().c_str());
            DcmDataset * dataset = fileformat.getAndRemoveDataset();

            // Create Store Rule
            auto storerule = dicomifier::actions::StoreDataset::New(
                        dataset, address, std::stoi(port), called, caller,
                        idType, first, second);

            // Execute Store
            storerule->run();
        }
    }
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

        QSettings settings;

        settings.beginGroup(CONF_GROUP_OUTPUT);
        settings.setValue(CONF_KEY_DIRECTORY, directory);
        settings.endGroup();

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

void
GenerationFrame
::on_CreateButton_clicked()
{
    emit this->CreateNewPACSConfiguration();
}

} // namespace gui

} // namespace dicomifier
