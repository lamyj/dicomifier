#include "SubjectsTreeModel.h"
#include "SubjectsTreeView.h"

#include <QHeaderView>

SubjectsTreeView
::SubjectsTreeView(QWidget *parent) :
    QTreeView(parent)
{
    this->setAlternatingRowColors(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void
SubjectsTreeView
::Initialize(std::vector<SubjectsTreeItemData> const & dataList)
{
    this->_dataList = dataList;

    SubjectsTreeModel * model = new SubjectsTreeModel("");
    model->Initialize(this->sortedSubjects());

    if (this->model() != NULL)
    {
        delete this->model();
    }
    this->setModel(model);

    disconnect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(ontreeviewclick(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(ontreeviewclick(QModelIndex)));

    this->header()->setStretchLastSection(false);
    this->header()->setResizeMode(1, QHeaderView::Fixed);
    this->header()->setResizeMode(1, QHeaderView::Stretch);
    this->header()->setResizeMode(2, QHeaderView::Fixed);

    this->header()->resizeSection(0, 80);
    this->header()->resizeSection(2, 200);
}

void
SubjectsTreeView
::ontreeviewclick(QModelIndex const & index)
{
    if (index.column() == 0)
    {
        SubjectsTreeItem *item = static_cast<SubjectsTreeItem*>(index.internalPointer());

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
}

std::map<std::string, std::vector<SubjectsTreeItemData> > SubjectsTreeView::sortedSubjects() const
{
    std::map<std::string, std::vector<SubjectsTreeItemData> > returnmap;

    for (auto couple : this->_dataList)
    {
        if (returnmap.find(couple.get_name()) == returnmap.end())
        {// create new entry
            returnmap[couple.get_name()] = {};
        }

        returnmap[couple.get_name()].push_back(couple);
    }

    return returnmap;
}
