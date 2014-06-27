#include <algorithm>

#include "Any.h"
#include "core/Factory.h"

namespace router
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
{
    // Nothing to do
}

Any
::Any(Condition::ConstPointer left, Condition::ConstPointer right)
{
    this->_children.push_back(left);
    this->_children.push_back(right);
}

static unsigned int const registration = Factory::get_instance().register_<Any>();

} // namespace conditions

} // namespace router
