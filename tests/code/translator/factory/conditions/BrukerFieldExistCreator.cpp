/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerFieldExistCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/conditions/BrukerFieldExistCreator.h"
#include "translator/conditions/BrukerFieldExist.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "MyBrukerField");
        ptr.add_child("BrukerFieldExist", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto brukerfieldexistcreator = 
        dicomifier::translator::factory::BrukerFieldExistCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        auto object = brukerfieldexistcreator->Create(v, NULL, EVR_UN);
        dicomifier::translator::BrukerFieldExist::Pointer brukerfieldexist = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerFieldExist>(object);
        BOOST_CHECK_EQUAL(brukerfieldexist != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Missing mandatory attribut 'name'
 */
 struct TestDataKO01
{
    boost::property_tree::ptree ptr;
 
    TestDataKO01()
    {
        boost::property_tree::ptree emptynode;
        ptr.add_child("BrukerFieldExist", emptynode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto brukerfieldexistcreator = 
        dicomifier::translator::factory::BrukerFieldExistCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(brukerfieldexistcreator->Create(v, NULL, EVR_UN), 
                            std::runtime_error);
    }
}
