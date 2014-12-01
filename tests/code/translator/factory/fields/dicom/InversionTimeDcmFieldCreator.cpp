/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleInversionTimeDcmFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/dicom/InversionTimeDcmFieldCreator.h"
#include "translator/fields/dicom/InversionTimeDcmField.h"

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
        ptr.add_child("InversionTimeDcmField", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto inversiontimecreator = dicomifier::translator::factory::InversionTimeDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = inversiontimecreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::InversionTimeDcmField<EVR_AE>::Pointer inversiontimeAE = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(inversiontimeAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = inversiontimecreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::InversionTimeDcmField<EVR_AS>::Pointer inversiontimeAS = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(inversiontimeAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = inversiontimecreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::InversionTimeDcmField<EVR_CS>::Pointer inversiontimeCS = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(inversiontimeCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = inversiontimecreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::InversionTimeDcmField<EVR_DA>::Pointer inversiontimeDA = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(inversiontimeDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = inversiontimecreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::InversionTimeDcmField<EVR_DS>::Pointer inversiontimeDS = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(inversiontimeDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = inversiontimecreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::InversionTimeDcmField<EVR_DT>::Pointer inversiontimeDT = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(inversiontimeDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = inversiontimecreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::InversionTimeDcmField<EVR_FL>::Pointer inversiontimeFL = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(inversiontimeFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = inversiontimecreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::InversionTimeDcmField<EVR_FD>::Pointer inversiontimeFD = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(inversiontimeFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = inversiontimecreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::InversionTimeDcmField<EVR_IS>::Pointer inversiontimeIS = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(inversiontimeIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = inversiontimecreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::InversionTimeDcmField<EVR_LO>::Pointer inversiontimeLO = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(inversiontimeLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = inversiontimecreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::InversionTimeDcmField<EVR_LT>::Pointer inversiontimeLT = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(inversiontimeLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = inversiontimecreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::InversionTimeDcmField<EVR_PN>::Pointer inversiontimePN = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(inversiontimePN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = inversiontimecreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::InversionTimeDcmField<EVR_SH>::Pointer inversiontimeSH = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(inversiontimeSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = inversiontimecreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::InversionTimeDcmField<EVR_SL>::Pointer inversiontimeSL = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(inversiontimeSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = inversiontimecreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::InversionTimeDcmField<EVR_SS>::Pointer inversiontimeSS = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(inversiontimeSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = inversiontimecreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::InversionTimeDcmField<EVR_ST>::Pointer inversiontimeST = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(inversiontimeST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = inversiontimecreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::InversionTimeDcmField<EVR_TM>::Pointer inversiontimeTM = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(inversiontimeTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = inversiontimecreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::InversionTimeDcmField<EVR_UI>::Pointer inversiontimeUI = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(inversiontimeUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = inversiontimecreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::InversionTimeDcmField<EVR_UL>::Pointer inversiontimeUL = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(inversiontimeUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = inversiontimecreator->Create(v, NULL, EVR_US);
        dicomifier::translator::InversionTimeDcmField<EVR_US>::Pointer inversiontimeUS = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(inversiontimeUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = inversiontimecreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::InversionTimeDcmField<EVR_UT>::Pointer inversiontimeUT = 
                std::dynamic_pointer_cast<dicomifier::translator::InversionTimeDcmField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(inversiontimeUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK01)
{
    auto inversiontimecreator = dicomifier::translator::factory::InversionTimeDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(inversiontimecreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
