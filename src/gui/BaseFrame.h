/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _331c28b0_9e09_4517_9709_4714eac0fae8
#define _331c28b0_9e09_4517_9709_4714eac0fae8

#include <QWidget>

namespace dicomifier
{

namespace gui
{

class BaseFrame : public QWidget
{
    Q_OBJECT
public:
    explicit BaseFrame(QWidget *parent = 0);

    virtual ~BaseFrame();

    virtual void Initialize();

    virtual void Reset() = 0;

public slots:
    virtual void onUpdate_Preferences() = 0;

protected:
    virtual void modify_nextButton_enabled() = 0;

    virtual void modify_previousButton_enabled() = 0;

signals:
    void update_nextButton(bool enabled);

    void update_previousButton(bool enabled);

    void cancelled();

};

} // namespace gui

} // namespace dicomifier

#endif // _331c28b0_9e09_4517_9709_4714eac0fae8
