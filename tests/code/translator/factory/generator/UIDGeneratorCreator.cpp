/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleUIDGeneratorCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/generator/UIDGeneratorCreator.h"

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
        emptynode.put("<xmlattr>.uidtype", "SOPInstanceUID");
        ptr.add_child("UIDGenerator", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto uidgeneratorcreator = dicomifier::translator::factory::UIDGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = uidgeneratorcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::UIDGenerator<EVR_AE>::Pointer uidgeneratorAE = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(uidgeneratorAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = uidgeneratorcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::UIDGenerator<EVR_AS>::Pointer uidgeneratorAS = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(uidgeneratorAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = uidgeneratorcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::UIDGenerator<EVR_CS>::Pointer uidgeneratorCS = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(uidgeneratorCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = uidgeneratorcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::UIDGenerator<EVR_DA>::Pointer uidgeneratorDA = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(uidgeneratorDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = uidgeneratorcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::UIDGenerator<EVR_DS>::Pointer uidgeneratorDS = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(uidgeneratorDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = uidgeneratorcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::UIDGenerator<EVR_DT>::Pointer uidgeneratorDT = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(uidgeneratorDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = uidgeneratorcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::UIDGenerator<EVR_FL>::Pointer uidgeneratorFL = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(uidgeneratorFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = uidgeneratorcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::UIDGenerator<EVR_FD>::Pointer uidgeneratorFD = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(uidgeneratorFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = uidgeneratorcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::UIDGenerator<EVR_IS>::Pointer uidgeneratorIS = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(uidgeneratorIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = uidgeneratorcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::UIDGenerator<EVR_LO>::Pointer uidgeneratorLO = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(uidgeneratorLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = uidgeneratorcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::UIDGenerator<EVR_LT>::Pointer uidgeneratorLT = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(uidgeneratorLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = uidgeneratorcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::UIDGenerator<EVR_PN>::Pointer uidgeneratorPN = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(uidgeneratorPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = uidgeneratorcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::UIDGenerator<EVR_SH>::Pointer uidgeneratorSH = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(uidgeneratorSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = uidgeneratorcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::UIDGenerator<EVR_SL>::Pointer uidgeneratorSL = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(uidgeneratorSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = uidgeneratorcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::UIDGenerator<EVR_SS>::Pointer uidgeneratorSS = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(uidgeneratorSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = uidgeneratorcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::UIDGenerator<EVR_ST>::Pointer uidgeneratorST = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(uidgeneratorST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = uidgeneratorcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::UIDGenerator<EVR_TM>::Pointer uidgeneratorTM = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(uidgeneratorTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = uidgeneratorcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::UIDGenerator<EVR_UI>::Pointer uidgeneratorUI = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(uidgeneratorUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = uidgeneratorcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::UIDGenerator<EVR_UL>::Pointer uidgeneratorUL = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(uidgeneratorUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = uidgeneratorcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::UIDGenerator<EVR_US>::Pointer uidgeneratorUS = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(uidgeneratorUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = uidgeneratorcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::UIDGenerator<EVR_UT>::Pointer uidgeneratorUT = 
                std::dynamic_pointer_cast<dicomifier::translator::UIDGenerator<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(uidgeneratorUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Missing mandatory attribut 'uidtype'
 */
 struct TestDataKO01
{
    boost::property_tree::ptree ptr;
 
    TestDataKO01()
    {
        boost::property_tree::ptree emptynode;
        ptr.add_child("UIDGenerator", emptynode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto uidgeneratorcreator = dicomifier::translator::factory::UIDGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(uidgeneratorcreator->Create(v, NULL, EVR_AE), 
                            std::runtime_error);
    }
}
 
/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataOK01)
{
    auto uidgeneratorcreator = dicomifier::translator::factory::UIDGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(uidgeneratorcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
