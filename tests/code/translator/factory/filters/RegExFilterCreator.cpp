/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleRegExFilterCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/filters/RegExFilterCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree regexfilternode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        regexfilternode.add_child("ConstantField", constantfield);
        regexfilternode.put("<xmlattr>.expression", "^.*");
        ptr.add_child("RegExFilter", regexfilternode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto regexfiltercreator = dicomifier::translator::factory::RegExFilterCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = regexfiltercreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::RegExFilter<EVR_AE>::Pointer regexfilterAE = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(regexfilterAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = regexfiltercreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::RegExFilter<EVR_AS>::Pointer regexfilterAS = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(regexfilterAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = regexfiltercreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::RegExFilter<EVR_CS>::Pointer regexfilterCS = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(regexfilterCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = regexfiltercreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::RegExFilter<EVR_DA>::Pointer regexfilterDA = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(regexfilterDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = regexfiltercreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::RegExFilter<EVR_DS>::Pointer regexfilterDS = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(regexfilterDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = regexfiltercreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::RegExFilter<EVR_DT>::Pointer regexfilterDT = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(regexfilterDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = regexfiltercreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::RegExFilter<EVR_FL>::Pointer regexfilterFL = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(regexfilterFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = regexfiltercreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::RegExFilter<EVR_FD>::Pointer regexfilterFD = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(regexfilterFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = regexfiltercreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::RegExFilter<EVR_IS>::Pointer regexfilterIS = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(regexfilterIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = regexfiltercreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::RegExFilter<EVR_LO>::Pointer regexfilterLO = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(regexfilterLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = regexfiltercreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::RegExFilter<EVR_LT>::Pointer regexfilterLT = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(regexfilterLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = regexfiltercreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::RegExFilter<EVR_PN>::Pointer regexfilterPN = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(regexfilterPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = regexfiltercreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::RegExFilter<EVR_SH>::Pointer regexfilterSH = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(regexfilterSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = regexfiltercreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::RegExFilter<EVR_SL>::Pointer regexfilterSL = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(regexfilterSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = regexfiltercreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::RegExFilter<EVR_SS>::Pointer regexfilterSS = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(regexfilterSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = regexfiltercreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::RegExFilter<EVR_ST>::Pointer regexfilterST = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(regexfilterST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = regexfiltercreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::RegExFilter<EVR_TM>::Pointer regexfilterTM = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(regexfilterTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = regexfiltercreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::RegExFilter<EVR_UI>::Pointer regexfilterUI = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(regexfilterUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = regexfiltercreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::RegExFilter<EVR_UL>::Pointer regexfilterUL = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(regexfilterUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = regexfiltercreator->Create(v, NULL, EVR_US);
        dicomifier::translator::RegExFilter<EVR_US>::Pointer regexfilterUS = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(regexfilterUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = regexfiltercreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::RegExFilter<EVR_UT>::Pointer regexfilterUT = 
                std::dynamic_pointer_cast<dicomifier::translator::RegExFilter<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(regexfilterUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Missing mandatory attribut 'expression'
 */
 struct TestDataKO01
{
    boost::property_tree::ptree ptr;
 
    TestDataKO01()
    {
        boost::property_tree::ptree regexfilternode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        regexfilternode.add_child("ConstantField", constantfield);
        ptr.add_child("RegExFilter", regexfilternode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto regexfiltercreator = dicomifier::translator::factory::RegExFilterCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(regexfiltercreator->Create(v, NULL, EVR_AE), 
                            std::runtime_error);
    }
}
 
/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
struct TestDataKO02
{
    boost::property_tree::ptree ptr;
 
    TestDataKO02()
    {
        boost::property_tree::ptree regexfilternode;
        regexfilternode.put("<xmlattr>.expression", "^.*");
        ptr.add_child("RegExFilter", regexfilternode);
    }
 
    ~TestDataKO02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataKO02)
{
    auto regexfiltercreator = dicomifier::translator::
        factory::RegExFilterCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(regexfiltercreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
