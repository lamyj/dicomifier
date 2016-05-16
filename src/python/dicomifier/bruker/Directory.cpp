/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "bruker/Directory.h"

namespace 
{

boost::python::object
get_series_and_reco(std::string const & path)
{
    auto const result_cpp = dicomifier::bruker::Directory::get_series_and_reco(path);
    
    boost::python::dict result_python;
    for(auto const & entry: result_cpp)
    {
        boost::python::list value;
        for(auto const & item: entry.second)
        {
            value.append(item);
        }
        result_python[entry.first] = value;
    }
    
    return result_python;
}

}

void wrap_Directory()
{
    using namespace boost::python;
    using namespace dicomifier::bruker;
    
    scope directory_scope = class_<Directory>("Directory", init<>())
        .def("load", &Directory::load)
        .def("has_dataset", &Directory::has_dataset)
        .def(
            "get_dataset", &Directory::get_dataset,
            return_value_policy<copy_const_reference>())
        .def("get_series_and_reco", &get_series_and_reco).staticmethod("get_series_and_reco");
}
