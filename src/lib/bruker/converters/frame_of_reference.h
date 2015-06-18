/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _962f5d8c_d253_4511_b0cd_dacf2a644178
#define _962f5d8c_d253_4511_b0cd_dacf2a644178

#include <memory>

#include <dcmtkpp/registry.h>
#include <dcmtkpp/Tag.h>

#include "bruker/converters/constant_value_converter.h"
#include "bruker/converters/default_converter.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

std::map<dcmtkpp::Tag, converter_base::pointer> const frame_of_reference = {
    { dcmtkpp::registry::FrameOfReferenceUID,
        std::make_shared<default_converter>("VisuUid", 1) },
    { dcmtkpp::registry::PositionReferenceIndicator,
        std::make_shared<constant_value_converter>(dcmtkpp::Value()) },
};

}

}

}

#endif // _962f5d8c_d253_4511_b0cd_dacf2a644178
