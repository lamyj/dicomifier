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

namespace ihm
{

ProtocolsTreeModel
::ProtocolsTreeModel(QObject *parent) :
    TreeModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Select" << "Name" << "Date";
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
        QList<QVariant> columnData;
        columnData << "";
        columnData << QString(iter->first.c_str());
        columnData << "";
        TreeItem * item = new TreeItem(this->_rootItem);
        item->set_data(columnData);

        for (auto iterdata : iter->second)
        {
            QList<QVariant> data;
            data << "";
            data << QString(iterdata->get_reconstruction().c_str());
            data << QString(iterdata->get_date().c_str());
            iterdata->set_data(data);
            iterdata->set_parent(item);
            item->appendChild(iterdata);
        }

        this->_rootItem->appendChild(item);
    }
}

} // namespace ihm

} // namespace dicomifier
