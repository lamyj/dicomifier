/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bruker/Field.h"

namespace
{

template<typename T>
T item_get(dicomifier::bruker::Field::Item const & item)
{
    return boost::get<T>(item);
}

template<typename T>
bool item_is(dicomifier::bruker::Field::Item const & item)
{
    return (item.type() == typeid(T));
}

pybind11::object as_value(dicomifier::bruker::Field::Item const & item)
{
    auto && type = item.type();
    if(type == typeid(long))
    {
        return pybind11::cast(boost::get<long>(item));
    }
    else if(type == typeid(double))
    {
        return pybind11::cast(boost::get<double>(item));
    }
    else if(type == typeid(std::string))
    {
        return pybind11::cast(boost::get<std::string>(item));
    }
    else
    {
        pybind11::list result;
        for(auto && child: boost::get<dicomifier::bruker::Field::Value>(item))
        {
            result.append(as_value(child));
        }
        return result;
    }
}

pybind11::object as_value(dicomifier::bruker::Field const & field)
{
    pybind11::list result;
    for(auto && item: field.value)
    {
        result.append(as_value(item));
    }
    return result;
}

}

void wrap_Field(pybind11::module & m)
{
    using namespace pybind11;
    using namespace dicomifier::bruker;
    
    auto field = class_<Field>(m, "Field")
        .def_readonly("name", &Field::name)
        .def_readonly("shape", &Field::shape)
        // WARNING: the following moves the data. Use as_value instead.
        // .def_readonly("value", &Field::value)
        .def_property_readonly(
            "value", static_cast<object(*)(Field const &)>(&as_value))
        .def("get_string", &Field::get_string)
        .def("get_int", &Field::get_int)
        .def("get_real", &Field::get_real)
        .def("get_struct", &Field::get_struct)
        .def("is_int", &Field::is_int)
        .def("is_real", &Field::is_real)
        .def("is_string", &Field::is_string)
        .def("is_struct", &Field::is_struct)
        .def(self == self)
        .def(self != self)
    ;
    
    class_<Field::Item>(field, "Item")
        .def("get_int", &item_get<long>)
        .def("get_real", &item_get<double>)
        .def("get_string", &item_get<std::string>)
        .def("get_struct", &item_get<Field::Value>)
        .def("is_int", &item_is<long>)
        .def("is_real", &item_is<double>)
        .def("is_string", &item_is<std::string>)
        .def("is_struct", &item_is<Field::Value>)
        .def_property_readonly("value", static_cast<object(*)(Field::Item const &)>(&as_value))
    ;
}
