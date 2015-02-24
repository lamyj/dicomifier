/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "PACSTreeModel.h"

namespace dicomifier
{

namespace gui
{

PACSTreeModel
::PACSTreeModel(QObject *parent):
    QAbstractItemModel(parent),
    _rootItem(NULL)
{
    this->_rootItem = new PACSTreeItem();

    QList<QVariant> rootData;
    rootData << "Name" << "Address" << "Called" << "Caller";
    this->_rootItem->set_data(rootData);
}

PACSTreeModel
::~PACSTreeModel()
{
    if (this->_rootItem != NULL)
    {
        delete this->_rootItem;
        this->_rootItem = NULL;
    }
}

void
PACSTreeModel
::Initialize(std::vector<PACSTreeItem *> items)
{
    for (auto item : items)
    {
        PACSTreeItem * newitem = new PACSTreeItem(this->_rootItem, item);
        this->_rootItem->appendChild(newitem);
    }
}

QVariant
PACSTreeModel
::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    PACSTreeItem *item = static_cast<PACSTreeItem*>(index.internalPointer());

    switch (role)
    {
    case Qt::CheckStateRole:
    {
        break;
    }
    case Qt::DisplayRole:
    {
        return item->data(index.column());
    }
    case Qt::SizeHintRole:
    {
        return QSize(100,40);
    }
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags
PACSTreeModel
::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    // Items are selectable
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    return flags;
}

QVariant
PACSTreeModel
::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return this->_rootItem->data(section);
    }

    return QVariant();
}

QModelIndex
PACSTreeModel
::index(int row, int column, const QModelIndex &parent) const
{
    if (!this->hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    PACSTreeItem * parentItem;

    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<PACSTreeItem*>(parent.internalPointer());
    }

    PACSTreeItem * childItem = parentItem->child(row);
    if (childItem)
    {
        return this->createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex
PACSTreeModel
::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    PACSTreeItem * childItem =
            static_cast<PACSTreeItem*>(index.internalPointer());
    PACSTreeItem * parentItem = childItem->parent();

    if (parentItem == this->_rootItem)
    {
        return QModelIndex();
    }

    return this->createIndex(parentItem->row(), 0, parentItem);
}

int
PACSTreeModel
::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    PACSTreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<PACSTreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int
PACSTreeModel
::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<PACSTreeItem*>(parent.internalPointer())->columnCount();
    }

    return this->_rootItem->columnCount();
}

} // namespace gui

} // namespace dicomifier
