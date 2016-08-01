/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Field.h"

#include <string>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
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
        return std::stol(boost::get<std::string>(this->value[index]));
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
            return std::stof(boost::get<std::string>(this->value[index]));
        }
    }
}

Field::Value
Field
::get_struct(unsigned int index) const
{
    return boost::get<Value>(this->value[index]);
}

bool
Field
::is_int(unsigned int index) const
{
    return this->value[index].type() == typeid(long);
}

bool
Field
::is_float(unsigned int index) const
{
    return this->value[index].type() == typeid(float);
}

bool
Field
::is_string(unsigned int index) const
{
    return this->value[index].type() == typeid(std::string);
}

bool
Field
::is_struct(unsigned int index) const
{
    return this->value[index].type() == typeid(Field::Value);
}

} // namespace bruker

} // namespace dicomifier
