/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleImagePositionPatientDcmFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/dicom/ImagePositionPatientDcmFieldCreator.h"
#include "translator/fields/dicom/ImagePositionPatientDcmField.h"

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
        ptr.add_child("ImagePositionPatientDcmField", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto imagepositionpatientcreator = dicomifier::translator::factory::ImagePositionPatientDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = imagepositionpatientcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_AE>::Pointer imagepositionpatientAE = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(imagepositionpatientAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = imagepositionpatientcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_AS>::Pointer imagepositionpatientAS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(imagepositionpatientAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = imagepositionpatientcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_CS>::Pointer imagepositionpatientCS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(imagepositionpatientCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = imagepositionpatientcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_DA>::Pointer imagepositionpatientDA = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(imagepositionpatientDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = imagepositionpatientcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_DS>::Pointer imagepositionpatientDS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(imagepositionpatientDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = imagepositionpatientcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_DT>::Pointer imagepositionpatientDT = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(imagepositionpatientDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = imagepositionpatientcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_FL>::Pointer imagepositionpatientFL = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(imagepositionpatientFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = imagepositionpatientcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_FD>::Pointer imagepositionpatientFD = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(imagepositionpatientFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = imagepositionpatientcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_IS>::Pointer imagepositionpatientIS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(imagepositionpatientIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = imagepositionpatientcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_LO>::Pointer imagepositionpatientLO = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(imagepositionpatientLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = imagepositionpatientcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_LT>::Pointer imagepositionpatientLT = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(imagepositionpatientLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = imagepositionpatientcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_PN>::Pointer imagepositionpatientPN = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(imagepositionpatientPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = imagepositionpatientcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_SH>::Pointer imagepositionpatientSH = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(imagepositionpatientSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = imagepositionpatientcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_SL>::Pointer imagepositionpatientSL = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(imagepositionpatientSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = imagepositionpatientcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_SS>::Pointer imagepositionpatientSS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(imagepositionpatientSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = imagepositionpatientcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_ST>::Pointer imagepositionpatientST = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(imagepositionpatientST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = imagepositionpatientcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_TM>::Pointer imagepositionpatientTM = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(imagepositionpatientTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = imagepositionpatientcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_UI>::Pointer imagepositionpatientUI = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(imagepositionpatientUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = imagepositionpatientcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_UL>::Pointer imagepositionpatientUL = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(imagepositionpatientUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = imagepositionpatientcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_US>::Pointer imagepositionpatientUS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(imagepositionpatientUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = imagepositionpatientcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::ImagePositionPatientDcmField<EVR_UT>::Pointer imagepositionpatientUT = 
                std::dynamic_pointer_cast<dicomifier::translator::ImagePositionPatientDcmField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(imagepositionpatientUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK01)
{
    auto imagepositionpatientcreator = dicomifier::translator::factory::ImagePositionPatientDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(imagepositionpatientcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}
