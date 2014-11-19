/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ProgressionFrame.h"
#include "ui_ProgressionFrame.h"

namespace dicomifier
{

namespace ihm
{

ProgressionFrame
::ProgressionFrame(QWidget *parent) :
    BaseFrame(parent),
    _ui(new Ui::ProgressionFrame)
{
    this->_ui->setupUi(this);
}

ProgressionFrame
::~ProgressionFrame()
{
    delete this->_ui;
}

void
ProgressionFrame
::Initialize()
{
    BaseFrame::Initialize();
}

void
ProgressionFrame
::Reset()
{
    // TODO
}

void
ProgressionFrame
::modify_nextButton_enabled()
{
    // TODO
}

void
ProgressionFrame
::modify_previousButton_enabled()
{
    // TODO
}

} // namespace ihm

} // namespace dicomifier
