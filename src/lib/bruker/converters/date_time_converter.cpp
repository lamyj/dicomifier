/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "bruker/converters/date_time_converter.h"

#include <functional>
#include <string>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Element.h>
#include <dcmtkpp/Tag.h>
#include <dcmtkpp/VR.h>

#include "bruker/Dataset.h"
#include "bruker/converters/functor_converter.h"
#include "core/DateTime.h"
#include "core/FrameIndexGenerator.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

date_time_converter
::date_time_converter(
    std::string const & bruker_tag, int type, std::string const & format)
: functor_converter<dcmtkpp::Value::Strings>(
    bruker_tag, type,
    std::bind(&date_time_converter::convert, this, std::placeholders::_1),
    &dcmtkpp::Element::as_string), format(format)
{
    // Nothing else.
}

date_time_converter
::~date_time_converter()
{
    // Nothing to do.
}

void
date_time_converter
::convert(dcmtkpp::Value::String & value) const
{
    std::string format = "";
    auto const ldt = dicomifier::string_to_local_date_time(value, format);
    value = dicomifier::local_date_time_to_string(ldt, this->format);
}

}

}

}
