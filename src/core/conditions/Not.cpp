#include "core/Factory.h"
#include "Not.h"

namespace router
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

static unsigned int const registration = Factory::get_instance().register_<Not>();
    
}
    
} // namespace router
