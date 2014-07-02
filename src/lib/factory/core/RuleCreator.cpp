/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "core/Factory.h"
#include "core/Rule.h"
#include "RuleCreator.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<RuleCreator>();
    
RuleCreator::RuleCreator()
{
}

RuleCreator::~RuleCreator()
{
}

Object::Pointer 
RuleCreator
::Create(boost::property_tree::ptree::value_type & value) const
{
    dicomifier::Rule::Pointer rule = dicomifier::Rule::New();
    
    // Look for Conditions
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            value.second.get_child("Condition"))
    {
        Object::Pointer object = Factory::get_instance().create(v);
        dicomifier::conditions::Condition::Pointer cond = 
            std::dynamic_pointer_cast<dicomifier::conditions::Condition>(object);
        if (cond != NULL)
        {
            rule->set_condition(cond);
            break;
        }
    }
    
    // Look for Actions
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            value.second.get_child("Actions"))
    {
        Object::Pointer object = Factory::get_instance().create(v);
        dicomifier::actions::Action::Pointer act = 
            std::dynamic_pointer_cast<dicomifier::actions::Action>(object);
        if (act != NULL)
        {
            rule->add_action(act);
        }
    }
    
    return rule;
}
   
} // namespace factory

} // namespace dicomifier
