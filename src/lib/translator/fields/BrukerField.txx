/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

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
    return Pointer(new Self(brukerFieldName));
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
::BrukerField(std::string const & brukerFieldName)
    :SubTag<VR>(), _brukerFieldName(brukerFieldName)
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
        dicomifier::bruker::BrukerFieldData fielddata = brukerdataset->GetFieldData(this->_brukerFieldName);
        
        if (fielddata.GetDataType() == "string")
        {
            for (auto value : fielddata.GetStringValue())
            {
                dicomifier::bruker::BrukerFieldData::CleanString(value);
                // Warning: cannot lexical_cast String to OFString
                this->_array.push_back(ElementTraits<VR>::fromString(value));
            }
        }
        else if (fielddata.GetDataType() == "int")
        {
            for (auto value : fielddata.GetIntValue())
            {
                this->_array.push_back(boost::lexical_cast<ValueType>(value));
            }
        }
        else if (fielddata.GetDataType() == "float")
        {
            for (auto value : fielddata.GetDoubleValue())
            {
                this->_array.push_back(boost::lexical_cast<ValueType>(value));
            }
        }
    }
}

} // namespace translator
    
} // namespace dicomifier
