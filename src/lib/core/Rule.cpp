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

bool 
Rule
::Execute()
{
	// If there is a condition and condition return false
    if (this->_condition != NULL && this->_condition->eval() == false)
    {
		return false;
	}
	
	// No condition or condition return true
	for (auto action: this->_actions)
	{
		action->run();
	}
	
	return true;
}
    
} // namespace dicomifier
