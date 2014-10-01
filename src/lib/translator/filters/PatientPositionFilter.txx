/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "PatientPositionFilter.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename PatientPositionFilter<VR>::Pointer
PatientPositionFilter<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
typename PatientPositionFilter<VR>::Pointer
PatientPositionFilter<VR>
::New(Tag::Pointer tag)
{
    return Pointer(new Self(tag));
}

template<DcmEVR VR>
PatientPositionFilter<VR>
::PatientPositionFilter()
    :SubTag<VR>(), _tag(NULL)
{
    // Nothing to do
}

template<DcmEVR VR>
PatientPositionFilter<VR>
::PatientPositionFilter(Tag::Pointer tag)
    :SubTag<VR>(), _tag(tag)
{
    // Nothing to do
}

template<DcmEVR VR>
PatientPositionFilter<VR>
::~PatientPositionFilter()
{
    // Nothing to do
}

template<DcmEVR VR>
void
PatientPositionFilter<VR>
::run(DcmDataset* dataset,
      dicomifier::bruker::BrukerDataset* brukerdataset)
{
    if (VR != EVR_CS)
    {
        throw DicomifierException("PatientPositionFilter only available for CS");
    }
    
    typename SubTag<VR>::Pointer subtag = 
        std::dynamic_pointer_cast<SubTag<VR>>(this->_tag);

    subtag->run(dataset, brukerdataset);
    
    auto array = subtag->get_array();
    
    for (int i = 0; i < array.size(); i++)
    {
        std::string temp = ElementTraits<VR>::toString(array[i]);
        
        std::string result = "";
        
        // See ParaVision document: D13_PvParams.pdf (D13-71)
        // See DICOM PS3.3 2013: C.7.3.1.1.2
        if (temp == "Head_Supine")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("HFS"));
        }
        else if (temp == "Head_Prone")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("HFP"));
        }
        else if (temp == "Head_Left")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("HFDL"));
        }
        else if (temp == "Head_Right")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("HFDR"));
        }
        else if (temp == "Foot_Supine")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("FFS"));
        }
        else if (temp == "Foot_Prone")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("FFP"));
        }
        else if (temp == "Foot_Left")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("FFDL"));
        }
        else if (temp == "Foot_Right")
        {
            this->_array.push_back(ElementTraits<VR>::fromString("FFDR"));
        }
    }
}

} // namespace translator
    
} // namespace dicomifier
