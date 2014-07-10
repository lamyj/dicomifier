/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/Factory.h"
#include "Not.h"

namespace dicomifier
{
    
namespace conditions
{
    
Not::Not()
{
    // Nothing to do
}

Not::Not(Condition::ConstPointer condition)
{
    this->_condition = condition;
}

Not::~Not()
{
    // Nothing to do
}

bool Not::eval() const
{
    return ! this->_condition->eval();
}
    
}
    
} // namespace dicomifier
