/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "InstanceNumberDcmFieldCreator.h"
#include "translator/fields/dicom/InstanceNumberDcmField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<InstanceNumberDcmFieldCreator>(); 

InstanceNumberDcmFieldCreator
::InstanceNumberDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

InstanceNumberDcmFieldCreator
::~InstanceNumberDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
InstanceNumberDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    TranslatorInstanceNumberDcmFieldCreator action;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.instancenumber;
}

template<>
void 
InstanceNumberDcmFieldCreator::TranslatorInstanceNumberDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR> 
void 
InstanceNumberDcmFieldCreator::TranslatorInstanceNumberDcmFieldCreator
::run() const
{
    instancenumber = dicomifier::translator::InstanceNumberDcmField<VR>::New();
}
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
