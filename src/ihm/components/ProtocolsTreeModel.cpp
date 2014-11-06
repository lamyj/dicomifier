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
    QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Select" << "Name" << "Date";
    this->_rootItem = new ProtocolsTreeItem(rootData);
}

ProtocolsTreeModel::~ProtocolsTreeModel()
{
    if (this->_rootItem != NULL)
    {
        delete this->_rootItem;
        this->_rootItem = NULL;
    }
}

QVariant ProtocolsTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    ProtocolsTreeItem *item = static_cast<ProtocolsTreeItem*>(index.internalPointer());

    switch (role)
    {
    case Qt::CheckStateRole:
    {
        if (index.column() == 0)
        {
            return static_cast< int >(item->get_checkState());
        }
        break;
    }
    case Qt::DisplayRole:
    {
        return item->data(index.column());
    }
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags ProtocolsTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    // Items are selectable
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    // First column is a CheckBox
    if ( index.column() == 0 )
    {
        flags |= Qt::ItemIsUserCheckable;
    }

    return flags;
}

QVariant ProtocolsTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return this->_rootItem->data(section);
    }

    return QVariant();
}

QModelIndex ProtocolsTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!this->hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    ProtocolsTreeItem * parentItem;

    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<ProtocolsTreeItem*>(parent.internalPointer());
    }

    ProtocolsTreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return this->createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex ProtocolsTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    ProtocolsTreeItem * childItem =
            static_cast<ProtocolsTreeItem*>(index.internalPointer());
    ProtocolsTreeItem * parentItem = childItem->parent();

    if (parentItem == this->_rootItem)
    {
        return QModelIndex();
    }

    return this->createIndex(parentItem->row(), 0, parentItem);
}

int ProtocolsTreeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    ProtocolsTreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<ProtocolsTreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int ProtocolsTreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<ProtocolsTreeItem*>(parent.internalPointer())->columnCount();
    }

    return this->_rootItem->columnCount();
}

} // namespace ihm

} // namespace dicomifier
