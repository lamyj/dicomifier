/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleNotCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include "core/conditions/Not.h"
#include "core/Object.h"
#include "factory/core/conditions/NotCreator.h"

struct TestData
{
    boost::property_tree::ptree ptr;
 
    TestData()
    {
        boost::property_tree::ptree truenode;
        boost::property_tree::ptree emptynode;
        truenode.add_child("True", emptynode);
        ptr.add_child("Not", truenode);
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Creation, TestData)
{
    auto testnot = dicomifier::factory::NotCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testnot->Create(v);
        
        dicomifier::conditions::Not::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::Not>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

