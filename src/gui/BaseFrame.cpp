/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "BaseFrame.h"

namespace dicomifier
{

namespace gui
{

BaseFrame
::BaseFrame(QWidget *parent) :
    QWidget(parent)
{
    // Nothing to do
}

BaseFrame
::~BaseFrame()
{
    // Nothing to do
}

void
BaseFrame
::Initialize()
{
    this->modify_previousButton_enabled();
    this->modify_nextButton_enabled();

    this->show();
}

} // namespace gui

} // namespace dicomifier
