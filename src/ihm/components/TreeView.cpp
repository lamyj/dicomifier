/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "TreeView.h"

namespace dicomifier
{

namespace ihm
{

TreeView
::TreeView(QWidget *parent):
    QTreeView(parent), _dataList({})
{
    this->setAlternatingRowColors(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

TreeView
::~TreeView()
{
    // Nothing to do
}

void
TreeView
::OnTreeViewClicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        TreeItem *item =
                static_cast<TreeItem*>(index.internalPointer());

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

} // namespace ihm

} // namespace dicomifier
