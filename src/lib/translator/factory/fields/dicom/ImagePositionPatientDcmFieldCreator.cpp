/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ImagePositionPatientDcmFieldCreator.h"
#include "translator/fields/dicom/ImagePositionPatientDcmField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<ImagePositionPatientDcmFieldCreator>(); 

ImagePositionPatientDcmFieldCreator
::ImagePositionPatientDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

ImagePositionPatientDcmFieldCreator
::~ImagePositionPatientDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
ImagePositionPatientDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    TranslatorImagePositionPatientDcmFieldCreator action;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.imageposition;
}

template<>
void 
ImagePositionPatientDcmFieldCreator::TranslatorImagePositionPatientDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR> 
void 
ImagePositionPatientDcmFieldCreator::TranslatorImagePositionPatientDcmFieldCreator
::run() const
{
    imageposition = dicomifier::translator::ImagePositionPatientDcmField<VR>::New();
}

} // namespace factory

} // namespace translator

} // namespace dicomifier
