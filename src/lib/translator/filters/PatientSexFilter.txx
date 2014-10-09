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

template<DcmEVR VR>
void
PatientSexFilter<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      std::vector<int> const & indexes,
      DcmDataset* dataset)
{
    if (VR != EVR_CS)
    {
        throw DicomifierException("PatientSexFilter only available for CS");
    }
    
    typename SubTag<VR>::Pointer subtag = 
        std::dynamic_pointer_cast<SubTag<VR>>(this->_tag);

    subtag->run(brukerdataset, indexes, dataset);
    
    auto array = subtag->get_array();
    
    for (int i = 0; i < array.size(); i++)
    {
        std::string temp = ElementTraits<VR>::toString(array[i]);
        
        std::string result = "";
        
        // See ParaVision document: D13_PvParams.pdf (D13-70)
        // See DICOM PS3.3 2013: table C.7-1
        if (temp == "MALE")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("M"));
        }
        else if (temp == "FEMALE")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("F"));
        }
        else // if (temp == "UNDEFINED" || temp == "UNKNOWN")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("O"));
        }
    }
}

} // namespace translator
    
} // namespace dicomifier
