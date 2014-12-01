/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "EffectiveEchoTimeFieldCreator.h"
#include "translator/fields/dicom/EffectiveEchoTimeField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{

namespace translator
{

namespace factory
{

static unsigned int const registration =
        TranslatorFactory::get_instance().register_<EffectiveEchoTimeFieldCreator>();

EffectiveEchoTimeFieldCreator
::EffectiveEchoTimeFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

EffectiveEchoTimeFieldCreator
::~EffectiveEchoTimeFieldCreator()
{
    // Nothing to do
}

Tag::Pointer
EffectiveEchoTimeFieldCreator
::Create(boost::property_tree::ptree::value_type & value,
         DcmDataset* dataset,
         DcmEVR evr)
{
    TranslatorEffectiveEchoTimeFieldCreator action;

    dicomifier::vr_dispatch(action, evr);

    return action.effectiveechotime;
}

template<>
void
EffectiveEchoTimeFieldCreator::TranslatorEffectiveEchoTimeFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR>
void
EffectiveEchoTimeFieldCreator::TranslatorEffectiveEchoTimeFieldCreator
::run() const
{
    effectiveechotime = dicomifier::translator::EffectiveEchoTimeField<VR>::New();
}

} // namespace factory

} // namespace translator

} // namespace dicomifier
