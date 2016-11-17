/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "GenerationFrame.h"

#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

#include <odil/Association.h>
#include <odil/BasicDirectoryCreator.h>
#include <odil/Reader.h>
#include <odil/registry.h>
#include <odil/StoreSCU.h>

#include <QtCore>
#include <QtGui>

#include "BaseFrame.h"
#include "components/GenerationResultItem.h"
#include "components/TreeItem.h"
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
    // boost::filesystem::path::preferred_separator does not exist in
    // wheezy or precise
    static char const separator =
        boost::filesystem::path("/").make_preferred().string()[0];
    auto relative_file = file.string().substr(directory.string().size());
    if(relative_file[0] == separator)
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
::GenerationFrame(QWidget *parent)
: BaseFrame(parent), _ui(new Ui::GenerationFrame)
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

    // Set Output Format File
    auto const abstract_syntax = settings.value(
        CONF_GROUP_OUTPUT+"/"+CONF_KEY_FORMAT, "").toString().toStdString();
    if(abstract_syntax == odil::registry::MRImageStorage)
    {
        this->_ui->multiple_files_radio_button->setChecked(true);
    }
    else if(abstract_syntax == odil::registry::EnhancedMRImageStorage)
    {
        this->_ui->single_file_radio_button->setChecked(true);
    }
    else
    {
        this->_ui->multiple_files_radio_button->setChecked(true);
    }

    // Set DICOMDIR Creation
    this->_ui->dicomdir_check_box->setCheckState(
        Qt::CheckState(settings.value(
            CONF_GROUP_OUTPUT+"/"+CONF_KEY_DICOMDIR,
            Qt::CheckState::Unchecked).toInt()));

    // Set ZIP Creation
    this->_ui->zip_check_box->setCheckState(
        Qt::CheckState(settings.value(
            CONF_GROUP_OUTPUT+"/"+CONF_KEY_ZIP,
            Qt::CheckState::Unchecked).toInt()));

    // Set Save Option
    this->_ui->save_check_box->setCheckState(
        Qt::CheckState(settings.value(
            CONF_GROUP_OUTPUT+"/"+CONF_KEY_SAVE,
            Qt::CheckState::Unchecked).toInt()));

    // Set Store Option
    this->_ui->store_check_box->setCheckState(
        Qt::CheckState(settings.value(
            CONF_GROUP_OUTPUT+"/"+CONF_KEY_STORE,
            Qt::CheckState::Unchecked).toInt()));

    // Set PACS name
    this->_ui->pacs_combo_box->clear();
    int number = settings.value(CONF_GROUP_PACS+"/"+CONF_KEY_NUMBER, 0).toInt();
    QStringList itemslist;
    for(int i = 0 ; i < number ; ++i)
    {
        auto const name =
            QString("%1/%1%2_%3").arg(CONF_GROUP_PACS).arg(i).arg(CONF_KEY_NAME);
        itemslist << settings.value(name, "").toString();
    }
    this->_ui->pacs_combo_box->addItems(itemslist);

    this->BaseFrame::Initialize();
}

void
GenerationFrame
::Reset()
{
    this->Initialize();
}

void
GenerationFrame
::generate(std::vector<TreeItem *> const & selected_items)
{
    // Create ProgressDialog
    QProgressDialog progress(
        "Converting...", "Cancel", 0, selected_items.size(), this);
    progress.setWindowModality(Qt::WindowModal);
    auto geom = progress.geometry();
    geom.setWidth(900);
    progress.setGeometry(geom);
    progress.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    progress.show();

    // Save preferences
    this->_save_preferences();

    // Convert selected items
    progress.setValue(0);
    std::map<std::string, std::vector<Path>> subject_files;
    std::map<std::string, boost::python::object> bruker_directories;
    for(auto const & currentItem: selected_items)
    {
        // Canceled => force stop
        if(progress.wasCanceled())
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
        if(this->_ui->save_check_box->isChecked())
        {
            outputdir = this->_ui->output_directory_text->text().toStdString();
        }
        else
        {
            // Create temporary directory
            auto const temp = boost::filesystem::temp_directory_path();
            auto const uniquepath = boost::filesystem::unique_path();
            outputdir = temp/uniquepath;
        }

        // Force to look if Cancel is called
        QApplication::processEvents(QEventLoop::AllEvents);

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
                outputdir.string(), true);
            
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
        catch(std::exception const & e)
        {
            dicomifier::loggerError() << e.what();
            currentItem->set_DicomErrorMsg(e.what());
        }

        if(this->_ui->store_check_box->isChecked() &&
            currentItem->get_DicomErrorMsg() == "OK")
        {
            try
            {
                this->_store_files_in_pacs(outputdir.string());
                currentItem->set_StoreErrorMsg("OK");
            }
            catch(dicomifier::DicomifierException const & e)
            {
                dicomifier::loggerError() << e.what();
                currentItem->set_StoreErrorMsg(e.what());
            }
            catch (std::exception &e)
            {
                dicomifier::loggerError() << e.what();
                currentItem->set_StoreErrorMsg(e.what());
            }
        }
        else if(!this->_ui->store_check_box->isChecked())
        {
            currentItem->set_StoreErrorMsg("");
        }
        
        if(!this->_ui->save_check_box->isChecked())
        {
            // Remove temporary directory
            boost::filesystem::remove_all(outputdir);
        }

        progress.setValue(1+progress.value());
    }

    this->_create_extra_files(progress, subject_files);

    // Disabled Run button
    this->update_nextButton(false);

    // Terminate the progressDialog
    progress.setValue(progress.maximum());
}

std::map<std::string, GenerationResultItem>
GenerationFrame
::get_results() const
{
    return this->_results;
}

void
GenerationFrame
::onUpdate_Preferences()
{
    QSettings settings;

    // Set PACS name
    this->_ui->pacs_combo_box->clear();
    int number = settings.value(CONF_GROUP_PACS+"/"+CONF_KEY_NUMBER, 0).toInt();
    QStringList itemslist;
    for(int i = 0 ; i < number ; ++i)
    {
        auto const name =
            QString("%1/%1%2_%3").arg(CONF_GROUP_PACS).arg(i).arg(CONF_KEY_NAME);
        itemslist << settings.value(name, "").toString();
    }
    this->_ui->pacs_combo_box->addItems(itemslist);
}

void
GenerationFrame
::modify_nextButton_enabled()
{
    // "Next button" is "Run Button" for this Frame

    std::string const directory =
            this->_ui->output_directory_text->text().toUtf8().constData();

    // Directory is filled and available or Store selected
    bool enabled = (
            this->_ui->save_check_box->checkState() == Qt::Checked &&
            directory != "" &&
            boost::filesystem::exists(boost::filesystem::path(directory))
        ) || (this->_ui->store_check_box->checkState() == Qt::Checked);

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
::_create_dicomdir(std::vector<Path> const & files) const
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
::_create_zip_archive(
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
::_create_extra_files(
    QProgressDialog & progress,
    std::map<std::string, std::vector<Path>> const & subject_files)
{
    // Initialize Result items
    this->_results.clear();
    for(auto const & entry: subject_files)
    {
        this->_results[entry.first] =  GenerationResultItem();
    }

    if(!this->_ui->save_check_box->isChecked() || subject_files.empty())
    {
        // No data to process
        return;
    }

    progress.setValue(0);
    progress.setMaximum(subject_files.size());

    for(auto const & entry: subject_files)
    {
        // Canceled => force stop
        if(progress.wasCanceled())
        {
            return;
        }

        auto & result = this->_results[entry.first];

        if(this->_ui->dicomdir_check_box->isChecked())
        {
            progress.setLabelText(
                QString("Create DICOMDIR %1/%2 (Directory: %3)")
                    .arg(1+progress.value())
                    .arg(progress.maximum())
                    .arg(QString::fromStdString(entry.first)));

            try
            {
                this->_create_dicomdir(entry.second);
                result.set_dicomdirCreation(GenerationResultItem::Result::OK);
            }
            catch(std::exception const & e)
            {
                result.set_dicomdirCreation(GenerationResultItem::Result::Fail);
                result.set_DicomdirErrorMsg(e.what());
            }
        }

        if(this->_ui->zip_check_box->isChecked())
        {
            progress.setLabelText(
                QString("Create ZIP archive %1/%2 (Directory: %3)")
                    .arg(1+progress.value())
                    .arg(progress.maximum())
                    .arg(QString::fromStdString(entry.first)));

            auto const message = this->_create_zip_archive(
                entry.first, entry.second,
                this->_ui->dicomdir_check_box->isChecked());

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

        progress.setValue(1+progress.value());
    }
}

void
GenerationFrame
::_store_files_in_pacs(std::string const & directory)
{
    // Find all files in directory
    std::vector<Path> files;
    for(boost::filesystem::recursive_directory_iterator it(directory);
        it != boost::filesystem::recursive_directory_iterator(); ++it)
    {
        if(boost::filesystem::is_directory(*it))
        {
            continue;
        }
        files.push_back(*it);
    }

    // Find all transfer syntaxes and abstract syntaxes
    std::map<std::string, std::set<std::string>> transfer_syntaxes;
    for(auto const & file: files)
    {
        // Read only header
        boost::filesystem::ifstream stream(file, std::ios::in|std::ios::binary);
        auto const header_and_data_set = odil::Reader::read_file(
            stream, false, [](odil::Tag const &) { return true; });
        auto const & header = header_and_data_set.first;

        auto const & abstract_syntax = header.as_string(
            odil::registry::MediaStorageSOPClassUID, 0);
        auto const & transfer_syntax = header.as_string(
            odil::registry::TransferSyntaxUID, 0);

        transfer_syntaxes[abstract_syntax].insert(transfer_syntax);
    }

    // Search PACS information
    QSettings settings;
    auto const count = settings.value(CONF_GROUP_PACS+"/"+CONF_KEY_NUMBER).toInt();
    QString pacs;
    for(int i = 0 ; i < count ; ++i)
    {
        auto const name =
            QString("%1/%1%2_%3").arg(CONF_GROUP_PACS).arg(i).arg(CONF_KEY_NAME);

        if(settings.value(name) == this->_ui->pacs_combo_box->currentText())
        {
            pacs = QString("%1/%1%2").arg(CONF_GROUP_PACS).arg(i);
            break;
        }
    }

    // Configure association
    odil::Association association;
    association.set_peer_host(
        settings.value(pacs+"_"+CONF_KEY_ADDRESS).toString().toStdString());
    association.set_peer_port(settings.value(pacs+"_"+CONF_KEY_PORT).toInt());

    auto & parameters = association.update_parameters();

    parameters
        .set_called_ae_title(
            settings.value(pacs+"_"+CONF_KEY_CALLED).toString().toStdString())
        .set_calling_ae_title(
            settings.value(pacs+"_"+CONF_KEY_CALLER).toString().toStdString());

    uint8_t pc_index = 1;
    std::vector<odil::AssociationParameters::PresentationContext> contexts;
    for(auto const & entry: transfer_syntaxes)
    {
        std::vector<std::string> syntaxes(
            entry.second.begin(), entry.second.end());
        contexts.push_back(odil::AssociationParameters::PresentationContext{
            pc_index, entry.first, syntaxes, true, false});
        pc_index += 2;
    }
    parameters.set_presentation_contexts(contexts);

    int const identification = settings.value(pacs+"_"+CONF_KEY_IDENTITY).toInt();
    std::string const first_field =
        settings.value(pacs+"_"+CONF_KEY_FIRST).toString().toStdString();
    std::string const second_field =
        settings.value(pacs+"_"+CONF_KEY_SECOND).toString().toStdString();

    if(identification == 0)
    {
        parameters.set_user_identity_to_none();
    }
    else if(identification == 1)
    {
        parameters.set_user_identity_to_username(first_field);
    }
    else if(identification == 2)
    {
        parameters.set_user_identity_to_username_and_password(
            first_field, second_field);
    }
    else if(identification == 3)
    {
        parameters.set_user_identity_to_kerberos(first_field);
    }
    else if(identification == 4)
    {
        parameters.set_user_identity_to_saml(first_field);
    }
    else
    {
        throw DicomifierException("Unknown identity type");
    }

    association.associate();

    odil::StoreSCU scu(association);
    for(auto const & file: files)
    {
        boost::filesystem::ifstream stream(file, std::ios::in|std::ios::binary);
        odil::DataSet data_set;
        std::tie(std::ignore, data_set) = odil::Reader::read_file(stream);

        scu.set_affected_sop_class(data_set);
        scu.store(data_set);
    }

    association.release();
}

void
GenerationFrame
::_save_preferences()
{
    std::string abstract_syntax = "";
    if (this->_ui->multiple_files_radio_button->isChecked())
    {
        abstract_syntax = odil::registry::MRImageStorage;
    }
    else if (this->_ui->single_file_radio_button->isChecked())
    {
        abstract_syntax = odil::registry::EnhancedMRImageStorage;
    }

    QSettings settings;
    settings.beginGroup(CONF_GROUP_OUTPUT);
    settings.setValue(
        CONF_KEY_FORMAT, QString::fromStdString(abstract_syntax));
    settings.setValue(
        CONF_KEY_DICOMDIR, this->_ui->dicomdir_check_box->checkState());
    settings.setValue(CONF_KEY_ZIP, this->_ui->zip_check_box->checkState());
    settings.setValue(CONF_KEY_SAVE, this->_ui->save_check_box->checkState());
    settings.setValue(CONF_KEY_STORE, this->_ui->store_check_box->checkState());
    settings.endGroup();
}

void
GenerationFrame
::on_save_check_box_clicked()
{
    this->modify_nextButton_enabled();
}

void
GenerationFrame
::on_output_directory_button_clicked()
{
    // Create dialog
    QFileDialog dialog;
    // Initialize: Only search directory
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    dialog.setDirectory(this->_ui->output_directory_text->text());

    if(dialog.exec())
    {
        QString directory = dialog.selectedFiles()[0];
        this->_ui->output_directory_text->setText(directory);

        // Save this directory as default path
        QSettings settings;
        settings.beginGroup(CONF_GROUP_OUTPUT);
        settings.setValue(CONF_KEY_DIRECTORY, directory);
        settings.endGroup();

        // Update
        this->on_output_directory_text_editingFinished();
    }
}

void
GenerationFrame
::on_output_directory_text_textEdited(QString const &)
{
    this->modify_nextButton_enabled();
}

void
GenerationFrame
::on_output_directory_text_editingFinished()
{
    this->modify_nextButton_enabled();
}

void
GenerationFrame
::on_pacs_button_clicked()
{
    this->CreateNewPACSConfiguration();
}

} // namespace gui

} // namespace dicomifier
