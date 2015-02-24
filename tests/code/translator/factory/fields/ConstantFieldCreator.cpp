/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleConstantFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/ConstantFieldCreator.h"
#include "translator/fields/ConstantField.h"

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
        emptynode.put("<xmlattr>.values", "1");
        ptr.add_child("ConstantField", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto constantfieldcreator = dicomifier::translator::factory::ConstantFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = constantfieldcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::ConstantField<EVR_AE>::Pointer constantfieldAE = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(constantfieldAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = constantfieldcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::ConstantField<EVR_AS>::Pointer constantfieldAS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(constantfieldAS != NULL, true);

        // Test VR = AT
        dicomifier::translator::Tag::Pointer objectAT = constantfieldcreator->Create(v, NULL, EVR_AT);
        dicomifier::translator::ConstantField<EVR_AT>::Pointer constantfieldAT =
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_AT>>(objectAT);
        BOOST_CHECK_EQUAL(constantfieldAT != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = constantfieldcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::ConstantField<EVR_CS>::Pointer constantfieldCS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(constantfieldCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = constantfieldcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::ConstantField<EVR_DA>::Pointer constantfieldDA = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(constantfieldDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = constantfieldcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::ConstantField<EVR_DS>::Pointer constantfieldDS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(constantfieldDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = constantfieldcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::ConstantField<EVR_DT>::Pointer constantfieldDT = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(constantfieldDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = constantfieldcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::ConstantField<EVR_FL>::Pointer constantfieldFL = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(constantfieldFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = constantfieldcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::ConstantField<EVR_FD>::Pointer constantfieldFD = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(constantfieldFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = constantfieldcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::ConstantField<EVR_IS>::Pointer constantfieldIS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(constantfieldIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = constantfieldcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::ConstantField<EVR_LO>::Pointer constantfieldLO = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(constantfieldLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = constantfieldcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::ConstantField<EVR_LT>::Pointer constantfieldLT = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(constantfieldLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = constantfieldcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::ConstantField<EVR_PN>::Pointer constantfieldPN = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(constantfieldPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = constantfieldcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::ConstantField<EVR_SH>::Pointer constantfieldSH = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(constantfieldSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = constantfieldcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::ConstantField<EVR_SL>::Pointer constantfieldSL = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(constantfieldSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = constantfieldcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::ConstantField<EVR_SS>::Pointer constantfieldSS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(constantfieldSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = constantfieldcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::ConstantField<EVR_ST>::Pointer constantfieldST = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(constantfieldST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = constantfieldcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::ConstantField<EVR_TM>::Pointer constantfieldTM = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(constantfieldTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = constantfieldcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::ConstantField<EVR_UI>::Pointer constantfieldUI = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(constantfieldUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = constantfieldcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::ConstantField<EVR_UL>::Pointer constantfieldUL = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(constantfieldUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = constantfieldcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::ConstantField<EVR_US>::Pointer constantfieldUS = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(constantfieldUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = constantfieldcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::ConstantField<EVR_UT>::Pointer constantfieldUT = 
                std::dynamic_pointer_cast<dicomifier::translator::ConstantField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(constantfieldUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Missing mandatory attribut 'values'
 */
 struct TestDataKO01
{
    boost::property_tree::ptree ptr;
 
    TestDataKO01()
    {
        boost::property_tree::ptree emptynode;
        ptr.add_child("ConstantField", emptynode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto constantfieldcreator = dicomifier::translator::factory::ConstantFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(constantfieldcreator->Create(v, NULL, EVR_AE), 
                            std::runtime_error);
    }
}
 
/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataOK01)
{
    auto constantfieldcreator = dicomifier::translator::factory::ConstantFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(constantfieldcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
