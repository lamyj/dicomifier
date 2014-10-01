/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModulePatientSexFilterCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/filters/PatientSexFilterCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree patientpositionfilternode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        patientpositionfilternode.add_child("ConstantField", constantfield);
        ptr.add_child("PatientSexFilter", patientpositionfilternode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto patientsexfiltercreator = dicomifier::translator::factory::PatientSexFilterCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = patientsexfiltercreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::PatientSexFilter<EVR_AE>::Pointer patientsexfilterAE = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(patientsexfilterAE != NULL, true);
        
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = patientsexfiltercreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::PatientSexFilter<EVR_AS>::Pointer patientsexfilterAS = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(patientsexfilterAS != NULL, true);
        
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = patientsexfiltercreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::PatientSexFilter<EVR_CS>::Pointer patientsexfilterCS = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(patientsexfilterCS != NULL, true);
        
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = patientsexfiltercreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::PatientSexFilter<EVR_DA>::Pointer patientsexfilterDA = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(patientsexfilterDA != NULL, true);
        
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = patientsexfiltercreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::PatientSexFilter<EVR_DS>::Pointer patientsexfilterDS = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(patientsexfilterDS != NULL, true);
        
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = patientsexfiltercreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::PatientSexFilter<EVR_DT>::Pointer patientsexfilterDT = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(patientsexfilterDT != NULL, true);
        
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = patientsexfiltercreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::PatientSexFilter<EVR_FL>::Pointer patientsexfilterFL = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(patientsexfilterFL != NULL, true);
        
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = patientsexfiltercreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::PatientSexFilter<EVR_FD>::Pointer patientsexfilterFD = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(patientsexfilterFD != NULL, true);
        
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = patientsexfiltercreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::PatientSexFilter<EVR_IS>::Pointer patientsexfilterIS = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(patientsexfilterIS != NULL, true);
        
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = patientsexfiltercreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::PatientSexFilter<EVR_LO>::Pointer patientsexfilterLO = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(patientsexfilterLO != NULL, true);
        
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = patientsexfiltercreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::PatientSexFilter<EVR_LT>::Pointer patientsexfilterLT = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(patientsexfilterLT != NULL, true);
        
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = patientsexfiltercreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::PatientSexFilter<EVR_PN>::Pointer patientsexfilterPN = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(patientsexfilterPN != NULL, true);
        
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = patientsexfiltercreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::PatientSexFilter<EVR_SH>::Pointer patientsexfilterSH = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(patientsexfilterSH != NULL, true);
        
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = patientsexfiltercreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::PatientSexFilter<EVR_SL>::Pointer patientsexfilterSL = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(patientsexfilterSL != NULL, true);
        
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = patientsexfiltercreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::PatientSexFilter<EVR_SS>::Pointer patientsexfilterSS = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(patientsexfilterSS != NULL, true);
        
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = patientsexfiltercreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::PatientSexFilter<EVR_ST>::Pointer patientsexfilterST = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(patientsexfilterST != NULL, true);
        
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = patientsexfiltercreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::PatientSexFilter<EVR_TM>::Pointer patientsexfilterTM = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(patientsexfilterTM != NULL, true);
        
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = patientsexfiltercreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::PatientSexFilter<EVR_UI>::Pointer patientsexfilterUI = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(patientsexfilterUI != NULL, true);
        
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = patientsexfiltercreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::PatientSexFilter<EVR_UL>::Pointer patientsexfilterUL = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(patientsexfilterUL != NULL, true);
        
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = patientsexfiltercreator->Create(v, NULL, EVR_US);
        dicomifier::translator::PatientSexFilter<EVR_US>::Pointer patientsexfilterUS = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(patientsexfilterUS != NULL, true);
        
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = patientsexfiltercreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::PatientSexFilter<EVR_UT>::Pointer patientsexfilterUT = 
                std::dynamic_pointer_cast<dicomifier::translator::PatientSexFilter<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(patientsexfilterUT != NULL, true);
    }
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create SQ element
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK01)
{
    auto patientsexfiltercreator = 
        dicomifier::translator::factory::PatientSexFilterCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = SQ
        BOOST_REQUIRE_THROW(patientsexfiltercreator->Create(v, NULL, EVR_SQ), 
                            dicomifier::DicomifierException);
    }
}

