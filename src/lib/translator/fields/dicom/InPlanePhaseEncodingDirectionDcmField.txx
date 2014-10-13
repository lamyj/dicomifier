/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "InPlanePhaseEncodingDirectionDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename InPlanePhaseEncodingDirectionDcmField<VR>::Pointer
InPlanePhaseEncodingDirectionDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
typename InPlanePhaseEncodingDirectionDcmField<VR>::Pointer
InPlanePhaseEncodingDirectionDcmField<VR>
::New(Tag::Pointer tag)
{
    return Pointer(new Self(tag));
}

template<DcmEVR VR>
InPlanePhaseEncodingDirectionDcmField<VR>
::InPlanePhaseEncodingDirectionDcmField()
    :SubTag<VR>(), _tag(NULL)
{
    // Nothing to do
}

template<DcmEVR VR>
InPlanePhaseEncodingDirectionDcmField<VR>
::InPlanePhaseEncodingDirectionDcmField(Tag::Pointer tag)
    :SubTag<VR>(), _tag(tag)
{
    // Nothing to do
}

template<DcmEVR VR>
InPlanePhaseEncodingDirectionDcmField<VR>
::~InPlanePhaseEncodingDirectionDcmField()
{
    // Nothing to do
}

template<>
void
InPlanePhaseEncodingDirectionDcmField<EVR_CS>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmDataset* dataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Bruker Dataset is NULL");
    }
    
    if (this->_tag == NULL)
    {
        throw DicomifierException("Missing node");
    }
    
    typename SubTag<EVR_CS>::Pointer subtag = 
        std::dynamic_pointer_cast<SubTag<EVR_CS>>(this->_tag);

    subtag->run(brukerdataset, generator, dataset);
    
    auto array = subtag->get_array();
    
    int step = generator.get_step();
    
    this->_array.push_back(array[step]);
}

template<DcmEVR VR>
void
InPlanePhaseEncodingDirectionDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmDataset* dataset)
{
    throw DicomifierException("VR should be CS for Tag 0018,1312.");
}
    
} // namespace dicomifier

} // namespace translator
