/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "TreeModel.h"

namespace dicomifier
{

namespace ihm
{

TreeModel
::TreeModel(QObject *parent):
    QAbstractItemModel(parent)
{
    this->_rootItem = new TreeItem();
}

TreeModel
::~TreeModel()
{
    if (this->_rootItem != NULL)
    {
        delete this->_rootItem;
        this->_rootItem = NULL;
    }
}

bool
TreeModel
::is_item_selected()
{
    for (int i = 0; i < this->_rootItem->childCount(); i++)
    {
        auto child = this->_rootItem->child(i);
        if (child->get_checkState() != Qt::Unchecked)
        {
            return true;
        }

        for (int j = 0; j < child->childCount(); j++)
        {
            if (child->child(j)->get_checkState() != Qt::Unchecked)
            {
                return true;
            }
        }
    }
    return false;
}

std::vector<TreeItem *>
TreeModel
::get_item_selected() const
{
    std::vector<TreeItem*>  returnvect;
    for (int i = 0; i < this->_rootItem->childCount(); i++)
    {
        auto child = this->_rootItem->child(i);
        if (child->get_checkState() == Qt::Unchecked)
        {// no child selected
            continue;
        }

        for (int j = 0; j < child->childCount(); j++)
        {
            if (child->child(j)->get_checkState() != Qt::Unchecked)
            {// child selected
                returnvect.push_back(child->child(j));
            }
        }
    }

    return returnvect;
}

Qt::CheckState TreeModel::compute_selection()
{
    bool oneselected = false;
    bool oneunselected = false;
    for (int i = 0; i < this->_rootItem->childCount(); i++)
    {
        auto child = this->_rootItem->child(i);
        if (child->get_checkState() == Qt::PartiallyChecked)
        {
            return Qt::PartiallyChecked;
        }
        else if (child->get_checkState() == Qt::Checked)
        {
            oneselected = true;
        }
        else
        {
            oneunselected = true;
        }
    }

    if (oneselected && oneunselected)
    {
        return Qt::PartiallyChecked;
    }
    else if (oneselected)
    {
        return Qt::Checked;
    }
    return Qt::Unchecked;
}

void
TreeModel
::setCheckState_all(Qt::CheckState state)
{
    for (int i = 0; i < this->_rootItem->childCount(); i++)
    {
        auto child = this->_rootItem->child(i);
        child->set_checkState(state);

        for (int j = 0; j < child->childCount(); j++)
        {
            child->child(j)->set_checkState(state);
        }
    }
}

QVariant
TreeModel
::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

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
TreeModel
::flags(const QModelIndex &index) const
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

QVariant
TreeModel
::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return this->_rootItem->data(section);
    }

    return QVariant();
}

QModelIndex
TreeModel
::index(int row, int column, const QModelIndex &parent) const
{
    if (!this->hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    TreeItem * parentItem;

    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return this->createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex
TreeModel
::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    TreeItem * childItem =
            static_cast<TreeItem*>(index.internalPointer());
    TreeItem * parentItem = childItem->parent();

    if (parentItem == this->_rootItem)
    {
        return QModelIndex();
    }

    return this->createIndex(parentItem->row(), 0, parentItem);
}

int
TreeModel
::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    TreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int
TreeModel
::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    }

    return this->_rootItem->columnCount();
}

} // namespace ihm

} // namespace dicomifier
