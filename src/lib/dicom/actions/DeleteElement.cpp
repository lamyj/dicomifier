/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>
#include <stdexcept>
#include <algorithm>

#include "core/DicomifierException.h"
#include "core/Factory.h"
#include "DeleteElement.h"
#include "dicom/ElementTraits.h"

namespace dicomifier
{
    
namespace actions
{
    
DeleteElement
::DeleteElement():
    _dataset(NULL)
{
    // Nothing to do
}

DeleteElement
::DeleteElement(DcmDataset * dataset, std::vector<TagAndRange> tags):
    _dataset(dataset),
    _tags(tags)
{
    // Nothing to do
}

DeleteElement
::~DeleteElement()
{
    // Nothing to do
}

typename DeleteElement::Pointer
DeleteElement
::New()
{
    return Pointer(new Self());
}

typename DeleteElement::Pointer
DeleteElement
::New(DcmDataset * dataset, std::vector<TagAndRange> tags)
{
    return Pointer(new Self(dataset, tags));
}

DcmDataset *
DeleteElement
::get_dataset() const
{
    return this->_dataset;
}

void
DeleteElement
::set_dataset(DcmDataset * dataset)
{
    this->_dataset = dataset;
}

void
DeleteElement
::run() const
{
    if (this->_dataset != NULL)
    {
        this->removeItem(0, this->_dataset);
    }
}

void DeleteElement::removeItem(int indice, DcmItem* dataset) const
{
    if (dataset == NULL)
    {
        return;
    }
    
    TagAndRange tar = this->_tags[indice];
        
    if (indice == this->_tags.size() - 1)
    {
        DcmElement* dcmelement = NULL;
        OFCondition ret = dataset->findAndGetElement(tar._tag, dcmelement);
        
        if (ret.good())
        {
            if      (dcmelement->getVR() == EVR_AE) this->removeElement<EVR_AE>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_AS) this->removeElement<EVR_AS>(dataset, dcmelement, tar);
            // TODO: EVR_AT
            else if (dcmelement->getVR() == EVR_CS) this->removeElement<EVR_CS>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_DA) this->removeElement<EVR_DA>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_DS) this->removeElement<EVR_DS>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_DT) this->removeElement<EVR_DT>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_FD) this->removeElement<EVR_FD>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_FL) this->removeElement<EVR_FL>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_IS) this->removeElement<EVR_IS>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_LO) this->removeElement<EVR_LO>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_LT) this->removeElement<EVR_LT>(dataset, dcmelement, tar);
            // TODO: OB
            // TODO: OF
            // TODO: OW
            else if (dcmelement->getVR() == EVR_PN) this->removeElement<EVR_PN>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_SH) this->removeElement<EVR_SH>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_SL) this->removeElement<EVR_SL>(dataset, dcmelement, tar);

            else if (dcmelement->getVR() == EVR_SQ) this->removeElementSQ(dataset, dcmelement, tar);
            
            else if (dcmelement->getVR() == EVR_SS) this->removeElement<EVR_SS>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_UI) this->removeElement<EVR_UI>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_TM) this->removeElement<EVR_TM>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_ST) this->removeElement<EVR_ST>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_UL) this->removeElement<EVR_UL>(dataset, dcmelement, tar);
            // TODO: UN
            else if (dcmelement->getVR() == EVR_US) this->removeElement<EVR_US>(dataset, dcmelement, tar);
            else if (dcmelement->getVR() == EVR_UT) this->removeElement<EVR_UT>(dataset, dcmelement, tar);
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
                    removeItem(indice+1, seq);
                }
            }
        }
    }
}
    
template<DcmEVR VR>
void 
DeleteElement
::removeElement(DcmItem* dataset, DcmElement* dcmelement, TagAndRange const & tagandrange) const
{
    auto values = dicomifier::ElementTraits<VR>::array_getter(dcmelement);

    int size = values.size();
    int pos = tagandrange._range._min;
    for (unsigned int i = tagandrange._range._min; i < std::max(tagandrange._range._max, size); i++)
    {
        values.erase(values.begin() + pos);
    }
    
    if (values.size() == 0)
    {
        dataset->findAndDeleteElement(tagandrange._tag);
    }
    else
    {
        dicomifier::ElementTraits<VR>::array_setter(dcmelement, &values[0], values.size());
    }
}

void 
DeleteElement
::removeElementSQ(DcmItem* dataset, DcmElement* dcmelement, TagAndRange const & tagandrange) const
{
    DcmSequenceOfItems* seq = dynamic_cast<DcmSequenceOfItems*>(dcmelement);
    
    std::vector<DcmItem*> vect;
    for (unsigned int i = tagandrange._range._min; 
         i < std::max(tagandrange._range._max, (int)dcmelement->getVR()); 
         i++)
    {
        vect.push_back(seq->getItem(i));
    }
    
    if (vect.size() == (int)dcmelement->getVR())
    {
        dataset->findAndDeleteElement(tagandrange._tag);
    }
    else
    {
        for (auto item : vect)
        {
            seq->remove(item);
        }
    }
}
    
} // namespace actions
    
} // namespace dicomifier
