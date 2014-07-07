/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleRuleCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include "core/Object.h"
#include "core/Rule.h"
#include "factory/core/RuleCreator.h"

struct TestDataEmpty
{
    boost::property_tree::ptree ptr;
 
    TestDataEmpty()
    {
        boost::property_tree::ptree rulenode;
        boost::property_tree::ptree emptynode;
        rulenode.add_child("Condition", emptynode);
        rulenode.add_child("Actions", emptynode);
        ptr.add_child("Rule", rulenode);
    }
 
    ~TestDataEmpty()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationEmpty, TestDataEmpty)
{
    auto testrule = dicomifier::factory::RuleCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testrule->Create(v);
        
        dicomifier::Rule::Pointer rule = 
                std::dynamic_pointer_cast<dicomifier::Rule>(object);
        
        BOOST_CHECK_EQUAL(rule != NULL, true);
    }
}

struct TestData
{
    boost::property_tree::ptree ptr;
 
    TestData()
    {
        boost::property_tree::ptree rulenode;
        boost::property_tree::ptree condnode;
        boost::property_tree::ptree actnode;
        boost::property_tree::ptree emptynode;
        condnode.add_child("True", emptynode);
        rulenode.add_child("Condition", condnode);
        actnode.add_child("None", emptynode);
        rulenode.add_child("Actions", actnode);
        ptr.add_child("Rule", rulenode);
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Creation, TestData)
{
    auto testrule = dicomifier::factory::RuleCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testrule->Create(v);
        
        dicomifier::Rule::Pointer rule = 
                std::dynamic_pointer_cast<dicomifier::Rule>(object);
        
        BOOST_CHECK_EQUAL(rule != NULL, true);
    }
}

struct TestDataMissingNode
{
    boost::property_tree::ptree ptr1;
    boost::property_tree::ptree ptr2;
 
    TestDataMissingNode()
    {
        boost::property_tree::ptree rule1node;
        boost::property_tree::ptree rule2node;
        boost::property_tree::ptree emptynode;
        
        rule1node.add_child("Actions", emptynode);
        ptr1.add_child("Rule", rule1node);
        
        rule2node.add_child("Condition", emptynode);
        ptr2.add_child("Rule", rule2node);
    }
 
    ~TestDataMissingNode()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(MissingNodeCondition, TestDataMissingNode)
{
    auto testrule = dicomifier::factory::RuleCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr1)
    {
        BOOST_REQUIRE_THROW(testrule->Create(v), dicomifier::DicomifierException);
    }
}

BOOST_FIXTURE_TEST_CASE(MissingNodeActions, TestDataMissingNode)
{
    auto testrule = dicomifier::factory::RuleCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr2)
    {
        BOOST_REQUIRE_THROW(testrule->Create(v), dicomifier::DicomifierException);
    }
}