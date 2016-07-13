/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <string>
#include <vector>

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

#include <odil/Association.h>
#include <odil/BasicDirectoryCreator.h>
#include <odil/Reader.h>
#include <odil/registry.h>
#include <odil/StoreSCU.h>

#include <zlib.h>

#include "components/PACSTreeItem.h"
#include "core/DicomifierException.h"
#include "core/Logger.h"
#include "GenerationFrame.h"
#include "ui_GenerationFrame.h"

namespace
{

/// @brief Return the path of file relative to directory.
boost::filesystem::path
make_relative(
    boost::filesystem::path const & directory,
    boost::filesystem::path const & file)
{
    auto relative_file = file.string().substr(directory.string().size());
    if(relative_file[0] == boost::filesystem::path::preferred_separator)
    {
        relative_file = relative_file.substr(1);
    }
    return relative_file;
}

}

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
    QProgressDialog progress(
        "Converting...", "Cancel", 0, selectedItems.size(), this);
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

    progress.setValue(0);
    // Convert selected items
    std::map<std::string, std::vector<Path>> subject_files;
    std::map<std::string, boost::python::object> bruker_directories;
    for(auto const & currentItem: selectedItems)
    {
        // Canceled => force stop
        if (progress.wasCanceled())
        {
            return;
        }

        progress.setLabelText(
            QString("Converting %1/%2 (Directory: %3, Series: %4, Reco: %5)")
                .arg(1+progress.value()).arg(progress.maximum())
                .arg(QString::fromStdString(currentItem->get_subjectDirectory()))
                .arg(QString::fromStdString(currentItem->get_seriesDirectory()))
                .arg(QString::fromStdString(currentItem->get_recoDirectory())));

        boost::filesystem::path outputdir;
        if(this->_ui->saveCheckBox->isChecked())
        {
            outputdir = this->_ui->outputDirectory->text().toStdString();
        }
        else
        {
            // Create temporary directory
            auto const temp = boost::filesystem::temp_directory_path();
            auto const uniquepath = boost::filesystem::unique_path();
            outputdir = temp/uniquepath;
        }

        // Force to look if Cancel is called
        QApplication::processEvents( QEventLoop::AllEvents );

        try
        {
            using namespace boost::python;
            
            object dicomifier = import("dicomifier");

            object bruker = dicomifier.attr("bruker");
            object Directory = bruker.attr("Directory");

            object bruker_to_dicom = dicomifier.attr("bruker_to_dicom");
            object mr_image_storage = bruker_to_dicom.attr("mr_image_storage");
            object convert_reconstruction = 
                bruker_to_dicom.attr("convert_reconstruction");

            auto const source = currentItem->get_directory();
            if(bruker_directories.find(source) == bruker_directories.end())
            {
                object bruker_directory = Directory();
                bruker_directory.attr("load")(source);
                bruker_directories[source] = bruker_directory;
            }
            auto const & bruker_directory = bruker_directories.at(source);
            
            object files_python = convert_reconstruction(
                bruker_directory,
                currentItem->get_seriesDirectory(),
                currentItem->get_recoDirectory(),
                mr_image_storage, "1.2.840.10008.1.2.1",
                outputdir.string(), true, "hierarchical");
            
            if(len(files_python) > 0)
            {
                auto & files = subject_files[currentItem->get_name()];
                std::copy(
                    stl_input_iterator<std::string>(files_python),
                    stl_input_iterator<std::string>(),
                    std::back_inserter(files));
            }

            currentItem->set_DicomErrorMsg("OK");
        }
        catch(boost::python::error_already_set const &)
        {
            PyObject *type, *value, *traceback;
            PyErr_Fetch(&type, &value, &traceback);
            PyErr_NormalizeException(&type, &value, &traceback);
            
            using namespace boost::python;
            
            boost::python::handle<> type_handle(type), value_handle(allow_null(value)),
                traceback_handle(allow_null(traceback));
            
            object traceback_module = import("traceback");
            object format_exception = traceback_module.attr("format_exception");
            object formatted_list = format_exception(
                type_handle, value_handle, traceback_handle);
            object formatted  = str("").join(formatted_list);
            
            std::string const message = extract<std::string>(formatted);
            dicomifier::loggerError() << message;
            currentItem->set_DicomErrorMsg(message);
        }
        catch(std::exception &e)
        {
            dicomifier::loggerError() << e.what();
            currentItem->set_DicomErrorMsg(e.what());
        }

        if (this->_ui->StoreCheckBox->isChecked() &&
            currentItem->get_DicomErrorMsg() == "OK")
        {
            try
            {
                this->storeFilesIntoPACS(outputdir.string());
        
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
            boost::filesystem::remove_all(outputdir);
        }

        progress.setValue(1+progress.value());
    }

    // Create DICOMDIR and ZIP files
    this->createDicomdirsOrZipFiles(progress, subject_files);

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
::createDicomdir(std::vector<Path> const & files) const
{
    // Compute the files relative to the subject directory
    auto const directory =
        files[0].parent_path().parent_path().parent_path();
    std::vector<std::string> relative_files(files.size());
    std::transform(
        files.begin(), files.end(), relative_files.begin(),
        [&directory](Path const & file)
        {
            return make_relative(directory, file).string();
        });

    odil::BasicDirectoryCreator const creator(
        directory.string(), relative_files,
        { { "SERIES", { { odil::registry::SeriesDescription, 3 } } } });
    creator();
}

std::string
GenerationFrame
::createZipArchive(
    std::string const & subject, std::vector<Path> const & files,
    bool has_dicomdir) const
{
    // Compute the files relative to the root directory
    auto const directory =
        files[0].parent_path().parent_path().parent_path().parent_path();
    std::vector<std::string> relative_files(files.size());
    std::transform(
        files.begin(), files.end(), relative_files.begin(),
        [&directory](Path const & file)
        {
            return make_relative(directory, file).string();
        });
    if(has_dicomdir)
    {
        auto const dicomdir =
            files[0].parent_path().parent_path().parent_path()/"DICOMDIR";
        relative_files.push_back(make_relative(directory, dicomdir).string());
    }

    QStringList args;
    args << "-r" << QString::fromStdString(subject)+".zip";
    for(auto const & file: relative_files)
    {
        args << QString::fromStdString(file);
    }

    QProcess zip;
    zip.setWorkingDirectory(QString::fromStdString(directory.string()));
    zip.start("zip", args);

    zip.waitForFinished();

    std::string message;
    if(zip.exitCode() != EXIT_SUCCESS)
    {
        message = QString(zip.readAll()).toStdString();
    }

    return message;
}

void
GenerationFrame
::createDicomdirsOrZipFiles(
    QProgressDialog & progress,
    std::map<std::string, std::vector<Path>> const & subject_files)
{
    // Initialize Result items
    this->_Results.clear();
    for(auto const & entry: subject_files)
    {
        this->_Results[entry.first] =  GenerationResultItem();
    }
    this->_Results["mrsiam1"] = GenerationResultItem();
    this->_Results["mrsiam1"].set_dicomdirCreation(GenerationResultItem::Result::OK);

    bool createDICOMDIR = this->_ui->saveCheckBox->isChecked() &&
                          this->_ui->DicomdirCheckBox->isChecked();
    bool createZIP = this->_ui->saveCheckBox->isChecked() &&
                     this->_ui->ZIPCheckBox->isChecked();

    if(subject_files.empty() && !createDICOMDIR && !createZIP)
    {
        // nothing to do
        return;
    }

    progress.setValue(0);
    progress.setMaximum(subject_files.size());

    for(auto const & entry: subject_files)
    {
        // Canceled => force stop
        if (progress.wasCanceled())
        {
            return;
        }

        auto & result = this->_Results[entry.first];

        // Create DICOMDIR file (One per Subject)
        if(createDICOMDIR)
        {
            progress.setLabelText(
                QString("Create DICOMDIR %1/%2 (Directory: %3)")
                    .arg(1+progress.value())
                    .arg(progress.maximum())
                    .arg(QString::fromStdString(entry.first)));

            try
            {
                this->createDicomdir(entry.second);
                result.set_dicomdirCreation(GenerationResultItem::Result::OK);
            }
            catch(std::exception const & e)
            {
                result.set_dicomdirCreation(GenerationResultItem::Result::Fail);
                result.set_DicomdirErrorMsg(e.what());
            }
        }

        // Create ZIP Archive (One per Subject)
        if(createZIP)
        {
            progress.setLabelText(
                QString("Create ZIP archive %1/%2 (Directory: %3)")
                    .arg(1+progress.value())
                    .arg(progress.maximum())
                    .arg(QString::fromStdString(entry.first)));

            auto const message = this->createZipArchive(
                entry.first, entry.second, createDICOMDIR);

            if(message.empty())
            {
                result.set_zipCreation(GenerationResultItem::Result::OK);
            }
            else
            {
                result.set_zipCreation(GenerationResultItem::Result::Fail);
                result.set_ZipErrorMsg(message);
            }
        }

        // Update progressDialog
        progress.setValue(1+progress.value());
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
