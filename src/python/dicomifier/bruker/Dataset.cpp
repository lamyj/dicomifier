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
    
    class_<Dataset>(m, "Dataset")
        .def(init<>())
        .def("load", &Dataset::load)
        .def("has_field", &Dataset::has_field)
        .def(
            "get_field", &Dataset::get_field, 
            return_value_policy::reference_internal)
        // TODO? set_field
        .def(
            "get_used_files", &Dataset::get_used_files, 
            return_value_policy::reference_internal)
        .def("__contains__", &Dataset::has_field)
        .def(
            "__getitem__", &Dataset::get_field, 
            return_value_policy::reference_internal)
        .def(
            "__iter__", 
            [](Dataset const & d) { return make_iterator(d.begin(), d.end()); },
            keep_alive<0, 1>())
    ;
}
