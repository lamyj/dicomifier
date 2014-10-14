/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/BrukerFieldCreator.h"
#include "translator/fields/BrukerField.h"

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
        emptynode.put("<xmlattr>.name", "BrukerDataName");
        ptr.add_child("BrukerField", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto brukerfieldcreator = dicomifier::translator::factory::BrukerFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = brukerfieldcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::BrukerField<EVR_AE>::Pointer brukerfieldAE = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(brukerfieldAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = brukerfieldcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::BrukerField<EVR_AS>::Pointer brukerfieldAS = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(brukerfieldAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = brukerfieldcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::BrukerField<EVR_CS>::Pointer brukerfieldCS = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(brukerfieldCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = brukerfieldcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::BrukerField<EVR_DA>::Pointer brukerfieldDA = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(brukerfieldDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = brukerfieldcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::BrukerField<EVR_DS>::Pointer brukerfieldDS = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(brukerfieldDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = brukerfieldcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::BrukerField<EVR_DT>::Pointer brukerfieldDT = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(brukerfieldDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = brukerfieldcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::BrukerField<EVR_FL>::Pointer brukerfieldFL = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(brukerfieldFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = brukerfieldcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::BrukerField<EVR_FD>::Pointer brukerfieldFD = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(brukerfieldFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = brukerfieldcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::BrukerField<EVR_IS>::Pointer brukerfieldIS = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(brukerfieldIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = brukerfieldcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::BrukerField<EVR_LO>::Pointer brukerfieldLO = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(brukerfieldLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = brukerfieldcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::BrukerField<EVR_LT>::Pointer brukerfieldLT = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(brukerfieldLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = brukerfieldcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::BrukerField<EVR_PN>::Pointer brukerfieldPN = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(brukerfieldPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = brukerfieldcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::BrukerField<EVR_SH>::Pointer brukerfieldSH = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(brukerfieldSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = brukerfieldcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::BrukerField<EVR_SL>::Pointer brukerfieldSL = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(brukerfieldSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = brukerfieldcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::BrukerField<EVR_SS>::Pointer brukerfieldSS = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(brukerfieldSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = brukerfieldcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::BrukerField<EVR_ST>::Pointer brukerfieldST = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(brukerfieldST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = brukerfieldcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::BrukerField<EVR_TM>::Pointer brukerfieldTM = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(brukerfieldTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = brukerfieldcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::BrukerField<EVR_UI>::Pointer brukerfieldUI = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(brukerfieldUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = brukerfieldcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::BrukerField<EVR_UL>::Pointer brukerfieldUL = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(brukerfieldUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = brukerfieldcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::BrukerField<EVR_US>::Pointer brukerfieldUS = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(brukerfieldUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = brukerfieldcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::BrukerField<EVR_UT>::Pointer brukerfieldUT = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(brukerfieldUT != NULL, true);
    }
}
 
/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Constructor with Specific Range
 */
struct TestDataOK02
{
    boost::property_tree::ptree ptr;
 
    TestDataOK02()
    {
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.name", "BrukerDataName");
        emptynode.put("<xmlattr>.range", "0,1");
        ptr.add_child("BrukerField", emptynode);
    }
 
    ~TestDataOK02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    auto brukerfieldcreator = dicomifier::translator::factory::BrukerFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = brukerfieldcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::BrukerField<EVR_CS>::Pointer brukerfieldCS = 
                std::dynamic_pointer_cast<dicomifier::translator::BrukerField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(brukerfieldCS != NULL, true);
    }
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Missing mandatory attribut 'name'
 */
 struct TestDataKO01
{
    boost::property_tree::ptree ptr;
 
    TestDataKO01()
    {
        boost::property_tree::ptree emptynode;
        ptr.add_child("BrukerField", emptynode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto brukerfieldcreator = dicomifier::translator::factory::BrukerFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(brukerfieldcreator->Create(v, NULL, EVR_AE), 
                            std::runtime_error);
    }
}
 
/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataOK01)
{
    auto brukerfieldcreator = dicomifier::translator::factory::BrukerFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(brukerfieldcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
