/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "RuleCreator.h"
#include "core/Factory.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<RuleCreator>();
    
RuleCreator::RuleCreator()
{
}

RuleCreator::~RuleCreator()
{
}

Object::Pointer RuleCreator::Create(boost::property_tree::ptree::value_type & value) const
{
    return Object::New();
}
   
} // namespace factory

} // namespace dicomifier
