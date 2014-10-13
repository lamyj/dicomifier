/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <ctime>

#include "UIDGenerator.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename UIDGenerator<VR>::Pointer
UIDGenerator<VR>
::New()
{
    return Pointer(new Self());
}
    
template<DcmEVR VR>
typename UIDGenerator<VR>::Pointer
UIDGenerator<VR>
::New(std::string const & uid_type)
{
    return Pointer(new Self(uid_type));
}

template<DcmEVR VR>
UIDGenerator<VR>
::UIDGenerator()
    :SubTag<VR>(), _uid_type("")
{
    // Nothing to do
}

template<DcmEVR VR>
UIDGenerator<VR>
::UIDGenerator(std::string const & uid_type)
    :SubTag<VR>(), _uid_type(uid_type)
{
    // Nothing to do
}

template<DcmEVR VR>
UIDGenerator<VR>
::~UIDGenerator()
{
    // Nothing to do
}

template<DcmEVR VR>
void
UIDGenerator<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmDataset* dataset)
{
    if (this->_uid_type == "SOPInstanceUID")
    {
        char uidinstance[128];
        dcmGenerateUniqueIdentifier(uidinstance, SITE_INSTANCE_UID_ROOT);
        std::string value(&uidinstance[0]);
        this->_array.push_back(ElementTraits<VR>::fromString(value));
    }
}

} // namespace translator
    
} // namespace dicomifier
