/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <pybind11/pybind11.h>

void wrap_Dataset(pybind11::module &);
void wrap_Directory(pybind11::module &);
void wrap_Field(pybind11::module &);

PYBIND11_MODULE(bruker, bruker)
{
    wrap_Dataset(bruker);
    wrap_Directory(bruker);
    wrap_Field(bruker);
}
