/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _83dcbd0c_a302_46e5_a6a9_a0ae53d2a870
#define _83dcbd0c_a302_46e5_a6a9_a0ae53d2a870

#include <QHeaderView>
#include <QTreeView>

#include "PACSTreeItem.h"

namespace dicomifier
{

namespace gui
{

class PACSTreeView: public QTreeView
{
    Q_OBJECT

public:
    explicit PACSTreeView(QWidget * parent = 0);
    virtual ~PACSTreeView();

    void Initialize();

    void DeleteSelectedItem();

    void SaveData();

public slots:
    void receiveNewItem(PACSTreeItem * item);

protected:

private:
    std::vector<PACSTreeItem *> _items;

};

} // namespace gui

} // namespace dicomifier

#endif // _83dcbd0c_a302_46e5_a6a9_a0ae53d2a870
