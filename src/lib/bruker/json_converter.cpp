/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "json_converter.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "core/DicomifierException.h"

namespace dicomifier
{

namespace bruker
{

Json::Value
as_json_value(Field::Item const & item)
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

template<typename TType>
std::string
value_as_string(TType value)
{
    return boost::lexical_cast<std::string>(value);
}

std::string
as_string(Json::Value const & data_set)
{
    std::stringstream result;
    switch (data_set.type())
    {
    case Json::ValueType::arrayValue:
    {
        result << "[";

        for (auto it = data_set.begin(); it != data_set.end(); ++it)
        {
            result << as_string(*it);

            if (it != --data_set.end())
            {
                result << ", ";
            }
        }

        result << "]";

        break;
    }
    case Json::ValueType::intValue:
    {
        result << value_as_string(data_set.asInt());
        break;
    }
    case Json::ValueType::realValue:
    {
        std::string value = value_as_string(data_set.asFloat());
        boost::replace_all(value, ",", ".");
        result << value;
        break;
    }
    case Json::ValueType::uintValue:
    {
        result << value_as_string(data_set.asUInt());
        break;
    }
    case Json::ValueType::stringValue:
    {
        std::string value = data_set.asString();
        boost::replace_all(value, "\"", "\\\"");
        boost::replace_all(value, "\r", "");
        result << "\"" << value << "\"";
        break;
    }
    case Json::ValueType::booleanValue:
    {
        result << value_as_string(data_set.asBool());
        break;
    }
    case Json::ValueType::objectValue:
    {
        result << "{\n";

        for (auto it = data_set.begin(); it != data_set.end(); ++it)
        {
            result << "\"" << it.memberName() << "\" : " << as_string(*it);

            if (it != --data_set.end())
            {
                result << ",";
            }

            result << "\n";
        }

        result << "}";
        break;
    }
    case Json::ValueType::nullValue:
    {
        result << "null";
        break;
    }
    default:
    {
        throw DicomifierException("Unknown Json::ValueType");
    }
    }

    return result.str();
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
        std::string const name = it.memberName();
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
