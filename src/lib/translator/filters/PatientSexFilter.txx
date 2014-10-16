/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "PatientSexFilter.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename PatientSexFilter<VR>::Pointer
PatientSexFilter<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
typename PatientSexFilter<VR>::Pointer
PatientSexFilter<VR>
::New(Tag::Pointer tag)
{
    return Pointer(new Self(tag));
}

template<DcmEVR VR>
PatientSexFilter<VR>
::PatientSexFilter()
    :SubTag<VR>(), _tag(NULL)
{
    // Nothing to do
}

template<DcmEVR VR>
PatientSexFilter<VR>
::PatientSexFilter(Tag::Pointer tag)
    :SubTag<VR>(), _tag(tag)
{
    // Nothing to do
}

template<DcmEVR VR>
PatientSexFilter<VR>
::~PatientSexFilter()
{
    // Nothing to do
}

template<>
void
PatientSexFilter<EVR_CS>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    // Clean residual values
    this->_array.clear();
    
    typename SubTag<EVR_CS>::Pointer subtag = 
        std::dynamic_pointer_cast<SubTag<EVR_CS>>(this->_tag);

    subtag->run(brukerdataset, generator, dataset);
    
    auto array = subtag->get_array();
    
    for (int i = 0; i < array.size(); i++)
    {
        std::string temp = ElementTraits<EVR_CS>::toString(array[i]);
        
        std::string result = "";
        
        // See ParaVision document: D13_PvParams.pdf (D13-70)
        // See DICOM PS3.3 2013: table C.7-1
        if (temp == "MALE")
        {
            this->_array.push_back(OFString("M"));
        }
        else if (temp == "FEMALE")
        {
            this->_array.push_back(OFString("F"));
        }
        else // if (temp == "UNDEFINED" || temp == "UNKNOWN")
        {
            this->_array.push_back(OFString("O"));
        }
    }
}

template<DcmEVR VR>
void
PatientSexFilter<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    throw DicomifierException("PatientSexFilter only available for CS");
}

} // namespace translator
    
} // namespace dicomifier
