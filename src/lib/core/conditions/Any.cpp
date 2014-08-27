/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <algorithm>

#include "Any.h"
#include "core/Factory.h"

namespace dicomifier
{

namespace conditions
{

Any
::~Any()
{
    // Nothing to do
}

bool
Any
::eval() const
{
    return std::any_of(this->_children.begin(), this->_children.end(),
        [] (Condition::ConstPointer c) { return c->eval(); } );
}

Any
::Any()
    :Condition()
{
    // Nothing to do
}

Any
::Any(Condition::ConstPointer left, Condition::ConstPointer right)
    :Condition()
{
    this->_children.push_back(left);
    this->_children.push_back(right);
}

void
Any
::add_child(Condition::ConstPointer child)
{
    this->_children.push_back(child);
}

} // namespace conditions

} // namespace dicomifier
