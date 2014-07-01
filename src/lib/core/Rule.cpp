#include "Factory.h"
#include "Rule.h"

namespace dicomifier
{
    
Rule::Rule()
{
    // Nothing to do
}

Rule::~Rule()
{
    // Nothing to do
}

void 
Rule
::add_condition(conditions::Condition::ConstPointer condition)
{
    this->_conditions.push_back(condition);
}
    
void
Rule 
::add_action(actions::Action::ConstPointer action)
{
    this->_actions.push_back(action);
}
    
} // namespace dicomifier
