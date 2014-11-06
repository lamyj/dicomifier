/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _094b008d_a5d4_4d54_ba6d_9109a3e5f611
#define _094b008d_a5d4_4d54_ba6d_9109a3e5f611

#include <QTreeView>

#include "SubjectsTreeItemData.h"
#include "SubjectsTreeModel.h"

namespace dicomifier
{

namespace ihm
{

class SubjectsTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit SubjectsTreeView(QWidget *parent = 0);

    void Initialize(std::vector<SubjectsTreeItemData::Pointer> const & dataList);

    void set_displaySubject(bool displaysubject);

    bool is_item_selected();

signals:
    void itemsSelectionChanged();

private slots:
    void ontreeviewclick(const QModelIndex &index);

private :
    std::vector<SubjectsTreeItemData::Pointer> _dataList;

    bool _displaySubject;

    std::map<std::string, std::vector<SubjectsTreeItemData::Pointer>> sortedSubjects() const;

};

} // namespace ihm

} // namespace dicomifier

#endif // _094b008d_a5d4_4d54_ba6d_9109a3e5f611
