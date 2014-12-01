/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleImageOrientationPatientDcmFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/dicom/ImageOrientationPatientDcmFieldCreator.h"
#include "translator/fields/dicom/ImageOrientationPatientDcmField.h"

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
        ptr.add_child("ImageOrientationPatientDcmField", emptynode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto imageorientationpatientcreator = dicomifier::translator::factory::ImageOrientationPatientDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = imageorientationpatientcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_AE>::Pointer imageorientationpatientAE = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(imageorientationpatientAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = imageorientationpatientcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_AS>::Pointer imageorientationpatientAS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(imageorientationpatientAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = imageorientationpatientcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_CS>::Pointer imageorientationpatientCS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(imageorientationpatientCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = imageorientationpatientcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_DA>::Pointer imageorientationpatientDA = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(imageorientationpatientDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = imageorientationpatientcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_DS>::Pointer imageorientationpatientDS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(imageorientationpatientDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = imageorientationpatientcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_DT>::Pointer imageorientationpatientDT = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(imageorientationpatientDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = imageorientationpatientcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_FL>::Pointer imageorientationpatientFL = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(imageorientationpatientFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = imageorientationpatientcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_FD>::Pointer imageorientationpatientFD = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(imageorientationpatientFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = imageorientationpatientcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_IS>::Pointer imageorientationpatientIS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(imageorientationpatientIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = imageorientationpatientcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_LO>::Pointer imageorientationpatientLO = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(imageorientationpatientLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = imageorientationpatientcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_LT>::Pointer imageorientationpatientLT = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(imageorientationpatientLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = imageorientationpatientcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_PN>::Pointer imageorientationpatientPN = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(imageorientationpatientPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = imageorientationpatientcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_SH>::Pointer imageorientationpatientSH = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(imageorientationpatientSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = imageorientationpatientcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_SL>::Pointer imageorientationpatientSL = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(imageorientationpatientSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = imageorientationpatientcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_SS>::Pointer imageorientationpatientSS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(imageorientationpatientSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = imageorientationpatientcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_ST>::Pointer imageorientationpatientST = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(imageorientationpatientST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = imageorientationpatientcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_TM>::Pointer imageorientationpatientTM = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(imageorientationpatientTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = imageorientationpatientcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_UI>::Pointer imageorientationpatientUI = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(imageorientationpatientUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = imageorientationpatientcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_UL>::Pointer imageorientationpatientUL = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(imageorientationpatientUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = imageorientationpatientcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_US>::Pointer imageorientationpatientUS = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(imageorientationpatientUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = imageorientationpatientcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::ImageOrientationPatientDcmField<EVR_UT>::Pointer imageorientationpatientUT = 
                std::dynamic_pointer_cast<dicomifier::translator::ImageOrientationPatientDcmField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(imageorientationpatientUT != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK01)
{
    auto imageorientationpatientcreator = dicomifier::translator::factory::ImageOrientationPatientDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(imageorientationpatientcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}

