/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dd05e8c5_1691_4fc4_9525_6518ae932117
#define _dd05e8c5_1691_4fc4_9525_6518ae932117

#include <algorithm>
#include <cstdint>
#include <limits>
#include <string>

#include "core/Endian.h"

namespace dicomifier
{

namespace bruker
{

template<typename TPixelType>
dcmtkpp::Value::Binary
pixel_data_converter
::_read_pixel_data(unsigned int frame_size, unsigned int index) const
{
    dcmtkpp::Value::Binary pixel_data;
    pixel_data.resize(
        sizeof(OutputPixelType)/sizeof(dcmtkpp::Value::Binary::value_type)*frame_size);

    TPixelType const * const source_begin =
        reinterpret_cast<TPixelType const *>(&this->_pixel_data[0]) +
        + frame_size*index;
    //TPixelType const * const source_end = source_begin+frame_size ;

    OutputPixelType * const destination_begin =
        reinterpret_cast<OutputPixelType *>(&pixel_data[0]);
    OutputPixelType * const destination_end = destination_begin + frame_size;
    //OutputPixelType * destination_it = destination_begin;

    std::transform(source_begin, source_begin+frame_size, destination_begin,
        [&] (TPixelType const & source)
        {
            double const destination =
                (source-this->_min)/
                    (this->_max-this->_min)*
                    std::numeric_limits<OutputPixelType>::max();
            return destination;
        }
    );

    if(endian::is_big_endian())
    {
        // Transfer syntax is little endian
        endian::swap(destination_begin, destination_end);
    }

    return pixel_data;
}

template<typename TPixelType>
void
pixel_data_converter
::_flip()
{
    TPixelType * const begin =
        reinterpret_cast<TPixelType *>(&this->_pixel_data[0]);
    auto const factor = sizeof(TPixelType)/sizeof(dcmtkpp::Value::Binary::value_type);
    TPixelType * const end=begin+this->_pixel_data.size()/factor;

    endian::swap(begin, end);
}

template<typename TPixelType>
void
pixel_data_converter
::_update_min_max()
{
    TPixelType const * const begin =
        reinterpret_cast<TPixelType const *>(&this->_pixel_data[0]);
    auto const factor = sizeof(TPixelType)/sizeof(dcmtkpp::Value::Binary::value_type);
    TPixelType const * const end=begin+this->_pixel_data.size()/factor;

    this->_min = *std::min_element(begin, end);
    this->_max = *std::max_element(begin, end);
}

} // namespace bruker

} // namespace dicomifier

#endif // _dd05e8c5_1691_4fc4_9525_6518ae932117
