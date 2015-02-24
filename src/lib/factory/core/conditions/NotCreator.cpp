/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "core/conditions/Condition.h"
#include "core/conditions/Not.h"
#include "core/DicomifierException.h"
#include "core/Factory.h"
#include "NotCreator.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration =
        Factory::get_instance().register_<NotCreator>();
    
NotCreator
::NotCreator():
    CreatorBase()
{
    // Nothing to do
}

NotCreator
::~NotCreator()
{
    // Nothing to do
}

Object::Pointer
NotCreator
::Create(boost::property_tree::ptree::value_type & value)
{
    dicomifier::conditions::Not::Pointer not_ = dicomifier::conditions::Not::New();
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            value.second)
    {
        Object::Pointer object = Factory::get_instance().create(v, this->_inputs,
                                                                this->_outputs);
        dicomifier::conditions::Condition::Pointer cond = 
            std::dynamic_pointer_cast<dicomifier::conditions::Condition>(object);
        if (cond != NULL)
        {
            not_->set_condition(cond);
            return not_; // only one condition
        }
    }
    throw DicomifierException("Missing Condition for Not node");
}
    
} // namespace factory
    
} // namespace dicomifier
