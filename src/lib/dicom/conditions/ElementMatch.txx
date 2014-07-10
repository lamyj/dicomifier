/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _1d031fdc_6f06_4415_8b31_3b9270fb67de
#define _1d031fdc_6f06_4415_8b31_3b9270fb67de

#include <sstream>
#include <stdexcept>

#include "ElementMatch.h"

namespace dicomifier
{
    
namespace conditions
{

/******************* Functions NEW *******************/

template<DcmEVR VR>
typename ElementMatch<VR>::Pointer
ElementMatch<VR>::New()
{
    return Pointer(new Self());
}

template<DcmEVR VR>
typename ElementMatch<VR>::Pointer
ElementMatch<VR>::New(DcmDataset * dataset, DcmTagKey tag, 
                      ValueType const & value, bool destructDataset)
{
    return Pointer(new Self(dataset, tag, value, destructDataset));
}
    
template<DcmEVR VR>
typename ElementMatch<VR>::Pointer
ElementMatch<VR>::New(DcmDataset * dataset, DcmTagKey tag, 
                      ArrayType const & array, bool destructDataset)
{
    return Pointer(new Self(dataset, tag, array, destructDataset));
}

/******************* CONSTRUCTORS *******************/

template<DcmEVR VR>
ElementMatch<VR>
::ElementMatch():
    _dataset(NULL),
    _destructDataset(false)
{
    // Nothing to do
}

template<DcmEVR VR>
ElementMatch<VR>
::ElementMatch(DcmDataset * dataset, DcmTagKey tag, ValueType const & value, bool destructDataset):
    _dataset(dataset),
    _tag(tag),
    _destructDataset(destructDataset)
{
    this->_array = { value };
}

template<DcmEVR VR>
ElementMatch<VR>
::ElementMatch(DcmDataset * dataset, DcmTagKey tag, ArrayType const & array, bool destructDataset):
    _dataset(dataset),
    _tag(tag),
    _array(array),
    _destructDataset(destructDataset)
{
}

/******************* DESTRUCTOR *******************/

template<DcmEVR VR>
ElementMatch<VR>
::~ElementMatch()
{
    if (this->_destructDataset && this->_dataset != NULL)
    {
        delete this->_dataset;
        this->_dataset = NULL;
    }
}

/******************* ACCESSORS *******************/

template<DcmEVR VR>
DcmDataset *
ElementMatch<VR>
::get_dataset() const
{
    return this->_dataset;
}

template<DcmEVR VR>
void
ElementMatch<VR>
::set_dataset(DcmDataset * dataset, bool destructDataset)
{
    this->_dataset = dataset;
    this->_destructDataset = destructDataset;
}

template<DcmEVR VR>
DcmTag const &
ElementMatch<VR>
::get_tag() const
{
    return this->_tag;
}

template<DcmEVR VR>
void
ElementMatch<VR>
::set_tag(DcmTag const & tag)
{
    this->_tag = tag;
}

template<DcmEVR VR>
typename ElementMatch<VR>::ArrayType const &
ElementMatch<VR>
::get_value() const
{
    return this->_array;
}

template<DcmEVR VR>
void
ElementMatch<VR>
::set_value(ValueType const & value)
{
    this->_array = { value };
}

template<DcmEVR VR>
void
ElementMatch<VR>
::set_value(ArrayType const & array)
{
    this->_array = array;
}

/******************* Other Functions *******************/

template<DcmEVR VR>
bool
ElementMatch<VR>
::eval() const
{
    // dataset not empty
    if(this->_dataset == NULL)
    {
        return false;
    }
   
    // Tag Exist
    if( ! this->_dataset->tagExists(this->_tag))
    {
        return false;
    }
   
    // Get the element
    DcmElement * element = NULL;
    OFCondition const element_ok =
        this->_dataset->findAndGetElement(this->_tag, element);

    if(element_ok.bad())
    {
        return false;
    }
    
    // Get values
    auto const vect = ElementTraits<VR>::array_getter(element);
    
    // Compare Size
    if (vect.size() != element->getVM() ||
        this->_array.size() != vect.size())
    {
        return false;
    }
    
    // Compare values    
    return this->_array == vect;
}

} // namespace conditions

} // namespace dicomifier

#endif // _1d031fdc_6f06_4415_8b31_3b9270fb67de
