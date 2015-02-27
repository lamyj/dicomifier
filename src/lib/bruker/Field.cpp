/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Field.h"

#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>

namespace dicomifier
{
    
namespace bruker
{

Field
::Field()
: name(), shape(), value()
{
}

Field
::Field(std::string const & name, Shape const & shape, Value const & value)
: name(name), shape(shape), value(value)
{
}

Field::Shape::size_type
Field
::get_size() const
{
    return this->value.size();
}
    
std::string const &
Field
::get_string(unsigned int index) const
{
    return boost::get<std::string>(this->value[index]);
}

long
Field
::get_int(unsigned int index) const
{
    try
    {
        return boost::get<long>(this->value[index]);
    }
    catch(boost::bad_get const & e)
    {
        return boost::lexical_cast<long>(
            boost::get<std::string>(this->value[index]));
    }
}

float
Field
::get_float(unsigned int index) const
{
    try
    {
        return boost::get<float>(this->value[index]);
    }
    catch(boost::bad_get const & e)
    {
        try
        {
            return boost::get<long>(this->value[index]);
        }
        catch(boost::bad_get const & e)
        {
            return boost::lexical_cast<float>(
                boost::get<std::string>(this->value[index]));
        }
    }
}

template<>
std::string
Field
::get<std::string>(unsigned int index) const
{
    return this->get_string(index);
}

template<>
long
Field
::get<long>(unsigned int index) const
{
    return this->get_int(index);
}

template<>
float
Field
::get<float>(unsigned int index) const
{
    return this->get_float(index);
}

} // namespace bruker

} // namespace dicomifier
