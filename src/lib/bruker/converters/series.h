/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _e2848327_7056_49b1_a0e2_a62ef686bb67
#define _e2848327_7056_49b1_a0e2_a62ef686bb67

#include <memory>

#include <dcmtkpp/Element.h>
#include <dcmtkpp/registry.h>
#include <dcmtkpp/Tag.h>

#include "bruker/converters/constant_value_converter.h"
#include "bruker/converters/date_time_converter.h"
#include "bruker/converters/default_converter.h"
#include "bruker/converters/mapping_converter.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

std::map<dcmtkpp::Tag, converter_base::pointer> const general_series= {
    { dcmtkpp::registry::Modality,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({"MR"})) },
    { dcmtkpp::registry::SeriesInstanceUID,
        std::make_shared<default_converter>("VisuUid", 1) },
    { dcmtkpp::registry::SeriesNumber,
        std::make_shared<generic_converter>(
            [](Dataset const & data_set, dicomifier::FrameIndexGenerator const & index, dcmtkpp::Value & value) {
                int number;
                if(data_set.has_field("VisuExperimentNumber"))
                {
                    number = data_set.get_field("VisuExperimentNumber").get_int(0);
                }
                else
                {
                    number = data_set.get_field("VisuSeriesNumber").get_int(0);
                }
                value.as_integers().push_back(number);
            } ) },
    { dcmtkpp::registry::Laterality,
        std::make_shared<constant_value_converter>(dcmtkpp::Value()) },
    { dcmtkpp::registry::SeriesDate,
        std::make_shared<date_time_converter>("SeriesSeriesDate", 3, "%Y%m%d") },
    { dcmtkpp::registry::SeriesTime,
        std::make_shared<date_time_converter>("VisuSeriesDate", 3, "%H%M%S") },
    { dcmtkpp::registry::PerformingPhysicianName,
        std::make_shared<default_converter>("OWNER", 3) },
    { dcmtkpp::registry::ProtocolName,
        std::make_shared<default_converter>("VisuAcquisitionProtocol", 3) },
    { dcmtkpp::registry::SeriesDescription,
        std::make_shared<default_converter>("VisuAcquisitionProtocol", 3) },
    { dcmtkpp::registry::PatientPosition,
        converter_base::pointer(new mapping_converter<dcmtkpp::Value::Strings>(
            "VisuSubjectPosition", 2, {
                {"Head_Supine", "HFS"}, {"Head_Prone", "HFP"},
                {"Head_Left", "HFDL"}, {"Head_Right", "HFDR"},
                {"Foot_Supine", "FFS"}, {"Foot_Prone", "FFP"},
                {"Foot_Left", "FFDL"}, {"Foot_Right", "FFDR"}
            }, &dcmtkpp::Element::as_string))},
    { dcmtkpp::registry::AnatomicalOrientationType,
        std::make_shared<default_converter>("VisuSubjectType", 3) },
};

}

}

}

#endif // _e2848327_7056_49b1_a0e2_a62ef686bb67
