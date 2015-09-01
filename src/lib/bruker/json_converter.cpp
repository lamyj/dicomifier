/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/lexical_cast.hpp>

#include "core/DicomifierException.h"
#include "json_converter.h"

namespace dicomifier
{

namespace bruker
{

Json::Value as_json_value(Field::Item const & item)
{
    // INT
    if (item.type() == typeid(long))
    {
        return (Json::Int64)boost::get<long>(item);
    }

    // FLOAT
    if (item.type() == typeid(float))
    {
        return boost::get<float>(item);
    }

    // STRING
    if (item.type() == typeid(std::string))
    {
        return boost::get<std::string>(item);
    }

    // else, it's a recursive field
    if (item.type() == typeid(Field::Value))
    {
        Json::Value json;
        for (Field::Item const subitem : boost::get<Field::Value>(item))
        {
            json.append(as_json_value(subitem));
        }
        return json;
    }

    // Never happen
    throw DicomifierException("Unknown type");
}

Json::Value as_json(Dataset const & data_set)
{
    Json::Value json;

    for(auto const & it: data_set)
    {
        auto const & name = it.first;
        auto const & field = it.second;

        for (Field::Item const item : field.value)
        {
            json[name].append(as_json_value(item));
        }
    }

    return json;
}

} // namespace bruker

} // namespace dicomifier
