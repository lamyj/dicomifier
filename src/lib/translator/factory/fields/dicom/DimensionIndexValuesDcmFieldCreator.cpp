/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "DimensionIndexValuesDcmFieldCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<DimensionIndexValuesDcmFieldCreator>(); 

DimensionIndexValuesDcmFieldCreator
::DimensionIndexValuesDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

DimensionIndexValuesDcmFieldCreator
::~DimensionIndexValuesDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
DimensionIndexValuesDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    TranslatorDimensionIndexValuesDcmFieldCreator action;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.dimensionindexvalues;
}

template<>
void 
DimensionIndexValuesDcmFieldCreator::TranslatorDimensionIndexValuesDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR> 
void 
DimensionIndexValuesDcmFieldCreator::TranslatorDimensionIndexValuesDcmFieldCreator
::run() const
{
    dimensionindexvalues = dicomifier::translator::DimensionIndexValuesDcmField<VR>::New();
}

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
