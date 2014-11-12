/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "TreeItem.h"

namespace dicomifier
{

namespace ihm
{

TreeItem
::TreeItem(TreeItem *parent, TreeItem * copy):
    _parentItem(parent), _checkState(Qt::Unchecked),
    _name(""), _study(""), _series(""), _reconstruction(""),
    _date(""), _directory(""), _seriesDirectory(""), _recoDirectory("")
{
    if (copy != NULL)
    {
        this->_name            = copy->get_name();
        this->_study           = copy->get_study();
        this->_series          = copy->get_series();
        this->_reconstruction  = copy->get_reconstruction();
        this->_date            = copy->get_date();
        this->_directory       = copy->get_directory();
        this->_seriesDirectory = copy->get_seriesDirectory();
        this->_recoDirectory   = copy->get_recoDirectory();
    }
}

TreeItem
::~TreeItem()
{
    qDeleteAll(this->_childItems);
}

void
TreeItem
::appendChild(TreeItem *child)
{
    if (child != NULL)
    {
        this->_childItems.append(child);
    }
}

TreeItem *
TreeItem
::child(int row)
{
    return this->_childItems.value(row);
}

int
TreeItem
::childCount() const
{
    return this->_childItems.count();
}

int
TreeItem
::columnCount() const
{
    return this->_itemData.count();
}

QVariant
TreeItem
::data(int column) const
{
    return this->_itemData.value(column);
}

int
TreeItem
::row() const
{
    if (this->_parentItem != NULL)
    {
        return this->_parentItem->_childItems.indexOf(const_cast<TreeItem*>(this));
    }

    return 0;
}

TreeItem *
TreeItem
::parent()
{
    return this->_parentItem;
}

Qt::CheckState
TreeItem
::get_checkState() const
{
    return this->_checkState;
}

void
TreeItem
::set_checkState(Qt::CheckState value)
{
    this->_checkState = value;
}

void
TreeItem
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

void
TreeItem
::update_from_child(Qt::CheckState childstate)
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
TreeItem
::update_from_parent(Qt::CheckState parentState)
{
    this->_checkState = parentState;
}

void
TreeItem
::fill_data(bruker::BrukerDataset * const brukerdataset)
{
    if (brukerdataset->HasFieldData("SUBJECT_name_string"))
    {
        this->_name = brukerdataset->GetFieldData("SUBJECT_name_string")->get_string(0);
    }

    if (brukerdataset->HasFieldData("SUBJECT_study_name"))
    {
        this->_study = brukerdataset->GetFieldData("SUBJECT_study_name")->get_string(0);
    }

    this->_date = ""; // TODO

    if (brukerdataset->HasFieldData("Method"))
    {
        this->_series = brukerdataset->GetFieldData("Method")->get_string(0);
    }

    if (brukerdataset->HasFieldData("RECO_mode"))
    {
        this->_reconstruction = brukerdataset->GetFieldData("RECO_mode")->get_string(0);
    }
}

} // namespace ihm

} // namespace dicomifier
