/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "DivisionOperator.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename DivisionOperator<VR>::Pointer
DivisionOperator<VR>
::New()
{
    return Pointer(new Self());
}
    
template<DcmEVR VR>
typename DivisionOperator<VR>::Pointer
DivisionOperator<VR>
::New(std::vector<Tag::Pointer> tags)
{
    return Pointer(new Self(tags));
}
    
template<DcmEVR VR>
DivisionOperator<VR>
::DivisionOperator()
    :SubTag<VR>()
{
    // Nothing to do
}
    
template<DcmEVR VR>
DivisionOperator<VR>
::DivisionOperator(std::vector<Tag::Pointer> tags)
    :SubTag<VR>(), _tags(tags)
{
    // Nothing to do
}

template<DcmEVR VR>
DivisionOperator<VR>
::~DivisionOperator()
{
    // Nothing to do
}

template<DcmEVR VR>
void
DivisionOperator<VR>
::run(DcmDataset* dataset,
      dicomifier::bruker::BrukerDataset* brukerdataset)
{
    for (auto currentTag : this->_tags)
    {
        typename SubTag<VR>::Pointer subtag = 
            std::dynamic_pointer_cast<SubTag<VR>>(currentTag);
        
        subtag->run(dataset, brukerdataset);
        
        auto array = subtag->get_array();
        
        if (this->_array.size() == 0)
        {
            this->_array = array;
        }
        else if (array.size() != this->_array.size())
        {
            throw DicomifierException("Different size");
        }
        else
        {
            for (int i = 0; i < array.size(); i++)
            {
                this->_array[i] = ElementTraits<VR>::division(this->_array[i], array[i]);
            }
        }
    }
}
    
} // namespace translator
    
} // namespace dicomifier
