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
        auto const s = boost::get<std::string>(item);
        return pybind11::str(
            PyUnicode_Decode(s.data(), s.length(), "iso-8859-15", nullptr));
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
    
    auto field = class_<Field>(
            m, "Field", R"doc(
                A field (i.e. record in JCAMP-DX jargon) of a Bruker data set:
                container of named variant-typed items.)doc")
        .def_readonly("name", &Field::name, "Name of the field.")
        .def_readonly("shape", &Field::shape, "Shape of the field.")
        // WARNING: the following moves the data. Use as_value instead.
        // .def_readonly("value", &Field::value)
        .def_property_readonly(
            "value", static_cast<object(*)(Field const &)>(&as_value),
            "Value of the field.")
        .def(
            "get_string", &Field::get_string,  arg("index"), 
            "Return a string item, throw an exception if not string-typed.")
        .def(
            "get_int", &Field::get_int, arg("index"), 
            "Return a int-convertible item, throw an exception if not convertible.")
        .def(
            "get_real", &Field::get_real, arg("index"), 
            "Return a real-convertible item, throw an exception if not convertible.")
        .def(
            "get_struct", &Field::get_struct, arg("index"), 
            "Return a struct item, throw an exception if not struct-typed.")
        .def(
            "is_int", &Field::is_int, arg("index"), 
            "Test whether item is an int.")
        .def(
            "is_real", &Field::is_real, arg("index"),
            "Test whether item is a real.")
        .def(
            "is_string", &Field::is_string, arg("index"),
            "Test whether item is a string.")
        .def(
            "is_struct", &Field::is_struct, arg("index"),
            "Test whether item is a struct.")
        .def(self == self)
        .def(self != self)
    ;
    
    class_<Field::Item>(field, "Item")
        .def(
            "get_int", &item_get<long>,
            "Return a int-convertible item, throw an exception if not convertible.")
        .def(
            "get_real", &item_get<double>,
            "Return a real-convertible item, throw an exception if not convertible.")
        .def(
            "get_string", &item_get<std::string>,
            "Return a string item, throw an exception if not string-typed.")
        .def(
            "get_struct", &item_get<Field::Value>,
            "Return a struct item, throw an exception if not struct-typed.")
        .def("is_int", &item_is<long>, "Test whether item is an int.")
        .def("is_real", &item_is<double>, "Test whether item is a real.")
        .def(
            "is_string", &item_is<std::string>, 
            "Test whether item is a string.")
        .def(
            "is_struct", &item_is<Field::Value>, 
            "Test whether item is a struct.")
        .def_property_readonly(
            "value", static_cast<object(*)(Field::Item const &)>(&as_value))
    ;
}
