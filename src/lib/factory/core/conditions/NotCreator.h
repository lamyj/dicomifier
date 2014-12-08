/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7dc82581_5bfc_4ad3_9bdc_c257956f86aa
#define _7dc82581_5bfc_4ad3_9bdc_c257956f86aa

#include "factory/core/CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
/**
 * @brief The NotCreator class: Factory for the class Not
 */
class NotCreator : public CreatorBase
{
public:
    typedef NotCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of NotCreator
    static Pointer New() { return Pointer(new Self()); }

    /// Destroy the instance of NotCreator
    virtual ~NotCreator();
    
    /**
     * @brief Create an object Not
     * @param value: XML node
     * @return new instancce of Not
     */
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    /**
     * @brief get_class_name: return XML node name
     * @return Not
     */
    static std::string get_class_name() { return "Not"; }

protected:
    /// Create an instance of NotCreator
    NotCreator();

private:
    NotCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _7dc82581_5bfc_4ad3_9bdc_c257956f86aa
