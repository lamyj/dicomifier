/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _49042f7b_a8e8_4ead_bd6b_a042b95be327
#define _49042f7b_a8e8_4ead_bd6b_a042b95be327

#include "TreeModel.h"

namespace dicomifier
{

namespace gui
{

class ProtocolsTreeModel : public TreeModel
{
    Q_OBJECT

public:
    ProtocolsTreeModel(QObject * parent = 0);

    virtual void Initialize(std::map<std::string,
                            std::vector<TreeItem*>> dataList);

protected:

private:

};

} // namespace gui

} // namespace dicomifier

#endif // _49042f7b_a8e8_4ead_bd6b_a042b95be327
