/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e3c36f6b_ae80_47c0_9a2f_226e659fd6d8
#define _e3c36f6b_ae80_47c0_9a2f_226e659fd6d8

#include "BaseFrame.h"

#include "components/PACSTreeView.h"

namespace dicomifier
{

namespace gui
{

namespace Ui {
class PreferencesFrame;
}

class PreferencesFrame : public BaseFrame
{
    Q_OBJECT

public:
    explicit PreferencesFrame(QWidget *parent = 0);
    virtual ~PreferencesFrame();

    virtual void Initialize();

    virtual void Reset();

    void SavePreferences();

public slots:
    virtual void onUpdate_Preferences();

    void TreeViewClicked(QModelIndex index);

protected:
    virtual void modify_nextButton_enabled();

    virtual void modify_previousButton_enabled();

    void paintEvent(QPaintEvent *event);

private slots:
    void on_NewButton_clicked();

    void on_EditButton_clicked();

    void on_DeleteButton_clicked();

private:
    Ui::PreferencesFrame * _ui;

    PACSTreeView * _treeView;

};

} // namespace gui

} // namespace dicomifier

#endif // _e3c36f6b_ae80_47c0_9a2f_226e659fd6d8
