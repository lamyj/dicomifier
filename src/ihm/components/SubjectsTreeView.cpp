/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/algorithm/string.hpp>
#include "boost/regex.hpp"

#include "SubjectsTreeView.h"

namespace dicomifier
{

namespace ihm
{

SubjectsTreeView
::SubjectsTreeView(QWidget *parent) :
    TreeView(parent), _displaySubject(true), _expression("*"),
    _begin(QDate::currentDate()), _end(QDate::currentDate())
{
    // Nothing to do
}

void
SubjectsTreeView
::Initialize(const std::vector<TreeItem *> &dataList)
{
    this->_dataList = dataList;

    if (this->model() != NULL)
    {
        delete this->model();
    }

    SubjectsTreeModel * model = new SubjectsTreeModel(this->_displaySubject);
    model->Initialize(this->sortedItems());
    this->setModel(model);

    disconnect(this, SIGNAL(clicked(QModelIndex)),
               this, SLOT(OnTreeViewClicked(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)),
            this, SLOT(OnTreeViewClicked(QModelIndex)));

    this->header()->setStretchLastSection(false);
    this->header()->setResizeMode(0, QHeaderView::Fixed);
    this->header()->setResizeMode(1, QHeaderView::Stretch);
    this->header()->setResizeMode(2, QHeaderView::Fixed);

    this->header()->resizeSection(0, 80);
    this->header()->resizeSection(2, 200);
}

void
SubjectsTreeView
::set_displaySubject(bool displaysubject)
{
    this->_displaySubject = displaysubject;
    this->Initialize(this->_dataList);
}

bool
SubjectsTreeView
::is_item_selected()
{
    if (this->model() == NULL)
    {
        return false;
    }

    SubjectsTreeModel* model = dynamic_cast<SubjectsTreeModel*>(this->model());
    return model->is_item_selected();
}

void
SubjectsTreeView
::filter_name(const QString &filter)
{
    this->_expression = filter.toStdString();
    if (filter.size() == 0)
    {
        this->_expression = "*";
    }

    this->Initialize(this->_dataList);
}

void
SubjectsTreeView
::filter_date(const QDate &begin, const QDate &end, bool refresh)
{
    this->_begin = begin;
    this->_end = end;

    if (refresh)
    {
        this->Initialize(this->_dataList);
    }
}

std::map<std::string, std::vector<TreeItem *> >
SubjectsTreeView
::sortedItems() const
{
    std::map<std::string, std::vector<TreeItem*> > returnmap;

    for (auto couple : this->_dataList)
    {
        std::string name = this->_displaySubject ? couple->get_name() :
                                                   couple->get_study();

        boost::cmatch what;
        if (regex_search(name.c_str(), what, this->transform_regex()))
        {
            if (couple->get_qdate() >= this->_begin && couple->get_qdate() <= this->_end)
            {
                if (returnmap.find(name) == returnmap.end())
                {// create new entry
                    returnmap[name] = {};
                }

                TreeItem* item = new TreeItem(NULL, couple);
                returnmap[name].push_back(item);
            }
        }
    }

    return returnmap;
}

boost::regex
SubjectsTreeView
::transform_regex() const
{
    std::string regex = this->_expression;
    // Escape "\\" first since we're using it to replace "."
    boost::replace_all(regex, "\\", "\\\\");
    // Escape "." second since we're using it to replace "*"
    boost::replace_all(regex, ".", "\\.");
    boost::replace_all(regex, "*", ".*");
    boost::replace_all(regex, "?", ".");
    // Escape other PCRE metacharacters
    boost::replace_all(regex, "^", "\\^");
    boost::replace_all(regex, "$", "\\$");
    boost::replace_all(regex, "[", "\\[");
    boost::replace_all(regex, "]", "\\]");
    boost::replace_all(regex, "(", "\\(");
    boost::replace_all(regex, ")", "\\)");
    boost::replace_all(regex, "+", "\\+");
    boost::replace_all(regex, "{", "\\{");
    boost::replace_all(regex, "}", "\\}");
    // Add the start and end anchors
    regex = "^" + regex;

    return boost::regex(regex, boost::regex::icase);
}

} // namespace ihm

} // namespace dicomifier
