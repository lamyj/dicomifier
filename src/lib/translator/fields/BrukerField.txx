/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "BrukerField.h"
#include "dicom/ElementTraits.h"
#include "translator/VRToField.h"

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
::run(dicomifier::bruker::Dataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmItem* dataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Empty Bruker Dataset");
    }
    // Clean residual values
    this->_array.clear();
    
    if (brukerdataset->has_field(this->_brukerFieldName))
    {
        auto const & fielddata = 
            brukerdataset->get_field(this->_brukerFieldName);
        
        for(unsigned int i = this->_range._min;
            i < std::min((int)fielddata.get_size(), this->_range._max);
            ++i)
        {
            typedef typename VRToFieldType<VR>::Type FieldType;
            typedef typename ElementTraits<VR>::ValueType VRType;
            
            this->_array.push_back(
                convert_field_item<FieldType, VRType>(
                    fielddata.template get<FieldType>(i)));
        }
    }
}

} // namespace translator
    
} // namespace dicomifier
