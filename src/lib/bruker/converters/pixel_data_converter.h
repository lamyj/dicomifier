/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e7c45dce_2bc3_47ba_93bd_017c50687fb4
#define _e7c45dce_2bc3_47ba_93bd_017c50687fb4

#include <cstdint>
#include <tuple>
#include <vector>

#include "bruker/Dataset.h"

namespace dicomifier
{

namespace bruker
{

/**
 * @brief Convert Bruker pixel data to a DICOM-compatible representation (host
 * endianness, 16 bits integers).
 *
 * @return DICOM-compatible data, flag indicating whether the data was
 * resampled, rescale slope and rescale intercept.
 *
 * If the Bruker data is of integer type and 16 bits or shorter, then the Bruker
 * data will be copied without resampling. Otherwise, the data is resampled
 * to the 0, 65535 range.
 */
std::tuple<std::vector<uint8_t>, bool, double, double>
convert_pixel_data_to_dicom(Dataset const & data_set);

/**
 * @brief Convert Bruker pixel data to a DICOM-compatible representation (host
 * endianness, 16 bits integers).
 */
template<typename T>
std::tuple<std::vector<uint8_t>, bool, double, double>
convert_pixel_data_to_dicom(Dataset const & data_set);

} // namespace bruker

} // namespace dicomifier

#include "bruker/converters/pixel_data_converter.txx"

#endif // _e7c45dce_2bc3_47ba_93bd_017c50687fb4
