/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>

#include <boost/lexical_cast.hpp>

#include "bruker/BrukerFieldData.h"
#include "BrukerField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename BrukerField<VR>::Pointer
BrukerField<VR>
::New()
{
    return Pointer(new Self());
}
    
template<DcmEVR VR>
typename BrukerField<VR>::Pointer
BrukerField<VR>
::New(std::string const & brukerFieldName)
{
    return Pointer(new Self(brukerFieldName, Range()));
}
    
template<DcmEVR VR>
typename BrukerField<VR>::Pointer
BrukerField<VR>
::New(std::string const & brukerFieldName, Range range)
{
    return Pointer(new Self(brukerFieldName, range));
}
    
template<DcmEVR VR>
BrukerField<VR>
::BrukerField()
    :SubTag<VR>(), _brukerFieldName("")
{
    // Nothing to do
}
    
template<DcmEVR VR>
BrukerField<VR>
::BrukerField(std::string const & brukerFieldName, Range range)
    :SubTag<VR>(), _brukerFieldName(brukerFieldName), _range(range)
{
    // Nothing to do
}

template<DcmEVR VR>
BrukerField<VR>
::~BrukerField()
{
    // Nothing to do
}

template<DcmEVR VR>
void
BrukerField<VR>
::run(DcmDataset* dataset,
      dicomifier::bruker::BrukerDataset* brukerdataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Empty Bruker Dataset");
    }
    
    if (brukerdataset->HasFieldData(this->_brukerFieldName))
    {
        dicomifier::bruker::BrukerFieldData::Pointer fielddata = 
            brukerdataset->GetFieldData(this->_brukerFieldName);
        
        if (fielddata->get_data_type() != "BrukerFieldData")
        {
            for (auto count = this->_range._min; 
                 count < std::min(fielddata->get_values_number(), this->_range._max); 
                 count++)
            {
                // Warning: cannot lexical_cast String to OFString
                this->_array.push_back(ElementTraits<VR>::fromString(fielddata->get_string(count)));
            }
        }
    }
}

} // namespace translator
    
} // namespace dicomifier
