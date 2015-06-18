/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _93f6fb02_fde3_40b2_a655_808ce2f57c02
#define _93f6fb02_fde3_40b2_a655_808ce2f57c02

#include <memory>

#include <dcmtkpp/Element.h>
#include <dcmtkpp/registry.h>
#include <dcmtkpp/Tag.h>

#include "bruker/converters/constant_value_converter.h"
#include "bruker/converters/default_converter.h"
#include "bruker/converters/mapping_converter.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

std::map<dcmtkpp::Tag, converter_base::pointer> const patient = {
    { dcmtkpp::registry::PatientName,
        std::make_shared<default_converter>("VisuSubjectName", 2) },
    { dcmtkpp::registry::PatientID,
        std::make_shared<default_converter>("VisuSubjectId", 2) },
    { dcmtkpp::registry::PatientBirthDate,
        std::make_shared<default_converter>("VisuSubjectBirthDate", 2) },
    { dcmtkpp::registry::PatientSex,
        converter_base::pointer(new mapping_converter<dcmtkpp::Value::Strings>(
            "VisuSubjectSex", 2, {
                {"MALE","M"}, {"FEMALE", "F"},
                {"UNDEFINED", "O"}, {"UNKNOWN", "O"}},
            &dcmtkpp::Element::as_string)) },
    { dcmtkpp::registry::PatientComments,
        converter_base::pointer(new default_converter("VisuSubjectComment", 3)) },
    { dcmtkpp::registry::PatientSpeciesDescription,
        std::make_shared<constant_value_converter>(dcmtkpp::Value({"UNKNOWN"}))},
    { dcmtkpp::registry::PatientBreedDescription,
        std::make_shared<constant_value_converter>(dcmtkpp::Value()) },
    { dcmtkpp::registry::PatientBreedCodeSequence,
        std::make_shared<constant_value_converter>(dcmtkpp::Value())},
    { dcmtkpp::registry::BreedRegistrationSequence,
        std::make_shared<constant_value_converter>(dcmtkpp::Value())},
    { dcmtkpp::registry::ResponsiblePerson,
        std::make_shared<constant_value_converter>(dcmtkpp::Value())},
    // ResponsiblePersonRole
    { dcmtkpp::registry::ResponsibleOrganization,
        std::make_shared<constant_value_converter>(dcmtkpp::Value())},
};

}

}

}

#endif // _93f6fb02_fde3_40b2_a655_808ce2f57c02
