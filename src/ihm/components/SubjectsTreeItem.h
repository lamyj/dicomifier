#ifndef SUBJECTSTREEITEM_H
#define SUBJECTSTREEITEM_H

#include <QList>
#include <QVariant>

class SubjectsTreeItem
{
public:
    SubjectsTreeItem(const QList<QVariant> & data, SubjectsTreeItem * parent = 0);
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

#endif // SUBJECTSTREEITEM_H
