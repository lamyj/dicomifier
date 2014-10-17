/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "StackIDDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename StackIDDcmField<VR>::Pointer
StackIDDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
StackIDDcmField<VR>
::StackIDDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
StackIDDcmField<VR>
::~StackIDDcmField()
{
    // Nothing to do
}

template<>
void
StackIDDcmField<EVR_SH>
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
    
    std::stringstream stream;
    stream << (generator.compute_index({indexposition}) + 1);
    
    this->_array.push_back(OFString(stream.str().c_str()));
}

template<DcmEVR VR>
void
StackIDDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be SH for Tag 0020,9056.");
}

} // namespace translator
    
} // namespace dicomifier
