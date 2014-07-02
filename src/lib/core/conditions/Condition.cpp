/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Condition.h"

namespace dicomifier
{

namespace conditions
{

Condition
::Condition()
{
    // Nothing to do
}

Condition
::~Condition()
{
    // Nothing to do
}

void 
Condition
::set_input(boost::any const & object, int pos)
{
    if (this->_inputs.size() < pos + 1)
    {
        this->_inputs.resize(pos + 1);
    }
    this->_inputs.insert(this->_inputs.begin() + pos, object);
}

template<typename T>
void 
Condition
::set_input(T const & object, int pos)
{
    this->set_input(boost::any(object), pos);
}

} // namespace conditions

} // namespace dicomifier
