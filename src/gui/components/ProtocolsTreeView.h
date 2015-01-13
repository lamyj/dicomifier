/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c43441d0_8c1c_40ce_a337_a72d5c01a34d
#define _c43441d0_8c1c_40ce_a337_a72d5c01a34d

#include "ProtocolsTreeModel.h"
#include "TreeView.h"

namespace dicomifier
{

namespace gui
{

/**
 * @brief The ProtocolsTreeView class
 */
class ProtocolsTreeView : public TreeView
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of ProtocolsTreeView
     * @param parent: Widget containing this ProtocolsTreeView
     */
    explicit ProtocolsTreeView(QWidget *parent = 0);

    /**
     * @brief Initialize the instance of ProtocolsTreeView
     * @param dataList: list of items
     */
    virtual void Initialize(std::vector<TreeItem*> const & dataList);

    /// Indicate if at least one item is selected
    virtual bool is_item_selected();

private:
    /**
     * @brief Sort the items list
     * @return Sorted items list
     */
    virtual std::map<std::string, std::vector<TreeItem*>> sortedItems() const;

};

} // namespace gui

} // namespace dicomifier

#endif // _c43441d0_8c1c_40ce_a337_a72d5c01a34d
