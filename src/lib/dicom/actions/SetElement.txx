/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _011c6f7f_9d18_430c_88d5_d3dc2c015cd6
#define _011c6f7f_9d18_430c_88d5_d3dc2c015cd6

#include "SetElement.h"

#include <sstream>
#include <stdexcept>
#include <vector>

namespace dicomifier
{

namespace actions
{

template<DcmEVR VR>
typename SetElement<VR>::Pointer
SetElement<VR>
::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
typename SetElement<VR>::Pointer
SetElement<VR>
::New(DcmDataset * dataset, DcmTagKey tag, ValueType const & value)
{
    return Pointer(new Self(dataset, tag, value));
}

template<DcmEVR VR>
typename SetElement<VR>::Pointer
SetElement<VR>
::New(DcmDataset * dataset, DcmTagKey tag, ArrayType const & array)
{
    return Pointer(new Self(dataset, tag, array));
}

template<DcmEVR VR>
SetElement<VR>
::~SetElement()
{
    // Nothing to do
}

template<DcmEVR VR>
DcmDataset *
SetElement<VR>
::get_dataset() const
{
    return this->_dataset;
}

template<DcmEVR VR>
void
SetElement<VR>
::set_dataset(DcmDataset * dataset)
{
    this->_dataset = dataset;
}

template<DcmEVR VR>
DcmTag const &
SetElement<VR>
::get_tag() const
{
    return this->_tag;
}

template<DcmEVR VR>
void
SetElement<VR>
::set_tag(DcmTag const & tag)
{
    this->_tag = tag;
}

template<DcmEVR VR>
typename SetElement<VR>::ArrayType const &
SetElement<VR>
::get_value() const
{
    return this->_array;
}

template<DcmEVR VR>
void
SetElement<VR>
::set_value(ValueType const & value)
{
    this->_array = { value };
}


template<DcmEVR VR>
void
SetElement<VR>
::set_value(ArrayType const & array)
{
    this->_array = array;
}

template<DcmEVR VR>
void
SetElement<VR>
::run() const
{
    if(this->_dataset != NULL)
    {
        if(!this->_dataset->tagExists(this->_tag))
        {
            this->_dataset->insertEmptyElement(this->_tag);
        }
        DcmElement * element = NULL;
        OFCondition const element_ok =
            this->_dataset->findAndGetElement(this->_tag, element);

        if(element_ok.bad())
        {
            std::ostringstream message;
            message << "Could not get element: " << element_ok.text();
            throw std::runtime_error(message.str());
        }

        OFCondition const set_ok = ElementTraits<VR>::array_setter(element, &this->_array[0], this->_array.size());
        if(set_ok.bad())
        {
            std::ostringstream message;
            message << "Could not get array: " << set_ok.text();
            throw std::runtime_error(message.str());
        }
    }
}

template<DcmEVR VR>
SetElement<VR>
::SetElement()
: _dataset(NULL)
{
    // Nothing else
}

template<DcmEVR VR>
SetElement<VR>
::SetElement(DcmDataset * dataset, DcmTagKey tag, ValueType const & value)
: _dataset(dataset), _tag(tag)
{
    this->_array = { value };
}

template<DcmEVR VR>
SetElement<VR>
::SetElement(DcmDataset * dataset, DcmTagKey tag, ArrayType const & value)
: _dataset(dataset), _tag(tag), _array(value)
{
    // Nothing else
}

} // namespace actions

} // namespace dicomifier

#endif // _011c6f7f_9d18_430c_88d5_d3dc2c015cd6
