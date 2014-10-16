/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "InstanceNumberDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename InstanceNumberDcmField<VR>::Pointer
InstanceNumberDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
InstanceNumberDcmField<VR>
::InstanceNumberDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
InstanceNumberDcmField<VR>
::~InstanceNumberDcmField()
{
    // Nothing to do
}

template<DcmEVR VR>
void
InstanceNumberDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    std::stringstream stream;
    stream << (generator.get_step() + 1);
    this->_array.push_back(ElementTraits<VR>::fromString(stream.str()));
}

} // namespace translator
   
} // namespace dicomifier
