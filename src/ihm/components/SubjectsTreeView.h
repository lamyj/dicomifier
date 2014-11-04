#ifndef SUBJECTSTREEVIEW_H
#define SUBJECTSTREEVIEW_H

#include <QTreeView>

#include "SubjectsTreeItemData.h"

class SubjectsTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit SubjectsTreeView(QWidget *parent = 0);

    void Initialize(std::vector<SubjectsTreeItemData> const & dataList);

signals:

private slots:
    void ontreeviewclick(const QModelIndex &index);

private :
    std::vector<SubjectsTreeItemData> _dataList;

    std::map<std::string, std::vector<SubjectsTreeItemData>> sortedSubjects() const;

};

#endif // SUBJECTSTREEVIEW_H
