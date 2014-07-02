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
    
EmptyElement
::EmptyElement():
    _dataset(NULL),
    _destructDataset(false)
{
}

EmptyElement
::EmptyElement(DcmDataset * dataset, DcmTagKey tag, bool destructDataset):
    _dataset(dataset),
    _tag(tag),
    _destructDataset(destructDataset)
{
}

EmptyElement
::~EmptyElement()
{
    if (this->_destructDataset && this->_dataset != NULL)
    {
        delete this->_dataset;
        this->_dataset = NULL;
    }
}

typename EmptyElement::Pointer
EmptyElement
::New()
{
    return Pointer(new Self());
}

typename EmptyElement::Pointer
EmptyElement
::New(DcmDataset * dataset, DcmTagKey tag, bool destructDataset)
{
    return Pointer(new Self(dataset, tag, destructDataset));
}

DcmDataset *
EmptyElement
::get_dataset() const
{
    return this->_dataset;
}

void
EmptyElement
::set_dataset(DcmDataset * dataset, bool destructDataset)
{
    this->_dataset = dataset;
    this->_destructDataset = destructDataset;
}

DcmTag const &
EmptyElement
::get_tag() const
{
    return this->_tag;
}

void
EmptyElement
::set_tag(DcmTag const & tag)
{
    this->_tag = tag;
}

void
EmptyElement
::run() const
{
    if (this->_dataset != NULL)
    {
        OFCondition ret = this->_dataset->insertEmptyElement(this->_tag, true);
        
        if (ret.bad())
        {
            std::ostringstream message;
            message << "Could not insert empty element: " << ret.text();
            throw DicomifierException(message.str());
        }
    }
}
    
} // namespace actions
    
} // namespace dicomifier
