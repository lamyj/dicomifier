/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DateTime.h"
#include "DateTimeFilter.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename DateTimeFilter<VR>::Pointer
DateTimeFilter<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
typename DateTimeFilter<VR>::Pointer
DateTimeFilter<VR>
::New(Tag::Pointer tag, std::string const & outputformat)
{
    return Pointer(new Self(tag, outputformat));
}

template<DcmEVR VR>
DateTimeFilter<VR>
::DateTimeFilter()
    :SubTag<VR>(), _tag(NULL), _outputFormat("")
{
    // Nothing to do
}

template<DcmEVR VR>
DateTimeFilter<VR>
::DateTimeFilter(Tag::Pointer tag, std::string const & outputformat)
    :SubTag<VR>(), _tag(tag), _outputFormat(outputformat)
{
    // Nothing to do
}

template<DcmEVR VR>
DateTimeFilter<VR>
::~DateTimeFilter()
{
    // Nothing to do
}

template<DcmEVR VR>
void
DateTimeFilter<VR>
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (this->_tag == NULL)
    {
        throw DicomifierException("Cannot run DateTimeFilter.");
    }

    this->_array.clear();

    typename SubTag<VR>::Pointer subtag =
        std::dynamic_pointer_cast<SubTag<VR>>(this->_tag);

    subtag->run(brukerdataset, generator, dataset);

    auto array = subtag->get_array();

    for (int i = 0; i < array.size(); i++)
    {
        std::string temp = ElementTraits<VR>::toString(array[i]);;

        std::string format = "";
        auto ldt = dicomifier::string_to_local_date_time(temp, format);
        std::string result = dicomifier::local_date_time_to_string(ldt, this->_outputFormat);

        this->_array.push_back(ElementTraits<VR>::fromString(result));
    }
}

} // namespace translator
    
} // namespace dicomifier
