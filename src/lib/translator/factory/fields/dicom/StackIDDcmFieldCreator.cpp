/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "StackIDDcmFieldCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration =
        TranslatorFactory::get_instance().register_<StackIDDcmFieldCreator>();

StackIDDcmFieldCreator
::StackIDDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

StackIDDcmFieldCreator
::~StackIDDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
StackIDDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    TranslatorStackIDDcmFieldCreator action;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.stackid;
}

template<>
void 
StackIDDcmFieldCreator::TranslatorStackIDDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR> 
void 
StackIDDcmFieldCreator::TranslatorStackIDDcmFieldCreator
::run() const
{
    stackid = dicomifier::translator::StackIDDcmField<VR>::New();
}

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
