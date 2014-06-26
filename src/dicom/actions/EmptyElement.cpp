#include <sstream>
#include <stdexcept>

#include "EmptyElement.h"

namespace router
{
    
namespace actions
{
    
EmptyElement
::EmptyElement():
    _dataset(NULL)
{
}

EmptyElement
::EmptyElement(DcmDataset * dataset, DcmTagKey tag):
    _dataset(dataset),
    _tag(tag)
{
}

EmptyElement
::~EmptyElement()
{
    // nothing to do
}

typename EmptyElement::Pointer
EmptyElement
::New()
{
    return Pointer(new Self());
}

typename EmptyElement::Pointer
EmptyElement
::New(DcmDataset * dataset, DcmTagKey tag)
{
    return Pointer(new Self(dataset, tag));
}

DcmDataset *
EmptyElement
::get_dataset() const
{
    return this->_dataset;
}

void
EmptyElement
::set_dataset(DcmDataset * dataset)
{
    this->_dataset = dataset;
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
            throw std::runtime_error(message.str());
        }
    }
}
    
} // namespace actions
    
} // namespace router
