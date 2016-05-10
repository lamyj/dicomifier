/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

#include "core/DicomifierException.h"

#include "exception_factory.h"

namespace
{

PyObject * wrapped_Exception;

void translator(dicomifier::DicomifierException const & e)
{
    PyErr_SetString(wrapped_Exception, e.what());
}

}

void wrap_DicomifierException()
{
    using namespace boost::python;
    using namespace dicomifier;
    wrapped_Exception = exception_factory("DicomifierException");
    register_exception_translator<DicomifierException>(translator);
}
