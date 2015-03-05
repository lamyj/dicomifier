/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "Dataset.h"

#include <fstream>
#include <iterator>
#include <vector>

#include <boost/regex.hpp>

#include "core/DicomifierException.h"
#include "core/Logger.h"

#include "Field.h"
#include "grammar.h"

namespace dicomifier
{
    
namespace bruker
{

void
Dataset
::load(std::string const & path)
{
    // Read the file
    std::ifstream stream(path);
    if(stream.fail())
    {
        throw DicomifierException("Could not open file");
    }
    std::string data(
        (std::istreambuf_iterator<typename std::string::value_type>(stream)),
        (std::istreambuf_iterator<typename std::string::value_type>()));
    stream.close();

    // Join the lines
    data = boost::regex_replace(data, boost::regex("\\\\?\\R(?!##|\\$\\$)"), "");

    // Parse the data
    std::string::const_iterator begin = data.begin();
    std::string::const_iterator const end = data.end();
    
    std::vector<Field> fields;
    grammar<std::string::const_iterator> g;
    bool const parsed = boost::spirit::qi::parse(begin, end, g, fields);
    
    if(!parsed)
    {
        throw DicomifierException("Could not parse file");
    }
    
    if(begin != end)
    {
        throw DicomifierException("File was parsed incompletely");
    }

    // Update the map
    for(auto field: fields)
    {
        if(field.name[0] == '$')
        {
            field.name = field.name.substr(1);
        }
        this->set_field(field);
    }
    
    this->_update_frame_groups();
}

bool
Dataset
::has_field(std::string const & name) const
{
    auto const field_it = this->_fields.find(name);
    return (field_it != this->_fields.end());
}

Field const &
Dataset
::get_field(std::string const & name) const
{
    auto const field_it = this->_fields.find(name);
    if(field_it == this->_fields.end())
    {
        throw DicomifierException("No such field");
    }
    
    return field_it->second;
}

void
Dataset
::set_field(Field const & field)
{
    this->_fields[field.name] = field;
    this->_update_frame_groups();
}

std::vector<FrameGroup> const &
Dataset
::get_frame_groups() const
{
    return this->_frame_groups;
}

void 
Dataset
::get_indexForValue(
    std::string const & valuename, int & indexposition, int & startposition) const
{
    indexposition = -1;
    startposition = 0;
    int count = -1;
    for(auto const & frame_group: this->_frame_groups)
    {
        ++count;
        for(auto const & parameter: frame_group.parameters)
        {
            if(parameter.name == valuename)
            {
                startposition = parameter.start_index;
                indexposition = count;
                return;
            }
        }
    }
}

void
Dataset
::_update_frame_groups()
{
    // VisuFGOrderDescDim: number of frame groups
    // VisuFGOrderDesc: array of frame group descriptions
    //   - len: number of elements in the frame group (e.g. number of echo or slices)
    //   - groupId: unique identifier string
    //   - groupComment: free comment or description
    //   - valsStart: start offset for the frame group parameters in VisuGroupDepVals
    //   - valsCnt: count of the frame group parameters
    // VisuGroupDepVals is an array of parameters which depend on a frame group
    //   - name: name of the parameter
    //   - valsStart: start index in the parameter array
    
    this->_frame_groups.clear();
    
    if(!this->has_field("VisuFGOrderDescDim") || 
       !this->has_field("VisuFGOrderDesc") ||
       !this->has_field("VisuGroupDepVals"))
    {
        return;
    }

    for(long fg_index=0; 
        fg_index < this->get_field("VisuFGOrderDescDim").get_int(0); ++fg_index)
    {
        auto const & fg_item = boost::get<std::vector<Field::Item> >(
            this->get_field("VisuFGOrderDesc").value[fg_index]);

        FrameGroup fg;
        fg.size = boost::get<long>(fg_item[0]);
        fg.name = boost::get<std::string>(fg_item[1]);
        fg.comment = boost::get<std::string>(fg_item[2]);

        long const start = boost::get<long>(fg_item[3]);
        long const parameters_count = boost::get<long>(fg_item[4]);
        for(long parameter_index=start; 
            parameter_index < start+parameters_count; ++parameter_index)
        {
            auto fieldvisu = this->get_field("VisuGroupDepVals");

            bruker::Field::Value parameter_item;
            parameter_item = fieldvisu.get_struct(parameter_index);

            FrameGroup::Parameter parameter;
            parameter.name = boost::get<std::string>(parameter_item[0]);
            parameter.start_index = boost::get<long>(parameter_item[1]);
            
            fg.parameters.push_back(parameter);
        }

        this->_frame_groups.push_back(fg);
    }
}

} // namespace bruker

} // namespace dicomifier
