/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDivisionOperatorCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/mathOperators/DivisionOperatorCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree divisionoperatornode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        divisionoperatornode.add_child("ConstantField", constantfield);
        divisionoperatornode.add_child("ConstantField", constantfield);
        ptr.add_child("DivisionOperator", divisionoperatornode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto divisionoperatorcreator = dicomifier::translator::factory::DivisionOperatorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = divisionoperatorcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::DivisionOperator<EVR_AE>::Pointer divisionoperatorAE = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(divisionoperatorAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = divisionoperatorcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::DivisionOperator<EVR_AS>::Pointer divisionoperatorAS = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(divisionoperatorAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = divisionoperatorcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::DivisionOperator<EVR_CS>::Pointer divisionoperatorCS = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(divisionoperatorCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = divisionoperatorcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::DivisionOperator<EVR_DA>::Pointer divisionoperatorDA = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(divisionoperatorDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = divisionoperatorcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::DivisionOperator<EVR_DS>::Pointer divisionoperatorDS = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(divisionoperatorDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = divisionoperatorcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::DivisionOperator<EVR_DT>::Pointer divisionoperatorDT = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(divisionoperatorDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = divisionoperatorcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::DivisionOperator<EVR_FL>::Pointer divisionoperatorFL = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(divisionoperatorFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = divisionoperatorcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::DivisionOperator<EVR_FD>::Pointer divisionoperatorFD = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(divisionoperatorFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = divisionoperatorcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::DivisionOperator<EVR_IS>::Pointer divisionoperatorIS = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(divisionoperatorIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = divisionoperatorcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::DivisionOperator<EVR_LO>::Pointer divisionoperatorLO = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(divisionoperatorLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = divisionoperatorcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::DivisionOperator<EVR_LT>::Pointer divisionoperatorLT = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(divisionoperatorLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = divisionoperatorcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::DivisionOperator<EVR_PN>::Pointer divisionoperatorPN = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(divisionoperatorPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = divisionoperatorcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::DivisionOperator<EVR_SH>::Pointer divisionoperatorSH = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(divisionoperatorSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = divisionoperatorcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::DivisionOperator<EVR_SL>::Pointer divisionoperatorSL = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(divisionoperatorSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = divisionoperatorcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::DivisionOperator<EVR_SS>::Pointer divisionoperatorSS = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(divisionoperatorSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = divisionoperatorcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::DivisionOperator<EVR_ST>::Pointer divisionoperatorST = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(divisionoperatorST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = divisionoperatorcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::DivisionOperator<EVR_TM>::Pointer divisionoperatorTM = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(divisionoperatorTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = divisionoperatorcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::DivisionOperator<EVR_UI>::Pointer divisionoperatorUI = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(divisionoperatorUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = divisionoperatorcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::DivisionOperator<EVR_UL>::Pointer divisionoperatorUL = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(divisionoperatorUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = divisionoperatorcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::DivisionOperator<EVR_US>::Pointer divisionoperatorUS = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(divisionoperatorUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = divisionoperatorcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::DivisionOperator<EVR_UT>::Pointer divisionoperatorUT = 
                std::dynamic_pointer_cast<dicomifier::translator::DivisionOperator<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(divisionoperatorUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
struct TestDataKO01
{
    boost::property_tree::ptree ptr;
 
    TestDataKO01()
    {
        boost::property_tree::ptree emptynode;
        ptr.add_child("DivisionOperator", emptynode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto divisionoperatorcreator = dicomifier::translator::
        factory::DivisionOperatorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(divisionoperatorcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
