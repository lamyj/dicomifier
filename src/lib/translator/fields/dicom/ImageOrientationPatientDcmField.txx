/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ImageOrientationPatientDcmField.h"

namespace dicomifier
{
    
namespace translator
{ 
    
template<DcmEVR VR>
typename ImageOrientationPatientDcmField<VR>::Pointer
ImageOrientationPatientDcmField<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
ImageOrientationPatientDcmField<VR>
::ImageOrientationPatientDcmField()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
ImageOrientationPatientDcmField<VR>
::~ImageOrientationPatientDcmField()
{
    // Nothing to do
}

template<>
void
ImageOrientationPatientDcmField<EVR_DS>
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
    brukerdataset->get_indexForValue("VisuCoreOrientation", 
                                     indexposition, 
                                     startposition);
    
    // Clean residual values
    this->_array.clear();
    
    auto brukerfield = brukerdataset->GetFieldData("VisuCoreOrientation");
    
    if (indexposition == -1)
    {
        // Only one orientation
        indexposition = 0;
    }
    else
    {
        startposition = generator.get_index()[indexposition] *
                        brukerfield->get_dimensionNumbers()[1] + 
                        startposition;
    }
    
    // DICOM PS3.6 2013: 0020,0037 VM = 6
    for (auto i = 0; i < 6; i++)
    {
        this->_array.push_back
        (
            ElementTraits<EVR_DS>::fromString(brukerfield->get_string(startposition + i))
        );
    }
}

template<DcmEVR VR>
void
ImageOrientationPatientDcmField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("VR should be DS for Tag 0020,0037.");
}

} // namespace translator
    
} // namespace dicomifier
