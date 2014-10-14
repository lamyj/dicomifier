/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SpacingBetweenSlicesDcmFieldCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<SpacingBetweenSlicesDcmFieldCreator>(); 

SpacingBetweenSlicesDcmFieldCreator
::SpacingBetweenSlicesDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

SpacingBetweenSlicesDcmFieldCreator
::~SpacingBetweenSlicesDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
SpacingBetweenSlicesDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{    
    TranslatorSpacingBetweenSlicesDcmFieldCreator action;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.spacingbetweenslices;
}

template<>
void 
SpacingBetweenSlicesDcmFieldCreator::TranslatorSpacingBetweenSlicesDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR> 
void 
SpacingBetweenSlicesDcmFieldCreator::TranslatorSpacingBetweenSlicesDcmFieldCreator
::run() const
{
    spacingbetweenslices = dicomifier::translator::SpacingBetweenSlicesDcmField<VR>::New();
}

} // namespace factory
    
} // namespace translator

}// namespace dicomifier
