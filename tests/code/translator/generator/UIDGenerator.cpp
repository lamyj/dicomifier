/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleUIDGenerator
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/generator/UIDGenerator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::UIDGenerator<EVR_AE>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::UIDGenerator<EVR_AS>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::UIDGenerator<EVR_CS>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::UIDGenerator<EVR_DA>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::UIDGenerator<EVR_DS>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::UIDGenerator<EVR_DT>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::UIDGenerator<EVR_FL>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::UIDGenerator<EVR_FD>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::UIDGenerator<EVR_IS>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::UIDGenerator<EVR_LO>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::UIDGenerator<EVR_LT>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::UIDGenerator<EVR_PN>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::UIDGenerator<EVR_SH>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::UIDGenerator<EVR_SL>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::UIDGenerator<EVR_SS>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::UIDGenerator<EVR_ST>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::UIDGenerator<EVR_TM>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::UIDGenerator<EVR_UI>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::UIDGenerator<EVR_UL>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::UIDGenerator<EVR_US>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::UIDGenerator<EVR_UT>::New();
    // Pointer exists and class type is UIDGenerator
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_UIDGenerator);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run SOPInstanceUID
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    // Test VR = AE
    auto uidgeneratorAE = dicomifier::translator::UIDGenerator<EVR_AE>::
        New("SOPInstanceUID");
    uidgeneratorAE->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsAE = uidgeneratorAE->get_array();
    std::string const valueAE(resultsAE[0].c_str());
    BOOST_CHECK_EQUAL(valueAE.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = AS
    auto uidgeneratorAS = dicomifier::translator::UIDGenerator<EVR_AS>::
        New("SOPInstanceUID");
    uidgeneratorAS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsAS = uidgeneratorAS->get_array();
    std::string const valueAS(resultsAS[0].c_str());
    BOOST_CHECK_EQUAL(valueAS.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto uidgeneratorCS = dicomifier::translator::UIDGenerator<EVR_CS>::
        New("SOPInstanceUID");
    uidgeneratorCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsCS = uidgeneratorCS->get_array();
    std::string const valueCS(resultsCS[0].c_str());
    BOOST_CHECK_EQUAL(valueCS.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
    
    // Test VR = DA
    auto uidgeneratorDA = dicomifier::translator::UIDGenerator<EVR_DA>::
        New("SOPInstanceUID");
    uidgeneratorDA->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDA = uidgeneratorDA->get_array();
    std::string const valueDA(resultsDA[0].c_str());
    BOOST_CHECK_EQUAL(valueDA.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = DS => not String VR
                        
    // Test VR = DT
    auto uidgeneratorDT = dicomifier::translator::UIDGenerator<EVR_DT>::
        New("SOPInstanceUID");
    uidgeneratorDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsDT = uidgeneratorDT->get_array();
    std::string const valueDT(resultsDT[0].c_str());
    BOOST_CHECK_EQUAL(valueDT.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = FL => not String VR
                        
    // Test VR = FD => not String VR
                        
    // Test VR = IS => not String VR
                        
    // Test VR = LO
    auto uidgeneratorLO = dicomifier::translator::UIDGenerator<EVR_LO>::
        New("SOPInstanceUID");
    uidgeneratorLO->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsLO = uidgeneratorLO->get_array();
    std::string const valueLO(resultsLO[0].c_str());
    BOOST_CHECK_EQUAL(valueLO.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = LT
    auto uidgeneratorLT = dicomifier::translator::UIDGenerator<EVR_LT>::
        New("SOPInstanceUID");
    uidgeneratorLT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsLT = uidgeneratorLT->get_array();
    std::string const valueLT(resultsLT[0].c_str());
    BOOST_CHECK_EQUAL(valueLT.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto uidgeneratorPN = dicomifier::translator::UIDGenerator<EVR_PN>::
        New("SOPInstanceUID");
    uidgeneratorPN->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsPN = uidgeneratorPN->get_array();
    std::string const valuePN(resultsPN[0].c_str());
    BOOST_CHECK_EQUAL(valuePN.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = SH
    auto uidgeneratorSH = dicomifier::translator::UIDGenerator<EVR_SH>::
        New("SOPInstanceUID");
    uidgeneratorSH->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsSH = uidgeneratorSH->get_array();
    std::string const valueSH(resultsSH[0].c_str());
    BOOST_CHECK_EQUAL(valueSH.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = SL => not String VR
                        
    // Test VR = SQ => Not implemented
                        
    // Test VR = SS => not String VR
                        
    // Test VR = ST
    auto uidgeneratorST = dicomifier::translator::UIDGenerator<EVR_ST>::
        New("SOPInstanceUID");
    uidgeneratorST->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsST = uidgeneratorST->get_array();
    std::string const valueST(resultsST[0].c_str());
    BOOST_CHECK_EQUAL(valueST.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = TM
    auto uidgeneratorTM = dicomifier::translator::UIDGenerator<EVR_TM>::
        New("SOPInstanceUID");
    uidgeneratorTM->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsTM = uidgeneratorTM->get_array();
    std::string const valueTM(resultsTM[0].c_str());
    BOOST_CHECK_EQUAL(valueTM.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = UI
    auto uidgeneratorUI = dicomifier::translator::UIDGenerator<EVR_UI>::
        New("SOPInstanceUID");
    uidgeneratorUI->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUI = uidgeneratorUI->get_array();
    std::string const valueUI(resultsUI[0].c_str());
    BOOST_CHECK_EQUAL(valueUI.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
                        
    // Test VR = UL => not String VR
                        
    // Test VR = US => not String VR
                        
    // Test VR = UT
    auto uidgeneratorUT = dicomifier::translator::UIDGenerator<EVR_UT>::
        New("SOPInstanceUID");
    uidgeneratorUT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto resultsUT = uidgeneratorUT->get_array();
    std::string const valueUT(resultsUT[0].c_str());
    BOOST_CHECK_EQUAL(valueUT.find(SITE_INSTANCE_UID_ROOT) != std::string::npos, true);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run without UID type
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    // Test VR = UI
    auto uidgeneratorUI = dicomifier::translator::UIDGenerator<EVR_UI>::New();
    uidgeneratorUI->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(uidgeneratorUI->get_array().size(), 0);
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Run with bad UID type
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    // Test VR = UI
    auto uidgeneratorUI = dicomifier::translator::UIDGenerator<EVR_UI>::
        New("BadValue");
    uidgeneratorUI->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(uidgeneratorUI->get_array().size(), 0);
}
