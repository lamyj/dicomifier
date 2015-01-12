/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _508febdb_0508_40bd_8395_726fad7b436e
#define _508febdb_0508_40bd_8395_726fad7b436e

#include "BaseFrame.h"
#include "components/GenerationResultItem.h"
#include "components/ResultsTreeView.h"

namespace dicomifier
{

namespace gui
{

namespace Ui {
class ResultsFrame;
}

class ResultsFrame : public BaseFrame
{
    Q_OBJECT

public:
    explicit ResultsFrame(QWidget *parent = 0);
    ~ResultsFrame();

    virtual void Reset();

    void InitializeWithData(std::vector<TreeItem*> subjectslist,
                            std::map<std::string, GenerationResultItem> results);

public slots:
    void ontreeViewclicked();

    virtual void onUpdate_Preferences();

protected:
    virtual void modify_nextButton_enabled();

    virtual void modify_previousButton_enabled();

    void paintEvent(QPaintEvent *event);

private:
    Ui::ResultsFrame * _ui;

    ResultsTreeView * _treeView;

};

} // namespace gui

} // namespace dicomifier

#endif // _508febdb_0508_40bd_8395_726fad7b436e
