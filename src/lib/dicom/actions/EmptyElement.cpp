/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>
#include <stdexcept>

#include "core/DicomifierException.h"
#include "core/Factory.h"
#include "EmptyElement.h"

namespace dicomifier
{
    
namespace actions
{

/****************************** Constructor ***************************/

EmptyElement
::EmptyElement():
    _dataset(NULL)
{
    // Nothing to do
}

EmptyElement
::EmptyElement(DcmDataset * dataset, std::vector<TagAndRange> tags):
    _dataset(dataset),
    _tags(tags)
{
    // Nothing to do
}


/****************************** Destructor ****************************/

EmptyElement
::~EmptyElement()
{
    // Nothing to do
}

/****************************** Other Functions ***********************/

void
EmptyElement
::run() const
{
    if (this->_dataset != NULL)
    {
        this->emptyItem(0, this->_dataset);
    }
}

void EmptyElement::emptyItem(int indice, DcmItem* dataset) const
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
            ActionEmptyElement action;
            action.dataset =  dataset;
            action.tagandrange = tar;
            action.element = dcmelement;
            
            dicomifier::vr_dispatch(action, dcmelement->getVR());
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
                    emptyItem(indice+1, seq);
                }
            }
        }
    }
}

/****************************** ActionEmptyElement ********************/

template<DcmEVR VR> 
void 
EmptyElement::ActionEmptyElement
::run() const
{
    dataset->insertEmptyElement(tagandrange._tag, true);
}
    
} // namespace actions
    
} // namespace dicomifier
