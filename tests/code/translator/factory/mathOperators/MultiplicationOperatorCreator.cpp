/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleMultiplicationOperatorCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/mathOperators/MultiplicationOperatorCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree multiplicationoperatornode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        multiplicationoperatornode.add_child("ConstantField", constantfield);
        multiplicationoperatornode.add_child("ConstantField", constantfield);
        ptr.add_child("MultiplicationOperator", multiplicationoperatornode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto multiplicationoperatorcreator = dicomifier::translator::factory::MultiplicationOperatorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = multiplicationoperatorcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::MultiplicationOperator<EVR_AE>::Pointer multiplicationoperatorAE = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(multiplicationoperatorAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = multiplicationoperatorcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::MultiplicationOperator<EVR_AS>::Pointer multiplicationoperatorAS = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(multiplicationoperatorAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = multiplicationoperatorcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::MultiplicationOperator<EVR_CS>::Pointer multiplicationoperatorCS = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(multiplicationoperatorCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = multiplicationoperatorcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::MultiplicationOperator<EVR_DA>::Pointer multiplicationoperatorDA = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(multiplicationoperatorDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = multiplicationoperatorcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::MultiplicationOperator<EVR_DS>::Pointer multiplicationoperatorDS = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(multiplicationoperatorDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = multiplicationoperatorcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::MultiplicationOperator<EVR_DT>::Pointer multiplicationoperatorDT = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(multiplicationoperatorDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = multiplicationoperatorcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::MultiplicationOperator<EVR_FL>::Pointer multiplicationoperatorFL = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(multiplicationoperatorFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = multiplicationoperatorcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::MultiplicationOperator<EVR_FD>::Pointer multiplicationoperatorFD = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(multiplicationoperatorFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = multiplicationoperatorcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::MultiplicationOperator<EVR_IS>::Pointer multiplicationoperatorIS = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(multiplicationoperatorIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = multiplicationoperatorcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::MultiplicationOperator<EVR_LO>::Pointer multiplicationoperatorLO = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(multiplicationoperatorLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = multiplicationoperatorcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::MultiplicationOperator<EVR_LT>::Pointer multiplicationoperatorLT = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(multiplicationoperatorLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = multiplicationoperatorcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::MultiplicationOperator<EVR_PN>::Pointer multiplicationoperatorPN = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(multiplicationoperatorPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = multiplicationoperatorcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::MultiplicationOperator<EVR_SH>::Pointer multiplicationoperatorSH = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(multiplicationoperatorSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = multiplicationoperatorcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::MultiplicationOperator<EVR_SL>::Pointer multiplicationoperatorSL = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(multiplicationoperatorSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = multiplicationoperatorcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::MultiplicationOperator<EVR_SS>::Pointer multiplicationoperatorSS = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(multiplicationoperatorSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = multiplicationoperatorcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::MultiplicationOperator<EVR_ST>::Pointer multiplicationoperatorST = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(multiplicationoperatorST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = multiplicationoperatorcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::MultiplicationOperator<EVR_TM>::Pointer multiplicationoperatorTM = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(multiplicationoperatorTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = multiplicationoperatorcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::MultiplicationOperator<EVR_UI>::Pointer multiplicationoperatorUI = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(multiplicationoperatorUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = multiplicationoperatorcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::MultiplicationOperator<EVR_UL>::Pointer multiplicationoperatorUL = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(multiplicationoperatorUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = multiplicationoperatorcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::MultiplicationOperator<EVR_US>::Pointer multiplicationoperatorUS = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(multiplicationoperatorUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = multiplicationoperatorcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::MultiplicationOperator<EVR_UT>::Pointer multiplicationoperatorUT = 
                std::dynamic_pointer_cast<dicomifier::translator::MultiplicationOperator<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(multiplicationoperatorUT != NULL, true);
    }
}
