/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleInstanceNumberDcmField
#include <boost/test/unit_test.hpp>

#include "translator/fields/dicom/InstanceNumberDcmField.h"
#include "core/FrameIndexGenerator.h"

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::
            InstanceNumberDcmField<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK(testfieldae != NULL);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::
            InstanceNumberDcmField<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldas != NULL);
    
    // Test VR = AT
    auto testfieldat = dicomifier::translator::
            InstanceNumberDcmField<EVR_AT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldat != NULL);
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            InstanceNumberDcmField<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldcs != NULL);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::
            InstanceNumberDcmField<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK(testfieldda != NULL);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::
            InstanceNumberDcmField<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldds != NULL);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::
            InstanceNumberDcmField<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK(testfielddt != NULL);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::
            InstanceNumberDcmField<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldfl != NULL);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::
            InstanceNumberDcmField<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK(testfieldfd != NULL);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::
            InstanceNumberDcmField<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldis != NULL);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::
            InstanceNumberDcmField<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK(testfieldlo != NULL);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::
            InstanceNumberDcmField<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldlt != NULL);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::
            InstanceNumberDcmField<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK(testfieldpn != NULL);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::
            InstanceNumberDcmField<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK(testfieldsh != NULL);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::
            InstanceNumberDcmField<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldsl != NULL);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::
            InstanceNumberDcmField<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldss != NULL);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::
            InstanceNumberDcmField<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK(testfieldst != NULL);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::
            InstanceNumberDcmField<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK(testfieldtm != NULL);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::
            InstanceNumberDcmField<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK(testfieldui != NULL);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::
            InstanceNumberDcmField<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldul != NULL);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::
            InstanceNumberDcmField<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK(testfieldus != NULL);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::
            InstanceNumberDcmField<EVR_UT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldut != NULL);
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::
            InstanceNumberDcmField<EVR_AE>::New();
    testfieldae->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldae->get_array().size(), 1);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::
            InstanceNumberDcmField<EVR_AS>::New();
    testfieldas->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldas->get_array().size(), 1);
    
    // Test VR = AT
    auto testfieldat = dicomifier::translator::
            InstanceNumberDcmField<EVR_AT>::New();
    testfieldat->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldat->get_array().size(), 1);
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            InstanceNumberDcmField<EVR_CS>::New();
    testfieldcs->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::
            InstanceNumberDcmField<EVR_DA>::New();
    testfieldda->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldda->get_array().size(), 1);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::
            InstanceNumberDcmField<EVR_DS>::New();
    testfieldds->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldds->get_array().size(), 1);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::
            InstanceNumberDcmField<EVR_DT>::New();
    testfielddt->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfielddt->get_array().size(), 1);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::
            InstanceNumberDcmField<EVR_FL>::New();
    testfieldfl->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldfl->get_array().size(), 1);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::
            InstanceNumberDcmField<EVR_FD>::New();
    testfieldfd->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldfd->get_array().size(), 1);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::
            InstanceNumberDcmField<EVR_IS>::New();
    testfieldis->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldis->get_array().size(), 1);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::
            InstanceNumberDcmField<EVR_LO>::New();
    testfieldlo->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldlo->get_array().size(), 1);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::
            InstanceNumberDcmField<EVR_LT>::New();
    testfieldlt->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldlt->get_array().size(), 1);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::
            InstanceNumberDcmField<EVR_PN>::New();
    testfieldpn->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldpn->get_array().size(), 1);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::
            InstanceNumberDcmField<EVR_SH>::New();
    testfieldsh->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldsh->get_array().size(), 1);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::
            InstanceNumberDcmField<EVR_SL>::New();
    testfieldsl->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldsl->get_array().size(), 1);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::
            InstanceNumberDcmField<EVR_SS>::New();
    testfieldss->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldss->get_array().size(), 1);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::
            InstanceNumberDcmField<EVR_ST>::New();
    testfieldst->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldst->get_array().size(), 1);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::
            InstanceNumberDcmField<EVR_TM>::New();
    testfieldtm->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldtm->get_array().size(), 1);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::
            InstanceNumberDcmField<EVR_UI>::New();
    testfieldui->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldui->get_array().size(), 1);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::
            InstanceNumberDcmField<EVR_UL>::New();
    testfieldul->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldul->get_array().size(), 1);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::
            InstanceNumberDcmField<EVR_US>::New();
    testfieldus->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 1);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::
            InstanceNumberDcmField<EVR_UT>::New();
    testfieldut->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldut->get_array().size(), 1);
}
