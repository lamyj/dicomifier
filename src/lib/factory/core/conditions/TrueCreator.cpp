/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/conditions/True.h"
#include "core/Factory.h"
#include "TrueCreator.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<TrueCreator>();
    
TrueCreator::TrueCreator()
{
    // nothing to do
}

TrueCreator::~TrueCreator()
{
    // nothing to do
}

Object::Pointer TrueCreator::Create(boost::property_tree::ptree::value_type & value)
{
    return dicomifier::conditions::True::New();
}
    
} // namespace factory
    
} // namespace dicomifier
