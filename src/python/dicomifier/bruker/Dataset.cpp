/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include "bruker/Dataset.h"

void wrap_Dataset(pybind11::module & m)
{
    using namespace pybind11;
    using namespace dicomifier::bruker;
    
    class_<Dataset>(
            m, "Dataset", R"doc(
                A Bruker dataset. This objects implements part of the mapping 
                protocol: ``"foo" in d``, ``d["foo"]`` and ``for x in d``
                are valid constructs.)doc")
        .def(init<>(), "init docstring")
        .def(
            "load", &Dataset::load, arg("path"),
            "Load dataset from file, update any existing field.")
        .def(
            "loads", &Dataset::loads, arg("data"),
            "Load dataset from file content, update any existing field.")
        .def(
            "has_field", &Dataset::has_field, arg("name"),
            "Test if dataset contains a given field.")
        .def(
            "get_field", &Dataset::get_field, arg("name"),
            return_value_policy::reference_internal,
            "Return the field, throw an exception if field is missing.")
        .def(
            "set_field", &Dataset::set_field, arg("field"),
            "Add a field to the dataset or modify an existing field.")
        .def(
            "get_used_files", &Dataset::get_used_files, 
            return_value_policy::reference_internal, R"doc(
                Return a set of files used to create the dataset 
                (except the PixelData file))doc")
        .def("__contains__", &Dataset::has_field)
        .def(
            "__getitem__", &Dataset::get_field, 
            return_value_policy::reference_internal)
        .def(
            "__iter__", 
            [](Dataset const & d) { 
                return make_key_iterator(d.begin(), d.end()); },
            keep_alive<0, 1>())
        .def(
            "items", 
            [](Dataset const & d) { return make_iterator(d.begin(), d.end()); },
            keep_alive<0, 1>(), "Iterate on fields")
    ;
}
