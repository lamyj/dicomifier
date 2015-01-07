/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c0821587_1354_4a9f_930b_1577dadaa2f9
#define _c0821587_1354_4a9f_930b_1577dadaa2f9

#include "GenerationResultItem.h"
#include "TreeView.h"

namespace dicomifier
{

namespace gui
{

class ResultsTreeView: public TreeView
{
    Q_OBJECT

public:
    ResultsTreeView(QWidget * parent = 0);

    virtual void Initialize(std::vector<TreeItem*> const & dataList);

    virtual bool is_item_selected();

    void set_results(std::map<std::string, GenerationResultItem> results)
            { this->_results = results; }

private:
    virtual std::map<std::string, std::vector<TreeItem*>> sortedItems() const;

    std::map<std::string, GenerationResultItem> _results;

};

} // namespace gui

} // namespace dicomifier

#endif // _c0821587_1354_4a9f_930b_1577dadaa2f9
