/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a1d8cda2_3735_4f2a_bf35_972e85a48112
#define _a1d8cda2_3735_4f2a_bf35_972e85a48112

#include <string>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/Tag.h>
#include <dcmtkpp/Value.h>
#include <dcmtkpp/VR.h>

#include "bruker/Dataset.h"
#include "bruker/converters/functor_converter.h"
#include "core/FrameIndexGenerator.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

/// @brief Convert dates and times from Bruker to DICOM.
struct date_time_converter: public functor_converter<dcmtkpp::Value::Strings>
{
    /// @brief Output format.
    std::string format;

    date_time_converter(
        std::string const & bruker_tag, int type, std::string const & format);

    virtual ~date_time_converter();

    void convert(dcmtkpp::Value::String & value) const;
};

}

}

}

#endif // _a1d8cda2_3735_4f2a_bf35_972e85a48112
