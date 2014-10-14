/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleConditionFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/conditions/ConditionFieldCreator.h"
#include "translator/conditions/ConditionField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree conditionfieldnode;
        boost::property_tree::ptree ifnode;
        boost::property_tree::ptree thennode;
        boost::property_tree::ptree elsenode;
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "MyBrukerField");
        ifnode.add_child("BrukerFieldExist", emptynode);
        boost::property_tree::ptree emptynode1;
        emptynode1.put("<xmlattr>.values", "1");
        thennode.add_child("ConstantField", emptynode1);
        boost::property_tree::ptree emptynode2;
        emptynode2.put("<xmlattr>.values", "2");
        elsenode.add_child("ConstantField", emptynode2);
        conditionfieldnode.add_child("If", ifnode);
        conditionfieldnode.add_child("Then", thennode);
        conditionfieldnode.add_child("Else", elsenode);
        ptr.add_child("ConditionField", conditionfieldnode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto conditionfieldcreator = dicomifier::translator::factory::ConditionFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = conditionfieldcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::ConditionField<EVR_AE>::Pointer conditionfieldAE = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(conditionfieldAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = conditionfieldcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::ConditionField<EVR_AS>::Pointer conditionfieldAS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(conditionfieldAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = conditionfieldcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::ConditionField<EVR_CS>::Pointer conditionfieldCS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(conditionfieldCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = conditionfieldcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::ConditionField<EVR_DA>::Pointer conditionfieldDA = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(conditionfieldDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = conditionfieldcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::ConditionField<EVR_DS>::Pointer conditionfieldDS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(conditionfieldDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = conditionfieldcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::ConditionField<EVR_DT>::Pointer conditionfieldDT = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(conditionfieldDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = conditionfieldcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::ConditionField<EVR_FL>::Pointer conditionfieldFL = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(conditionfieldFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = conditionfieldcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::ConditionField<EVR_FD>::Pointer conditionfieldFD = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(conditionfieldFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = conditionfieldcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::ConditionField<EVR_IS>::Pointer conditionfieldIS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(conditionfieldIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = conditionfieldcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::ConditionField<EVR_LO>::Pointer conditionfieldLO = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(conditionfieldLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = conditionfieldcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::ConditionField<EVR_LT>::Pointer conditionfieldLT = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(conditionfieldLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = conditionfieldcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::ConditionField<EVR_PN>::Pointer conditionfieldPN = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(conditionfieldPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = conditionfieldcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::ConditionField<EVR_SH>::Pointer conditionfieldSH = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(conditionfieldSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = conditionfieldcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::ConditionField<EVR_SL>::Pointer conditionfieldSL = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(conditionfieldSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = conditionfieldcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::ConditionField<EVR_SS>::Pointer conditionfieldSS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(conditionfieldSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = conditionfieldcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::ConditionField<EVR_ST>::Pointer conditionfieldST = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(conditionfieldST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = conditionfieldcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::ConditionField<EVR_TM>::Pointer conditionfieldTM = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(conditionfieldTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = conditionfieldcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::ConditionField<EVR_UI>::Pointer conditionfieldUI = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(conditionfieldUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = conditionfieldcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::ConditionField<EVR_UL>::Pointer conditionfieldUL = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(conditionfieldUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = conditionfieldcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::ConditionField<EVR_US>::Pointer conditionfieldUS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(conditionfieldUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = conditionfieldcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::ConditionField<EVR_UT>::Pointer conditionfieldUT = 
                std::dynamic_pointer_cast<dicomifier::translator::ConditionField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(conditionfieldUT != NULL, true);
    }
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Missing mandatory tag 'If'
 */
 struct TestDataKO01
{
    boost::property_tree::ptree ptr;
 
    TestDataKO01()
    {
        boost::property_tree::ptree conditionfieldnode;
        boost::property_tree::ptree ifnode;
        boost::property_tree::ptree thennode;
        boost::property_tree::ptree elsenode;
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "MyBrukerField");
        ifnode.add_child("BrukerFieldExist", emptynode);
        boost::property_tree::ptree emptynode1;
        emptynode1.put("<xmlattr>.values", "1");
        thennode.add_child("ConstantField", emptynode1);
        boost::property_tree::ptree emptynode2;
        emptynode2.put("<xmlattr>.values", "2");
        elsenode.add_child("ConstantField", emptynode2);
        //conditionfieldnode.add_child("If", ifnode);
        conditionfieldnode.add_child("Then", thennode);
        conditionfieldnode.add_child("Else", elsenode);
        ptr.add_child("ConditionField", conditionfieldnode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto conditionfieldcreator = dicomifier::translator::factory::ConditionFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(conditionfieldcreator->Create(v, NULL, EVR_AE), 
                            dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Missing mandatory tag 'Then'
 */
 struct TestDataKO02
{
    boost::property_tree::ptree ptr;
 
    TestDataKO02()
    {
        boost::property_tree::ptree conditionfieldnode;
        boost::property_tree::ptree ifnode;
        boost::property_tree::ptree thennode;
        boost::property_tree::ptree elsenode;
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "MyBrukerField");
        ifnode.add_child("BrukerFieldExist", emptynode);
        boost::property_tree::ptree emptynode1;
        emptynode1.put("<xmlattr>.values", "1");
        thennode.add_child("ConstantField", emptynode1);
        boost::property_tree::ptree emptynode2;
        emptynode2.put("<xmlattr>.values", "2");
        elsenode.add_child("ConstantField", emptynode2);
        conditionfieldnode.add_child("If", ifnode);
        //conditionfieldnode.add_child("Then", thennode);
        conditionfieldnode.add_child("Else", elsenode);
        ptr.add_child("ConditionField", conditionfieldnode);
    }
 
    ~TestDataKO02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataKO02)
{
    auto conditionfieldcreator = dicomifier::translator::factory::ConditionFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(conditionfieldcreator->Create(v, NULL, EVR_AE), 
                            dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Missing mandatory tag 'Else'
 */
 struct TestDataKO03
{
    boost::property_tree::ptree ptr;
 
    TestDataKO03()
    {
        boost::property_tree::ptree conditionfieldnode;
        boost::property_tree::ptree ifnode;
        boost::property_tree::ptree thennode;
        boost::property_tree::ptree elsenode;
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "MyBrukerField");
        ifnode.add_child("BrukerFieldExist", emptynode);
        boost::property_tree::ptree emptynode1;
        emptynode1.put("<xmlattr>.values", "1");
        thennode.add_child("ConstantField", emptynode1);
        boost::property_tree::ptree emptynode2;
        emptynode2.put("<xmlattr>.values", "2");
        elsenode.add_child("ConstantField", emptynode2);
        conditionfieldnode.add_child("If", ifnode);
        conditionfieldnode.add_child("Then", thennode);
        //conditionfieldnode.add_child("Else", elsenode);
        ptr.add_child("ConditionField", conditionfieldnode);
    }
 
    ~TestDataKO03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataKO03)
{
    auto conditionfieldcreator = dicomifier::translator::factory::ConditionFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(conditionfieldcreator->Create(v, NULL, EVR_AE), 
                            dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 04 *******************************/
/**
 * Error test case: Too many tag 'If'
 */
 struct TestDataKO04
{
    boost::property_tree::ptree ptr;
 
    TestDataKO04()
    {
        boost::property_tree::ptree conditionfieldnode;
        boost::property_tree::ptree ifnode;
        boost::property_tree::ptree thennode;
        boost::property_tree::ptree elsenode;
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "MyBrukerField");
        ifnode.add_child("BrukerFieldExist", emptynode);
        boost::property_tree::ptree emptynode1;
        emptynode1.put("<xmlattr>.values", "1");
        thennode.add_child("ConstantField", emptynode1);
        boost::property_tree::ptree emptynode2;
        emptynode2.put("<xmlattr>.values", "2");
        elsenode.add_child("ConstantField", emptynode2);
        conditionfieldnode.add_child("If", ifnode);
        conditionfieldnode.add_child("If", ifnode);
        conditionfieldnode.add_child("Then", thennode);
        conditionfieldnode.add_child("Else", elsenode);
        ptr.add_child("ConditionField", conditionfieldnode);
    }
 
    ~TestDataKO04()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_04, TestDataKO04)
{
    auto conditionfieldcreator = dicomifier::translator::factory::ConditionFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(conditionfieldcreator->Create(v, NULL, EVR_AE), 
                            dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 05 *******************************/
/**
 * Error test case: Too many tag 'Then'
 */
 struct TestDataKO05
{
    boost::property_tree::ptree ptr;
 
    TestDataKO05()
    {
        boost::property_tree::ptree conditionfieldnode;
        boost::property_tree::ptree ifnode;
        boost::property_tree::ptree thennode;
        boost::property_tree::ptree elsenode;
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "MyBrukerField");
        ifnode.add_child("BrukerFieldExist", emptynode);
        boost::property_tree::ptree emptynode1;
        emptynode1.put("<xmlattr>.values", "1");
        thennode.add_child("ConstantField", emptynode1);
        boost::property_tree::ptree emptynode2;
        emptynode2.put("<xmlattr>.values", "2");
        elsenode.add_child("ConstantField", emptynode2);
        conditionfieldnode.add_child("If", ifnode);
        conditionfieldnode.add_child("Then", thennode);
        conditionfieldnode.add_child("Then", thennode);
        conditionfieldnode.add_child("Else", elsenode);
        ptr.add_child("ConditionField", conditionfieldnode);
    }
 
    ~TestDataKO05()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_05, TestDataKO05)
{
    auto conditionfieldcreator = dicomifier::translator::factory::ConditionFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(conditionfieldcreator->Create(v, NULL, EVR_AE), 
                            dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 06 *******************************/
/**
 * Error test case: Too many tag 'Else'
 */
 struct TestDataKO06
{
    boost::property_tree::ptree ptr;
 
    TestDataKO06()
    {
        boost::property_tree::ptree conditionfieldnode;
        boost::property_tree::ptree ifnode;
        boost::property_tree::ptree thennode;
        boost::property_tree::ptree elsenode;
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "MyBrukerField");
        ifnode.add_child("BrukerFieldExist", emptynode);
        boost::property_tree::ptree emptynode1;
        emptynode1.put("<xmlattr>.values", "1");
        thennode.add_child("ConstantField", emptynode1);
        boost::property_tree::ptree emptynode2;
        emptynode2.put("<xmlattr>.values", "2");
        elsenode.add_child("ConstantField", emptynode2);
        conditionfieldnode.add_child("If", ifnode);
        conditionfieldnode.add_child("Then", thennode);
        conditionfieldnode.add_child("Else", elsenode);
        conditionfieldnode.add_child("Else", elsenode);
        ptr.add_child("ConditionField", conditionfieldnode);
    }
 
    ~TestDataKO06()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_06, TestDataKO06)
{
    auto conditionfieldcreator = dicomifier::translator::factory::ConditionFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(conditionfieldcreator->Create(v, NULL, EVR_AE), 
                            dicomifier::DicomifierException);
    }
}
 
/*************************** TEST KO 07 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
struct TestDataKO07
{
    boost::property_tree::ptree ptr;
 
    TestDataKO07()
    {
        boost::property_tree::ptree conditionfieldnode;
        boost::property_tree::ptree ifnode;
        boost::property_tree::ptree thennode;
        boost::property_tree::ptree elsenode;
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "MyBrukerField");
        ifnode.add_child("BrukerFieldExist", emptynode);
        conditionfieldnode.add_child("If", ifnode);
        conditionfieldnode.add_child("Then", thennode);
        conditionfieldnode.add_child("Else", elsenode);
        ptr.add_child("ConditionField", conditionfieldnode);
    }
 
    ~TestDataKO07()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_07, TestDataKO07)
{
    auto conditionfieldcreator = dicomifier::translator::factory::ConditionFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(conditionfieldcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
