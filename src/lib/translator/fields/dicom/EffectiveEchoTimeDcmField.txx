/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "EffectiveEchoTimeDcmField.h"

namespace dicomifier
{

namespace translator
{

template<DcmEVR VR>
typename EffectiveEchoTimeDcmField<VR>::Pointer
EffectiveEchoTimeDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
EffectiveEchoTimeDcmField<VR>
::EffectiveEchoTimeDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
EffectiveEchoTimeDcmField<VR>
::~EffectiveEchoTimeDcmField()
{
    // Nothing to do
}

template<>
void
EffectiveEchoTimeDcmField<EVR_FD>
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Bruker Dataset is NULL");
    }

    // Clean residual values
    this->_array.clear();

    int startposition = 0;
    int indexposition = 0;
    brukerdataset->get_indexForValue("VisuAcqEchoTime",
                                     indexposition,
                                     startposition);

    auto brukerfield = brukerdataset->get_field("VisuAcqEchoTime");

    if (indexposition == -1)
    {
        // Only one position
        indexposition = 0;
    }
    else
    {
        startposition = generator.get_index()[indexposition] *
                        brukerfield.shape[1] +
                        startposition;
    }

    this->_array.push_back(brukerfield.get_float(startposition));
}

template<DcmEVR VR>
void
EffectiveEchoTimeDcmField<VR>
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be FD for Tag 0018,9082.");
}

} // namespace translator

} // namespace dicomifier
