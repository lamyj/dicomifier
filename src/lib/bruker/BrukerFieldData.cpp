/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

#include "BrukerFieldData.h"
#include "core/DicomifierException.h"

namespace dicomifier
{
    
namespace bruker
{
    
BrukerFieldData
::BrukerFieldData():
    _dimensionNumbers({}), _brukervalues()
{
    // Nothing to do
}

BrukerFieldData
::BrukerFieldData(std::string value):
    _dimensionNumbers({1}), _brukervalues()
{
    _brukervalues.children.push_back(value);
}

BrukerFieldData::
BrukerFieldData(BrukerValue values):
    _dimensionNumbers({}), _brukervalues(values)
{
    _dimensionNumbers.push_back(values.children.size());
}

BrukerFieldData
::~BrukerFieldData()
{
    // Nothing to do
}

std::string 
BrukerFieldData
::Parse(std::string const & data)
{
    // look for header key or not
    boost::cmatch what;
    if (regex_match(data.c_str(), what, RegEx_NotHeader))
    {// it is not a header key
        // look for dimension
        int dimCompute = this->parse_dimension(data);
        
        // look for values
        int dimFind = this->parse_values(what[1]);
        
        // if find string or struct and compute size is not correct
        if (dimFind != -1 && dimCompute != dimFind)
        {
            this->_dimensionNumbers.clear();
            this->_dimensionNumbers.push_back(dimFind);
        }
    }
    else
    {// it is a header key
        if (regex_match(data.c_str(), what, RegEx_Header))
        {
            this->_brukervalues.children.push_back(what[1]);
            this->_dimensionNumbers.push_back(1);
        }
    }
    
    // look for data Key name
    boost::cmatch whatname;
    if (regex_match(data.c_str(), whatname, RegEx_KeyWord))
    {
        return whatname[1];
    }
        
    return "";
}

std::string 
BrukerFieldData
::get_data_type(int position) const
{
    if (position >= this->_brukervalues.children.size())
    {
        throw dicomifier::DicomifierException("No value");
    }
    
    try 
    {
        this->get_int(position);
        return "Int";
    }
    catch(std::exception & ex)
    {
    }
    
    try 
    {
        this->get_double(position);
        return "Double";
    }
    catch(std::exception & ex)
    {
    }
    
    try 
    {
        this->get_struct(position);
        return "BrukerFieldData";
    }
    catch(std::exception & ex)
    {
    }
    
    return "String";
}

std::string 
BrukerFieldData
::get_string(int position) const
{
    if (position >= this->_brukervalues.children.size())
    {
        throw dicomifier::DicomifierException("No value");
    }
    
    return boost::get<std::string>(this->_brukervalues.children[position]);
}

int 
BrukerFieldData
::get_int(int position) const
{
    return boost::lexical_cast<int>(this->get_string(position));
}

double 
BrukerFieldData
::get_double(int position) const
{
    return boost::lexical_cast<double>(this->get_string(position));
}

BrukerFieldData::Pointer 
BrukerFieldData
::get_struct(int position) const
{
    if (position >= this->_brukervalues.children.size())
    {
        throw dicomifier::DicomifierException("No value");
    }
    
    auto subfield = Self::New();
    
    auto data = boost::get<BrukerValue>(this->_brukervalues.children[position]);
    subfield->set_brukervalues(data);
    
    std::vector<int> vect;
    vect.push_back(data.children.size());
    subfield->set_dimensionNumbers(vect);
    
    return subfield;
}

int 
BrukerFieldData
::get_values_number() const
{
    int dimReturn = 1;
    for (auto value : this->_dimensionNumbers) dimReturn *= value;
    return dimReturn;
}

int 
BrukerFieldData
::parse_dimension(std::string const & data)
{
    boost::cmatch what;
    if (regex_search(data.c_str(), what, RegEx_Dimensionnality))
    {
        std::string valuefind = what[1];
        // remove space
        boost::replace_all(valuefind, " ", "");
        
        // Get dimension separated by ','
        std::vector<std::string> splitvalues;
        boost::split(splitvalues, valuefind, boost::is_any_of(","));
        
        for (auto currentvalue : splitvalues)
        {
            this->_dimensionNumbers.push_back(boost::lexical_cast<int>(currentvalue));
        }
    }
    else
    {
        // Only one value
        this->_dimensionNumbers.push_back(1);
    }
    
    return this->get_values_number();
}

int 
BrukerFieldData
::parse_values(std::string const & data)
{
    std::string value = data;
    
    // Delete dimension
    boost::cmatch what;
    if (regex_search(data.c_str(), what, RegEx_DeleteDimension))
    {
        value = what[1];
    }
    
    // Remove '\n'
    boost::replace_all(value, "\n", "");
    boost::replace_all(value, ", ", ",");
    
    BrukerValue_grammar<std::string::const_iterator> xml;
    BrukerValue ast;
    std::string::const_iterator iter = value.begin();
    std::string::const_iterator end = value.end();
    bool r = phrase_parse(iter, end, xml, boost::spirit::ascii::space, ast);
    if (r && iter == end)
    {
        this->_brukervalues = ast;
    }
    else
    {
        throw DicomifierException("Parsing error");
    }
    
    return this->_brukervalues.children.size();
}

} // namespace bruker

} // namespace dicomifier

