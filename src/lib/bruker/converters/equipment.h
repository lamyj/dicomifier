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
              if(dataset.has_field("VisuCreator"))
              {
                auto const & creator = dataset.get_field("VisuCreator");
                for(int i=0; i<creator.get_size(); ++i)
                  {
                      value.as_strings().push_back(creator.get_string(i));
                  }
              }
              if(dataset.has_field("VisuCreatorVersion"))
              {
                  auto const & version = dataset.get_field("VisuCreatorVersion");
                  for(int i=0; i<version.get_size(); ++i)
                  {
                      value.as_strings().push_back(version.get_string(i));
                  }
              }
          }) },
};

}

}

}

#endif // _4a3a3117_816b_42f2_8e32_db0081a3ca31
