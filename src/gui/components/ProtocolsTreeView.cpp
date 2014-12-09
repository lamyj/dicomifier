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
    TreeView(parent)
{
    // Nothing to do
}

void
ProtocolsTreeView
::Initialize(std::vector<TreeItem *> const & dataList)
{
    this->_dataList = dataList;

    if (this->model() != NULL)
    {
        delete this->model();
    }
    ProtocolsTreeModel * model = new ProtocolsTreeModel();
    model->Initialize(this->sortedItems());
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

    this->header()->resizeSection(0, 80);
    this->header()->resizeSection(2, 200);
    this->header()->resizeSection(3, 200);
    this->header()->resizeSection(4, 200);
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

std::map<std::string, std::vector<TreeItem *> >
ProtocolsTreeView
::sortedItems() const
{
    std::map<std::string, std::vector<TreeItem*> > returnmap;

    for (auto couple : this->_dataList)
    {
        std::string name = couple->get_series();
        if (returnmap.find(name) == returnmap.end())
        {// create new entry
            returnmap[name] = {};
        }

        returnmap[name].push_back(couple);
    }

    return returnmap;
}

} // namespace gui

} // namespace dicomifier
