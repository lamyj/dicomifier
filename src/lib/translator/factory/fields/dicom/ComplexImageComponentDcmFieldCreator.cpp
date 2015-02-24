/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ComplexImageComponentDcmFieldCreator.h"
#include "translator/fields/dicom/ComplexImageComponentDcmField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{

namespace translator
{

namespace factory
{

static unsigned int const registration =
        TranslatorFactory::get_instance().register_<ComplexImageComponentDcmFieldCreator>();

ComplexImageComponentDcmFieldCreator
::ComplexImageComponentDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

ComplexImageComponentDcmFieldCreator
::~ComplexImageComponentDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer
ComplexImageComponentDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value,
         DcmDataset* dataset,
         DcmEVR evr)
{
    auto perframe_ = value.second.get_optional<bool>("<xmlattr>.perframe");
    bool perframe = true;
    if (perframe_)
    {
        perframe = perframe_.get();
    }

    TranslatorComplexImageComponentDcmFieldCreator action;
    action.perframe = perframe;

    dicomifier::vr_dispatch(action, evr);

    return action.compleximagecomponent;
}

template<>
void
ComplexImageComponentDcmFieldCreator::TranslatorComplexImageComponentDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR>
void
ComplexImageComponentDcmFieldCreator::TranslatorComplexImageComponentDcmFieldCreator
::run() const
{
    compleximagecomponent =
            dicomifier::translator::ComplexImageComponentDcmField<VR>::New(perframe);
}

} // namespace factory

} // namespace translator

} // namespace dicomifier
