/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _4a3a3117_816b_42f2_8e32_db0081a3ca31
#define _4a3a3117_816b_42f2_8e32_db0081a3ca31

#include <memory>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include <dcmtkpp/registry.h>
#include <dcmtkpp/Tag.h>

#include "bruker/converters/default_converter.h"
#include "bruker/converters/generic_converter.h"

namespace dicomifier
{

namespace bruker
{

namespace converters
{

std::map<dcmtkpp::Tag, converter_base::pointer> const general_equipment = {
    { dcmtkpp::registry::Manufacturer,
        std::make_shared<default_converter>("ORIGIN", 1) },
    { dcmtkpp::registry::InstitutionName,
        std::make_shared<default_converter>("VisuInstitution", 3) },
    { dcmtkpp::registry::StationName,
        std::make_shared<default_converter>("VisuStation", 3) },
    { dcmtkpp::registry::SoftwareVersions,
        std::make_shared<generic_converter>(
          [](Dataset const & dataset, dicomifier::FrameIndexGenerator const & , dcmtkpp::Value & value) {
              // VisuCreator - Creator application of this parameter set or data set. Two entries
              // are allowed separated by a semicolon.
              if(dataset.has_field("VisuCreator"))
              {
                auto const creator = dataset.get_field("VisuCreator").get_string(0);

                std::string version = "";
                // VisuCreatorVersion - Creator application version of this parameter set or data
                // set. They must match with the entries in VisuCreator and, therefore, can also
                // have two entries separated by semicolons.
                if(dataset.has_field("VisuCreatorVersion"))
                {
                  version = dataset.get_field("VisuCreatorVersion").get_string(0);
                }

                std::vector<std::string> creator_values;
                boost::split(creator_values, creator, boost::is_any_of(";"));

                std::vector<std::string> version_values;
                boost::split(version_values, version, boost::is_any_of(";"));

                for(int i=0; i<creator_values.size(); ++i)
                {
                    std::stringstream creator_version;
                    creator_version << creator_values[i];
                    if (version_values.size() > i)
                    {
                        creator_version << " " << version_values[i];
                    }
                    value.as_strings().push_back(creator_version.str());
                }
              }
          }) },
};

}

}

}

#endif // _4a3a3117_816b_42f2_8e32_db0081a3ca31
