/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "InversionTimeDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename InversionTimeDcmField<VR>::Pointer
InversionTimeDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
InversionTimeDcmField<VR>
::InversionTimeDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
InversionTimeDcmField<VR>
::~InversionTimeDcmField()
{
    // Nothing to do
}

template<>
void
InversionTimeDcmField<EVR_DS>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Bruker Dataset is NULL");
    }
    
    int startposition = 0;
    int indexposition = 0;
    brukerdataset->get_indexForValue("VisuAcqInversionTime", 
                                     indexposition, 
                                     startposition);
    
    if (indexposition == -1)
    {
        return; // no value
    }
    
    auto brukerfield = brukerdataset->GetFieldData("VisuAcqInversionTime");
    
    startposition = generator.get_index()[indexposition] + 
                    startposition;
                    
    this->_array.push_back
    (
        ElementTraits<EVR_DS>::fromString(brukerfield->get_string(startposition))
    );
}

template<DcmEVR VR>
void
InversionTimeDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be DS for Tag 0018,0082.");
}

} // namespace translator
    
} // namespace dicomifier
