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
    if (this->_dataset == NULL)
    {
        throw DicomifierException("Dataset is NULL");
    }
    
    this->emptyItem(0, this->_dataset);
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
        else if (std::string(ret.text()) == "Tag not found")
        {
            dataset->insertEmptyElement(tar._tag);
        }
    }
    else
    {
        DcmSequenceOfItems* dcmseqitems = NULL;
        OFCondition ret = dataset->findAndGetSequence(tar._tag, dcmseqitems);
        
        if (ret.good())
        {
            for (unsigned long i = tar._range._min; i < std::max(tar._range._max, (int)dcmseqitems->card()); i++)
            {
                DcmItem* seq = dcmseqitems->getItem(i);
                
                if (seq != NULL)
                {
                    emptyItem(indice+1, seq);
                }
            }
        }
    }
}

/****************************** ActionEmptyElement ********************/

template<>
void 
EmptyElement::ActionEmptyElement
::run<EVR_SQ>() const
{
    dataset->insertSequenceItem(tagandrange._tag, NULL);
}

template<DcmEVR VR> 
void 
EmptyElement::ActionEmptyElement
::run() const
{
    dataset->insertEmptyElement(tagandrange._tag, true);
}
    
} // namespace actions
    
} // namespace dicomifier
