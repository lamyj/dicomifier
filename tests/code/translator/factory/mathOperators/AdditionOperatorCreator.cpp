/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleAdditionOperatorCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/mathOperators/AdditionOperatorCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree additionoperatornode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        additionoperatornode.add_child("ConstantField", constantfield);
        additionoperatornode.add_child("ConstantField", constantfield);
        ptr.add_child("AdditionOperator", additionoperatornode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto additionoperatorcreator = dicomifier::translator::factory::AdditionOperatorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = additionoperatorcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::AdditionOperator<EVR_AE>::Pointer additionoperatorAE = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(additionoperatorAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = additionoperatorcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::AdditionOperator<EVR_AS>::Pointer additionoperatorAS = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(additionoperatorAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = additionoperatorcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::AdditionOperator<EVR_CS>::Pointer additionoperatorCS = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(additionoperatorCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = additionoperatorcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::AdditionOperator<EVR_DA>::Pointer additionoperatorDA = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(additionoperatorDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = additionoperatorcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::AdditionOperator<EVR_DS>::Pointer additionoperatorDS = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(additionoperatorDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = additionoperatorcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::AdditionOperator<EVR_DT>::Pointer additionoperatorDT = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(additionoperatorDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = additionoperatorcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::AdditionOperator<EVR_FL>::Pointer additionoperatorFL = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(additionoperatorFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = additionoperatorcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::AdditionOperator<EVR_FD>::Pointer additionoperatorFD = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(additionoperatorFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = additionoperatorcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::AdditionOperator<EVR_IS>::Pointer additionoperatorIS = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(additionoperatorIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = additionoperatorcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::AdditionOperator<EVR_LO>::Pointer additionoperatorLO = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(additionoperatorLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = additionoperatorcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::AdditionOperator<EVR_LT>::Pointer additionoperatorLT = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(additionoperatorLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = additionoperatorcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::AdditionOperator<EVR_PN>::Pointer additionoperatorPN = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(additionoperatorPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = additionoperatorcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::AdditionOperator<EVR_SH>::Pointer additionoperatorSH = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(additionoperatorSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = additionoperatorcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::AdditionOperator<EVR_SL>::Pointer additionoperatorSL = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(additionoperatorSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = additionoperatorcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::AdditionOperator<EVR_SS>::Pointer additionoperatorSS = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(additionoperatorSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = additionoperatorcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::AdditionOperator<EVR_ST>::Pointer additionoperatorST = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(additionoperatorST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = additionoperatorcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::AdditionOperator<EVR_TM>::Pointer additionoperatorTM = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(additionoperatorTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = additionoperatorcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::AdditionOperator<EVR_UI>::Pointer additionoperatorUI = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(additionoperatorUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = additionoperatorcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::AdditionOperator<EVR_UL>::Pointer additionoperatorUL = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(additionoperatorUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = additionoperatorcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::AdditionOperator<EVR_US>::Pointer additionoperatorUS = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(additionoperatorUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = additionoperatorcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::AdditionOperator<EVR_UT>::Pointer additionoperatorUT = 
                std::dynamic_pointer_cast<dicomifier::translator::AdditionOperator<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(additionoperatorUT != NULL, true);
    }
}
