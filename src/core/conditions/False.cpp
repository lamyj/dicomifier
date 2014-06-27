#include "core/Factory.h"
#include "False.h"

namespace dicomifier
{

namespace conditions
{

False
::~False()
{
    // Nothing to do
}

bool
False
::eval() const
{
    return false;
}

False
::False()
{
    // Nothing to do
}

static unsigned int const registration = Factory::get_instance().register_<False>();

} // namespace conditions

} // namespace dicomifier
