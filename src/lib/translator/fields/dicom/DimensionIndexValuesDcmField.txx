/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "DimensionIndexValuesDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename DimensionIndexValuesDcmField<VR>::Pointer
DimensionIndexValuesDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
DimensionIndexValuesDcmField<VR>
::DimensionIndexValuesDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
DimensionIndexValuesDcmField<VR>
::~DimensionIndexValuesDcmField()
{
    // Nothing to do
}

template<>
void
DimensionIndexValuesDcmField<EVR_UL>
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
    brukerdataset->get_indexForValue("VisuCoreOrientation", 
                                     indexposition, 
                                     startposition);
    
    // Attention: we should have 2 items in the sequence 0020,9222
    this->_array.push_back(generator.compute_index({indexposition}) + 1);
    this->_array.push_back(generator.get_index()[indexposition] + 1);
}

template<DcmEVR VR>
void
DimensionIndexValuesDcmField<VR>
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be UL for Tag 0020,9157.");
}
    
} // namespace translator
    
} // namespace dicomifier
