/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "InversionTimeDcmFieldCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<InversionTimeDcmFieldCreator>(); 

InversionTimeDcmFieldCreator
::InversionTimeDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

InversionTimeDcmFieldCreator
::~InversionTimeDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
InversionTimeDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{    
    TranslatorInversionTimeDcmFieldCreator action;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.inversiontime;
}

template<>
void 
InversionTimeDcmFieldCreator::TranslatorInversionTimeDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR> 
void 
InversionTimeDcmFieldCreator::TranslatorInversionTimeDcmFieldCreator
::run() const
{
    inversiontime = dicomifier::translator::InversionTimeDcmField<VR>::New();
}

} // namespace factory

} // namespace translator

} // namespace dicomifier
