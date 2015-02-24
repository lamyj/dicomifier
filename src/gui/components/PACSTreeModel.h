/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _18960c3b_9506_4345_b706_dcf8ce59bbcd
#define _18960c3b_9506_4345_b706_dcf8ce59bbcd

#include <QAbstractItemModel>
#include <QtGui>

#include "PACSTreeItem.h"

namespace dicomifier
{

namespace gui
{

/**
 * @brief The PACSTreeModel class
 */
class PACSTreeModel: public QAbstractItemModel
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of PACSTreeModel
     * @param parent: Object containing the treeModel
     */
    PACSTreeModel(QObject * parent = 0);

    /// Destroy the instance of PACSTreeModel
    virtual ~PACSTreeModel();

    /**
     * @brief Initialize the instance of PACSTreeModel
     * @param items: list of items
     */
    void Initialize(std::vector<PACSTreeItem *> items);

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

private:
    /// Main item
    PACSTreeItem * _rootItem;

};

} // namespace gui

} // namespace dicomifier

#endif // _18960c3b_9506_4345_b706_dcf8ce59bbcd
