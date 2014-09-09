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
        dicomifier::bruker::BrukerFieldData fielddata = brukerdataset->GetFieldData(this->_brukerFieldName);
        
        int count = 0;
        
        if (fielddata.GetDataType() == "string")
        {
            for (auto value : fielddata.GetStringValue())
            {
                if ((this->_range._max != 0 && count >= this->_range._min && 
                     count < this->_range._max) || 
                    (this->_range._max == 0 && this->_range._min == 0))
                {
                    dicomifier::bruker::BrukerFieldData::CleanString(value);
                    // Warning: cannot lexical_cast String to OFString
                    this->_array.push_back(ElementTraits<VR>::fromString(value));
                }
                count++;
            }
        }
        else if (fielddata.GetDataType() == "int")
        {
            for (auto value : fielddata.GetIntValue())
            {
                if ((this->_range._max != 0 && count >= this->_range._min && 
                     count < this->_range._max) || 
                    (this->_range._max == 0 && this->_range._min == 0))
                {
                    //this->_array.push_back(boost::lexical_cast<ValueType>(value));
                    std::stringstream tempstringstream;
                    tempstringstream << value;
                    this->_array.push_back(ElementTraits<VR>::fromString(tempstringstream.str()));
                }
                count++;
            }
        }
        else if (fielddata.GetDataType() == "float")
        {
            for (auto value : fielddata.GetDoubleValue())
            {
                if ((this->_range._max != 0 && count >= this->_range._min && 
                     count < this->_range._max) || 
                    (this->_range._max == 0 && this->_range._min == 0))
                {
                    this->_array.push_back(boost::lexical_cast<ValueType>(value));
                }
                count++;
            }
        }
    }
}

} // namespace translator
    
} // namespace dicomifier
