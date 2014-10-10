/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "MultiplicationOperator.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename MultiplicationOperator<VR>::Pointer
MultiplicationOperator<VR>
::New()
{
    return Pointer(new Self());
}
    
template<DcmEVR VR>
typename MultiplicationOperator<VR>::Pointer
MultiplicationOperator<VR>
::New(std::vector<Tag::Pointer> tags)
{
    return Pointer(new Self(tags));
}
    
template<DcmEVR VR>
MultiplicationOperator<VR>
::MultiplicationOperator()
    :SubTag<VR>()
{
    // Nothing to do
}
    
template<DcmEVR VR>
MultiplicationOperator<VR>
::MultiplicationOperator(std::vector<Tag::Pointer> tags)
    :SubTag<VR>(), _tags(tags)
{
    // Nothing to do
}

template<DcmEVR VR>
MultiplicationOperator<VR>
::~MultiplicationOperator()
{
    // Nothing to do
}

template<DcmEVR VR>
void
MultiplicationOperator<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmDataset* dataset)
{
    for (auto currentTag : this->_tags)
    {
        typename SubTag<VR>::Pointer subtag = 
            std::dynamic_pointer_cast<SubTag<VR>>(currentTag);
        
        subtag->run(brukerdataset, generator, dataset);
        
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
                this->_array[i] = ElementTraits<VR>::multiplication(this->_array[i], array[i]);
            }
        }
    }
}
    
} // namespace translator
    
} // namespace dicomifier
