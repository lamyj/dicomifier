/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _272e7b4f_d47c_4264_b306_4bd6c6ad6fed
#define _272e7b4f_d47c_4264_b306_4bd6c6ad6fed

#include <QList>
#include <QVariant>

namespace dicomifier
{

namespace ihm
{

class SubjectsTreeItem
{
public:
    SubjectsTreeItem(const QList<QVariant> & data,
                     SubjectsTreeItem * parent = 0);
    ~SubjectsTreeItem();

    void appendChild(SubjectsTreeItem * child);

    SubjectsTreeItem * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    SubjectsTreeItem * parent();

    Qt::CheckState get_checkState() const;
    void set_checkState(Qt::CheckState value);
    void update_checkState();

    void update_from_child(Qt::CheckState childstate);
    void update_from_parent(Qt::CheckState parentState);

private:
    QList<SubjectsTreeItem*> _childItems;
    QList<QVariant> _itemData;
    SubjectsTreeItem * _parentItem;
    Qt::CheckState _checkState;

};

} // namespace ihm

} // namespace dicomifier

#endif // _272e7b4f_d47c_4264_b306_4bd6c6ad6fed
