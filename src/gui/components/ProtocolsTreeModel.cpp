/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ProtocolsTreeModel.h"

namespace dicomifier
{

namespace gui
{

ProtocolsTreeModel
::ProtocolsTreeModel(bool sortedByName, QObject *parent) :
    TreeModel(parent), _sortedByName(sortedByName)
{
    QList<QVariant> rootData;
    rootData << "Select";
    if (this->_sortedByName)
    {
        rootData << "Name" << "Protocol Name";
    }
    else
    {
        rootData << "Protocol Name" << "Name";
    }
    rootData << "Subject name" << "Directory" << "Date";
    this->_rootItem->set_data(rootData);
}

void
ProtocolsTreeModel
::Initialize(std::map<std::string, std::vector<TreeItem *> > dataList)
{
    this->_datalist = dataList;

    for (auto iter = this->_datalist.begin();
         iter != this->_datalist.end();
         iter++)
    {
        QString firstname = "Not defined";
        if (iter->first != "")
        {
            firstname = QString(iter->first.c_str());
        }
        QList<QVariant> columnData;
        columnData << "";
        columnData << firstname;
        columnData << "";
        columnData << "";
        columnData << "";
        columnData << "";
        TreeItem * item = new TreeItem(this->_rootItem);
        item->set_data(columnData);

        for (auto iterdata : iter->second)
        {
            std::stringstream name;
            name << iterdata->get_reconstruction();
            if ( !iterdata->isEnabled() )
            {
                name << " - No Data";
            }

            std::stringstream directory;
            directory << iterdata->get_subjectDirectory() << "/" << iterdata->get_seriesDirectory();

            QString firstdata = QString(name.str().c_str());
            QString seconddata = QString(iterdata->get_protocolName().c_str());
            if (!this->_sortedByName)
            {
                firstdata = QString(iterdata->get_series().c_str());
                seconddata = QString(name.str().c_str());
            }
            QList<QVariant> data;
            data << "";
            data << firstdata;
            data << seconddata;
            data << QString(iterdata->get_name().c_str());
            data << QString(directory.str().c_str());
            data << QString(iterdata->get_acquisitionDate().c_str());
            iterdata->set_data(data);
            iterdata->set_parent(item);
            item->appendChild(iterdata);
        }

        item->update_from_child(Qt::Unchecked);
        this->_rootItem->appendChild(item);
    }
}

} // namespace gui

} // namespace dicomifier
