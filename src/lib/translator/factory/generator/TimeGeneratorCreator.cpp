/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "TimeGeneratorCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<TimeGeneratorCreator>(); 

TimeGeneratorCreator
::TimeGeneratorCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

TimeGeneratorCreator
::~TimeGeneratorCreator()
{
    // Nothing to do
}

Tag::Pointer 
TimeGeneratorCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    TranslatorTimeGeneratorCreator action;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.timegenerator;
}

template<>
void 
TimeGeneratorCreator::TranslatorTimeGeneratorCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Create SQ Element");
}

template<DcmEVR VR> 
void 
TimeGeneratorCreator::TranslatorTimeGeneratorCreator
::run() const
{
    timegenerator = dicomifier::translator::TimeGenerator<VR>::New();
}
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    


