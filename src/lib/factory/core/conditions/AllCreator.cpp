/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "AllCreator.h"
#include "core/conditions/All.h"
#include "core/conditions/Condition.h"
#include "core/Factory.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<AllCreator>();
    
AllCreator::AllCreator()
{
    // Nothing to do
}

AllCreator::~AllCreator()
{
    // Nothing to do
}

Object::Pointer AllCreator::Create(boost::property_tree::ptree::value_type & value) const
{
    dicomifier::conditions::All::Pointer all = dicomifier::conditions::All::New();
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            value.second)
    {
        Object::Pointer object = Factory::get_instance().create(v);
        dicomifier::conditions::Condition::Pointer cond = 
            std::dynamic_pointer_cast<dicomifier::conditions::Condition>(object);
        if (cond != NULL)
        {
            all->add_child(cond);
        }
    }
    return all;
}
    
} // namespace factory
    
} // namespace dicomifier
