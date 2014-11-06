/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <QHeaderView>

#include "SubjectsTreeView.h"

namespace dicomifier
{

namespace ihm
{

SubjectsTreeView
::SubjectsTreeView(QWidget *parent) :
    QTreeView(parent), _dataList({}), _displaySubject(true)
{
    this->setAlternatingRowColors(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void
SubjectsTreeView
::Initialize(const std::vector<SubjectsTreeItemData::Pointer> &dataList)
{
    this->_dataList = dataList;

    SubjectsTreeModel * model = new SubjectsTreeModel();
    model->Initialize(this->sortedSubjects(), this->_displaySubject);

    if (this->model() != NULL)
    {
        delete this->model();
    }
    this->setModel(model);

    disconnect(this, SIGNAL(clicked(QModelIndex)),
               this, SLOT(ontreeviewclick(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(ontreeviewclick(QModelIndex)));

    this->header()->setStretchLastSection(false);
    this->header()->setResizeMode(1, QHeaderView::Fixed);
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

bool SubjectsTreeView::is_item_selected()
{
    if (this->model() == NULL)
    {
        return false;
    }

    SubjectsTreeModel* model = dynamic_cast<SubjectsTreeModel*>(this->model());
    return model->is_item_selected();
}

void
SubjectsTreeView
::ontreeviewclick(QModelIndex const & index)
{
    if (index.column() == 0)
    {
        SubjectsTreeItem *item =
                static_cast<SubjectsTreeItem*>(index.internalPointer());

        item->update_checkState();

        this->update(index.parent());

        bool continue_ = true;
        int count = 0;
        while (continue_)
        {
            QModelIndex childindex = index.child(count, index.column());

            if (childindex.isValid())
            {
                this->update(childindex);
            }
            else
            {
                continue_ = false;
            }
            count++;
        }
    }
    this->update(index);

    emit itemsSelectionChanged();
}

std::map<std::string, std::vector<SubjectsTreeItemData::Pointer> >
SubjectsTreeView
::sortedSubjects() const
{
    std::map<std::string, std::vector<SubjectsTreeItemData::Pointer> > returnmap;

    for (auto couple : this->_dataList)
    {
        std::string name = this->_displaySubject ? couple->get_name() :
                                                   couple->get_study();
        if (returnmap.find(name) == returnmap.end())
        {// create new entry
            returnmap[name] = {};
        }

        returnmap[name].push_back(couple);
    }

    return returnmap;
}

} // namespace ihm

} // namespace dicomifier
