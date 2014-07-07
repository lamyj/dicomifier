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
    
class NotCreator : public CreatorBase
{
public:
    typedef NotCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }

    virtual ~NotCreator();
    
    virtual Object::Pointer Create(boost::property_tree::ptree::value_type & value);

    static std::string get_class_name() { return "Not"; }

protected:
    NotCreator();

private:
    NotCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};
    
} // namespace factory
    
} // namespace dicomifier

#endif // _7dc82581_5bfc_4ad3_9bdc_c257956f86aa