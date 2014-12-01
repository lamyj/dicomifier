/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "EffectiveEchoTimeDcmFieldCreator.h"
#include "translator/fields/dicom/EffectiveEchoTimeDcmField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{

namespace translator
{

namespace factory
{

static unsigned int const registration =
        TranslatorFactory::get_instance().register_<EffectiveEchoTimeDcmFieldCreator>();

EffectiveEchoTimeDcmFieldCreator
::EffectiveEchoTimeDcmFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

EffectiveEchoTimeDcmFieldCreator
::~EffectiveEchoTimeDcmFieldCreator()
{
    // Nothing to do
}

Tag::Pointer
EffectiveEchoTimeDcmFieldCreator
::Create(boost::property_tree::ptree::value_type & value,
         DcmDataset* dataset,
         DcmEVR evr)
{
    TranslatorEffectiveEchoTimeDcmFieldCreator action;

    dicomifier::vr_dispatch(action, evr);

    return action.effectiveechotime;
}

template<>
void
EffectiveEchoTimeDcmFieldCreator::TranslatorEffectiveEchoTimeDcmFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR>
void
EffectiveEchoTimeDcmFieldCreator::TranslatorEffectiveEchoTimeDcmFieldCreator
::run() const
{
    effectiveechotime = dicomifier::translator::EffectiveEchoTimeDcmField<VR>::New();
}

} // namespace factory

} // namespace translator

} // namespace dicomifier
