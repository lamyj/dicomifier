/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "BrukerFieldExistCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{

namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<BrukerFieldExistCreator>(); 

BrukerFieldExistCreator
::BrukerFieldExistCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

BrukerFieldExistCreator
::~BrukerFieldExistCreator()
{
    // Nothing to do
}

Tag::Pointer 
BrukerFieldExistCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    // Warning: throw exception if attribut is missing
    std::string const brukerfieldname = value.second.get<std::string>("<xmlattr>.name");
    
    return BrukerFieldExist::New(brukerfieldname);
}

}
    
}

}
