/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "UIDGeneratorCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<UIDGeneratorCreator>(); 

UIDGeneratorCreator
::UIDGeneratorCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

UIDGeneratorCreator
::~UIDGeneratorCreator()
{
    // Nothing to do
}

Tag::Pointer 
UIDGeneratorCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    // Warning: throw exception if attribut is missing
    std::string const uidtype = value.second.get<std::string>("<xmlattr>.uidtype");
    
    TranslatorUIDGeneratorCreator action;
    action.uidtype = uidtype;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.uidgenerator;
}

template<>
void 
UIDGeneratorCreator::TranslatorUIDGeneratorCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Create SQ Element");
}

template<DcmEVR VR> 
void 
UIDGeneratorCreator::TranslatorUIDGeneratorCreator
::run() const
{
    uidgenerator = dicomifier::translator::UIDGenerator<VR>::New(uidtype);
}
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
