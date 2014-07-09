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

#include <dcmtk/dcmdata/dctk.h>

#include "core/Object.h"
#include "core/Rule.h"
#include "factory/core/RuleCreator.h"

/********************************* TEST OK *********************************/

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

struct TestDataInput
{
    boost::property_tree::ptree ptr;
 
    TestDataInput()
    {
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_PatientSex, OFString("M"), true);
        dataset->saveFile("./tempfile_testdatainput", EXS_LittleEndianExplicit);
        delete dataset;

        boost::property_tree::ptree rulenode;
        boost::property_tree::ptree inputnode;
        boost::property_tree::ptree emptynode;
        inputnode.put("<xmlattr>.type", "dataset");
        inputnode.put("<xmlattr>.name", "input_dataset");
        inputnode.put("<xmlattr>.value", "./tempfile_testdatainput");
        rulenode.add_child("Input", inputnode);
        rulenode.add_child("Condition", emptynode);
        rulenode.add_child("Actions", emptynode);
        ptr.add_child("Rule", rulenode);
    }
 
    ~TestDataInput()
    {
        remove("./tempfile_testdatainput");
    }
};

BOOST_FIXTURE_TEST_CASE(CreationInput, TestDataInput)
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

struct TestDataOutput
{
    boost::property_tree::ptree ptr;
 
    TestDataOutput()
    {
        boost::property_tree::ptree rulenode;
        boost::property_tree::ptree outputnode;
        boost::property_tree::ptree emptynode;
        outputnode.put("<xmlattr>.type", "file");
        outputnode.put("<xmlattr>.name", "output_file");
        outputnode.put("<xmlattr>.value", "./unknownfile");
        rulenode.add_child("Output", outputnode);
        rulenode.add_child("Condition", emptynode);
        rulenode.add_child("Actions", emptynode);
        ptr.add_child("Rule", rulenode);
    }
 
    ~TestDataOutput()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationOutput, TestDataOutput)
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

/********************************* TEST ERROR *********************************/

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

struct TestDataTooManyNode
{
    boost::property_tree::ptree ptr1;
    boost::property_tree::ptree ptr2;
 
    TestDataTooManyNode()
    {
        boost::property_tree::ptree rule1node;
        boost::property_tree::ptree rule2node;
        boost::property_tree::ptree emptynode;
        
        rule1node.add_child("Condition", emptynode);
        rule1node.add_child("Condition", emptynode);
        rule1node.add_child("Condition", emptynode);
        rule1node.add_child("Actions", emptynode);
        ptr1.add_child("Rule", rule1node);
        
        rule2node.add_child("Condition", emptynode);
        rule2node.add_child("Actions", emptynode);
        rule2node.add_child("Actions", emptynode);
        rule2node.add_child("Actions", emptynode);
        ptr2.add_child("Rule", rule2node);
    }
 
    ~TestDataTooManyNode()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TooManyNodeCondition, TestDataTooManyNode)
{
    auto testrule = dicomifier::factory::RuleCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr1)
    {
        BOOST_REQUIRE_THROW(testrule->Create(v), dicomifier::DicomifierException);
    }
}

BOOST_FIXTURE_TEST_CASE(TooManyNodeActions, TestDataTooManyNode)
{
    auto testrule = dicomifier::factory::RuleCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr2)
    {
        BOOST_REQUIRE_THROW(testrule->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataUnknownType
{
    boost::property_tree::ptree ptr;
 
    TestDataUnknownType()
    {
        boost::property_tree::ptree rulenode;
        boost::property_tree::ptree outputnode;
        boost::property_tree::ptree emptynode;
        outputnode.put("<xmlattr>.type", "UnkownType");
        outputnode.put("<xmlattr>.name", "output_file");
        outputnode.put("<xmlattr>.value", "./unknownfile");
        rulenode.add_child("Output", outputnode);
        rulenode.add_child("Condition", emptynode);
        rulenode.add_child("Actions", emptynode);
        ptr.add_child("Rule", rulenode);
    }
 
    ~TestDataUnknownType()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(UnknownType, TestDataUnknownType)
{
    auto testrule = dicomifier::factory::RuleCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testrule->Create(v), dicomifier::DicomifierException);
    }
}
