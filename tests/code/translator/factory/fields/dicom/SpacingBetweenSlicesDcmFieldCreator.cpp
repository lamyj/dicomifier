/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleSpacingBetweenSlicesDcmFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/dicom/SpacingBetweenSlicesDcmFieldCreator.h"
#include "translator/fields/dicom/SpacingBetweenSlicesDcmField.h"

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
        ptr.add_child("SpacingBetweenSlicesDcmField", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto spacingbetweenslicescreator = dicomifier::translator::factory::SpacingBetweenSlicesDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = spacingbetweenslicescreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_AE>::Pointer spacingbetweenslicesAE = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(spacingbetweenslicesAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = spacingbetweenslicescreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_AS>::Pointer spacingbetweenslicesAS = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(spacingbetweenslicesAS != NULL, true);

        // Test VR = AT
        dicomifier::translator::Tag::Pointer objectAT = spacingbetweenslicescreator->Create(v, NULL, EVR_AT);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_AT>::Pointer spacingbetweenslicesAT =
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_AT>>(objectAT);
        BOOST_CHECK_EQUAL(spacingbetweenslicesAT != NULL, true);

        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = spacingbetweenslicescreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_CS>::Pointer spacingbetweenslicesCS = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(spacingbetweenslicesCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = spacingbetweenslicescreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_DA>::Pointer spacingbetweenslicesDA = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(spacingbetweenslicesDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = spacingbetweenslicescreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_DS>::Pointer spacingbetweenslicesDS = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(spacingbetweenslicesDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = spacingbetweenslicescreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_DT>::Pointer spacingbetweenslicesDT = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(spacingbetweenslicesDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = spacingbetweenslicescreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_FL>::Pointer spacingbetweenslicesFL = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(spacingbetweenslicesFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = spacingbetweenslicescreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_FD>::Pointer spacingbetweenslicesFD = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(spacingbetweenslicesFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = spacingbetweenslicescreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_IS>::Pointer spacingbetweenslicesIS = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(spacingbetweenslicesIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = spacingbetweenslicescreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_LO>::Pointer spacingbetweenslicesLO = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(spacingbetweenslicesLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = spacingbetweenslicescreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_LT>::Pointer spacingbetweenslicesLT = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(spacingbetweenslicesLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = spacingbetweenslicescreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_PN>::Pointer spacingbetweenslicesPN = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(spacingbetweenslicesPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = spacingbetweenslicescreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_SH>::Pointer spacingbetweenslicesSH = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(spacingbetweenslicesSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = spacingbetweenslicescreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_SL>::Pointer spacingbetweenslicesSL = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(spacingbetweenslicesSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = spacingbetweenslicescreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_SS>::Pointer spacingbetweenslicesSS = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(spacingbetweenslicesSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = spacingbetweenslicescreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_ST>::Pointer spacingbetweenslicesST = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(spacingbetweenslicesST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = spacingbetweenslicescreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_TM>::Pointer spacingbetweenslicesTM = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(spacingbetweenslicesTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = spacingbetweenslicescreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_UI>::Pointer spacingbetweenslicesUI = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(spacingbetweenslicesUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = spacingbetweenslicescreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_UL>::Pointer spacingbetweenslicesUL = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(spacingbetweenslicesUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = spacingbetweenslicescreator->Create(v, NULL, EVR_US);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_US>::Pointer spacingbetweenslicesUS = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(spacingbetweenslicesUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = spacingbetweenslicescreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_UT>::Pointer spacingbetweenslicesUT = 
                std::dynamic_pointer_cast<dicomifier::translator::SpacingBetweenSlicesDcmField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(spacingbetweenslicesUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK01)
{
    auto spacingbetweenslicescreator = dicomifier::translator::
        factory::SpacingBetweenSlicesDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(spacingbetweenslicescreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
