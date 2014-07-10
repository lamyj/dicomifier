/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _48df5c83_5dd1_4a3c_9f5b_494bdcc45d60
#define _48df5c83_5dd1_4a3c_9f5b_494bdcc45d60

#include <functional>
#include <map>
#include <memory>

#include "Object.h"
#include "factory/core/CreatorBase.h"

namespace dicomifier
{
    
class Factory
{
public:
    static Factory & get_instance();
    
    virtual ~Factory();

    template<typename T>
    unsigned int register_();
    
    bool can_create(std::string const & class_) const;
    
    std::shared_ptr<Object> create(boost::property_tree::ptree::value_type & value,
								   std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> const inputs,
								   std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> const outputs) const;
    
protected:

private:
    typedef std::function<std::shared_ptr<dicomifier::factory::CreatorBase>()> Creator;
    typedef std::map<std::string, Creator> CreatorMap;

    Factory();
    
    static Factory * _instance;
    CreatorMap _creators;

    // Purposely not implemented
    Factory(Factory const & other);
    void operator=(Factory const & other);
    
};
    
} // namespace dicomifier

#include "Factory.txx"

#endif // _48df5c83_5dd1_4a3c_9f5b_494bdcc45d60
