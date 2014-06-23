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

} // namespace conditions

} // namespace router
