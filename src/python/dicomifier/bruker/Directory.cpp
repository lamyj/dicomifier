/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bruker/Directory.h"

void wrap_Directory(pybind11::module & m)
{
    using namespace pybind11;
    using namespace dicomifier::bruker;
    
    class_<Directory>(m, "Directory")
        .def(init<>())
        .def("load", &Directory::load)
        .def("has_dataset", &Directory::has_dataset)
        .def("get_dataset", &Directory::get_dataset)
        .def("get_used_files", &Directory::get_used_files)
        .def_static("list_subjects", &Directory::list_subjects)
        .def_static("get_series_and_reco", &Directory::get_series_and_reco)
    ;
}
