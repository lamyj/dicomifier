#include <QtGui>

#include "SubjectsTreeModel.h"

SubjectsTreeModel
::SubjectsTreeModel(const QString &data, QObject *parent) :
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
::Initialize(std::map<std::string, std::vector<SubjectsTreeItemData> > dataList)
{
    this->_datalist = dataList;

    for (auto iter = this->_datalist.begin(); iter != this->_datalist.end(); iter++)
    {
        QList<QVariant> columnData;
        columnData << "";
        columnData << QString(iter->first.c_str());
        columnData << "00/00/0000 00:00:00";
        SubjectsTreeItem * item = new SubjectsTreeItem(columnData, this->_rootItem);

        for (auto iterdata : iter->second)
        {
            QList<QVariant> data;
            data << "";
            data << QString(iterdata.get_study().c_str());
            data << QString(iterdata.get_date().c_str());
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
    /*case Qt::BackgroundRole:
    {
        if (index.row() % 2 == 0)
            return QColor(64,128,255,64);
        else
            return QColor(64,128,255,128);
    }*/
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

    SubjectsTreeItem * childItem = static_cast<SubjectsTreeItem*>(index.internalPointer());
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
