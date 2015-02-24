/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleUpperCaseGeneratorCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/generator/UpperCaseGeneratorCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree uppercasegeneratornode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        uppercasegeneratornode.add_child("ConstantField", constantfield);
        ptr.add_child("UpperCaseGenerator", uppercasegeneratornode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto uppercasegeneratorcreator = dicomifier::translator::factory::UpperCaseGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = uppercasegeneratorcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::UpperCaseGenerator<EVR_AE>::Pointer uppercasegeneratorAE = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(uppercasegeneratorAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = uppercasegeneratorcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::UpperCaseGenerator<EVR_AS>::Pointer uppercasegeneratorAS = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(uppercasegeneratorAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = uppercasegeneratorcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::UpperCaseGenerator<EVR_CS>::Pointer uppercasegeneratorCS = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(uppercasegeneratorCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = uppercasegeneratorcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::UpperCaseGenerator<EVR_DA>::Pointer uppercasegeneratorDA = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(uppercasegeneratorDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = uppercasegeneratorcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::UpperCaseGenerator<EVR_DS>::Pointer uppercasegeneratorDS = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(uppercasegeneratorDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = uppercasegeneratorcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::UpperCaseGenerator<EVR_DT>::Pointer uppercasegeneratorDT = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(uppercasegeneratorDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = uppercasegeneratorcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::UpperCaseGenerator<EVR_FL>::Pointer uppercasegeneratorFL = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(uppercasegeneratorFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = uppercasegeneratorcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::UpperCaseGenerator<EVR_FD>::Pointer uppercasegeneratorFD = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(uppercasegeneratorFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = uppercasegeneratorcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::UpperCaseGenerator<EVR_IS>::Pointer uppercasegeneratorIS = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(uppercasegeneratorIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = uppercasegeneratorcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::UpperCaseGenerator<EVR_LO>::Pointer uppercasegeneratorLO = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(uppercasegeneratorLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = uppercasegeneratorcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::UpperCaseGenerator<EVR_LT>::Pointer uppercasegeneratorLT = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(uppercasegeneratorLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = uppercasegeneratorcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::UpperCaseGenerator<EVR_PN>::Pointer uppercasegeneratorPN = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(uppercasegeneratorPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = uppercasegeneratorcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::UpperCaseGenerator<EVR_SH>::Pointer uppercasegeneratorSH = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(uppercasegeneratorSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = uppercasegeneratorcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::UpperCaseGenerator<EVR_SL>::Pointer uppercasegeneratorSL = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(uppercasegeneratorSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = uppercasegeneratorcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::UpperCaseGenerator<EVR_SS>::Pointer uppercasegeneratorSS = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(uppercasegeneratorSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = uppercasegeneratorcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::UpperCaseGenerator<EVR_ST>::Pointer uppercasegeneratorST = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(uppercasegeneratorST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = uppercasegeneratorcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::UpperCaseGenerator<EVR_TM>::Pointer uppercasegeneratorTM = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(uppercasegeneratorTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = uppercasegeneratorcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::UpperCaseGenerator<EVR_UI>::Pointer uppercasegeneratorUI = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(uppercasegeneratorUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = uppercasegeneratorcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::UpperCaseGenerator<EVR_UL>::Pointer uppercasegeneratorUL = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(uppercasegeneratorUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = uppercasegeneratorcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::UpperCaseGenerator<EVR_US>::Pointer uppercasegeneratorUS = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(uppercasegeneratorUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = uppercasegeneratorcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::UpperCaseGenerator<EVR_UT>::Pointer uppercasegeneratorUT = 
                std::dynamic_pointer_cast<dicomifier::translator::UpperCaseGenerator<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(uppercasegeneratorUT != NULL, true);
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
        ptr.add_child("UpperCaseGenerator", emptynode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto uppercasegeneratorcreator = dicomifier::translator::
        factory::UpperCaseGeneratorCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(uppercasegeneratorcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
