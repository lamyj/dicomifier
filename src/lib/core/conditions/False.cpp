/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/Factory.h"
#include "False.h"

namespace dicomifier
{

namespace conditions
{

False
::~False()
{
    // Nothing to do
}

bool
False
::eval() const
{
    return false;
}

False
::False()
{
    // Nothing to do
}

} // namespace conditions

} // namespace dicomifier
