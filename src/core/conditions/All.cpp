#include "All.h"

#include <algorithm>

namespace router
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
    
} // namespace router
