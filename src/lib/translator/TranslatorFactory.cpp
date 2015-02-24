/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
TranslatorFactory * TranslatorFactory::_instance = NULL;

TranslatorFactory &
TranslatorFactory
::get_instance()
{
    if(TranslatorFactory::_instance == NULL)
    {
        TranslatorFactory::_instance = new TranslatorFactory();
    }
    return *TranslatorFactory::_instance;
}

void
TranslatorFactory
::delete_instance()
{
    if (TranslatorFactory::_instance != NULL)
    {
        delete TranslatorFactory::_instance;
        TranslatorFactory::_instance = NULL;
    }
}

TranslatorFactory
::TranslatorFactory()
{
    // Nothing to do
}

TranslatorFactory
::~TranslatorFactory()
{
    // Nothing to do
}

bool 
TranslatorFactory
::can_create(std::string const & class_) const
{
    std::map<std::string, TranslationCreator>::const_iterator const 
        creators_it = this->_creators.find(class_);
    return (creators_it != this->_creators.end());
}

Tag::Pointer 
TranslatorFactory
::create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    std::map<std::string, TranslationCreator>::const_iterator const 
        creators_it = this->_creators.find(value.first.data());
    if(creators_it != this->_creators.end())
    {
        auto creator = creators_it->second();
        return (creator->Create(value, dataset, evr));
    }
    return NULL;
}
    
} // namespace translator
    
} // namespace dicomifier
