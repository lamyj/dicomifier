/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _18d92dc6_ff7e_4f21_8b05_00c6eabe1c55
#define _18d92dc6_ff7e_4f21_8b05_00c6eabe1c55

#include <memory>

#include <dcmtkpp/Element.h>
#include <dcmtkpp/registry.h>
#include <dcmtkpp/Tag.h>

#include "bruker/converters/constant_value_converter.h"
#include "bruker/converters/default_converter.h"
#include "bruker/converters/functor_converter.h"
#include "bruker/converters/generic_converter.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

std::map<dcmtkpp::Tag, converter_base::pointer> const mr_image = {
    { dcmtkpp::registry::ScanningSequence,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({"RM"})) },
    { dcmtkpp::registry::SequenceVariant,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({"NONE"})) },
    { dcmtkpp::registry::ScanOptions,
        std::make_shared<constant_value_converter>(dcmtkpp::Value())},
    { dcmtkpp::registry::MRAcquisitionType,
        converter_base::pointer(new functor_converter<dcmtkpp::Value::Strings>(
            "VisuCoreDim", 2,
            [](dcmtkpp::Value::String & value) { value += "D"; },
            &dcmtkpp::Element::as_string))},
    { dcmtkpp::registry::RepetitionTime,
        std::make_shared<default_converter>("VisuAcqRepetitionTime", 2) },
    { dcmtkpp::registry::EchoTime,
        std::make_shared<default_converter>("VisuAcqEchoTime", 2) },
    { dcmtkpp::registry::EchoTrainLength,
        std::make_shared<default_converter>("VisuAcqEchoTrainLength", 2) },
    { dcmtkpp::registry::InversionTime,
        std::make_shared<default_converter>("VisuAcqInversionTime", 2) },
    { dcmtkpp::registry::SequenceName,
        std::make_shared<default_converter>("VisuAcqSequenceName", 3) },
    { dcmtkpp::registry::NumberOfAverages,
        std::make_shared<default_converter>("VisuAcqNumberOfAverages", 3) },
    { dcmtkpp::registry::ImagingFrequency,
        std::make_shared<default_converter>("VisuAcqImagingFrequency", 3) },
    { dcmtkpp::registry::ImagedNucleus,
        std::make_shared<default_converter>("VisuAcqImagedNucleus", 3) },
    { dcmtkpp::registry::MagneticFieldStrength,
        converter_base::pointer(new functor_converter<dcmtkpp::Value::Reals>(
            "VisuAcqImagingFrequency", 3,
            // According to Bruker doc, VisuAcqImagingFrequency is the imaging
            // frequency of 1H, regardless of VisuAcqImagingNucleus
            [](dcmtkpp::Value::Real & value) { value /= 42.577480610; },
            &dcmtkpp::Element::as_real)) },
    { dcmtkpp::registry::SpacingBetweenSlices,
        std::make_shared<generic_converter>(
            [](Dataset const & data_set, dcmtkpp::Value & value) {
                auto const field = data_set.get_field("VisuCorePosition");
                // We need at least two points
                if(field.shape[0]>1)
                {
                    std::vector<float> const p1({
                        field.get_float(0), field.get_float(1), field.get_float(2) });
                    std::vector<float> const p2({
                        field.get_float(3), field.get_float(4), field.get_float(5) });
                    std::vector<float> const difference(
                        { p2[0]-p1[0], p2[1]-p1[1], p2[2]-p1[2] });
                    value.as_reals().push_back(
                        difference[0]*difference[0] +
                        difference[1]*difference[1] +
                        difference[2]*difference[2]);
                }
            }) },
    { dcmtkpp::registry::NumberOfPhaseEncodingSteps,
        std::make_shared<default_converter>("VisuAcqPhaseEncSteps", 3) },
    { dcmtkpp::registry::PixelBandwidth,
        std::make_shared<default_converter>("VisuAcqPixelBandwidth", 3) },
    //{ dcmtkpp::registry::AcquisitionMatrix, { } },
    //{ dcmtkpp::registry::InPlanePhaseEncodingDirection, { } },
    { dcmtkpp::registry::FlipAngle,
        std::make_shared<default_converter>("VisuAcqFlipAngle", 3) },
};

}

}

}

#endif // _18d92dc6_ff7e_4f21_8b05_00c6eabe1c55
