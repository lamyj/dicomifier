/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d701c893_f5eb_43a4_bf29_271618b5489e
#define _d701c893_f5eb_43a4_bf29_271618b5489e

#include "BaseFrame.h"
#include "components/ProtocolsTreeView.h"

namespace dicomifier
{

namespace ihm
{

namespace Ui {
class ProtocolsFrame;
}

class ProtocolsFrame : public BaseFrame
{
    Q_OBJECT

public:
    explicit ProtocolsFrame(QWidget *parent = 0);
    virtual ~ProtocolsFrame();

    void InitializeWithData(std::vector<TreeItem*> subjectslist);

    virtual void Reset();

    std::vector<TreeItem*> get_selectedData() const;

public slots:
    void ontreeViewclicked();

    virtual void onUpdate_Preferences();

protected:
    virtual void modify_nextButton_enabled();

    virtual void modify_previousButton_enabled();

    void paintEvent(QPaintEvent *event);

private slots:
    void on_selectAllCheckBox_clicked();

private:
    Ui::ProtocolsFrame * _ui;

    ProtocolsTreeView * _treeView;

};

} // namespace ihm

} // namespace dicomifier

#endif // _d701c893_f5eb_43a4_bf29_271618b5489e
