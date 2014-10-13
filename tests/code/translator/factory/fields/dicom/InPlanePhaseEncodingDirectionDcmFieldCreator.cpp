/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleInPlanePhaseEncodingDirectionDcmFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/dicom/InPlanePhaseEncodingDirectionDcmFieldCreator.h"
#include "translator/fields/dicom/InPlanePhaseEncodingDirectionDcmField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree inplanephaseencodingdirnode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "COL\\COL\\COL");
        inplanephaseencodingdirnode.add_child("ConstantField", constantfield);
        ptr.add_child("InPlanePhaseEncodingDirectionDcmField", inplanephaseencodingdirnode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto inplanephaseencodingdircreator = dicomifier::translator::factory::InPlanePhaseEncodingDirectionDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = inplanephaseencodingdircreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_AE>::Pointer inplanephaseencodingdirAE = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = inplanephaseencodingdircreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_AS>::Pointer inplanephaseencodingdirAS = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = inplanephaseencodingdircreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_CS>::Pointer inplanephaseencodingdirCS = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = inplanephaseencodingdircreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_DA>::Pointer inplanephaseencodingdirDA = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = inplanephaseencodingdircreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_DS>::Pointer inplanephaseencodingdirDS = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = inplanephaseencodingdircreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_DT>::Pointer inplanephaseencodingdirDT = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = inplanephaseencodingdircreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_FL>::Pointer inplanephaseencodingdirFL = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = inplanephaseencodingdircreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_FD>::Pointer inplanephaseencodingdirFD = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = inplanephaseencodingdircreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_IS>::Pointer inplanephaseencodingdirIS = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = inplanephaseencodingdircreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_LO>::Pointer inplanephaseencodingdirLO = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = inplanephaseencodingdircreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_LT>::Pointer inplanephaseencodingdirLT = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = inplanephaseencodingdircreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_PN>::Pointer inplanephaseencodingdirPN = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = inplanephaseencodingdircreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_SH>::Pointer inplanephaseencodingdirSH = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = inplanephaseencodingdircreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_SL>::Pointer inplanephaseencodingdirSL = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = inplanephaseencodingdircreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_SS>::Pointer inplanephaseencodingdirSS = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = inplanephaseencodingdircreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_ST>::Pointer inplanephaseencodingdirST = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = inplanephaseencodingdircreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_TM>::Pointer inplanephaseencodingdirTM = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = inplanephaseencodingdircreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_UI>::Pointer inplanephaseencodingdirUI = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = inplanephaseencodingdircreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_UL>::Pointer inplanephaseencodingdirUL = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = inplanephaseencodingdircreator->Create(v, NULL, EVR_US);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_US>::Pointer inplanephaseencodingdirUS = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = inplanephaseencodingdircreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_UT>::Pointer inplanephaseencodingdirUT = 
                std::dynamic_pointer_cast<dicomifier::translator::InPlanePhaseEncodingDirectionDcmField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(inplanephaseencodingdirUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK01)
{
    auto inplanephaseencodingdircreator = dicomifier::translator::factory::InPlanePhaseEncodingDirectionDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(inplanephaseencodingdircreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
