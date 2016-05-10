/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

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

}

void wrap_Field()
{
    using namespace boost::python;
    using namespace dicomifier::bruker;
    
    scope field_scope = class_<Field>("Field", no_init)
        .def_readwrite("name", &Field::name)
        .def_readwrite("shape", &Field::shape)
        .def("get_size", &Field::get_size)
        .def(
            "get_string", &Field::get_string, 
            return_value_policy<copy_const_reference>())
        .def("get_int", &Field::get_int)
        .def("get_float", &Field::get_float)
        .def("get_struct", &Field::get_struct)
        .def("is_int", &Field::is_int)
        .def("is_float", &Field::is_float)
        .def("is_string", &Field::is_string)
        .def("is_struct", &Field::is_struct)
    ;
    
    class_<Field::Item>("Item", no_init)
        .def("get_int", &item_get<long>)
        .def("get_float", &item_get<float>)
        .def("get_string", &item_get<std::string>)
        //.def("get_struct", &Field::get_struct)
        .def("is_int", &item_is<long>)
        .def("is_float", &item_is<float>)
        .def("is_string", &item_is<std::string>)
        //.def("is_struct", &Field::is_struct)
    ;
    
    class_<Field::Shape>("Shape", no_init)
        .def(vector_indexing_suite<Field::Shape>())
        .def(self == self)
    ;
    
    class_<Field::Value>("Value", no_init)
        .def(vector_indexing_suite<Field::Value>())
    ;
}
