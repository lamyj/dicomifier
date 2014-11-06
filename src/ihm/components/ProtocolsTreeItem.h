/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6508331c_6267_4762_aa49_e308a53094a0
#define _6508331c_6267_4762_aa49_e308a53094a0

#include <QList>
#include <QVariant>

namespace dicomifier
{

namespace ihm
{

class ProtocolsTreeItem
{
public:
    ProtocolsTreeItem(const QList<QVariant> & data,
                     ProtocolsTreeItem * parent = 0);
    virtual ~ProtocolsTreeItem();

    void appendChild(ProtocolsTreeItem * child);

    ProtocolsTreeItem * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    ProtocolsTreeItem * parent();

    Qt::CheckState get_checkState() const;
    void set_checkState(Qt::CheckState value);
    void update_checkState();

    void update_from_child(Qt::CheckState childstate);
    void update_from_parent(Qt::CheckState parentState);

private:
    QList<ProtocolsTreeItem*> _childItems;
    QList<QVariant> _itemData;
    ProtocolsTreeItem * _parentItem;
    Qt::CheckState _checkState;

};

} // namespace ihm

} // namespace dicomifier

#endif // _6508331c_6267_4762_aa49_e308a53094a0
