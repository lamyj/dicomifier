/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "PACSTreeItem.h"

namespace dicomifier
{

namespace gui
{

PACSTreeItem
::PACSTreeItem(PACSTreeItem *parent, PACSTreeItem *copy):
    _parentItem(parent),
    _name(""), _address(""), _port(""),
    _caller(""), _called(""),
    _identityType(0),
    _idTypeFirst(""), _idTypeSecond("")
{
    this->extractData(copy);
}

PACSTreeItem
::~PACSTreeItem()
{
    qDeleteAll(this->_childItems);
}

void
PACSTreeItem
::extractData(PACSTreeItem *copy)
{
    this->_childItems.clear();

    if (copy != NULL)
    {
        this->_name = copy->get_name();
        this->_address = copy->get_address();
        this->_port = copy->get_port();
        this->_called = copy->get_called();
        this->_caller = copy->get_caller();
        this->_identityType = copy->get_identityType();
        this->_idTypeFirst = copy->get_idTypeFirst();
        this->_idTypeSecond = copy->get_idTypeSecond();
    }

    fill_data();
}

void
PACSTreeItem
::appendChild(PACSTreeItem *child)
{
    if (child != NULL)
    {
        this->_childItems.append(child);
    }
}

void
PACSTreeItem
::fill_data()
{
    this->_itemData.clear();

    // Add name
    this->_itemData << QString(this->_name.c_str());

    // Add address:port
    std::stringstream stream;
    stream << this->_address << ":" << this->_port;
    this->_itemData << QString(stream.str().c_str());

    // Add called
    this->_itemData << QString(this->_called.c_str());

    // Add caller
    this->_itemData << QString(this->_caller.c_str());
}

PACSTreeItem *
PACSTreeItem
::child(int row)
{
    return this->_childItems.value(row);
}

int
PACSTreeItem
::childCount() const
{
    return this->_childItems.count();
}

int
PACSTreeItem
::columnCount() const
{
    return this->_itemData.count();
}

QVariant
PACSTreeItem
::data(int column) const
{
    return this->_itemData.value(column);
}

int
PACSTreeItem
::row() const
{
    if (this->_parentItem != NULL)
    {
        return this->_parentItem->_childItems.indexOf(const_cast<PACSTreeItem*>(this));
    }

    return 0;
}

PACSTreeItem *
PACSTreeItem
::parent()
{
    return this->_parentItem;
}

} // namespace gui

} // namespace dicomifier
