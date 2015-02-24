/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ImageOrientationPatientDcmFieldCreator.h"
#include "translator/fields/dicom/ImageOrientationPatientDcmField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration =
        TranslatorFactory::get_instance().register_<ImageOrientationPatientDcmFieldCreator>();

ImageOrientationPatientDcmFieldCreator
::ImageOrientationPatientDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

ImageOrientationPatientDcmFieldCreator
::~ImageOrientationPatientDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
ImageOrientationPatientDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    TranslatorImageOrientationPatientDcmFieldCreator action;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.imageorientation;
}

template<>
void 
ImageOrientationPatientDcmFieldCreator::TranslatorImageOrientationPatientDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR> 
void 
ImageOrientationPatientDcmFieldCreator::TranslatorImageOrientationPatientDcmFieldCreator
::run() const
{
    imageorientation = dicomifier::translator::ImageOrientationPatientDcmField<VR>::New();
}

} // namespace factory

} // namespace translator

} // namespace dicomifier
