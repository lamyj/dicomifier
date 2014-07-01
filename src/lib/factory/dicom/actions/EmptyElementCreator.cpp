/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/Factory.h"
#include "dicom/actions/EmptyElement.h"
#include "EmptyElementCreator.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<EmptyElementCreator>();
    
EmptyElementCreator::EmptyElementCreator()
{
    // Nothing to do
}

EmptyElementCreator::~EmptyElementCreator()
{
    // Nothing to do
}

Object::Pointer 
EmptyElementCreator
::Create(boost::property_tree::ptree::value_type & value) const
{
    dicomifier::actions::EmptyElement::Pointer emptyElement = 
        dicomifier::actions::EmptyElement::New();

    // Get 'tag' attribut like 'XXXX,YYYY':
    std::string const second = value.second.get_child("<xmlattr>.tag").data();
    std::string const group = second.substr(0,4);
    std::string const element = second.substr(5,4);
    
    emptyElement->set_tag(DcmTag(atoi(group.c_str()), atoi(element.c_str())));

    return emptyElement;
}
    
} // namespace factory
    
} // namespace dicomifier
