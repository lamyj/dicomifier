/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModulePatientSexFilter
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/filters/PatientSexFilter.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::PatientSexFilter<EVR_AE>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::PatientSexFilter<EVR_AS>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::PatientSexFilter<EVR_CS>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::PatientSexFilter<EVR_DA>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::PatientSexFilter<EVR_DS>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::PatientSexFilter<EVR_DT>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::PatientSexFilter<EVR_FL>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::PatientSexFilter<EVR_FD>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::PatientSexFilter<EVR_IS>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::PatientSexFilter<EVR_LO>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::PatientSexFilter<EVR_LT>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::PatientSexFilter<EVR_PN>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::PatientSexFilter<EVR_SH>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::PatientSexFilter<EVR_SL>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::PatientSexFilter<EVR_SS>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::PatientSexFilter<EVR_ST>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::PatientSexFilter<EVR_TM>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::PatientSexFilter<EVR_UI>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::PatientSexFilter<EVR_UL>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::PatientSexFilter<EVR_US>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::PatientSexFilter<EVR_UT>::New();
    // Pointer exists and class type is PatientSexFilter
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_PatientSexFilter);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run (only available for CS)
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto patientsexfilterCS = dicomifier::translator::PatientSexFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("MALE"));
    patientsexfilterCS->run(NULL, {}, NULL);
    auto results = patientsexfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "M");
    
    patientsexfilterCS = dicomifier::translator::PatientSexFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("FEMALE"));
    patientsexfilterCS->run(NULL, {}, NULL);
    results = patientsexfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "F");
    
    patientsexfilterCS = dicomifier::translator::PatientSexFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("UNDEFINED"));
    patientsexfilterCS->run(NULL, {}, NULL);
    results = patientsexfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "O");
    
    patientsexfilterCS = dicomifier::translator::PatientSexFilter<EVR_CS>::
        New(dicomifier::translator::ConstantField<EVR_CS>::New("UNKNOWN"));
    patientsexfilterCS->run(NULL, {}, NULL);
    results = patientsexfilterCS->get_array();
    BOOST_CHECK_EQUAL(results[0], "O");
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Run with bad VR
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    // Test VR = AE
    auto patientsexfilterAE = dicomifier::translator::
        PatientSexFilter<EVR_AE>::
            New(dicomifier::translator::ConstantField<EVR_AE>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterAE->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = AS
    auto patientsexfilterAS = dicomifier::translator::
        PatientSexFilter<EVR_AS>::
            New(dicomifier::translator::ConstantField<EVR_AS>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterAS->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = AT => Not implemented
    
    // Test VR = DA
    auto patientsexfilterDA = dicomifier::translator::
        PatientSexFilter<EVR_DA>::
            New(dicomifier::translator::ConstantField<EVR_DA>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterDA->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = DS
    auto patientsexfilterDS = dicomifier::translator::
        PatientSexFilter<EVR_DS>::
            New(dicomifier::translator::ConstantField<EVR_DS>::New(1));
    BOOST_REQUIRE_THROW(patientsexfilterDS->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = DT
    auto patientsexfilterDT = dicomifier::translator::
        PatientSexFilter<EVR_DT>::
            New(dicomifier::translator::ConstantField<EVR_DT>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterDT->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = FL
    auto patientsexfilterFL = dicomifier::translator::
        PatientSexFilter<EVR_FL>::
            New(dicomifier::translator::ConstantField<EVR_FL>::New(1));
    BOOST_REQUIRE_THROW(patientsexfilterFL->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = FD
    auto patientsexfilterFD = dicomifier::translator::
        PatientSexFilter<EVR_FD>::
            New(dicomifier::translator::ConstantField<EVR_FD>::New(1));
    BOOST_REQUIRE_THROW(patientsexfilterFD->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = IS
    auto patientsexfilterIS = dicomifier::translator::
        PatientSexFilter<EVR_IS>::
            New(dicomifier::translator::ConstantField<EVR_IS>::New(1));
    BOOST_REQUIRE_THROW(patientsexfilterIS->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = LO
    auto patientsexfilterLO = dicomifier::translator::
        PatientSexFilter<EVR_LO>::
            New(dicomifier::translator::ConstantField<EVR_LO>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterLO->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = LT
    auto patientsexfilterLT = dicomifier::translator::
        PatientSexFilter<EVR_LT>::
            New(dicomifier::translator::ConstantField<EVR_LT>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterLT->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto patientsexfilterPN = dicomifier::translator::
        PatientSexFilter<EVR_PN>::
            New(dicomifier::translator::ConstantField<EVR_PN>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterPN->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = SH
    auto patientsexfilterSH = dicomifier::translator::
        PatientSexFilter<EVR_SH>::
            New(dicomifier::translator::ConstantField<EVR_SH>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterSH->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = SL
    auto patientsexfilterSL = dicomifier::translator::
        PatientSexFilter<EVR_SL>::
            New(dicomifier::translator::ConstantField<EVR_SL>::New(1));
    BOOST_REQUIRE_THROW(patientsexfilterSL->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = SQ => Not implemented
                        
    // Test VR = SS
    auto patientsexfilterSS = dicomifier::translator::
        PatientSexFilter<EVR_SS>::
            New(dicomifier::translator::ConstantField<EVR_SS>::New(1));
    BOOST_REQUIRE_THROW(patientsexfilterSS->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = ST
    auto patientsexfilterST = dicomifier::translator::
        PatientSexFilter<EVR_ST>::
            New(dicomifier::translator::ConstantField<EVR_ST>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterST->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = TM
    auto patientsexfilterTM = dicomifier::translator::
        PatientSexFilter<EVR_TM>::
            New(dicomifier::translator::ConstantField<EVR_TM>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterTM->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = UI
    auto patientsexfilterUI = dicomifier::translator::
        PatientSexFilter<EVR_UI>::
            New(dicomifier::translator::ConstantField<EVR_UI>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterUI->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = UL
    auto patientsexfilterUL = dicomifier::translator::
        PatientSexFilter<EVR_UL>::
            New(dicomifier::translator::ConstantField<EVR_UL>::New(1));
    BOOST_REQUIRE_THROW(patientsexfilterUL->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = US
    auto patientsexfilterUS = dicomifier::translator::
        PatientSexFilter<EVR_US>::
            New(dicomifier::translator::ConstantField<EVR_US>::New(1));
    BOOST_REQUIRE_THROW(patientsexfilterUS->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
                        
    // Test VR = UT
    auto patientsexfilterUT = dicomifier::translator::
        PatientSexFilter<EVR_UT>::
            New(dicomifier::translator::ConstantField<EVR_UT>::New("MALE"));
    BOOST_REQUIRE_THROW(patientsexfilterUT->run(NULL, {}, NULL), 
                        dicomifier::DicomifierException);
}

