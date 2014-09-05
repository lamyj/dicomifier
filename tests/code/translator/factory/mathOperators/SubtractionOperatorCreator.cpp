/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleSubtractionOperatorCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/mathOperators/SubtractionOperatorCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree subtractionoperatornode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        subtractionoperatornode.add_child("ConstantField", constantfield);
        subtractionoperatornode.add_child("ConstantField", constantfield);
        ptr.add_child("SubtractionOperator", subtractionoperatornode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto subtractionoperatorcreator = dicomifier::translator::factory::SubtractionOperatorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = subtractionoperatorcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::SubtractionOperator<EVR_AE>::Pointer subtractionoperatorAE = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(subtractionoperatorAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = subtractionoperatorcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::SubtractionOperator<EVR_AS>::Pointer subtractionoperatorAS = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(subtractionoperatorAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = subtractionoperatorcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::SubtractionOperator<EVR_CS>::Pointer subtractionoperatorCS = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(subtractionoperatorCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = subtractionoperatorcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::SubtractionOperator<EVR_DA>::Pointer subtractionoperatorDA = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(subtractionoperatorDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = subtractionoperatorcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::SubtractionOperator<EVR_DS>::Pointer subtractionoperatorDS = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(subtractionoperatorDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = subtractionoperatorcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::SubtractionOperator<EVR_DT>::Pointer subtractionoperatorDT = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(subtractionoperatorDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = subtractionoperatorcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::SubtractionOperator<EVR_FL>::Pointer subtractionoperatorFL = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(subtractionoperatorFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = subtractionoperatorcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::SubtractionOperator<EVR_FD>::Pointer subtractionoperatorFD = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(subtractionoperatorFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = subtractionoperatorcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::SubtractionOperator<EVR_IS>::Pointer subtractionoperatorIS = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(subtractionoperatorIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = subtractionoperatorcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::SubtractionOperator<EVR_LO>::Pointer subtractionoperatorLO = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(subtractionoperatorLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = subtractionoperatorcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::SubtractionOperator<EVR_LT>::Pointer subtractionoperatorLT = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(subtractionoperatorLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = subtractionoperatorcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::SubtractionOperator<EVR_PN>::Pointer subtractionoperatorPN = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(subtractionoperatorPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = subtractionoperatorcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::SubtractionOperator<EVR_SH>::Pointer subtractionoperatorSH = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(subtractionoperatorSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = subtractionoperatorcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::SubtractionOperator<EVR_SL>::Pointer subtractionoperatorSL = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(subtractionoperatorSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = subtractionoperatorcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::SubtractionOperator<EVR_SS>::Pointer subtractionoperatorSS = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(subtractionoperatorSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = subtractionoperatorcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::SubtractionOperator<EVR_ST>::Pointer subtractionoperatorST = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(subtractionoperatorST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = subtractionoperatorcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::SubtractionOperator<EVR_TM>::Pointer subtractionoperatorTM = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(subtractionoperatorTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = subtractionoperatorcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::SubtractionOperator<EVR_UI>::Pointer subtractionoperatorUI = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(subtractionoperatorUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = subtractionoperatorcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::SubtractionOperator<EVR_UL>::Pointer subtractionoperatorUL = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(subtractionoperatorUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = subtractionoperatorcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::SubtractionOperator<EVR_US>::Pointer subtractionoperatorUS = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(subtractionoperatorUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = subtractionoperatorcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::SubtractionOperator<EVR_UT>::Pointer subtractionoperatorUT = 
                std::dynamic_pointer_cast<dicomifier::translator::SubtractionOperator<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(subtractionoperatorUT != NULL, true);
    }
}
