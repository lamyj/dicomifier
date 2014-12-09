/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _094b008d_a5d4_4d54_ba6d_9109a3e5f611
#define _094b008d_a5d4_4d54_ba6d_9109a3e5f611

#include "SubjectsTreeModel.h"
#include "TreeView.h"

namespace dicomifier
{

namespace gui
{

class SubjectsTreeView : public TreeView
{
    Q_OBJECT

public:
    explicit SubjectsTreeView(QWidget *parent = 0);

    virtual void Initialize(std::vector<TreeItem*> const & dataList);

    void set_displaySubject(bool displaysubject);

    virtual bool is_item_selected();

    void filter_name(const QString & filter);

    void filter_date(const QDateTime & begin, const QDateTime & end, bool refresh = true);

private :
    bool _displaySubject;

    std::string _expression;
    QDateTime _begin;
    QDateTime _end;

    virtual std::map<std::string, std::vector<TreeItem*>> sortedItems() const;

    boost::regex transform_regex() const;

};

} // namespace gui

} // namespace dicomifier

#endif // _094b008d_a5d4_4d54_ba6d_9109a3e5f611
