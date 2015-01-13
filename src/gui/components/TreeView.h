/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _9b77c73a_0b6c_4216_bf41_bc3f8221ba9a
#define _9b77c73a_0b6c_4216_bf41_bc3f8221ba9a

#include <QHeaderView>
#include <QTreeView>

#include "TreeItem.h"

namespace dicomifier
{

namespace gui
{

/**
 * @brief The TreeView abstract class
 */
class TreeView : public QTreeView
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of TreeView
     * @param parent: Widget containing this TreeView
     */
    explicit TreeView(QWidget *parent = 0);

    /// Destroy the instance of TreeView
    virtual ~TreeView();

    /**
     * @brief Initialize the instance of TreeView
     * @param dataList: list of items
     */
    virtual void Initialize(std::vector<TreeItem*> const & dataList) = 0;

    /// Indicate if at least one item is selected
    virtual bool is_item_selected() = 0;

    /// Indicate "Select All" check state
    Qt::CheckState compute_selection();

    /// Modify check state for all items
    void setCheckState_all(Qt::CheckState state);

signals:
    /// Signal emit if selection changed
    void itemsSelectionChanged();

private slots:
    /// Event triggered by clicking on the treeView
    void OnTreeViewClicked(const QModelIndex &index);

protected:
    /**
     * @brief Sort the items list
     * @return Sorted items list
     */
    virtual std::map<std::string, std::vector<TreeItem*>> sortedItems() const = 0;

    /// list of items
    std::vector<TreeItem*> _dataList;

};

} // namespace gui

} // namespace dicomifier

#endif // _9b77c73a_0b6c_4216_bf41_bc3f8221ba9a
