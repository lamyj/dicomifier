/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModulePatientPositionFilter
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/filters/PatientPositionFilter.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::PatientPositionFilter<EVR_AE>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::PatientPositionFilter<EVR_AS>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::PatientPositionFilter<EVR_CS>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::PatientPositionFilter<EVR_DA>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::PatientPositionFilter<EVR_DS>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::PatientPositionFilter<EVR_DT>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::PatientPositionFilter<EVR_FL>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::PatientPositionFilter<EVR_FD>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::PatientPositionFilter<EVR_IS>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::PatientPositionFilter<EVR_LO>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::PatientPositionFilter<EVR_LT>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::PatientPositionFilter<EVR_PN>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::PatientPositionFilter<EVR_SH>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::PatientPositionFilter<EVR_SL>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::PatientPositionFilter<EVR_SS>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::PatientPositionFilter<EVR_ST>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::PatientPositionFilter<EVR_TM>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::PatientPositionFilter<EVR_UI>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::PatientPositionFilter<EVR_UL>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::PatientPositionFilter<EVR_US>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::PatientPositionFilter<EVR_UT>::New();
    // Pointer exists and class type is PatientPositionFilter
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_PatientPositionFilter);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run (only available for CS)
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto patientpositionfilterCS = dicomifier::translator::PatientPositionFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("Head_Supine"));
    patientpositionfilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    auto results = patientpositionfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "HFS");
    
    patientpositionfilterCS = dicomifier::translator::PatientPositionFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("Head_Prone"));
    patientpositionfilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = patientpositionfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "HFP");
    
    patientpositionfilterCS = dicomifier::translator::PatientPositionFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("Head_Left"));
    patientpositionfilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = patientpositionfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "HFDL");
    
    patientpositionfilterCS = dicomifier::translator::PatientPositionFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("Head_Right"));
    patientpositionfilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = patientpositionfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "HFDR");
    
    patientpositionfilterCS = dicomifier::translator::PatientPositionFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("Foot_Supine"));
    patientpositionfilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = patientpositionfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "FFS");
    
    patientpositionfilterCS = dicomifier::translator::PatientPositionFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("Foot_Prone"));
    patientpositionfilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = patientpositionfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "FFP");
    
    patientpositionfilterCS = dicomifier::translator::PatientPositionFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("Foot_Left"));
    patientpositionfilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = patientpositionfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "FFDL");
    
    patientpositionfilterCS = dicomifier::translator::PatientPositionFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("Foot_Right"));
    patientpositionfilterCS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
    results = patientpositionfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "FFDR");
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Run with bad VR
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    // Test VR = AE
    auto patientpositionfilterAE = dicomifier::translator::
        PatientPositionFilter<EVR_AE>::
            New(dicomifier::translator::ConstantField<EVR_AE>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterAE->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = AS
    auto patientpositionfilterAS = dicomifier::translator::
        PatientPositionFilter<EVR_AS>::
            New(dicomifier::translator::ConstantField<EVR_AS>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterAS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = AT => Not implemented
    
    // Test VR = DA
    auto patientpositionfilterDA = dicomifier::translator::
        PatientPositionFilter<EVR_DA>::
            New(dicomifier::translator::ConstantField<EVR_DA>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterDA->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = DS
    auto patientpositionfilterDS = dicomifier::translator::
        PatientPositionFilter<EVR_DS>::
            New(dicomifier::translator::ConstantField<EVR_DS>::New(1));
    BOOST_REQUIRE_THROW(patientpositionfilterDS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = DT
    auto patientpositionfilterDT = dicomifier::translator::
        PatientPositionFilter<EVR_DT>::
            New(dicomifier::translator::ConstantField<EVR_DT>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterDT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = FL
    auto patientpositionfilterFL = dicomifier::translator::
        PatientPositionFilter<EVR_FL>::
            New(dicomifier::translator::ConstantField<EVR_FL>::New(1));
    BOOST_REQUIRE_THROW(patientpositionfilterFL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = FD
    auto patientpositionfilterFD = dicomifier::translator::
        PatientPositionFilter<EVR_FD>::
            New(dicomifier::translator::ConstantField<EVR_FD>::New(1));
    BOOST_REQUIRE_THROW(patientpositionfilterFD->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = IS
    auto patientpositionfilterIS = dicomifier::translator::
        PatientPositionFilter<EVR_IS>::
            New(dicomifier::translator::ConstantField<EVR_IS>::New(1));
    BOOST_REQUIRE_THROW(patientpositionfilterIS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = LO
    auto patientpositionfilterLO = dicomifier::translator::
        PatientPositionFilter<EVR_LO>::
            New(dicomifier::translator::ConstantField<EVR_LO>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterLO->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = LT
    auto patientpositionfilterLT = dicomifier::translator::
        PatientPositionFilter<EVR_LT>::
            New(dicomifier::translator::ConstantField<EVR_LT>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterLT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto patientpositionfilterPN = dicomifier::translator::
        PatientPositionFilter<EVR_PN>::
            New(dicomifier::translator::ConstantField<EVR_PN>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterPN->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = SH
    auto patientpositionfilterSH = dicomifier::translator::
        PatientPositionFilter<EVR_SH>::
            New(dicomifier::translator::ConstantField<EVR_SH>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterSH->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = SL
    auto patientpositionfilterSL = dicomifier::translator::
        PatientPositionFilter<EVR_SL>::
            New(dicomifier::translator::ConstantField<EVR_SL>::New(1));
    BOOST_REQUIRE_THROW(patientpositionfilterSL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = SQ => Not implemented
                        
    // Test VR = SS
    auto patientpositionfilterSS = dicomifier::translator::
        PatientPositionFilter<EVR_SS>::
            New(dicomifier::translator::ConstantField<EVR_SS>::New(1));
    BOOST_REQUIRE_THROW(patientpositionfilterSS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = ST
    auto patientpositionfilterST = dicomifier::translator::
        PatientPositionFilter<EVR_ST>::
            New(dicomifier::translator::ConstantField<EVR_ST>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterST->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = TM
    auto patientpositionfilterTM = dicomifier::translator::
        PatientPositionFilter<EVR_TM>::
            New(dicomifier::translator::ConstantField<EVR_TM>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterTM->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = UI
    auto patientpositionfilterUI = dicomifier::translator::
        PatientPositionFilter<EVR_UI>::
            New(dicomifier::translator::ConstantField<EVR_UI>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterUI->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = UL
    auto patientpositionfilterUL = dicomifier::translator::
        PatientPositionFilter<EVR_UL>::
            New(dicomifier::translator::ConstantField<EVR_UL>::New(1));
    BOOST_REQUIRE_THROW(patientpositionfilterUL->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = US
    auto patientpositionfilterUS = dicomifier::translator::
        PatientPositionFilter<EVR_US>::
            New(dicomifier::translator::ConstantField<EVR_US>::New(1));
    BOOST_REQUIRE_THROW(patientpositionfilterUS->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = UT
    auto patientpositionfilterUT = dicomifier::translator::
        PatientPositionFilter<EVR_UT>::
            New(dicomifier::translator::ConstantField<EVR_UT>::New("Head_Supine"));
    BOOST_REQUIRE_THROW(patientpositionfilterUT->run(NULL, dicomifier::FrameIndexGenerator({}), NULL), 
                        dicomifier::DicomifierException);
}
