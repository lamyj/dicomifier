/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleTranslatorFactory
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/TranslatorFactory.h"
#include "translator/factory/fields/TestFieldCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    dicomifier::translator::TranslatorFactory::get_instance();
    dicomifier::translator::TranslatorFactory::delete_instance();
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Register
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    // Clean current instance (if exist)
    dicomifier::translator::TranslatorFactory::delete_instance();
    
    dicomifier::translator::TranslatorFactory& factory_ = 
        dicomifier::translator::TranslatorFactory::get_instance();
    
    BOOST_CHECK_EQUAL(factory_.can_create("TestField"), false);
    
    factory_.register_<dicomifier::translator::factory::TestFieldCreator>();
    
    BOOST_CHECK_EQUAL(factory_.can_create("TestField"), true);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Creation (Existing Class)
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    dicomifier::translator::TranslatorFactory& factory_ = 
        dicomifier::translator::TranslatorFactory::get_instance();
    
    boost::property_tree::ptree emptynode;
    boost::property_tree::ptree ptrOK;
    ptrOK.add_child("TestField", emptynode);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrOK)
    {
        BOOST_CHECK_EQUAL(factory_.create(v1, NULL, EVR_UN) != NULL, true);
    }
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Creation (Non-Existing Class)
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    dicomifier::translator::TranslatorFactory& factory_ = 
        dicomifier::translator::TranslatorFactory::get_instance();
    
    boost::property_tree::ptree emptynode;
    boost::property_tree::ptree ptrOK;
    ptrOK.add_child("UnknownedClass", emptynode);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrOK)
    {
        BOOST_CHECK_EQUAL(factory_.create(v1, NULL, EVR_UN) == NULL, true);
    }
}
