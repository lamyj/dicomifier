/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "InStackPositionNumberDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename InStackPositionNumberDcmField<VR>::Pointer
InStackPositionNumberDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
InStackPositionNumberDcmField<VR>
::InStackPositionNumberDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
InStackPositionNumberDcmField<VR>
::~InStackPositionNumberDcmField()
{
    // Nothing to do
}

template<>
void
InStackPositionNumberDcmField<EVR_UL>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
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
    brukerdataset->get_indexForValue("VisuCoreOrientation", 
                                     indexposition, 
                                     startposition);
    
    this->_array.push_back(generator.get_index()[indexposition] + 1);
}

template<DcmEVR VR>
void
InStackPositionNumberDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be UL for Tag 0020,9057.");
}
    
} // namespace translator
    
} // namespace dicomifier
