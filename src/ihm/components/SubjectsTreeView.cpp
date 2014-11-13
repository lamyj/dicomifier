/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SubjectsTreeView.h"

namespace dicomifier
{

namespace ihm
{

SubjectsTreeView
::SubjectsTreeView(QWidget *parent) :
    TreeView(parent), _displaySubject(true)
{
    // Nothing to do
}

void
SubjectsTreeView
::Initialize(const std::vector<TreeItem *> &dataList)
{
    this->_dataList = dataList;

    if (this->model() != NULL)
    {
        delete this->model();
    }

    SubjectsTreeModel * model = new SubjectsTreeModel(this->_displaySubject);
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

    this->header()->resizeSection(0, 80);
    this->header()->resizeSection(2, 200);
}

void
SubjectsTreeView
::set_displaySubject(bool displaysubject)
{
    this->_displaySubject = displaysubject;
    this->Initialize(this->_dataList);
}

bool
SubjectsTreeView
::is_item_selected()
{
    if (this->model() == NULL)
    {
        return false;
    }

    SubjectsTreeModel* model = dynamic_cast<SubjectsTreeModel*>(this->model());
    return model->is_item_selected();
}

std::map<std::string, std::vector<TreeItem *> >
SubjectsTreeView
::sortedItems() const
{
    std::map<std::string, std::vector<TreeItem*> > returnmap;

    for (auto couple : this->_dataList)
    {
        std::string name = this->_displaySubject ? couple->get_name() :
                                                   couple->get_study();
        if (returnmap.find(name) == returnmap.end())
        {// create new entry
            returnmap[name] = {};
        }

        TreeItem* item = new TreeItem(NULL, couple);
        returnmap[name].push_back(item);
    }

    return returnmap;
}

} // namespace ihm

} // namespace dicomifier
