/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "boost/regex.hpp"

#include "RegExFilter.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename RegExFilter<VR>::Pointer
RegExFilter<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
typename RegExFilter<VR>::Pointer
RegExFilter<VR>
::New(Tag::Pointer tag, std::string const & expression)
{
    return Pointer(new Self(tag, expression));
}

template<DcmEVR VR>
RegExFilter<VR>
::RegExFilter()
    :SubTag<VR>(), _tag(NULL)
{
    // Nothing to do
}

template<DcmEVR VR>
RegExFilter<VR>
::RegExFilter(Tag::Pointer tag, std::string const & expression)
    :SubTag<VR>(), _tag(tag), _expression(expression)
{
    // Nothing to do
}

template<DcmEVR VR>
RegExFilter<VR>
::~RegExFilter()
{
    // Nothing to do
}

template<DcmEVR VR>
void
RegExFilter<VR>
::run(DcmDataset* dataset,
      dicomifier::bruker::BrukerDataset* brukerdataset)
{
    typename SubTag<VR>::Pointer subtag = 
        std::dynamic_pointer_cast<SubTag<VR>>(this->_tag);

    subtag->run(dataset, brukerdataset);
    
    auto array = subtag->get_array();
    
    boost::regex currentRegEx(this->_expression);
    
    for (int i = 0; i < array.size(); i++)
    {
        std::string temp = ElementTraits<VR>::toString(array[i]);
        boost::cmatch what;
        if (regex_match(temp.c_str(), what, currentRegEx) && temp != "")
        {
            std::string value = "";
            for (int count = 1; count < what.size(); count++)
            {
                value += what[count];
            }
            this->_array.push_back(ElementTraits<VR>::fromString(value));
        }
        else
        {
            this->_array.push_back(array[i]);
        }
    }
}

} // namespace translator
    
} // namespace dicomifier
