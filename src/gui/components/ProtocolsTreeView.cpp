/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ProtocolsTreeView.h"

namespace dicomifier
{

namespace gui
{

ProtocolsTreeView
::ProtocolsTreeView(QWidget *parent):
    TreeView(parent), _sortedByName(true)
{
    // Nothing to do
}

void
ProtocolsTreeView
::Initialize(std::vector<TreeItem *> const & dataList)
{
    this->_dataList = dataList;

    std::vector<TreeItem*> previouslyselected;
    if (this->model() != NULL)
    {
        ProtocolsTreeModel * previousmodel = dynamic_cast<ProtocolsTreeModel *>(this->model());
        if (previousmodel != NULL)
        {
            previouslyselected = previousmodel->get_item_selected();
        }
        delete this->model();
    }
    ProtocolsTreeModel * model = new ProtocolsTreeModel(this->_sortedByName);
    model->Initialize(this->sortedItems(previouslyselected));
    this->setModel(model);

    disconnect(this, SIGNAL(clicked(QModelIndex)),
               this, SLOT(OnTreeViewClicked(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(OnTreeViewClicked(QModelIndex)));

    this->header()->setStretchLastSection(false);
    this->header()->setResizeMode(0, QHeaderView::Fixed);
    this->header()->setResizeMode(1, QHeaderView::Stretch);
    this->header()->setResizeMode(2, QHeaderView::Fixed);
    this->header()->setResizeMode(3, QHeaderView::Fixed);
    this->header()->setResizeMode(4, QHeaderView::Fixed);
    this->header()->setResizeMode(5, QHeaderView::Fixed);

    this->header()->resizeSection(0, 80);
    this->header()->resizeSection(2, 180);
    this->header()->resizeSection(3, 180);
    this->header()->resizeSection(4, 150);
    this->header()->resizeSection(5, 200);
}

bool
ProtocolsTreeView
::is_item_selected()
{
    if (this->model() == NULL)
    {
        return false;
    }

    ProtocolsTreeModel* model = dynamic_cast<ProtocolsTreeModel*>(this->model());
    return model->is_item_selected();
}

void ProtocolsTreeView::set_sortedByName(bool isbyname)
{
    this->_sortedByName = isbyname;
    this->Initialize(this->_dataList);
}

std::map<std::string, std::vector<TreeItem *> >
ProtocolsTreeView
::sortedItems(std::vector<TreeItem *> previouslyselected) const
{
    std::map<std::string, std::vector<TreeItem*> > returnmap;

    for (auto couple : this->_dataList)
    {
        std::string name = this->_sortedByName ? couple->get_series() :
                                                 couple->get_protocolName();

        if (returnmap.find(name) == returnmap.end())
        {// create new entry
            returnmap[name] = {};
        }

        // Create copy
        TreeItem* item = new TreeItem(NULL, couple);

        if (this->wasSelected(item, previouslyselected))
        {
            item->set_checkState(Qt::Checked);
        }

        returnmap[name].push_back(item);
    }

    return returnmap;
}

} // namespace gui

} // namespace dicomifier
