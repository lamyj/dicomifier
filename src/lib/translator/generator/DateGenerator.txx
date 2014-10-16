/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <ctime>

#include "DateGenerator.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename DateGenerator<VR>::Pointer
DateGenerator<VR>
::New()
{
    return Pointer(new Self());
}
    
template<DcmEVR VR>
typename DateGenerator<VR>::Pointer
DateGenerator<VR>
::New(Tag::Pointer tag, std::string const & inputformat, 
      std::string const & outputformat)
{
    return Pointer(new Self(tag, inputformat, outputformat));
}

template<DcmEVR VR>
DateGenerator<VR>
::DateGenerator()
    :SubTag<VR>(), _tag(NULL), _inputFormat(""), _outputFormat("%Y%m%d")
{
    // Nothing to do
}

template<DcmEVR VR>
DateGenerator<VR>
::DateGenerator(Tag::Pointer tag, std::string const & inputformat, 
                std::string const & outputformat)
    :SubTag<VR>(), _tag(tag), _inputFormat(inputformat), 
     _outputFormat(outputformat)
{
    // Nothing to do
}

template<DcmEVR VR>
DateGenerator<VR>
::~DateGenerator()
{
    // Nothing to do
}

template<DcmEVR VR>
void
DateGenerator<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    // Clean residual values
    this->_array.clear();
    
    if (this->_tag != NULL && this->_inputFormat != "")
    {
        typename SubTag<VR>::Pointer subtag = 
            std::dynamic_pointer_cast<SubTag<VR>>(this->_tag);

        subtag->run(brukerdataset, generator, dataset);
        
        auto array = subtag->get_array();
        
        for (int i = 0; i < array.size(); i++)
        {
            std::string temp = ElementTraits<VR>::toString(array[i]);
            
            struct tm parts = {0};
            strptime(temp.c_str(), this->_inputFormat.c_str(), &parts);
            
            char format[64];
            memset(&format[0], 0, 64);
            strftime(format, 64, this->_outputFormat.c_str(), &parts);
            
            std::string value(&format[0]);
            
            this->_array.push_back(ElementTraits<VR>::fromString(value));
        }
    }
    else
    {
        time_t _time;
        struct tm* timeInfo;
        char format[64];
         
        time(&_time);
        timeInfo = localtime(&_time);
        
        memset(&format[0], 0, 64);
        strftime(format, 64, this->_outputFormat.c_str(), timeInfo);
        
        std::string value(&format[0]);
        
        this->_array.push_back(ElementTraits<VR>::fromString(value));
    }
}

} // namespace translator
    
} // namespace dicomifier
