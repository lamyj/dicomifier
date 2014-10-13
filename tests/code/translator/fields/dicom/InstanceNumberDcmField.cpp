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

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::InstanceNumberDcmField<EVR_AE>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::InstanceNumberDcmField<EVR_AS>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::InstanceNumberDcmField<EVR_CS>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::InstanceNumberDcmField<EVR_DA>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::InstanceNumberDcmField<EVR_DS>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::InstanceNumberDcmField<EVR_DT>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::InstanceNumberDcmField<EVR_FL>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::InstanceNumberDcmField<EVR_FD>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::InstanceNumberDcmField<EVR_IS>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::InstanceNumberDcmField<EVR_LO>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::InstanceNumberDcmField<EVR_LT>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::InstanceNumberDcmField<EVR_PN>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::InstanceNumberDcmField<EVR_SH>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::InstanceNumberDcmField<EVR_SL>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::InstanceNumberDcmField<EVR_SS>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::InstanceNumberDcmField<EVR_ST>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::InstanceNumberDcmField<EVR_TM>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::InstanceNumberDcmField<EVR_UI>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::InstanceNumberDcmField<EVR_UL>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::InstanceNumberDcmField<EVR_US>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::InstanceNumberDcmField<EVR_UT>::New();
    // Pointer exists and class type is InstanceNumberDcmField
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_InstanceNumberDcmField);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::InstanceNumberDcmField<EVR_AE>::New();
    testfieldae->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldae->get_array().size(), 1);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::InstanceNumberDcmField<EVR_AS>::New();
    testfieldas->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldas->get_array().size(), 1);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::InstanceNumberDcmField<EVR_CS>::New();
    testfieldcs->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::InstanceNumberDcmField<EVR_DA>::New();
    testfieldda->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldda->get_array().size(), 1);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::InstanceNumberDcmField<EVR_DS>::New();
    testfieldds->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldds->get_array().size(), 1);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::InstanceNumberDcmField<EVR_DT>::New();
    testfielddt->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfielddt->get_array().size(), 1);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::InstanceNumberDcmField<EVR_FL>::New();
    testfieldfl->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldfl->get_array().size(), 1);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::InstanceNumberDcmField<EVR_FD>::New();
    testfieldfd->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldfd->get_array().size(), 1);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::InstanceNumberDcmField<EVR_IS>::New();
    testfieldis->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldis->get_array().size(), 1);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::InstanceNumberDcmField<EVR_LO>::New();
    testfieldlo->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldlo->get_array().size(), 1);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::InstanceNumberDcmField<EVR_LT>::New();
    testfieldlt->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldlt->get_array().size(), 1);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::InstanceNumberDcmField<EVR_PN>::New();
    testfieldpn->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldpn->get_array().size(), 1);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::InstanceNumberDcmField<EVR_SH>::New();
    testfieldsh->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldsh->get_array().size(), 1);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::InstanceNumberDcmField<EVR_SL>::New();
    testfieldsl->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldsl->get_array().size(), 1);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::InstanceNumberDcmField<EVR_SS>::New();
    testfieldss->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldss->get_array().size(), 1);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::InstanceNumberDcmField<EVR_ST>::New();
    testfieldst->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldst->get_array().size(), 1);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::InstanceNumberDcmField<EVR_TM>::New();
    testfieldtm->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldtm->get_array().size(), 1);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::InstanceNumberDcmField<EVR_UI>::New();
    testfieldui->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldui->get_array().size(), 1);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::InstanceNumberDcmField<EVR_UL>::New();
    testfieldul->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldul->get_array().size(), 1);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::InstanceNumberDcmField<EVR_US>::New();
    testfieldus->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 1);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::InstanceNumberDcmField<EVR_UT>::New();
    testfieldut->run(NULL, dicomifier::FrameIndexGenerator({2}), NULL);
    BOOST_CHECK_EQUAL(testfieldut->get_array().size(), 1);
}
