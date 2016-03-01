/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "bruker/converters/pixel_data_converter.h"

#include <cstdint>
#include <tuple>
#include <vector>

#include "bruker/Dataset.h"
#include "core/DicomifierException.h"

namespace dicomifier
{

namespace bruker
{

std::tuple<std::vector<uint8_t>, bool, double, double>
convert_pixel_data_to_dicom(Dataset const & data_set)
{
    auto const & word_type =
        data_set.get_field("VisuCoreWordType").get_string(0);

    if(word_type == "_8BIT_UNSGN_INT")
    {
        return convert_pixel_data_to_dicom<uint8_t>(data_set);
    }
    else if(word_type == "_16BIT_SGN_INT")
    {
        return convert_pixel_data_to_dicom<int16_t>(data_set);
    }
    else if(word_type == "_32BIT_SGN_INT")
    {
        return convert_pixel_data_to_dicom<int32_t>(data_set);
    }
    else if(word_type == "_32BIT_FLOAT")
    {
        return convert_pixel_data_to_dicom<float>(data_set);
    }
    else
    {
        throw DicomifierException("Invalid word type: "+word_type);
    }
}

} // namespace bruker

} // namespace dicomifier
