/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleAcquisitionMatrixDcmFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/dicom/AcquisitionMatrixDcmFieldCreator.h"
#include "translator/fields/dicom/AcquisitionMatrixDcmField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree acquisitionmatrixnode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "64\\64");
        acquisitionmatrixnode.add_child("ConstantField", constantfield);
        ptr.add_child("AcquisitionMatrixDcmField", acquisitionmatrixnode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto acquisitionmatrixcreator = dicomifier::translator::factory::AcquisitionMatrixDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = acquisitionmatrixcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_AE>::Pointer acquisitionmatrixAE = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(acquisitionmatrixAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = acquisitionmatrixcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_AS>::Pointer acquisitionmatrixAS = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(acquisitionmatrixAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = acquisitionmatrixcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_CS>::Pointer acquisitionmatrixCS = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(acquisitionmatrixCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = acquisitionmatrixcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_DA>::Pointer acquisitionmatrixDA = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(acquisitionmatrixDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = acquisitionmatrixcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_DS>::Pointer acquisitionmatrixDS = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(acquisitionmatrixDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = acquisitionmatrixcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_DT>::Pointer acquisitionmatrixDT = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(acquisitionmatrixDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = acquisitionmatrixcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_FL>::Pointer acquisitionmatrixFL = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(acquisitionmatrixFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = acquisitionmatrixcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_FD>::Pointer acquisitionmatrixFD = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(acquisitionmatrixFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = acquisitionmatrixcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_IS>::Pointer acquisitionmatrixIS = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(acquisitionmatrixIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = acquisitionmatrixcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_LO>::Pointer acquisitionmatrixLO = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(acquisitionmatrixLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = acquisitionmatrixcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_LT>::Pointer acquisitionmatrixLT = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(acquisitionmatrixLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = acquisitionmatrixcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_PN>::Pointer acquisitionmatrixPN = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(acquisitionmatrixPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = acquisitionmatrixcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_SH>::Pointer acquisitionmatrixSH = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(acquisitionmatrixSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = acquisitionmatrixcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_SL>::Pointer acquisitionmatrixSL = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(acquisitionmatrixSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = acquisitionmatrixcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_SS>::Pointer acquisitionmatrixSS = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(acquisitionmatrixSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = acquisitionmatrixcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_ST>::Pointer acquisitionmatrixST = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(acquisitionmatrixST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = acquisitionmatrixcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_TM>::Pointer acquisitionmatrixTM = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(acquisitionmatrixTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = acquisitionmatrixcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_UI>::Pointer acquisitionmatrixUI = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(acquisitionmatrixUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = acquisitionmatrixcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_UL>::Pointer acquisitionmatrixUL = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(acquisitionmatrixUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = acquisitionmatrixcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_US>::Pointer acquisitionmatrixUS = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(acquisitionmatrixUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = acquisitionmatrixcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::AcquisitionMatrixDcmField<EVR_UT>::Pointer acquisitionmatrixUT = 
                std::dynamic_pointer_cast<dicomifier::translator::AcquisitionMatrixDcmField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(acquisitionmatrixUT != NULL, true);
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
        ptr.add_child("AcquisitionMatrixDcmField", emptynode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto acquisitionmatrixcreator = dicomifier::translator::
        factory::AcquisitionMatrixDcmFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(acquisitionmatrixcreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}