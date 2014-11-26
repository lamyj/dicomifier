/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "TestFieldCreator.h"
#include "translator/fields/TestField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration =
        TranslatorFactory::get_instance().register_<TestFieldCreator>();

TestFieldCreator
::TestFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

TestFieldCreator
::~TestFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
TestFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    return dicomifier::translator::TestField::New();
}
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
