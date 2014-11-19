/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _016f8c65_a3bc_45d2_86a8_5d0b112192f3
#define _016f8c65_a3bc_45d2_86a8_5d0b112192f3

#include "BaseFrame.h"

namespace dicomifier
{

namespace ihm
{

namespace Ui {
class ProgressionFrame;
}

class ProgressionFrame : public BaseFrame
{
    Q_OBJECT

public:
    explicit ProgressionFrame(QWidget *parent = 0);
    virtual ~ProgressionFrame();

    virtual void Initialize();

    virtual void Reset();

protected:
    virtual void modify_nextButton_enabled();

    virtual void modify_previousButton_enabled();

private:
    Ui::ProgressionFrame * _ui;
};

} // namespace ihm

} // namespace dicomifier

#endif // _016f8c65_a3bc_45d2_86a8_5d0b112192f3
