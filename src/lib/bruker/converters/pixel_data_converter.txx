/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dd05e8c5_1691_4fc4_9525_6518ae932117
#define _dd05e8c5_1691_4fc4_9525_6518ae932117

#include "bruker/converters/pixel_data_converter.h"

#include <algorithm>
#include <fstream>
#include <cstdint>
#include <tuple>
#include <vector>

#include <boost/filesystem.hpp>
#include <odil/endian.h>

#include "bruker/Dataset.h"
#include "core/DicomifierException.h"

namespace dicomifier
{

namespace bruker
{

template<typename T>
std::tuple<std::vector<uint8_t>, bool, double, double>
convert_pixel_data_to_dicom(Dataset const & data_set)
{
    auto const & pixel_data_file = data_set.get_field("PIXELDATA").get_string(0);
    // Read the Bruker pixel data from the thile
    if(!boost::filesystem::is_regular_file(pixel_data_file) &&
        !boost::filesystem::is_symlink(pixel_data_file))
    {
        throw DicomifierException("Cannot read pixel data");
    }
    std::ifstream stream(pixel_data_file);
    if(!stream.good())
    {
        throw DicomifierException("Cannot read pixel data");
    }

    stream.seekg(0, stream.end);
    auto const bytes_count = stream.tellg();
    stream.seekg(0, stream.beg);

    if(bytes_count % sizeof(T) != 0)
    {
        throw DicomifierException("Invalid file");
    }

    std::vector<T> bruker_pixel_data(bytes_count / sizeof(T));
    stream.read(reinterpret_cast<char*>(&bruker_pixel_data[0]), bytes_count);

    // Swap to host order
    auto const & byte_order = data_set.get_field("VisuCoreByteOrder").get_string(0);
    if(byte_order == "bigEndian")
    {
        std::for_each(
            bruker_pixel_data.begin(), bruker_pixel_data.end(),
            [](T & item) { item = odil::big_endian_to_host<T>(item); });
    }
    else if(byte_order == "littleEndian")
    {
        std::for_each(
            bruker_pixel_data.begin(), bruker_pixel_data.end(),
            [](T & item) { item = odil::little_endian_to_host<T>(item); });
    }
    else
    {
        throw DicomifierException("Invalid byte order: "+byte_order);
    }

    // Compute downsampling parameters
    bool is_downsampled = false;
    double slope = 1;
    double intercept = 0;
    if(sizeof(T) > 2)
    {
        auto const min = *std::min_element(
            bruker_pixel_data.begin(), bruker_pixel_data.end());
        auto const max = *std::max_element(
            bruker_pixel_data.begin(), bruker_pixel_data.end());

        slope = float(max-min)/float(65535);
        intercept = min;

        is_downsampled = true;
    }

    // Convert to 16 bits
    std::vector<uint8_t> dicom_pixel_data(2*bruker_pixel_data.size());
    uint8_t * output_iterator = &dicom_pixel_data[0];

    for(auto const & item: bruker_pixel_data)
    {
        if(is_downsampled)
        {
            uint16_t const value = static_cast<uint16_t>((item-intercept)/slope);
            uint8_t const * input_iterator =
                reinterpret_cast<uint8_t const *>(&value);
            output_iterator = std::copy(
                input_iterator, input_iterator+2, output_iterator);
        }
        else
        {
            uint8_t const * input_iterator =
                reinterpret_cast<uint8_t const *>(&item);
            output_iterator = std::copy(
                input_iterator, input_iterator+sizeof(T), output_iterator);
        }
    }

    return std::make_tuple(dicom_pixel_data, is_downsampled, slope, intercept);
}

} // namespace bruker

} // namespace dicomifier

#endif // _dd05e8c5_1691_4fc4_9525_6518ae932117
