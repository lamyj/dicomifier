#include "False.h"

namespace router
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

} // namespace conditions

} // namespace router
