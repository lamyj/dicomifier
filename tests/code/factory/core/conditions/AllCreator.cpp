/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleAllCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include "core/conditions/All.h"
#include "core/Object.h"
#include "factory/core/conditions/AllCreator.h"

struct TestData
{
    boost::property_tree::ptree ptr;
 
    TestData()
    {
        boost::property_tree::ptree allnode;
        ptr.add_child("All", allnode);
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Creation, TestData)
{
    auto testall = dicomifier::factory::AllCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testall->Create(v);
        
        dicomifier::conditions::All::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::All>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}


