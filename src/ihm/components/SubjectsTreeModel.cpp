/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <QtGui>

#include "SubjectsTreeModel.h"

namespace dicomifier
{

namespace ihm
{

SubjectsTreeModel
::SubjectsTreeModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Select" << "Name" << "Date";
    this->_rootItem = new SubjectsTreeItem(rootData);
}

SubjectsTreeModel
::~SubjectsTreeModel()
{
    if (this->_rootItem != NULL)
    {
        delete this->_rootItem;
        this->_rootItem = NULL;
    }
}

void
SubjectsTreeModel
::Initialize(std::map<std::string,
             std::vector<SubjectsTreeItemData::Pointer> > dataList,
             bool displaySubject)
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
        SubjectsTreeItem * item = new SubjectsTreeItem(columnData, this->_rootItem);

        for (auto iterdata : iter->second)
        {
            QList<QVariant> data;
            data << "";
            data << QString(displaySubject ? iterdata->get_study().c_str() :
                                             iterdata->get_name().c_str());
            data << QString(iterdata->get_date().c_str());
            item->appendChild(new SubjectsTreeItem(data, item));
        }

        this->_rootItem->appendChild(item);
    }
}

QVariant
SubjectsTreeModel
::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    SubjectsTreeItem *item = static_cast<SubjectsTreeItem*>(index.internalPointer());

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

Qt::ItemFlags
SubjectsTreeModel
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
SubjectsTreeModel
::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return this->_rootItem->data(section);
    }

    return QVariant();
}

QModelIndex
SubjectsTreeModel
::index(int row, int column, const QModelIndex &parent) const
{
    if (!this->hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    SubjectsTreeItem * parentItem;

    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<SubjectsTreeItem*>(parent.internalPointer());
    }

    SubjectsTreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return this->createIndex(row, column, childItem);
    }

    return QModelIndex();
}

QModelIndex
SubjectsTreeModel
::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    SubjectsTreeItem * childItem =
            static_cast<SubjectsTreeItem*>(index.internalPointer());
    SubjectsTreeItem * parentItem = childItem->parent();

    if (parentItem == this->_rootItem)
    {
        return QModelIndex();
    }

    return this->createIndex(parentItem->row(), 0, parentItem);
}

int
SubjectsTreeModel
::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
    {
        return 0;
    }

    SubjectsTreeItem *parentItem;
    if (!parent.isValid())
    {
        parentItem = this->_rootItem;
    }
    else
    {
        parentItem = static_cast<SubjectsTreeItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int
SubjectsTreeModel
::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return static_cast<SubjectsTreeItem*>(parent.internalPointer())->columnCount();
    }

    return this->_rootItem->columnCount();
}

bool
SubjectsTreeModel
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

std::vector<SubjectsTreeItemData::Pointer>
SubjectsTreeModel
::get_item_selected() const
{
    std::vector<SubjectsTreeItemData::Pointer>  returnvect;
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
                returnvect.push_back(child->child(j)->get_data());
            }
        }
    }

    return returnvect;
}

} // namespace ihm

} // namespace dicomifier
