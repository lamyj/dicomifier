
#ifndef SUBJECTSTREEMODEL_H
#define SUBJECTSTREEMODEL_H

#include "SubjectsTreeItem.h"
#include "SubjectsTreeItemData.h"

#include <QAbstractItemModel>

class SubjectsTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    SubjectsTreeModel(const QString & data, QObject * parent = 0);
    ~SubjectsTreeModel();

    void Initialize(std::map<std::string, std::vector<SubjectsTreeItemData>> dataList);

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
    SubjectsTreeItem * _rootItem;

    std::map<std::string, std::vector<SubjectsTreeItemData> > _datalist;

};

#endif // SUBJECTSTREEMODEL_H
