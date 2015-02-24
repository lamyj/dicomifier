/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _de4665d1_8ae0_401b_8a64_ec821b387f5b
#define _de4665d1_8ae0_401b_8a64_ec821b387f5b

#include "core/actions/Action.h"
#include "core/conditions/Condition.h"
#include "Object.h"

namespace dicomifier
{
    
/**
 * @brief object Rule
 */
class Rule : public Object
{
public:
    typedef Rule Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of Rule
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of Rule
    virtual ~Rule();
    
    /**
     * Modify condition for this rule
     * @param condition: new condition
     */
    void set_condition(conditions::Condition::ConstPointer condition);
    
    /**
     * Register an action
     * @param action: action to add
     */
    void add_action(actions::Action::ConstPointer action);
    
    /**
     * Run all registered actions
     * @return true if registered condition is true, false otherwise
     */
    bool Execute();
    
    /**
     * Get this class name
     * @return this class name
     */
    static std::string get_class_name() { return "Rule"; }

protected:
    /// Create an instance of Rule
    Rule();

private:
    /// Condition
    conditions::Condition::ConstPointer _condition;
    
    /// List of Actions
    std::vector<actions::Action::ConstPointer> _actions;

    Rule(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace dicomifier

#endif // _de4665d1_8ae0_401b_8a64_ec821b387f5b
