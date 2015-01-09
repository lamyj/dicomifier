/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "PACSTreeModel.h"
#include "PACSTreeView.h"

namespace dicomifier
{

namespace gui
{

PACSTreeView
::PACSTreeView(QWidget *parent):
    QTreeView(parent)
{
    this->setAlternatingRowColors(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

PACSTreeView
::~PACSTreeView()
{
    // Nothing to do
}

void
PACSTreeView
::Initialize()
{
    if (this->model() != NULL)
    {
        delete this->model();
    }
    PACSTreeModel * model = new PACSTreeModel();

    QSettings settings;
    int number = settings.value(CONF_GROUP_PACS + "/" + CONF_KEY_NUMBER, 0).toInt();

    this->_items.clear();
    for (unsigned int i = 0 ; i < number ; ++i)
    {
        // Create tree item
        PACSTreeItem * pacsitem = new PACSTreeItem();

        std::stringstream stream;
        stream << CONF_GROUP_PACS.toStdString() << "/"
               << CONF_GROUP_PACS.toStdString() << i << "_";

        std::stringstream streamname;
        streamname << stream.str() << CONF_KEY_NAME.toStdString();
        pacsitem->set_name(settings.value(streamname.str().c_str(), QString("")).toString().toStdString());

        std::stringstream streamaddress;
        streamaddress << stream.str() << CONF_KEY_ADDRESS.toStdString();
        pacsitem->set_address(settings.value(streamaddress.str().c_str(), QString("")).toString().toStdString());

        std::stringstream streamport;
        streamport << stream.str() << CONF_KEY_PORT.toStdString();
        pacsitem->set_port(settings.value(streamport.str().c_str(), QString("")).toString().toStdString());

        std::stringstream streamcalled;
        streamcalled << stream.str() << CONF_KEY_CALLED.toStdString();
        pacsitem->set_called(settings.value(streamcalled.str().c_str(), QString("")).toString().toStdString());

        std::stringstream streamcaller;
        streamcaller << stream.str() << CONF_KEY_CALLER.toStdString();
        pacsitem->set_caller(settings.value(streamcaller.str().c_str(), QString("")).toString().toStdString());

        std::stringstream streamidentity;
        streamidentity << stream.str() << CONF_KEY_IDENTITY.toStdString();
        pacsitem->set_identityType((UserIdentityType)settings.value(streamidentity.str().c_str(), 0).toInt());

        std::stringstream streamfirst;
        streamfirst << stream.str() << CONF_KEY_FIRST.toStdString();
        pacsitem->set_idTypeFirst(settings.value(streamfirst.str().c_str(), QString("")).toString().toStdString());

        std::stringstream streamsecond;
        streamsecond << stream.str() << CONF_KEY_SECOND.toStdString();
        pacsitem->set_idTypeSecond(settings.value(streamsecond.str().c_str(), QString("")).toString().toStdString());

        pacsitem->fill_data();

        // Append Subject in Tree
        this->_items.push_back(pacsitem);
    }

    model->Initialize(this->_items);
    this->setModel(model);

    this->header()->setStretchLastSection(false);
    this->header()->setResizeMode(0, QHeaderView::Stretch);
    this->header()->setResizeMode(1, QHeaderView::Fixed);
    this->header()->setResizeMode(2, QHeaderView::Fixed);
    this->header()->setResizeMode(3, QHeaderView::Fixed);

    this->header()->resizeSection(1, 150);
    this->header()->resizeSection(2, 170);
    this->header()->resizeSection(3, 170);
}

void PACSTreeView::DeleteSelectedItem()
{
    if (this->currentIndex().isValid())
    {
        PACSTreeItem *item =
            static_cast<PACSTreeItem*>(this->currentIndex().internalPointer());

        if (item != NULL)
        {
            PACSTreeItem * deleteitem = NULL;
            std::vector<PACSTreeItem *> temp;
            for (auto currentitem : this->_items)
            {
                if (item->get_name() != currentitem->get_name())
                {
                    temp.push_back(currentitem);
                }
                else
                {
                    deleteitem = currentitem;
                }
            }

            if (deleteitem != NULL)
            {
                delete deleteitem;
            }

            this->_items = temp;

            if (this->model() != NULL)
            {
                delete this->model();
            }
            PACSTreeModel * model = new PACSTreeModel();

            if (model != NULL)
            {
                model->Initialize(this->_items);
                this->setModel(model);
            }
        }
    }

    emit this->clicked(QModelIndex());
}

void
PACSTreeView
::SaveData()
{
    QSettings settings;
    int number = settings.value(CONF_GROUP_PACS + "/" + CONF_KEY_NUMBER, 0).toInt();

    // delete all data
    for (unsigned int i = 0 ; i < number ; ++i)
    {
        std::stringstream stream;
        stream << CONF_GROUP_PACS.toStdString() << "/"
               << CONF_GROUP_PACS.toStdString() << i << "_";

        std::stringstream streamname;
        streamname << stream.str() << CONF_KEY_NAME.toStdString();
        settings.remove(QString(streamname.str().c_str()));

        std::stringstream streamaddress;
        streamaddress << stream.str() << CONF_KEY_ADDRESS.toStdString();
        settings.remove(QString(streamaddress.str().c_str()));

        std::stringstream streamport;
        streamport << stream.str() << CONF_KEY_PORT.toStdString();
        settings.remove(QString(streamport.str().c_str()));

        std::stringstream streamcalled;
        streamcalled << stream.str() << CONF_KEY_CALLED.toStdString();
        settings.remove(QString(streamcalled.str().c_str()));

        std::stringstream streamcaller;
        streamcaller << stream.str() << CONF_KEY_CALLER.toStdString();
        settings.remove(QString(streamcaller.str().c_str()));

        std::stringstream streamidentity;
        streamidentity << stream.str() << CONF_KEY_IDENTITY.toStdString();
        settings.remove(QString(streamidentity.str().c_str()));

        std::stringstream streamfirst;
        streamfirst << stream.str() << CONF_KEY_FIRST.toStdString();
        settings.remove(QString(streamfirst.str().c_str()));

        std::stringstream streamsecond;
        streamsecond << stream.str() << CONF_KEY_SECOND.toStdString();
        settings.remove(QString(streamsecond.str().c_str()));
    }

    // Write data
    settings.beginGroup(CONF_GROUP_PACS);
    int size = this->_items.size();
    settings.setValue(CONF_KEY_NUMBER, size);
    int count = 0;
    for (auto item : this->_items)
    {
        std::stringstream stream;
        stream << CONF_GROUP_PACS.toStdString() << count << "_";

        std::stringstream streamname;
        streamname << stream.str() << CONF_KEY_NAME.toStdString();
        settings.setValue(QString(streamname.str().c_str()), QString(item->get_name().c_str()));

        std::stringstream streamaddress;
        streamaddress << stream.str() << CONF_KEY_ADDRESS.toStdString();
        settings.setValue(QString(streamaddress.str().c_str()), QString(item->get_address().c_str()));

        std::stringstream streamport;
        streamport << stream.str() << CONF_KEY_PORT.toStdString();
        settings.setValue(QString(streamport.str().c_str()), QString(item->get_port().c_str()));

        std::stringstream streamcalled;
        streamcalled << stream.str() << CONF_KEY_CALLED.toStdString();
        settings.setValue(QString(streamcalled.str().c_str()), QString(item->get_called().c_str()));

        std::stringstream streamcaller;
        streamcaller << stream.str() << CONF_KEY_CALLER.toStdString();
        settings.setValue(QString(streamcaller.str().c_str()), QString(item->get_caller().c_str()));

        std::stringstream streamidentity;
        streamidentity << stream.str() << CONF_KEY_IDENTITY.toStdString();
        settings.setValue(QString(streamidentity.str().c_str()), (int)item->get_identityType());

        std::stringstream streamfirst;
        streamfirst << stream.str() << CONF_KEY_FIRST.toStdString();
        settings.setValue(QString(streamfirst.str().c_str()), QString(item->get_idTypeFirst().c_str()));

        std::stringstream streamsecond;
        streamsecond << stream.str() << CONF_KEY_SECOND.toStdString();
        settings.setValue(QString(streamsecond.str().c_str()), QString(item->get_idTypeSecond().c_str()));

        ++count;
    }
    settings.endGroup();

}

void
PACSTreeView
::receiveNewItem(PACSTreeItem *item)
{
    if (item == NULL)
        return;

    bool find = false;
    for (auto currentitem : this->_items)
    {
        if (currentitem->get_name() == item->get_name())
        {
            // replace
            currentitem->extractData(item);

            find = true;
        }
    }

    if (find == false)
    {
        this->_items.push_back(item);
    }

    if (this->model() != NULL)
    {
        delete this->model();
    }
    PACSTreeModel * model = new PACSTreeModel();

    if (model != NULL)
    {
        model->Initialize(this->_items);
        this->setModel(model);
        model->sort(0);
    }

    emit this->clicked(QModelIndex());
}


} // namespace gui

} // namespace dicomifier
