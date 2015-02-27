/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _094b008d_a5d4_4d54_ba6d_9109a3e5f611
#define _094b008d_a5d4_4d54_ba6d_9109a3e5f611

#include <boost/regex.hpp>

#include "SubjectsTreeModel.h"
#include "TreeView.h"

namespace dicomifier
{

namespace gui
{

/**
 * @brief The SubjectsTreeView class
 */
class SubjectsTreeView : public TreeView
{
    Q_OBJECT

public:
    /**
     * @brief Create an instance of SubjectsTreeView
     * @param parent: Widget containing this SubjectsTreeView
     */
    explicit SubjectsTreeView(QWidget *parent = 0);

    /**
     * @brief Initialize the instance of SubjectsTreeView
     * @param dataList: list of items
     */
    virtual void Initialize(std::vector<TreeItem*> const & dataList);

    void set_displaySubject(bool displaysubject);

    /// Indicate if at least one item is selected
    virtual bool is_item_selected();

    /// Filter the data by name
    void filter_name(const QString & filter);

    /// Filter the data by date
    void filter_date(const QDateTime & begin, const QDateTime & end, bool refresh = true);

private :
    /// Indicate if the data is sorted by Subject or Study
    bool _displaySubject;

    /// Name filter
    std::string _expression;

    /// Date filters
    QDateTime _begin;
    QDateTime _end;

    /**
     * @brief Sort the items list
     * @return Sorted items list
     */
    virtual std::map<std::string, std::vector<TreeItem*>> sortedItems(std::vector<TreeItem*> previouslyselected) const;

    /// Convert _expression (std::string) into boost::regex
    boost::regex transform_regex() const;

};

} // namespace gui

} // namespace dicomifier

#endif // _094b008d_a5d4_4d54_ba6d_9109a3e5f611
