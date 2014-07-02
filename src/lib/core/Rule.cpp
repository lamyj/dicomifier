#include "Factory.h"
#include "Rule.h"

namespace dicomifier
{
    
Rule::Rule():
    _condition(NULL)
{
    // Nothing to do
}

Rule::~Rule()
{
    // Nothing to do
}

void 
Rule
::set_condition(conditions::Condition::ConstPointer condition)
{
    this->_condition = condition;
}
    
void
Rule 
::add_action(actions::Action::ConstPointer action)
{
    this->_actions.push_back(action);
}

void 
Rule
::Execute()
{
    if (this->_condition->eval())
    {
        for (auto action: this->_actions)
        {
            action->run();
        }
    }
}
    
} // namespace dicomifier
