/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d21314ea_9172_4139_a4f1_54cc7b9c29dd
#define _d21314ea_9172_4139_a4f1_54cc7b9c29dd

#include "TreeModel.h"

namespace dicomifier
{

namespace ihm
{

class SubjectsTreeModel : public TreeModel
{
    Q_OBJECT

public:
    SubjectsTreeModel(bool displaySubject, QObject * parent = 0);

    virtual void Initialize(std::map<std::string,
                            std::vector<TreeItem*>> dataList);

    std::vector<TreeItem*> get_item_selected() const;

    void set_displaySubject(bool displaySubject);

protected:

private:
    bool _displaySubject;

};

} // namespace ihm

} // namespace dicomifier

#endif // _d21314ea_9172_4139_a4f1_54cc7b9c29dd
