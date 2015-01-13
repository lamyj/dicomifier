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

/**
 * @brief The PACSTreeView class
 */
class PACSTreeView: public QTreeView
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of PACSTreeView
     * @param parent: Widget containing the PACSTreeView
     */
    explicit PACSTreeView(QWidget * parent = 0);

    /// Destroy the instance of PACSTreeView
    virtual ~PACSTreeView();

    /// Initialize the instance of PACSTreeView
    void Initialize();

    /// Remove the selected item
    void DeleteSelectedItem();

    /// Save the data with QSettings
    void SaveData();

public slots:
    /**
     * @brief insert a new PACS
     * @param item: new PACS to insert
     */
    void receiveNewItem(PACSTreeItem * item);

protected:

private:
    /// List of items
    std::vector<PACSTreeItem *> _items;

};

} // namespace gui

} // namespace dicomifier

#endif // _83dcbd0c_a302_46e5_a6a9_a0ae53d2a870
