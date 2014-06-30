/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <algorithm>

#include "All.h"
#include "core/Factory.h"

namespace dicomifier
{
    
namespace conditions
{
    
All::All()
{
    // Nothing to do
}

All::All(Condition::ConstPointer left, Condition::ConstPointer right)
{
    this->_children.push_back(left);
    this->_children.push_back(right);
}

All::~All()
{
    // Nothing to do
}

bool All::eval() const
{
    return std::all_of(this->_children.begin(), this->_children.end(),
        [] (Condition::ConstPointer c) { return c->eval(); } );
}
    
} // namespace conditions
    
} // namespace dicomifier
