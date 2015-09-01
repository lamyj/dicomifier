/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _18bea9eb_cbff_4af8_89a2_21bbe2bac286
#define _18bea9eb_cbff_4af8_89a2_21bbe2bac286

#include <jsoncpp/json/json.h>

#include "Dataset.h"

namespace dicomifier
{

namespace bruker
{

/// @brief Convert a Bruker data set to its JSON representation.
Json::Value as_json(Dataset const & data_set);

/// @brief Convert JSON data set as string representation
std::string as_string(Json::Value const & data_set);

} // namespace bruker

} // namespace dicomifier

#endif // _18bea9eb_cbff_4af8_89a2_21bbe2bac286
