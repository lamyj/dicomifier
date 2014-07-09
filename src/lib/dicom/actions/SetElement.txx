/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _011c6f7f_9d18_430c_88d5_d3dc2c015cd6
#define _011c6f7f_9d18_430c_88d5_d3dc2c015cd6

#include <sstream>
#include <stdexcept>
#include <vector>

#include "core/DicomifierException.h"
#include "SetElement.h"

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
::New(DcmDataset * dataset, DcmTagKey tag, ValueType const & value, bool destructDataset)
{
    return Pointer(new Self(dataset, tag, value, destructDataset));
}

template<DcmEVR VR>
typename SetElement<VR>::Pointer
SetElement<VR>
::New(DcmDataset * dataset, DcmTagKey tag, ArrayType const & array, bool destructDataset)
{
    return Pointer(new Self(dataset, tag, array, destructDataset));
}

template<DcmEVR VR>
SetElement<VR>
::~SetElement()
{
    if (this->_destructDataset && this->_dataset != NULL)
    {
        delete this->_dataset;
        this->_dataset = NULL;
    }
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
::set_dataset(DcmDataset * dataset, bool destructDataset)
{
    this->_dataset = dataset;
    this->_destructDataset = destructDataset;
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
            throw DicomifierException("Error: SetElement::run(): Could not get element.");
        }

        OFCondition const set_ok = ElementTraits<VR>::array_setter(element, &this->_array[0], this->_array.size());
        if(set_ok.bad())
        {
            throw DicomifierException("Error: SetElement::run(): Could not set array");
        }
    }
}

template<DcmEVR VR>
SetElement<VR>
::SetElement()
: _dataset(NULL),
  _destructDataset(false)
{
    // Nothing else
}

template<DcmEVR VR>
SetElement<VR>
::SetElement(DcmDataset * dataset, DcmTagKey tag, 
             ValueType const & value, bool destructDataset)
: _dataset(dataset), _tag(tag), _destructDataset(destructDataset)
{
    this->_array = { value };
}

template<DcmEVR VR>
SetElement<VR>
::SetElement(DcmDataset * dataset, DcmTagKey tag, 
             ArrayType const & value, bool destructDataset)
: _dataset(dataset), _tag(tag), _array(value), _destructDataset(destructDataset)
{
    // Nothing else
}

} // namespace actions

} // namespace dicomifier

#endif // _011c6f7f_9d18_430c_88d5_d3dc2c015cd6
