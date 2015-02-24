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
    
/**
 * @brief Factory for generate Actions and Conditions
 */
class Factory
{
public:
    /**
     * Create (if not exist) and return an unique instance of Factory
     * @return unique instance of Factory
     */
    static Factory & get_instance();
    
    /// Destroy the unique instance of Factory
    static void delete_instance();
    
    /// Destroy the Factory
    virtual ~Factory();

    /// Register creator classes
    template<typename T>
    unsigned int register_();
    
    /**
     * Look if a given class is register in this factory
     * @param class_: class name to create
     * @return true if Factory can generate given class, false otherwise
     */
    bool can_create(std::string const & class_) const;
    
    /**
     * Create an instance of given class
     * @param value: class name of the object to create
     * @param inputs: other inputs add to the object
     * @param outputs: other outputs add to the object
     * @return smart pointer to the created object
     */
    std::shared_ptr<Object> create(boost::property_tree::ptree::value_type & value,
                                   std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> const inputs,
                                   std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> const outputs) const;
    
protected:

private:
    typedef std::function<std::shared_ptr<dicomifier::factory::CreatorBase>()> Creator;
    typedef std::map<std::string, Creator> CreatorMap;

    /// Create an instance of Factory
    Factory();
    
    /// Unique Instance
    static Factory * _instance;
    
    /// Map of managed creator
    CreatorMap _creators;

    // Purposely not implemented
    Factory(Factory const & other);
    void operator=(Factory const & other);
    
};
    
} // namespace dicomifier

#include "Factory.txx"

#endif // _48df5c83_5dd1_4a3c_9f5b_494bdcc45d60
