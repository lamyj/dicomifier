/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _49042f7b_a8e8_4ead_bd6b_a042b95be327
#define _49042f7b_a8e8_4ead_bd6b_a042b95be327

#include <QAbstractItemModel>

#include "TreeItem.h"

namespace dicomifier
{

namespace ihm
{

class ProtocolsTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ProtocolsTreeModel(QObject * parent = 0);
    virtual ~ProtocolsTreeModel();

    void Initialize(std::map<std::string,
                    std::vector<TreeItem*>> dataList);

    QVariant data(const QModelIndex & index, int role) const;
    Qt::ItemFlags flags(const QModelIndex & index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex & index) const;
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;

private:
    TreeItem * _rootItem;

    std::map<std::string, std::vector<TreeItem*> > _datalist;

};

} // namespace ihm

} // namespace dicomifier

#endif // _49042f7b_a8e8_4ead_bd6b_a042b95be327
