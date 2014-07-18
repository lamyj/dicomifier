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
ElementMatch<VR>::New(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                      ValueType const & value)
{
    return Pointer(new Self(dataset, tags, value));
}
    
template<DcmEVR VR>
typename ElementMatch<VR>::Pointer
ElementMatch<VR>::New(DcmDataset * dataset, std::vector<TagAndRange> tags, 
                      ArrayType const & array)
{
    return Pointer(new Self(dataset, tags, array));
}

/******************* CONSTRUCTORS *******************/

template<DcmEVR VR>
ElementMatch<VR>
::ElementMatch():
    _dataset(NULL)
{
    // Nothing to do
}

template<DcmEVR VR>
ElementMatch<VR>
::ElementMatch(DcmDataset * dataset, std::vector<TagAndRange> tags, ValueType const & value):
    _dataset(dataset),
    _tags(tags)
{
    this->_array = { value };
}

template<DcmEVR VR>
ElementMatch<VR>
::ElementMatch(DcmDataset * dataset, std::vector<TagAndRange> tags, ArrayType const & array):
    _dataset(dataset),
    _tags(tags),
    _array(array)
{
}

/******************* DESTRUCTOR *******************/

template<DcmEVR VR>
ElementMatch<VR>
::~ElementMatch()
{
    // Nothing to do
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
::set_dataset(DcmDataset * dataset)
{
    this->_dataset = dataset;
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
    if(this->_dataset != NULL)
    {
        return this->matchItem(0, this->_dataset);
    }
    return false;
}

template<DcmEVR VR>
bool 
ElementMatch<VR>
::matchItem(int indice, DcmItem* dataset) const
{
    if (dataset == NULL)
    {
        return false;
    }
    
    TagAndRange tar = this->_tags[indice];
        
    if (indice == this->_tags.size() - 1)
    {
        if (VR != EVR_SQ)
        {
            if(!this->_dataset->tagExists(tar._tag))
            {
                return false;
            }
            
            DcmElement * element = NULL;
            OFCondition const element_ok =
                this->_dataset->findAndGetElement(tar._tag, element);

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
    }
    else
    {
        DcmStack dcmstack;
        OFCondition ret = dataset->findAndGetElements(tar._tag, dcmstack);
        
        if (ret.good())
        {
            bool ret = true;
            
            for (unsigned long i = tar._range._min; i < std::max(tar._range._max, (int)dcmstack.card()); i++)
            {
                DcmObject* obj = dcmstack.elem(i);
                DcmItem* seq = dynamic_cast<DcmItem*>(obj);
                
                if (seq != NULL)
                {
                    ret &= this->matchItem(indice+1, seq);
                }
            }
            return ret;
        }
    }
    return false;
}

} // namespace conditions

} // namespace dicomifier

#endif // _1d031fdc_6f06_4415_8b31_3b9270fb67de
