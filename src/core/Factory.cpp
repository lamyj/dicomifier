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
}
    
Factory::~Factory()
{
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
::create(std::string const & class_) const
{
    CreatorMap::const_iterator const creators_it = this->_creators.find(class_);
    if(creators_it == this->_creators.end())
    {
        return NULL;
    }
    else
    {
        return creators_it->second();
    }
}
    
} // namespace dicomifier
