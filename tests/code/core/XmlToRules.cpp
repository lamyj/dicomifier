/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleXmlToRules
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/XmlToRules.h"

struct TestData
{
    std::string filename;
     
    TestData() : filename("./testfile_xmltorule.xml")
    {
        boost::property_tree::ptree ptr;
        boost::property_tree::ptree emptynode;
        ptr.add_child("True", emptynode);
        
        boost::property_tree::xml_parser::write_xml(filename, ptr);
    }
 
    ~TestData()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(ConvertFile, TestData)
{
    auto vect = dicomifier::XmlToRules::Convert(filename);
    BOOST_CHECK_EQUAL(vect.size(), 1);
}
 
