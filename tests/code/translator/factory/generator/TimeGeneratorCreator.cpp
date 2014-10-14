/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleTimeGeneratorCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/generator/TimeGeneratorCreator.h"

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
        ptr.add_child("TimeGenerator", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto timegeneratorcreator = dicomifier::translator::factory::TimeGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = timegeneratorcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::TimeGenerator<EVR_AE>::Pointer timegeneratorAE = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(timegeneratorAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = timegeneratorcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::TimeGenerator<EVR_AS>::Pointer timegeneratorAS = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(timegeneratorAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = timegeneratorcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::TimeGenerator<EVR_CS>::Pointer timegeneratorCS = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(timegeneratorCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = timegeneratorcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::TimeGenerator<EVR_DA>::Pointer timegeneratorDA = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(timegeneratorDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = timegeneratorcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::TimeGenerator<EVR_DS>::Pointer timegeneratorDS = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(timegeneratorDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = timegeneratorcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::TimeGenerator<EVR_DT>::Pointer timegeneratorDT = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(timegeneratorDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = timegeneratorcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::TimeGenerator<EVR_FL>::Pointer timegeneratorFL = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(timegeneratorFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = timegeneratorcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::TimeGenerator<EVR_FD>::Pointer timegeneratorFD = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(timegeneratorFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = timegeneratorcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::TimeGenerator<EVR_IS>::Pointer timegeneratorIS = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(timegeneratorIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = timegeneratorcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::TimeGenerator<EVR_LO>::Pointer timegeneratorLO = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(timegeneratorLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = timegeneratorcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::TimeGenerator<EVR_LT>::Pointer timegeneratorLT = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(timegeneratorLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = timegeneratorcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::TimeGenerator<EVR_PN>::Pointer timegeneratorPN = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(timegeneratorPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = timegeneratorcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::TimeGenerator<EVR_SH>::Pointer timegeneratorSH = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(timegeneratorSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = timegeneratorcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::TimeGenerator<EVR_SL>::Pointer timegeneratorSL = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(timegeneratorSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = timegeneratorcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::TimeGenerator<EVR_SS>::Pointer timegeneratorSS = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(timegeneratorSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = timegeneratorcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::TimeGenerator<EVR_ST>::Pointer timegeneratorST = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(timegeneratorST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = timegeneratorcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::TimeGenerator<EVR_TM>::Pointer timegeneratorTM = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(timegeneratorTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = timegeneratorcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::TimeGenerator<EVR_UI>::Pointer timegeneratorUI = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(timegeneratorUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = timegeneratorcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::TimeGenerator<EVR_UL>::Pointer timegeneratorUL = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(timegeneratorUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = timegeneratorcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::TimeGenerator<EVR_US>::Pointer timegeneratorUS = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(timegeneratorUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = timegeneratorcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::TimeGenerator<EVR_UT>::Pointer timegeneratorUT = 
                std::dynamic_pointer_cast<dicomifier::translator::TimeGenerator<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(timegeneratorUT != NULL, true);
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
        ptr.add_child("TimeGenerator", emptynode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto timegeneratorcreator = dicomifier::translator::
        factory::TimeGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(timegeneratorcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
