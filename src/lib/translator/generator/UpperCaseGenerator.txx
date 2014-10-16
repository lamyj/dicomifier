/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "UpperCaseGenerator.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename UpperCaseGenerator<VR>::Pointer
UpperCaseGenerator<VR>
::New()
{
    return Pointer(new Self());
}
    
template<DcmEVR VR>
typename UpperCaseGenerator<VR>::Pointer
UpperCaseGenerator<VR>
::New(Tag::Pointer tag)
{
    return Pointer(new Self(tag));
}

template<DcmEVR VR>
UpperCaseGenerator<VR>
::UpperCaseGenerator()
    :SubTag<VR>(), _tag(NULL)
{
    // Nothing to do
}

template<DcmEVR VR>
UpperCaseGenerator<VR>
::UpperCaseGenerator(Tag::Pointer tag)
    :SubTag<VR>(), _tag(tag)
{
    // Nothing to do
}

template<DcmEVR VR>
UpperCaseGenerator<VR>
::~UpperCaseGenerator()
{
    // Nothing to do
}

template<DcmEVR VR>
void
UpperCaseGenerator<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (this->_tag != NULL)
    {
        // Clean residual values
        this->_array.clear();
        
        typename SubTag<VR>::Pointer subtag = 
            std::dynamic_pointer_cast<SubTag<VR>>(this->_tag);

        subtag->run(brukerdataset, generator, dataset);
        
        auto array = subtag->get_array();
        
        for (int i = 0; i < array.size(); i++)
        {
            std::string temp = ElementTraits<VR>::toString(array[i]);
            std::locale loc;
            std::stringstream tempstream;
            for (std::string::size_type i=0; i<temp.length(); ++i)
            {
                tempstream << std::toupper(temp[i],loc);
            }
            
            this->_array.push_back(ElementTraits<VR>::fromString(tempstream.str()));
        }
    }
}

} // namespace translator
    
} // namespace dicomifier

