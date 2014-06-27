#include <sstream>
#include <stdexcept>

#include "core/Factory.h"
#include "DeleteElement.h"

namespace router
{
    
namespace actions
{

static unsigned int const registration = Factory::get_instance().register_<DeleteElement>();
    
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
        OFCondition ret = this->_dataset->findAndDeleteElement(this->_tag);
        
        if (ret.bad())
        {
            std::ostringstream message;
            message << "Could not remove element: " << ret.text();
            throw std::runtime_error(message.str());
        }
    }
}
    
} // namespace actions
    
} // namespace router
