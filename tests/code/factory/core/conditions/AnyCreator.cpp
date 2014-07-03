/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleAnyCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include "core/conditions/Any.h"
#include "core/Object.h"
#include "factory/core/conditions/AnyCreator.h"

struct TestDataEmpty
{
    boost::property_tree::ptree ptr;
 
    TestDataEmpty()
    {
        boost::property_tree::ptree anynode;
        ptr.add_child("Any", anynode);
    }
 
    ~TestDataEmpty()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationEmpty, TestDataEmpty)
{
    auto testany = dicomifier::factory::AnyCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testany->Create(v);
        
        dicomifier::conditions::Any::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::Any>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

struct TestData
{
    boost::property_tree::ptree ptr;
 
    TestData()
    {
        boost::property_tree::ptree anynode;
        boost::property_tree::ptree emptynode;
        anynode.add_child("True", emptynode);
        ptr.add_child("Any", anynode);
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Creation, TestData)
{
    auto testany = dicomifier::factory::AnyCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testany->Create(v);
        
        dicomifier::conditions::Any::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::Any>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}
