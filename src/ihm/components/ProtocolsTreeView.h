/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _c43441d0_8c1c_40ce_a337_a72d5c01a34d
#define _c43441d0_8c1c_40ce_a337_a72d5c01a34d

#include <QTreeView>

namespace dicomifier
{

namespace ihm
{

class ProtocolsTreeView : public QTreeView
{
    Q_OBJECT

public:
    explicit ProtocolsTreeView(QWidget *parent = 0);

    void Initialize();

private slots:
    void ontreeviewclick(const QModelIndex &index);

};

} // namespace ihm

} // namespace dicomifier

#endif // _c43441d0_8c1c_40ce_a337_a72d5c01a34d
