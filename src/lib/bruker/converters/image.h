/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _3da580ab_8a5f_4755_89a6_d23c5ec04181
#define _3da580ab_8a5f_4755_89a6_d23c5ec04181

#include <limits>
#include <memory>

#include <boost/date_time/local_time/local_date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <dcmtkpp/registry.h>
#include <dcmtkpp/Tag.h>

#include "bruker/converters/constant_value_converter.h"
#include "bruker/converters/date_time_converter.h"
#include "bruker/converters/default_converter.h"
#include "bruker/converters/generic_converter.h"
#include "bruker/converters/pixel_data_converter.h"
#include "core/DateTime.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

std::map<dcmtkpp::Tag, converter_base::pointer> const general_image = {
    { dcmtkpp::registry::InstanceNumber,
        std::make_shared<generic_converter>(
            [](Dataset const & dataset, FrameIndexGenerator const & index, dcmtkpp::Value & value) {
                value.as_integers().push_back(1+index.get_step());
            })  },
    { dcmtkpp::registry::ImageType,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({"ORIGINAL", "PRIMARY"})) },
    { dcmtkpp::registry::AcquisitionDate,
        std::make_shared<date_time_converter>("VisuAcqDate", 3, "%Y%m%d") },
    { dcmtkpp::registry::AcquisitionTime,
        std::make_shared<date_time_converter>("VisuAcqDate", 3, "%H%M%S") },
    { dcmtkpp::registry::ImagesInAcquisition,
        std::make_shared<default_converter>("VisuCoreFrameCount", 3) },
    { dcmtkpp::registry::ImageComments,
        std::make_shared<constant_value_converter>(dcmtkpp::Value()) },
};

std::map<dcmtkpp::Tag, converter_base::pointer> const image_plane = {
    { dcmtkpp::registry::PixelSpacing,
        std::make_shared<generic_converter>(
          [](Dataset const & dataset, dicomifier::FrameIndexGenerator const & index, dcmtkpp::Value & value) {
              auto const & extent = dataset.get_field("VisuCoreExtent");
              auto const & size = dataset.get_field("VisuCoreSize");
              for(int i=0; i<extent.get_size(); ++i)
              {
                  value.as_reals().push_back(extent.get_float(i)/size.get_float(i));
              }
          }) },
    { dcmtkpp::registry::ImageOrientationPatient,
        std::make_shared<default_converter>("VisuCoreOrientation", 1, 0, 6, 9) },
    { dcmtkpp::registry::ImagePositionPatient,
        std::make_shared<default_converter>("VisuCorePosition", 1, 0, std::numeric_limits<int>::max(), 3) },
    { dcmtkpp::registry::SliceThickness,
        std::make_shared<default_converter>("VisuCoreFrameThickness", 2) },
};

std::map<dcmtkpp::Tag, converter_base::pointer> const image_pixel = {
    { dcmtkpp::registry::SamplesPerPixel,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({1})) },
    { dcmtkpp::registry::PhotometricInterpretation,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({ "MONOCHROME2" })) },
    { dcmtkpp::registry::Rows,
        std::make_shared<default_converter>("VisuCoreSize", 1, 0, 1, 2) },
    { dcmtkpp::registry::Columns,
        std::make_shared<default_converter>("VisuCoreSize", 1, 1, 2, 2) },
    { dcmtkpp::registry::BitsAllocated,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({16})) },
    { dcmtkpp::registry::BitsStored,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({16})) },
    { dcmtkpp::registry::HighBit,
        std::make_shared<constant_value_converter>(
            dcmtkpp::Value({dicomifier::endian::is_big_endian() ? 0 : 15})) },
    { dcmtkpp::registry::PixelRepresentation,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({0})) },
    { dcmtkpp::registry::PixelData, std::make_shared<pixel_data_converter>() },
};

std::map<dcmtkpp::Tag, converter_base::pointer> const sop_common = {
    { dcmtkpp::registry::SOPClassUID,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({"1.2.840.10008.5.1.4.1.1.4"})) },
    { dcmtkpp::registry::SOPInstanceUID,
        std::make_shared<generic_converter>(
          [](Dataset const & , dicomifier::FrameIndexGenerator const & index, dcmtkpp::Value & value) {
            char buffer[128];
            dcmGenerateUniqueIdentifier(buffer, SITE_INSTANCE_UID_ROOT);
            std::string const uid(buffer);
            value.as_strings().push_back(uid);
          }) },
    // Specific Character Set
    { dcmtkpp::registry::InstanceCreationDate,
        std::make_shared<generic_converter>(
            [](Dataset const & , dicomifier::FrameIndexGenerator const & index, dcmtkpp::Value & value) {
                auto const now = boost::posix_time::second_clock::local_time();
                value.as_strings().push_back(posix_time_to_string(now, "%Y%m%d"));
          }) },
    { dcmtkpp::registry::InstanceCreationTime,
          std::make_shared<generic_converter>(
          [](Dataset const & , dicomifier::FrameIndexGenerator const & index,dcmtkpp::Value & value) {
                auto const now = boost::posix_time::second_clock::local_time();
                value.as_strings().push_back(posix_time_to_string(now, "%H%M%S"));
          }) },
};

}

}

}

#endif // _3da580ab_8a5f_4755_89a6_d23c5ec04181
