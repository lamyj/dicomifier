/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "json_converter.h"

#include <string>

#include <json/json.h>

#include "bruker/Dataset.h"
#include "bruker/Field.h"
#include "core/DicomifierException.h"

namespace dicomifier
{

namespace bruker
{

Json::Value
as_json_value(Field::Item const & item)
{
    if(item.type() == typeid(long))
    {
        return (Json::Int64)boost::get<long>(item);
    }
    else if(item.type() == typeid(float))
    {
        return boost::get<float>(item);
    }
    else if(item.type() == typeid(std::string))
    {
        return boost::get<std::string>(item);
    }
    else if(item.type() == typeid(Field::Value))
    {
        Json::Value json;
        for(auto const & subitem : boost::get<Field::Value>(item))
        {
            json.append(as_json_value(subitem));
        }
        return json;
    }
    else
    {
        throw DicomifierException("Unknown type");
    }
}

Json::Value
as_json(Dataset const & data_set)
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

Field::Item as_field_item(Json::Value const & json)
{
    Field::Item item;

    if(json.isInt())
    {
        item = long(json.asInt());
    }
    else if(json.isDouble())
    {
        item = float(json.asDouble());
    }
    else if(json.isString())
    {
        item = json.asString();
    }
    else if(json.isArray())
    {
        Field::Value sub_items;
        for(auto const & sub_item: json)
        {
            sub_items.push_back(as_field_item(sub_item));
        }
        item = sub_items;
    }
    else
    {
        throw DicomifierException("Unknown item type");
    }

    return item;
}

Dataset as_dataset(Json::Value const & json)
{
    Dataset dataset;

    for(Json::Value::const_iterator it=json.begin(); it != json.end(); ++it)
    {
#if JSONCPP_VERSION_HEXA >= 0x160
        auto const name = it.name();
#else
        std::string const name = it.memberName();
#endif
        auto const & json_element = *it;

        if(!json_element.isArray())
        {
            throw DicomifierException("Not an array: "+name);
        }

        Field::Value items;
        for(auto const & item: json_element)
        {
            items.push_back(as_field_item(item));
        }

        dataset.set_field(Field(name, Field::Shape(), items));
    }

    return dataset;
}

} // namespace bruker

} // namespace dicomifier
