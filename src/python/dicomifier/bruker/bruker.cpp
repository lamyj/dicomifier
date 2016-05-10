/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/python.hpp>

void wrap_Dataset();
void wrap_Directory();
void wrap_Field();
void wrap_json_converter();

BOOST_PYTHON_MODULE(bruker)
{
    wrap_Dataset();
    wrap_Directory();
    wrap_Field();
    wrap_json_converter();
}
