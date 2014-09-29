/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <ctime>

#include "TimeGenerator.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename TimeGenerator<VR>::Pointer
TimeGenerator<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
TimeGenerator<VR>
::TimeGenerator()
    :SubTag<VR>()
{
    // Nothing to do
}

template<DcmEVR VR>
TimeGenerator<VR>
::~TimeGenerator()
{
    // Nothing to do
}

template<DcmEVR VR>
void
TimeGenerator<VR>
::run(DcmDataset* dataset,
      dicomifier::bruker::BrukerDataset* brukerdataset)
{
    time_t _time;
    struct tm* timeInfo;
    char format[8];
     
    time(&_time);
    timeInfo = localtime(&_time);
    
    memset(&format[0], 0, 8);
    strftime(format, 8, "%H%M%S", timeInfo);
    
    std::string value(&format[0]);
    
    this->_array.push_back(ElementTraits<VR>::fromString(value));
}

} // namespace translator
    
} // namespace dicomifier
