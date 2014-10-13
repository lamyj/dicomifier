/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleInstanceNumberDcmFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/dicom/InstanceNumberDcmFieldCreator.h"
#include "translator/fields/dicom/InstanceNumberDcmField.h"

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
        ptr.add_child("InstanceNumberDcmField", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto instancenumbercreator = dicomifier::translator::factory::InstanceNumberDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = instancenumbercreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::InstanceNumberDcmField<EVR_AE>::Pointer instancenumberAE = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(instancenumberAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = instancenumbercreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::InstanceNumberDcmField<EVR_AS>::Pointer instancenumberAS = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(instancenumberAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = instancenumbercreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::InstanceNumberDcmField<EVR_CS>::Pointer instancenumberCS = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(instancenumberCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = instancenumbercreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::InstanceNumberDcmField<EVR_DA>::Pointer instancenumberDA = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(instancenumberDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = instancenumbercreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::InstanceNumberDcmField<EVR_DS>::Pointer instancenumberDS = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(instancenumberDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = instancenumbercreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::InstanceNumberDcmField<EVR_DT>::Pointer instancenumberDT = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(instancenumberDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = instancenumbercreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::InstanceNumberDcmField<EVR_FL>::Pointer instancenumberFL = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(instancenumberFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = instancenumbercreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::InstanceNumberDcmField<EVR_FD>::Pointer instancenumberFD = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(instancenumberFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = instancenumbercreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::InstanceNumberDcmField<EVR_IS>::Pointer instancenumberIS = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(instancenumberIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = instancenumbercreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::InstanceNumberDcmField<EVR_LO>::Pointer instancenumberLO = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(instancenumberLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = instancenumbercreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::InstanceNumberDcmField<EVR_LT>::Pointer instancenumberLT = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(instancenumberLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = instancenumbercreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::InstanceNumberDcmField<EVR_PN>::Pointer instancenumberPN = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(instancenumberPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = instancenumbercreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::InstanceNumberDcmField<EVR_SH>::Pointer instancenumberSH = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(instancenumberSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = instancenumbercreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::InstanceNumberDcmField<EVR_SL>::Pointer instancenumberSL = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(instancenumberSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = instancenumbercreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::InstanceNumberDcmField<EVR_SS>::Pointer instancenumberSS = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(instancenumberSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = instancenumbercreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::InstanceNumberDcmField<EVR_ST>::Pointer instancenumberST = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(instancenumberST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = instancenumbercreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::InstanceNumberDcmField<EVR_TM>::Pointer instancenumberTM = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(instancenumberTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = instancenumbercreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::InstanceNumberDcmField<EVR_UI>::Pointer instancenumberUI = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(instancenumberUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = instancenumbercreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::InstanceNumberDcmField<EVR_UL>::Pointer instancenumberUL = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(instancenumberUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = instancenumbercreator->Create(v, NULL, EVR_US);
        dicomifier::translator::InstanceNumberDcmField<EVR_US>::Pointer instancenumberUS = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(instancenumberUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = instancenumbercreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::InstanceNumberDcmField<EVR_UT>::Pointer instancenumberUT = 
                std::dynamic_pointer_cast<dicomifier::translator::InstanceNumberDcmField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(instancenumberUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK01)
{
    auto instancenumbercreator = dicomifier::translator::factory::InstanceNumberDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(instancenumbercreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
