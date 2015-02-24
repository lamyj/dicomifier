/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "InStackPositionNumberDcmFieldCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{

namespace factory
{
    
static unsigned int const registration =
        TranslatorFactory::get_instance().register_<InStackPositionNumberDcmFieldCreator>();

InStackPositionNumberDcmFieldCreator
::InStackPositionNumberDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

InStackPositionNumberDcmFieldCreator
::~InStackPositionNumberDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
InStackPositionNumberDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    TranslatorInStackPositionNumberDcmFieldCreator action;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.instackpositionnumber;
}

template<>
void 
InStackPositionNumberDcmFieldCreator::TranslatorInStackPositionNumberDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR> 
void 
InStackPositionNumberDcmFieldCreator::TranslatorInStackPositionNumberDcmFieldCreator
::run() const
{
    instackpositionnumber = dicomifier::translator::
                    InStackPositionNumberDcmField<VR>::New();
}

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
