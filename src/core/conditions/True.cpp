#include "core/Factory.h"
#include "True.h"

namespace router
{

namespace conditions
{

True
::~True()
{
    // Nothing to do
}

bool
True
::eval() const
{
    return true;
}

True
::True()
{
    // Nothing to do
}

static unsigned int const registration = Factory::get_instance().register_<True>();

} // namespace conditions

} // namespace router
