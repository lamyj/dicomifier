/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDateGeneratorCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/generator/DateGeneratorCreator.h"

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
        ptr.add_child("DateGenerator", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto dategeneratorcreator = dicomifier::translator::factory::DateGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = dategeneratorcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::DateGenerator<EVR_AE>::Pointer dategeneratorAE = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(dategeneratorAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = dategeneratorcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::DateGenerator<EVR_AS>::Pointer dategeneratorAS = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(dategeneratorAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = dategeneratorcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::DateGenerator<EVR_CS>::Pointer dategeneratorCS = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(dategeneratorCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = dategeneratorcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::DateGenerator<EVR_DA>::Pointer dategeneratorDA = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(dategeneratorDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = dategeneratorcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::DateGenerator<EVR_DS>::Pointer dategeneratorDS = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(dategeneratorDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = dategeneratorcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::DateGenerator<EVR_DT>::Pointer dategeneratorDT = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(dategeneratorDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = dategeneratorcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::DateGenerator<EVR_FL>::Pointer dategeneratorFL = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(dategeneratorFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = dategeneratorcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::DateGenerator<EVR_FD>::Pointer dategeneratorFD = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(dategeneratorFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = dategeneratorcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::DateGenerator<EVR_IS>::Pointer dategeneratorIS = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(dategeneratorIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = dategeneratorcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::DateGenerator<EVR_LO>::Pointer dategeneratorLO = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(dategeneratorLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = dategeneratorcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::DateGenerator<EVR_LT>::Pointer dategeneratorLT = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(dategeneratorLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = dategeneratorcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::DateGenerator<EVR_PN>::Pointer dategeneratorPN = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(dategeneratorPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = dategeneratorcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::DateGenerator<EVR_SH>::Pointer dategeneratorSH = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(dategeneratorSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = dategeneratorcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::DateGenerator<EVR_SL>::Pointer dategeneratorSL = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(dategeneratorSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = dategeneratorcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::DateGenerator<EVR_SS>::Pointer dategeneratorSS = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(dategeneratorSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = dategeneratorcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::DateGenerator<EVR_ST>::Pointer dategeneratorST = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(dategeneratorST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = dategeneratorcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::DateGenerator<EVR_TM>::Pointer dategeneratorTM = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(dategeneratorTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = dategeneratorcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::DateGenerator<EVR_UI>::Pointer dategeneratorUI = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(dategeneratorUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = dategeneratorcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::DateGenerator<EVR_UL>::Pointer dategeneratorUL = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(dategeneratorUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = dategeneratorcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::DateGenerator<EVR_US>::Pointer dategeneratorUS = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(dategeneratorUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = dategeneratorcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::DateGenerator<EVR_UT>::Pointer dategeneratorUT = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(dategeneratorUT != NULL, true);
    }
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Constructor with SubTag
 */
struct TestDataOK02
{
    boost::property_tree::ptree ptr;
 
    TestDataOK02()
    {
        boost::property_tree::ptree dategeneratornode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        dategeneratornode.add_child("ConstantField", constantfield);
        dategeneratornode.put("<xmlattr>.inputformat", "%d%m%Y");
        ptr.add_child("DateGenerator", dategeneratornode);
    }
 
    ~TestDataOK02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    auto dategeneratorcreator = dicomifier::translator::factory::DateGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = dategeneratorcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::DateGenerator<EVR_DA>::Pointer dategeneratorDA = 
                std::dynamic_pointer_cast<dicomifier::translator::DateGenerator<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(dategeneratorDA != NULL, true);
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
        ptr.add_child("DateGenerator", emptynode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto dategeneratorcreator = dicomifier::translator::
        factory::DateGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dategeneratorcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
