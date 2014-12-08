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

namespace dicomifier
{

namespace gui
{

namespace Ui {
class PreferencesFrame;
}

QString const CONF_GROUP_INPUT = "Input";
QString const CONF_GROUP_OUTPUT = "Output";
QString const CONF_KEY_DIRECTORY = "directory";
QString const CONF_KEY_FORMAT = "dicomformat";

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

protected:
    virtual void modify_nextButton_enabled();

    virtual void modify_previousButton_enabled();

private:
    Ui::PreferencesFrame * _ui;
};

} // namespace gui

} // namespace dicomifier

#endif // _e3c36f6b_ae80_47c0_9a2f_226e659fd6d8
