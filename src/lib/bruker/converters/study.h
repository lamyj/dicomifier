/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _d7af67c1_255a_46ea_882f_757700bab58b
#define _d7af67c1_255a_46ea_882f_757700bab58b

#include <memory>

#include <dcmtkpp/registry.h>
#include <dcmtkpp/Tag.h>

#include "bruker/converters/constant_value_converter.h"
#include "bruker/converters/date_time_converter.h"
#include "bruker/converters/default_converter.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

std::map<dcmtkpp::Tag, converter_base::pointer> const general_study = {
    { dcmtkpp::registry::StudyInstanceUID,
        std::make_shared<default_converter>("VisuStudyUid", 1) },
    { dcmtkpp::registry::StudyDate,
        std::make_shared<date_time_converter>("VisuStudyDate", 2, "%Y%m%d") },
    { dcmtkpp::registry::StudyTime,
        std::make_shared<date_time_converter>("VisuStudyDate", 2, "%H%M%S") },
    { dcmtkpp::registry::ReferringPhysicianName,
        std::make_shared<default_converter>("VisuStudyReferringPhysician", 2) },
    { dcmtkpp::registry::StudyID,
        std::make_shared<default_converter>("VisuStudyNumber", 2) },
    { dcmtkpp::registry::AccessionNumber,
        std::make_shared<constant_value_converter>(dcmtkpp::Value()) },
    { dcmtkpp::registry::StudyDescription,
        std::make_shared<default_converter>("VisuStudyId", 3) },
};

std::map<dcmtkpp::Tag, converter_base::pointer> const patient_study = {
    { dcmtkpp::registry::PatientWeight,
        std::make_shared<default_converter>("VisuSubjectWeight", 3) },
    { dcmtkpp::registry::PatientSexNeutered,
        std::make_shared<constant_value_converter>(dcmtkpp::Value())},
};

}

}

}

#endif // _d7af67c1_255a_46ea_882f_757700bab58b
