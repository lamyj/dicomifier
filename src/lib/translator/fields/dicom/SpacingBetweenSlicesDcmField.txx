/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SpacingBetweenSlicesDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename SpacingBetweenSlicesDcmField<VR>::Pointer
SpacingBetweenSlicesDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
SpacingBetweenSlicesDcmField<VR>
::SpacingBetweenSlicesDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
SpacingBetweenSlicesDcmField<VR>
::~SpacingBetweenSlicesDcmField()
{
    // Nothing to do
}

template<>
void
SpacingBetweenSlicesDcmField<EVR_DS>
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Bruker Dataset is NULL");
    }
    
    auto brukerfield = brukerdataset->get_field("VisuCorePosition");
    
    // Clean residual values
    this->_array.clear();
    
    // we should have at least 2 points
    if (brukerfield.shape[0] > 1)
    {
        double Ax = brukerfield.get_float(0);
        double Ay = brukerfield.get_float(1);
        double Az = brukerfield.get_float(2);
        
        double Bx = brukerfield.get_float(3);
        double By = brukerfield.get_float(4);
        double Bz = brukerfield.get_float(5);
        
        double result = (Ax - Bx)*(Ax - Bx) + (Ay - By)*(Ay - By) + (Az - Bz)*(Az - Bz);
        result = sqrt(result);
        
        this->_array.push_back(result);
    }
}

template<DcmEVR VR>
void
SpacingBetweenSlicesDcmField<VR>
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be DS for Tag 0018,0088.");
}

} // namespace translator
    
} // namespace dicomifier
