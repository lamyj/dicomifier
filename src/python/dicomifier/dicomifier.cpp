/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

#include "core/Exception.h"

PYBIND11_MODULE(_dicomifier, _dicomifier)
{
    pybind11::register_exception<dicomifier::Exception>(
        _dicomifier, "Exception");
}
