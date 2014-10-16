/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ImagePositionPatientDcmField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename ImagePositionPatientDcmField<VR>::Pointer
ImagePositionPatientDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
ImagePositionPatientDcmField<VR>
::ImagePositionPatientDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
ImagePositionPatientDcmField<VR>
::~ImagePositionPatientDcmField()
{
    // Nothing to do
}

template<>
void
ImagePositionPatientDcmField<EVR_DS>
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
    brukerdataset->get_indexForValue("VisuCorePosition", 
                                     indexposition, 
                                     startposition);
    
    if (indexposition == -1)
    {
        throw DicomifierException("Missing VisuCorePosition field");
    }
    
    auto brukerfield = brukerdataset->GetFieldData("VisuCorePosition");
    
    startposition = generator.get_index()[indexposition] * 
                    brukerfield->get_dimensionNumbers()[1] + 
                    startposition;
    
    // we assume that dimensionNumbers contains 2 elements
    for (auto i = 0; i < brukerfield->get_dimensionNumbers()[1]; i++)
    {
        this->_array.push_back
        (
            ElementTraits<EVR_DS>::fromString(brukerfield->get_string(startposition + i))
        );
    }
}

template<DcmEVR VR>
void
ImagePositionPatientDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be DS for Tag 0020,0032.");
}
    
} // namespace dicomifier

} // namespace translator
