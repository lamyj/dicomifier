/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iostream>

#include <boost/foreach.hpp>

#include "Factory.h"
#include "XmlToRules.h"

namespace dicomifier
{
    
std::vector<Object::Pointer> XmlToRules::Convert(std::string const & filename)
{
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(filename, pt);
    
    std::vector<Object::Pointer> rules = XmlToRules::Convert(pt);
    
    /*BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            pt.get_child("Rule"))
    {
        std::string const second = v.second.get_child("<xmlattr>.type").data();
        auto object = Factory::get_instance().create(second);
        
        rules.push_back(object);
    }*/
        
    return rules;
}

std::vector<Object::Pointer> XmlToRules::Convert(boost::property_tree::ptree & pt)
{
    std::vector<Object::Pointer> rules;
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            pt)
    {
        rules.push_back(Factory::get_instance().create(v));
    }
    
    return rules;
}
    
} // namespace dicomifier
