#include "SubjectsTreeItem.h"

SubjectsTreeItem
::SubjectsTreeItem(const QList<QVariant> &data, SubjectsTreeItem *parent)
{
    this->_parentItem = parent;
    this->_itemData = data;
    this->_checkState = Qt::Unchecked;
}

SubjectsTreeItem
::~SubjectsTreeItem()
{
    qDeleteAll(this->_childItems);
}

void
SubjectsTreeItem
::appendChild(SubjectsTreeItem *child)
{
    this->_childItems.append(child);
}

SubjectsTreeItem *
SubjectsTreeItem
::child(int row)
{
    return this->_childItems.value(row);
}

int
SubjectsTreeItem
::childCount() const
{
    return this->_childItems.count();
}

int
SubjectsTreeItem
::columnCount() const
{
    return this->_itemData.count();
}

QVariant
SubjectsTreeItem
::data(int column) const
{
    return this->_itemData.value(column);
}

int
SubjectsTreeItem
::row() const
{
    if (this->_parentItem != NULL)
    {
        return this->_parentItem->_childItems.indexOf(const_cast<SubjectsTreeItem*>(this));
    }

    return 0;
}

SubjectsTreeItem *
SubjectsTreeItem
::parent()
{
    return this->_parentItem;
}

Qt::CheckState
SubjectsTreeItem
::get_checkState() const
{
    return this->_checkState;
}

void
SubjectsTreeItem
::set_checkState(Qt::CheckState value)
{
    this->_checkState = value;
}

void
SubjectsTreeItem
::update_checkState()
{
    switch (this->_checkState)
    {
    case Qt::Checked:
    {
        this->set_checkState(Qt::Unchecked);

        for (auto child : this->_childItems)
        {
            child->update_from_parent(Qt::Unchecked);
        }
        break;
    }

    case Qt::PartiallyChecked:
    {
        this->set_checkState(Qt::Checked);

        for (auto child : this->_childItems)
        {
            child->update_from_parent(Qt::Checked);
        }
        break;
    }

    case Qt::Unchecked:
    {
        this->set_checkState(Qt::Checked);

        for (auto child : this->_childItems)
        {
            child->update_from_parent(Qt::Checked);
        }
        break;
    }

    default:
    {
        this->set_checkState(Qt::Unchecked);
        break;
    }
    }

    if (this->_parentItem != NULL && this->_parentItem != this)
    {
        this->_parentItem->update_from_child(this->get_checkState());
    }
}

void SubjectsTreeItem::update_from_child(Qt::CheckState childstate)
{
    bool oneselected = false;
    bool oneunselected = false;

    for (auto child : this->_childItems)
    {
        if (child->get_checkState() == Qt::Unchecked)
        {
            oneunselected = true;
        }
        else
        {
            oneselected = true;
        }
    }

    // Not all selected
    if (oneselected && oneunselected)
    {
        this->_checkState = Qt::PartiallyChecked;
    }
    // All selected
    else if (oneselected)
    {
        this->_checkState = Qt::Checked;
    }
    // All unselected
    else
    {
        this->_checkState = Qt::Unchecked;
    }
}

void
SubjectsTreeItem
::update_from_parent(Qt::CheckState parentState)
{
    this->_checkState = parentState;
}
