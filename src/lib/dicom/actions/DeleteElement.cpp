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
#include "DeleteElement.h"

namespace dicomifier
{
    
namespace actions
{
    
DeleteElement
::DeleteElement():
    _dataset(NULL),
    _destructDataset(false)
{
}

DeleteElement
::DeleteElement(DcmDataset * dataset, DcmTagKey tag, bool destructDataset):
    _dataset(dataset),
    _tag(tag),
    _destructDataset(destructDataset)
{
}

DeleteElement
::~DeleteElement()
{
    if (this->_destructDataset && this->_dataset != NULL)
    {
        delete this->_dataset;
        this->_dataset = NULL;
    }
}

typename DeleteElement::Pointer
DeleteElement
::New()
{
    return Pointer(new Self());
}

typename DeleteElement::Pointer
DeleteElement
::New(DcmDataset * dataset, DcmTagKey tag, bool destructDataset)
{
    return Pointer(new Self(dataset, tag, destructDataset));
}

DcmDataset *
DeleteElement
::get_dataset() const
{
    return this->_dataset;
}

void
DeleteElement
::set_dataset(DcmDataset * dataset, bool destructDataset)
{
    this->_dataset = dataset;
    this->_destructDataset = destructDataset;
}

DcmTag const &
DeleteElement
::get_tag() const
{
    return this->_tag;
}

void
DeleteElement
::set_tag(DcmTag const & tag)
{
    this->_tag = tag;
}

void
DeleteElement
::run() const
{
    if (this->_dataset != NULL)
    {
        if (this->_dataset->tagExists(this->_tag))
        {
            OFCondition ret = this->_dataset->findAndDeleteElement(this->_tag);
            
            if (ret.bad())
            {
                std::ostringstream message;
                message << "Could not remove element: " << ret.text();
                throw DicomifierException(message.str());
            }
        }
    }
}
    
} // namespace actions
    
} // namespace dicomifier
