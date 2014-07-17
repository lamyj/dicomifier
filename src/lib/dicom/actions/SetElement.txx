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
::New(DcmDataset * dataset, std::vector<TagAndRange> tags, ValueType const & value)
{
    return Pointer(new Self(dataset, tags, value));
}

template<DcmEVR VR>
typename SetElement<VR>::Pointer
SetElement<VR>
::New(DcmDataset * dataset, std::vector<TagAndRange> tags, ArrayType const & array)
{
    return Pointer(new Self(dataset, tags, array));
}

template<DcmEVR VR>
SetElement<VR>
::~SetElement()
{
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
        this->setItem(0, this->_dataset);
    }
}

template<DcmEVR VR>
void 
SetElement<VR>
::setItem(int indice, DcmItem* dataset) const
{
    if (dataset == NULL)
    {
        return;
    }
    
    TagAndRange tar = this->_tags[indice];
        
    if (indice == this->_tags.size() - 1)
    {
        if (VR != EVR_SQ)
        {
            if(!this->_dataset->tagExists(tar._tag))
            {
                this->_dataset->insertEmptyElement(tar._tag);
            }
            DcmElement * element = NULL;
            OFCondition const element_ok =
                this->_dataset->findAndGetElement(tar._tag, element);

            if(element_ok.bad())
            {
                throw DicomifierException("SetElement::run(): Could not get element.");
            }

            OFCondition const set_ok = ElementTraits<VR>::array_setter(element, &this->_array[0], this->_array.size());
            if(set_ok.bad())
            {
                throw DicomifierException("SetElement::run(): Could not set array");
            }
        }
    }
    else
    {
        DcmStack dcmstack;
        OFCondition ret = dataset->findAndGetElements(tar._tag, dcmstack);
        
        if (ret.good())
        {
            for (unsigned long i = tar._range._min; i < std::max(tar._range._max, (int)dcmstack.card()); i++)
            {
                DcmObject* obj = dcmstack.elem(i);
                DcmItem* seq = dynamic_cast<DcmItem*>(obj);
                
                if (seq != NULL)
                {
                    setItem(indice+1, seq);
                }
            }
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
::SetElement(DcmDataset * dataset, std::vector<TagAndRange> tags, 
             ValueType const & value)
: _dataset(dataset), _tags(tags)
{
    this->_array = { value };
}

template<DcmEVR VR>
SetElement<VR>
::SetElement(DcmDataset * dataset, std::vector<TagAndRange> tags, 
             ArrayType const & value)
: _dataset(dataset), _tags(tags), _array(value)
{
    // Nothing else
}

} // namespace actions

} // namespace dicomifier

#endif // _011c6f7f_9d18_430c_88d5_d3dc2c015cd6
