/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>

#include "Factory.h"

namespace dicomifier
{
    
Factory * Factory::_instance = NULL;

Factory &
Factory
::get_instance()
{
    if(Factory::_instance == NULL)
    {
        Factory::_instance = new Factory();
    }
    return *Factory::_instance;
}

Factory::Factory()
{
    // Nothing to do
}
    
Factory::~Factory()
{
    // Nothing to do
}

bool 
Factory
::can_create(std::string const & class_) const
{
    CreatorMap::const_iterator const creators_it = this->_creators.find(class_);
    return (creators_it != this->_creators.end());
}

std::shared_ptr<Object> 
Factory
::create(boost::property_tree::ptree::value_type & value,
         std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> const inputs,
         std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> const outputs) const
{
    CreatorMap::const_iterator const creators_it = this->_creators.find(value.first.data());
    if(creators_it != this->_creators.end())
    {
        auto creator = creators_it->second();
        creator->set_inputs(inputs);
        creator->set_outputs(outputs);
        return (creator->Create(value));
    }
    return NULL;
}
    
} // namespace dicomifier
