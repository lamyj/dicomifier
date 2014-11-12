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

namespace ihm
{

class TreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit TreeView(QWidget *parent = 0);
    virtual ~TreeView();

    virtual void Initialize(std::vector<TreeItem*> const & dataList) = 0;

signals:
    void itemsSelectionChanged();

private slots:
    void OnTreeViewClicked(const QModelIndex &index);

protected:
    virtual std::map<std::string, std::vector<TreeItem*>> sortedItems() const = 0;

    std::vector<TreeItem*> _dataList;

};

} // namespace ihm

} // namespace dicomifier

#endif // _9b77c73a_0b6c_4216_bf41_bc3f8221ba9a
