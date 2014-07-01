/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/Factory.h"
#include "DeleteElementCreator.h"
#include "dicom/actions/DeleteElement.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<DeleteElementCreator>();
    
DeleteElementCreator::DeleteElementCreator()
{
    // Nothing to do
}

DeleteElementCreator::~DeleteElementCreator()
{
    // Nothing to do
}

Object::Pointer 
DeleteElementCreator
::Create(boost::property_tree::ptree::value_type & value) const
{
    dicomifier::actions::DeleteElement::Pointer deleteElement = 
        dicomifier::actions::DeleteElement::New();

    // Get 'tag' attribut like 'XXXX,YYYY':
    std::string const second = value.second.get_child("<xmlattr>.tag").data();
    std::string const group = second.substr(0,4);
    std::string const element = second.substr(5,4);
    
    deleteElement->set_tag(DcmTag(atoi(group.c_str()), atoi(element.c_str())));
    
    return deleteElement;
}
    
} // namespace factory
    
} // namespace dicomifier
