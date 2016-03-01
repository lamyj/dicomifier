/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <QFileDialog>
#include <QProcess>
#include <QSettings>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include <odil/Association.h>
#include <odil/BasicDirectoryCreator.h>
#include <odil/Reader.h>
#include <odil/registry.h>
#include <odil/StoreSCU.h>

#include <zlib.h>

#include "bruker/converters/EnhanceBrukerDicom.h"
#include "components/PACSTreeItem.h"
#include "core/DicomifierException.h"
#include "core/Logger.h"
#include "GenerationFrame.h"
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

    if (selectitem.toStdString() == odil::registry::MRImageStorage)
    {
        this->_ui->formatMRIMultiple->setChecked(true);
    }
    else if (selectitem.toStdString() == odil::registry::EnhancedMRImageStorage)
    {
        this->_ui->formatMRISingle->setChecked(true);
    }
    else
    {// default
        this->_ui->formatMRIMultiple->setChecked(true);
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
    // Initialize ProgressDialog
    progress.setWindowModality(Qt::WindowModal);
    QRect geom = progress.geometry();
    geom.setWidth(900);
    progress.setGeometry(geom);
    progress.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Display ProgressDialog
    progress.show();

    // Save preferences
    this->SavePreferences();

    std::map<std::string, std::string> mapHascodeToSubject;

    std::map<std::string, std::string> mapOutputStudyNumber;

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
            boost::filesystem::path dir(currentItem->get_directory());
            mapHascodeToSubject[std::string(dir.filename().c_str())] = currentItem->get_name();
        }

        int seriesnum = atoi(currentItem->get_seriesDirectory().c_str());
        int reconum = atoi(currentItem->get_recoDirectory().c_str());

        std::string mask = seriesnum < 10 ? "%01d%04d" : "%02d%04d";

        // Conversion: seriesnum (A) + reconum (B) => AABBBB
        char temp[7];
        memset(&temp[0], 0, 7);
        snprintf(&temp[0], 7, mask.c_str(), seriesnum, reconum);
        std::string seriesnumber(temp);

        std::string outputdir = this->_ui->outputDirectory->text().toStdString();
        if (this->_ui->saveCheckBox->isChecked() == false)
        {
            // Create temporary directory
            boost::filesystem::path uniquepath = boost::filesystem::unique_path();
            boost::filesystem::path temp = boost::filesystem::temp_directory_path();

            outputdir = boost::filesystem::absolute(temp).string() + "/" + uniquepath.filename().string();

            boost::filesystem::create_directories(boost::filesystem::path(outputdir.c_str()));
        }

        std::string currentStudyNumber;
        if (mapOutputStudyNumber.find(currentItem->get_subjectDirectory()) == mapOutputStudyNumber.end())
        {
            boost::filesystem::path const dest =
                boost::filesystem::path(outputdir) / currentItem->get_name();
            currentStudyNumber = dicomifier::bruker::EnhanceBrukerDicom::get_default_directory_name(dest);
            mapOutputStudyNumber[currentItem->get_subjectDirectory()] = currentStudyNumber;
        }
        else
        {
            currentStudyNumber = mapOutputStudyNumber[currentItem->get_subjectDirectory()];
        }

        // create Rule
        auto rule = dicomifier::bruker::EnhanceBrukerDicom::New(
            currentItem->get_directory(), this->get_selectedFormat_toString(),
            outputdir, currentStudyNumber, seriesnumber);

        if (rule == NULL)
        {
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

                currentItem->set_StoreErrorMsg("OK");
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
        else if (!this->_ui->StoreCheckBox->isChecked())
        {
            currentItem->set_StoreErrorMsg("");
        }

        if (this->_ui->saveCheckBox->isChecked() == false)
        {
            // Remove temporary directory
            boost::filesystem::remove_all(boost::filesystem::path(outputdir.c_str()));
        }
    }

    // Initialize Result items
    this->_Results.clear();
    for (auto iter = mapHascodeToSubject.begin();
         iter != mapHascodeToSubject.end();
         iter++)
    {
        this->_Results[iter->second] = GenerationResultItem();
    }

    // Create DICOMDIR and ZIP files
    this->createDicomdirsOrZipFiles(progress, mapHascodeToSubject);

    // Disabled Run button
    this->update_nextButton(false);

    // Terminate the progressDialog
    progress.setValue(progress.maximum());
}

std::string
GenerationFrame
::get_selectedFormat_toString() const
{
    std::string format = "";
    if (this->_ui->formatMRIMultiple->isChecked())
    {
        format = odil::registry::MRImageStorage;
    }
    else if (this->_ui->formatMRISingle->isChecked())
    {
        format = odil::registry::EnhancedMRImageStorage;
    }

    return format;
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

    // Directory is filled and available or Store selected
    bool enabled = (this->_ui->saveCheckBox->checkState() == Qt::Checked &&
                   directory != "" &&
                   boost::filesystem::exists(boost::filesystem::path(directory))) ||

                   (this->_ui->StoreCheckBox->checkState() == Qt::Checked);

    this->update_nextButton(enabled);
}

void
GenerationFrame
::modify_previousButton_enabled()
{
    // always true
    this->update_previousButton(true);
}

void
GenerationFrame
::createDicomdirs(const std::string &directory, const std::string &absdirectory,
                  const std::string &dicomdirfile)
{
    std::vector<std::string> const files =
            GenerationFrame::getFilesForDicomdir(directory, absdirectory);

    // Should add path separator at the end for odil
    // (see BasicDirectoryCreator, attribute 'root')
    QString rootdir(directory.c_str());
    if (rootdir.at(rootdir.length()-1) != QDir::separator())
    {
        rootdir.append(QDir::separator());
    }

    odil::BasicDirectoryCreator creator(rootdir.toStdString(), files,
        {
            {"PATIENT", { }},
            {"STUDY", { {odil::registry::StudyDescription, 3} }},
            {"SERIES", { {odil::registry::SeriesDescription, 3} }},
            {"IMAGE", { }},
        });

    creator();
}

std::string
GenerationFrame
::createZipArchives(std::string const & directory,
                    std::string const & filename)
{
    QDir qdirectory(QString(directory.c_str()));

    // Create ZIP Archive (One per Subject)
    QString command = "zip";
    QStringList args;
    args << "-r" << QString(filename.c_str());
    args << qdirectory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot);

    QProcess *myProcess = new QProcess(this);
    myProcess->setWorkingDirectory(QString(directory.c_str()));
    myProcess->start(command, args);

    myProcess->waitForFinished();

    if (myProcess->exitCode() == EXIT_SUCCESS)
    {
        return "";
    }

    return myProcess->errorString().toStdString();
}

void
GenerationFrame
::createDicomdirsOrZipFiles(QProgressDialog &progress,
                            std::map<std::string, std::string> &mapHascodeToSubject)
{
    bool createDICOMDIR = this->_ui->saveCheckBox->isChecked() &&
                          this->_ui->DicomdirCheckBox->isChecked();
    bool createZIP = this->_ui->saveCheckBox->isChecked() &&
                     this->_ui->ZIPCheckBox->isChecked();

    if (!createDICOMDIR && !createZIP)
    {
        // nothing to do
        return;
    }

    int nbdir = mapHascodeToSubject.size();
    int progressValue = 0;
    progress.setValue(progressValue);
    progress.setMaximum(nbdir);

    std::list<std::string> alreadyprocess;

    for(auto it = mapHascodeToSubject.begin(); it != mapHascodeToSubject.end(); ++it)
    {
        // Canceled => force stop
        if (progress.wasCanceled())
        {
            return;
        }

        std::string filename(it->first);
        GenerationResultItem& resultitem = this->_Results[it->second];

        // Update progressValue
        ++progressValue;

        std::string dir = this->_ui->outputDirectory->text().toStdString() +
                          boost::filesystem::path("/").make_preferred().string() +
                          it->second;

        if (std::find(alreadyprocess.begin(), alreadyprocess.end(), dir) == alreadyprocess.end())
        {
            alreadyprocess.push_back(dir);

        // Create DICOMDIR file (One per Subject)
        if (createDICOMDIR)
        {
            // Update ProgressDialog label
            std::stringstream progressLabel;
            progressLabel << "Create DICOMDIR " << progressValue << " / " << nbdir
                          << " (Directory = " << filename << ")";
            progress.setLabelText(QString(progressLabel.str().c_str()));

            std::string dicomdirfile = dir + boost::filesystem::path("/").make_preferred().string() + "DICOMDIR";

            if (boost::filesystem::exists(boost::filesystem::path(dicomdirfile.c_str())))
            {
                resultitem.set_dicomdirCreation(GenerationResultItem::Result::Fail);
                resultitem.set_DicomdirErrorMsg("DICOMDIR already exist: " + dicomdirfile);
            }
            else
            {
                try
                {
                    this->createDicomdirs(dir, dir, dicomdirfile);
                    resultitem.set_dicomdirCreation(GenerationResultItem::Result::OK);
                }
                catch (odil::Exception const & odilexc)
                {
                    resultitem.set_dicomdirCreation(GenerationResultItem::Result::Fail);
                    resultitem.set_DicomdirErrorMsg(odilexc.what());
                }
                catch (DicomifierException const & dcmexc)
                {
                    resultitem.set_dicomdirCreation(GenerationResultItem::Result::Fail);
                    resultitem.set_DicomdirErrorMsg(dcmexc.what());
                }
            }
        }

        // Create ZIP Archive (One per Subject)
        if (createZIP)
        {
            // Update ProgressDialog label
            std::stringstream progressLabel;
            progressLabel << "Create ZIP Archive " << progressValue << " / " << nbdir
                          << " (Directory = " << filename << ")";
            progress.setLabelText(QString(progressLabel.str().c_str()));

            std::string zipfile = dir + boost::filesystem::path("/").make_preferred().string() + filename;

            if (boost::filesystem::exists(boost::filesystem::path(zipfile.c_str())))
            {
                resultitem.set_zipCreation(GenerationResultItem::Result::Fail);
                resultitem.set_ZipErrorMsg("ZIP already exist: " + zipfile);
            }
            else
            {
                std::string errormsg = this->createZipArchives(dir, it->second);

                if (errormsg == "")
                {
                    resultitem.set_zipCreation(GenerationResultItem::Result::OK);
                }
                else
                {
                    resultitem.set_zipCreation(GenerationResultItem::Result::Fail);
                    resultitem.set_ZipErrorMsg(errormsg);
                }
            }
        }
        }

        // Update progressDialog
        progress.setValue(progressValue);
    }
}

void
GenerationFrame
::storeFilesIntoPACS(std::string const & directory)
{
    std::string address = "";
    std::string port = "";
    std::string called = "";
    std::string caller = "";
    int idType = 0;
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
            idType = settings.value(streamidentity.str().c_str(), 0).toInt();

            std::stringstream streamfirst;
            streamfirst << stream.str() << CONF_KEY_FIRST.toStdString();
            first = settings.value(streamfirst.str().c_str(), QString("")).toString().toStdString();

            std::stringstream streamsecond;
            streamsecond << stream.str() << CONF_KEY_SECOND.toStdString();
            second = settings.value(streamsecond.str().c_str(), QString("")).toString().toStdString();

            break;
        }
    }

    boost::filesystem::directory_iterator it_end;
    for(boost::filesystem::directory_iterator it(directory); it != it_end; ++it)
    {
        // if it is a directory
        if( boost::filesystem::is_directory( (*it) ) )
        {
            std::string const object =
                    directory +
                    boost::filesystem::path("/").make_preferred().string() +
                    std::string((*it).path().filename().c_str());
            // Recursive call
            this->storeFilesIntoPACS(object);
        }
        else
        {
            std::ifstream stream(
                        boost::filesystem::absolute(*it).string().c_str(),
                        std::ios::in | std::ios::binary);

            auto const header_and_data_set = odil::Reader::read_file(stream);

            odil::Association association;
            association.set_peer_host(address);
            association.set_peer_port(std::stoul(port));
            association.update_parameters()
                .set_called_ae_title(called)
                .set_calling_ae_title(caller)
                .set_presentation_contexts({
                    {
                        1,
                        header_and_data_set.second.as_string("MediaStorageSOPClassUID", 0),
                        header_and_data_set.first.as_string("TransferSyntaxUID"),
                        true, false
                    }
                });
            if(idType == 0)
            {
                association.update_parameters().set_user_identity_to_none();
            }
            else if(idType == 1)
            {
                association.update_parameters()
                    .set_user_identity_to_username(first);
            }
            else if(idType == 2)
            {
                association.update_parameters()
                    .set_user_identity_to_username_and_password(first, second);
            }
            else if(idType == 3)
            {
                association.update_parameters()
                    .set_user_identity_to_kerberos(first);
            }
            else if(idType == 4)
            {
                association.update_parameters()
                    .set_user_identity_to_saml(first);
            }
            else
            {
                throw DicomifierException("Unknown identity type");
            }

            association.associate();

            odil::StoreSCU scu(association);
            scu.set_affected_sop_class(header_and_data_set.second);
            scu.store(header_and_data_set.second);

            association.release();
        }
    }
}

std::vector<std::string>
GenerationFrame
::getFilesForDicomdir(std::string const & directory,
                    std::string const & absdirectory)
{
    std::vector<std::string> files;

    boost::filesystem::directory_iterator it_end;
    for(boost::filesystem::directory_iterator it(directory); it != it_end; ++it)
    {
        // if it is a directory
        if( boost::filesystem::is_directory( (*it) ) )
        {
            std::string const object =
                    directory +
                    boost::filesystem::path("/").make_preferred().string() +
                    std::string((*it).path().filename().c_str());
            // Recursive call
            auto const ret = GenerationFrame::getFilesForDicomdir(object,
                                                                  absdirectory);

            files.insert(files.end(), ret.begin(), ret.end());
        }
        else
        {
            // filename = relative path from DICOMDIR directory
            std::string filename =
                directory.substr(absdirectory.length() + 1) +
                boost::filesystem::path("/").make_preferred().string() +
                std::string((*it).path().filename().c_str());

            // add file
            files.push_back(filename);
        }
    }

    return files;
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
    // Initialize: Only search directory
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.setDirectory(this->_ui->outputDirectory->text());

    if (dialog.exec())
    {   // Dialog validate
        // Get selected Directory path
        QString directory = dialog.selectedFiles()[0];
        this->_ui->outputDirectory->setText(directory);

        // Save this directory as default path
        QSettings settings;
        settings.beginGroup(CONF_GROUP_OUTPUT);
        settings.setValue(CONF_KEY_DIRECTORY, directory);
        settings.endGroup();

        // Update
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
    this->CreateNewPACSConfiguration();
}

void
GenerationFrame
::SavePreferences()
{
    QSettings settings;
    settings.beginGroup(CONF_GROUP_OUTPUT);
    settings.setValue(CONF_KEY_FORMAT,
                      QString(this->get_selectedFormat_toString().c_str()));
    settings.setValue(CONF_KEY_DICOMDIR,
                      this->_ui->DicomdirCheckBox->checkState());
    settings.setValue(CONF_KEY_ZIP, this->_ui->ZIPCheckBox->checkState());
    settings.setValue(CONF_KEY_SAVE, this->_ui->saveCheckBox->checkState());
    settings.setValue(CONF_KEY_STORE, this->_ui->StoreCheckBox->checkState());
    settings.endGroup();
}

} // namespace gui

} // namespace dicomifier
