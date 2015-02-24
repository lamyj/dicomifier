/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f165cac8_f18e_4712_a7a3_94a5afb35989
#define _f165cac8_f18e_4712_a7a3_94a5afb35989

#include <QAbstractItemModel>
#include <QtGui>

#include "TreeItem.h"

namespace dicomifier
{

namespace gui
{

/**
 * @brief The TreeModel abstract class
 */
class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of TreeModel
     * @param parent: Object containing the treeModel
     */
    TreeModel(QObject * parent = 0);

    /// Destroy the instance of TreeModel
    virtual ~TreeModel();

    /**
     * @brief Initialize the instance of TreeModel
     * @param dataList: list of items
     */
    virtual void Initialize(std::map<std::string,
                                     std::vector<TreeItem*>> dataList) = 0;

    /// Indicate if at least one item is selected
    bool is_item_selected();

    /**
     * @brief Return all selected items
     * @return selected items
     */
    std::vector<TreeItem*> get_item_selected() const;

    /// Indicate "Select All" check state
    Qt::CheckState compute_selection();

    /// Modify check state for all items
    void setCheckState_all(Qt::CheckState state);

    QVariant data(const QModelIndex & index, int role) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;

protected:
    /// Main item
    TreeItem * _rootItem;

    /// List of items
    std::map<std::string, std::vector<TreeItem*> > _datalist;

private:

};

} // namespace gui

} // namespace dicomifier

#endif // _f165cac8_f18e_4712_a7a3_94a5afb35989
