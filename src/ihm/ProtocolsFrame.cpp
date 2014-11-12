
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "bruker/BrukerDirectory.h"
#include "ProtocolsFrame.h"
#include "ui_ProtocolsFrame.h"

namespace dicomifier
{

namespace ihm
{

ProtocolsFrame
::ProtocolsFrame(QWidget *parent) :
    BaseFrame(parent),
    _ui(new Ui::ProtocolsFrame)
{
    this->_ui->setupUi(this);

    this->_treeView = new ProtocolsTreeView(this->_ui->widget);
    this->_treeView->Initialize({});
}

ProtocolsFrame
::~ProtocolsFrame()
{
    delete this->_ui;
}

void
ProtocolsFrame
::Initialize()
{
    this->modify_previousButton_enabled();
    this->modify_nextButton_enabled();

    this->show();
}

void
ProtocolsFrame
::Initialize(std::vector<TreeItem *> subjectslist)
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

                        dicomifier::bruker::BrukerDataset * dataset =
                                new dicomifier::bruker::BrukerDataset();

                        dataset->LoadFile(filemethod);
                        dataset->LoadFile(filereco);

                        TreeItem* item = new TreeItem(NULL, subjects);
                        item->set_seriesDirectory(std::string((*it).path().filename().c_str()));
                        item->set_recoDirectory(std::string((*itsub).path().filename().c_str()));
                        item->fill_data(dataset);

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

void
ProtocolsFrame
::modify_nextButton_enabled()
{
    // TODO
    emit this->update_nextButton(false);
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

} // namespace ihm

} // namespace dicomifier
