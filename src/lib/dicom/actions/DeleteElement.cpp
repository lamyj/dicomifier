/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "core/Factory.h"
#include "DeleteElement.h"

namespace dicomifier
{
    
namespace actions
{

/****************************** Constructor *****************************/

DeleteElement
::DeleteElement():
    Action(), _dataset(NULL)
{
    // Nothing to do
}

DeleteElement
::DeleteElement(DcmDataset * dataset, std::vector<TagAndRange> tags):
    Action(), _dataset(dataset), _tags(tags)
{
    // Nothing to do
}

/****************************** Destructor ******************************/

DeleteElement
::~DeleteElement()
{
    // Nothing to do
}

/****************************** Other Functions *************************/

void
DeleteElement
::run() const
{
    if (this->_dataset == NULL)
    {
        throw DicomifierException("Dataset is NULL");
    }
    
    this->removeItem(0, this->_dataset);
}

void
DeleteElement
::removeItem(int indice, DcmItem* dataset) const
{
    if (dataset == NULL)
    {
        return;
    }
    
    TagAndRange tar = this->_tags[indice];
        
    if (indice == this->_tags.size() - 1)
    {
        DcmElement* dcmelement = NULL;
        OFCondition const ret = dataset->findAndGetElement(tar._tag, dcmelement);
        
        if (ret.good() && dcmelement != NULL)
        {
            ActionDeleteElement action;
            action.dataset =  dataset;
            action.tagandrange = tar;
            action.element = dcmelement;
            
            dicomifier::vr_dispatch(action, dcmelement->getVR());
        }
    }
    else
    {
        DcmStack dcmstack;
        OFCondition const ret = dataset->findAndGetElements(tar._tag, dcmstack);
        
        if (ret.good())
        {
            for (unsigned long i = tar._range._min;
                 i < std::max(tar._range._max, (int)dcmstack.card());
                 i++)
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

/****************************** ActionDeleteElement *********************/

template<>
void 
DeleteElement::ActionDeleteElement
::run<EVR_SQ>() const
{
    DcmSequenceOfItems* seq = dynamic_cast<DcmSequenceOfItems*>(element);
    
    std::vector<DcmItem*> vect;
    for (unsigned int i = tagandrange._range._min; 
         i < std::min(tagandrange._range._max, (int)element->getVM()); 
         i++)
    {
        vect.push_back(seq->getItem(i));
    }
    
    if (vect.size() == (int)element->getVM())
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

template<DcmEVR VR> 
void 
DeleteElement::ActionDeleteElement
::run() const
{
    auto values = dicomifier::ElementTraits<VR>::array_getter(element);

    int size = values.size();
    int pos = tagandrange._range._min;
    for (unsigned int i = tagandrange._range._min; 
         i < std::min(tagandrange._range._max, size); 
         i++)
    {
        values.erase(values.begin() + pos);
    }
    
    if (values.size() == 0)
    {
        dataset->findAndDeleteElement(tagandrange._tag);
    }
    else
    {
        dicomifier::ElementTraits<VR>::array_setter(element,
                                                    &values[0],
                                                    values.size());
    }
}
    
} // namespace actions
    
} // namespace dicomifier
