/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/Factory.h"
#include "True.h"

namespace dicomifier
{

namespace conditions
{

True
::~True()
{
    // Nothing to do
}

bool
True
::eval() const
{
    return true;
}

True
::True()
{
    // Nothing to do
}

static unsigned int const registration = Factory::get_instance().register_<True>();

} // namespace conditions

} // namespace dicomifier
