/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/actions/None.h"
#include "core/Factory.h"
#include "NoneCreator.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration =
        Factory::get_instance().register_<NoneCreator>();
    
NoneCreator
::NoneCreator():
    CreatorBase()
{
    // nothing to do
}

NoneCreator
::~NoneCreator()
{
    // nothing to do
}

Object::Pointer
NoneCreator
::Create(boost::property_tree::ptree::value_type & value)
{
    return dicomifier::actions::None::New();
}

} // namespace factory

} // namespace dicomifier
