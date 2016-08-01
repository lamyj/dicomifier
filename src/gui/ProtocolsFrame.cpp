/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "bruker/Directory.h"
#include "ProtocolsFrame.h"
#include "ui_ProtocolsFrame.h"

namespace dicomifier
{

namespace gui
{

ProtocolsFrame
::ProtocolsFrame(QWidget *parent) :
    BaseFrame(parent),
    _ui(new Ui::ProtocolsFrame)
{
    this->_ui->setupUi(this);

    // Initialize TreeView
    this->_treeView = new ProtocolsTreeView(this->_ui->widget);
    this->_treeView->Initialize({});

    // Link Signals and Slots
    connect(this->_treeView, SIGNAL(itemsSelectionChanged()),
            this, SLOT(ontreeViewclicked()));
}

ProtocolsFrame
::~ProtocolsFrame()
{
    // TreeView is destroy by deleting _ui

    delete this->_ui;
}

void
ProtocolsFrame
::InitializeWithData(std::vector<TreeItem *> subjectslist)
{
    // Create ProgressDialog
    QProgressDialog progress("", "Cancel", 0, subjectslist.size(), this);
    // Initialize ProgressDialog
    progress.setWindowModality(Qt::WindowModal);
    QRect geom = progress.geometry();
    geom.setWidth(900);
    progress.setGeometry(geom);
    progress.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // Display ProgressDialog
    progress.show();

    std::vector<TreeItem*> itemslist;

    int progressValue = 0;
    for (TreeItem* subjects : subjectslist)
    {
        ++progressValue;
        // Update ProgressDialog label
        std::stringstream progressLabel;
        progressLabel << "Process Subject " << progressValue << " / " << subjectslist.size();
        progressLabel << " (Name = " << subjects->get_name() << ")";
        progress.setLabelText(QString(progressLabel.str().c_str()));

        boost::filesystem::directory_iterator it(subjects->get_directory()), it_end;
        for(; it != it_end; ++it)
        {
            // Force to look if Cancel is called
            QApplication::processEvents( QEventLoop::AllEvents );

            // If we find a directory ( = series )
            if( boost::filesystem::is_directory( (*it) ) )
            {
                std::string const dir = subjects->get_directory() +
                                        VALID_FILE_SEPARATOR +
                                        std::string((*it).path().filename().c_str());
                std::string filemethod = dir +
                                         VALID_FILE_SEPARATOR +
                                         "method";

                if (!boost::filesystem::exists(boost::filesystem::path(filemethod)))
                {
                    continue;
                }

                std::string const dirPdata = dir + VALID_FILE_SEPARATOR + "/pdata";

                boost::filesystem::directory_iterator itsub(dirPdata), itsub_end;
                for(; itsub != itsub_end; ++itsub)
                {
                    // If we find a directory ( = reconstruction )
                    if( boost::filesystem::is_directory( (*it) ) )
                    {
                        std::string const dirsub = dirPdata +
                                                   VALID_FILE_SEPARATOR +
                                                   std::string((*itsub).path().filename().c_str());
                        std::string filereco = dirsub +
                                               VALID_FILE_SEPARATOR +
                                               "reco";

                        if (!boost::filesystem::exists(boost::filesystem::path(filereco)))
                        {
                            continue;
                        }

                        std::string filevisu = dirsub +
                                               VALID_FILE_SEPARATOR +
                                               "visu_pars";

                        dicomifier::bruker::Dataset dataset;

                        dataset.load(filemethod);
                        dataset.load(filereco);
                        if (boost::filesystem::exists(boost::filesystem::path(filevisu)))
                        {
                            dataset.load(filevisu);
                        }

                        // Force to look if Cancel is called
                        QApplication::processEvents( QEventLoop::AllEvents );

                        TreeItem* item = new TreeItem(NULL, subjects);
                        item->set_seriesDirectory(std::string((*it).path().filename().c_str()));
                        item->set_recoDirectory(std::string((*itsub).path().filename().c_str()));
                        item->fill_data(dataset);
                        item->set_checkState(Qt::Unchecked);

                        std::string filebinary = dirsub +
                                                 VALID_FILE_SEPARATOR +
                                                 "2dseq";
                        if (!boost::filesystem::exists(boost::filesystem::path(filebinary)) ||
                            !boost::filesystem::exists(boost::filesystem::path(filevisu)))
                        {
                            item->setEnabled(false);
                        }

                        itemslist.push_back(item);
                    }
                    // else ignore files

                    // Canceled => force stop
                    if (progress.wasCanceled())
                    {
                        break;
                    }
                } // for itsub
            }
            // else ignore files

            // Canceled => force stop
            if (progress.wasCanceled())
            {
                break;
            }
        } // for (; it != it_end; ++it)


        // Canceled => force stop
        if (progress.wasCanceled())
        {
            break;
        }
        // Update progressDialog
        progress.setValue(progressValue);
    }

    // Canceled => force stop
    if ( ! progress.wasCanceled())
    {
        this->Initialize();
        this->_treeView->Initialize(itemslist);

        // Terminate the progressDialog
        progress.setValue(subjectslist.size());
    }
    else
    {
        this->cancelled();
    }
}

void
ProtocolsFrame
::Reset()
{
    // Nothing to do
}

std::vector<TreeItem *>
ProtocolsFrame
::get_selected_data() const
{
    std::vector<TreeItem*> returnvect;
    ProtocolsTreeModel* model =
            dynamic_cast<ProtocolsTreeModel*>(this->_treeView->model());

    if (model != NULL)
    {
        returnvect = model->get_item_selected();
    }

    return returnvect;
}

void
ProtocolsFrame
::ontreeViewclicked()
{
    this->_ui->selectAllCheckBox->setCheckState(this->_treeView->compute_selection());
    this->modify_nextButton_enabled();
}

void
ProtocolsFrame
::onUpdate_Preferences()
{
    // Nothing to do
}

void
ProtocolsFrame
::modify_nextButton_enabled()
{
    bool enabled = (this->_ui->selectAllCheckBox->checkState() != Qt::Unchecked);
    this->update_nextButton(enabled);
}

void
ProtocolsFrame
::modify_previousButton_enabled()
{
    // always true
    this->update_previousButton(true);
}

void
ProtocolsFrame
::paintEvent(QPaintEvent *event)
{
    if (this->_treeView != NULL)
    {
        this->_treeView->resize(this->_ui->widget->size());
    }

    QWidget::paintEvent(event);
}

void
ProtocolsFrame
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
ProtocolsFrame
::on_sortedByName_toggled(bool checked)
{
    this->_treeView->set_sortedByName(checked);
}

} // namespace gui

} // namespace dicomifier
