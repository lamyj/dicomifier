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
    std::string const data(
        (std::istreambuf_iterator<typename std::string::value_type>(stream)),
        (std::istreambuf_iterator<typename std::string::value_type>()));
    stream.close();
    
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
        loggerWarning() << "File was parsed incompletely";
    }
    
    // Update the map
    for(auto const & field: fields)
    {
        this->set_field(field);
    }
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
    if(field_it != this->_fields.end())
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
}

} // namespace bruker

} // namespace dicomifier
