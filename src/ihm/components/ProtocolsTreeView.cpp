/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ProtocolsTreeModel.h"
#include "ProtocolsTreeView.h"

namespace dicomifier
{

namespace ihm
{

ProtocolsTreeView
::ProtocolsTreeView(QWidget *parent):
    QTreeView(parent)
{
    this->setAlternatingRowColors(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ProtocolsTreeView::Initialize()
{
    ProtocolsTreeModel * model = new ProtocolsTreeModel();

    if (this->model() != NULL)
    {
        delete this->model();
    }
    this->setModel(model);

    disconnect(this, SIGNAL(clicked(QModelIndex)),
               this, SLOT(ontreeviewclick(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(ontreeviewclick(QModelIndex)));
}

void ProtocolsTreeView::ontreeviewclick(const QModelIndex &index)
{

}

} // namespace ihm

} // namespace dicomifier
