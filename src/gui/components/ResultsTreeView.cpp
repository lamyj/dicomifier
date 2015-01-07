/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ResultsTreeModel.h"
#include "ResultsTreeView.h"

namespace dicomifier
{

namespace gui
{

ResultsTreeView
::ResultsTreeView(QWidget * parent):
    TreeView(parent)
{
    // Nothing to do
}

void
ResultsTreeView
::Initialize(const std::vector<TreeItem *> & dataList)
{
    this->_dataList = dataList;

    if (this->model() != NULL)
    {
        delete this->model();
    }
    ResultsTreeModel * model = new ResultsTreeModel();
    model->Initialize(this->_dataList, this->_results);
    this->setModel(model);

    disconnect(this, SIGNAL(clicked(QModelIndex)),
               this, SLOT(OnTreeViewClicked(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(OnTreeViewClicked(QModelIndex)));

    this->header()->setStretchLastSection(false);
    this->header()->setResizeMode(0, QHeaderView::Stretch);
    this->header()->setResizeMode(1, QHeaderView::Fixed);
    this->header()->setResizeMode(2, QHeaderView::Fixed);
    this->header()->setResizeMode(3, QHeaderView::Fixed);

    this->header()->resizeSection(1, 150);
    this->header()->resizeSection(2, 150);
    this->header()->resizeSection(3, 150);
}

bool
ResultsTreeView
::is_item_selected()
{
    return false;
}

std::map<std::string, std::vector<TreeItem *> >
ResultsTreeView
::sortedItems() const
{
    std::map<std::string, std::vector<TreeItem*> > returnmap;

    for (auto couple : this->_dataList)
    {
        std::string name = couple->get_name();
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
