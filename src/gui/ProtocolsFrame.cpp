/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "bruker/BrukerDirectory.h"
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

    this->_treeView = new ProtocolsTreeView(this->_ui->widget);
    this->_treeView->Initialize({});

    connect(this->_treeView, SIGNAL(itemsSelectionChanged()),
            this, SLOT(ontreeViewclicked()));
}

ProtocolsFrame
::~ProtocolsFrame()
{
    delete this->_ui;
}

void
ProtocolsFrame
::InitializeWithData(std::vector<TreeItem *> subjectslist)
{
    std::vector<TreeItem*> itemslist;

    for (TreeItem* subjects : subjectslist)
    {
        boost::filesystem::directory_iterator it(subjects->get_directory()), it_end;
        for(; it != it_end; ++it)
        {
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

                        dicomifier::bruker::BrukerDataset * dataset =
                                new dicomifier::bruker::BrukerDataset();

                        dataset->LoadFile(filemethod);
                        dataset->LoadFile(filereco);
                        if (boost::filesystem::exists(boost::filesystem::path(filevisu)))
                        {
                            dataset->LoadFile(filevisu);
                        }

                        TreeItem* item = new TreeItem(NULL, subjects);
                        item->set_seriesDirectory(std::string((*it).path().filename().c_str()));
                        item->set_recoDirectory(std::string((*itsub).path().filename().c_str()));
                        item->fill_data(dataset);

                        std::string filebinary = dirsub +
                                                 VALID_FILE_SEPARATOR +
                                                 "2dseq";
                        if (!boost::filesystem::exists(boost::filesystem::path(filebinary)) ||
                            !boost::filesystem::exists(boost::filesystem::path(filevisu)))
                        {
                            item->setEnabled(false);
                        }

                        itemslist.push_back(item);

                        delete dataset;
                    }
                    // else ignore files

                } // for itsub
            }
            // else ignore files
        }
    }

    this->Initialize();
    this->_treeView->Initialize(itemslist);
}

void
ProtocolsFrame
::Reset()
{

}

std::vector<TreeItem *>
ProtocolsFrame
::get_selectedData() const
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
    emit this->update_nextButton(enabled);
}

void
ProtocolsFrame
::modify_previousButton_enabled()
{
    // always true
    emit this->update_previousButton(true);
}

void ProtocolsFrame::paintEvent(QPaintEvent *event)
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

} // namespace gui

} // namespace dicomifier
