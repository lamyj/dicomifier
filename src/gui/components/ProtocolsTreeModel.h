/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _49042f7b_a8e8_4ead_bd6b_a042b95be327
#define _49042f7b_a8e8_4ead_bd6b_a042b95be327

#include "TreeModel.h"

namespace dicomifier
{

namespace gui
{

/**
 * @brief The ProtocolsTreeModel class
 */
class ProtocolsTreeModel : public TreeModel
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of ProtocolsTreeModel
     * @param parent: Object containing the treeModel
     */
    ProtocolsTreeModel(bool sortedByName, QObject * parent = 0);

    /**
     * @brief Initialize the instance of ProtocolsTreeModel
     * @param dataList: list of items
     */
    virtual void Initialize(std::map<std::string,
                                     std::vector<TreeItem*>> dataList);

protected:

private:
    bool _sortedByName;

};

} // namespace gui

} // namespace dicomifier

#endif // _49042f7b_a8e8_4ead_bd6b_a042b95be327
