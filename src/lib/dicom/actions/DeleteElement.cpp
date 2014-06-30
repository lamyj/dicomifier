/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <sstream>
#include <stdexcept>

#include "core/Factory.h"
#include "DeleteElement.h"

namespace dicomifier
{
    
namespace actions
{
    
DeleteElement
::DeleteElement():
    _dataset(NULL)
{
}

DeleteElement
::DeleteElement(DcmDataset * dataset, DcmTagKey tag):
    _dataset(dataset),
    _tag(tag)
{
}

DeleteElement
::~DeleteElement()
{
    // nothing to do
}

typename DeleteElement::Pointer
DeleteElement
::New()
{
    return Pointer(new Self());
}

typename DeleteElement::Pointer
DeleteElement
::New(DcmDataset * dataset, DcmTagKey tag)
{
    return Pointer(new Self(dataset, tag));
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
                throw std::runtime_error(message.str());
            }
        }
    }
}
    
} // namespace actions
    
} // namespace dicomifier
