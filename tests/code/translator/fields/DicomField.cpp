/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDicomField
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/fields/DicomField.h"
#include "translator/fields/TestField.h"

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::DicomField<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK(testfieldae != NULL);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::DicomField<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldas != NULL);
    
    // Test VR = AT
    auto testfieldat = dicomifier::translator::DicomField<EVR_AT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldat != NULL);
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::DicomField<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldcs != NULL);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::DicomField<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK(testfieldda != NULL);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::DicomField<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldds != NULL);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::DicomField<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK(testfielddt != NULL);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::DicomField<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldfl != NULL);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::DicomField<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK(testfieldfd != NULL);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::DicomField<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldis != NULL);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::DicomField<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK(testfieldlo != NULL);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::DicomField<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldlt != NULL);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::DicomField<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK(testfieldpn != NULL);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::DicomField<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK(testfieldsh != NULL);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::DicomField<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldsl != NULL);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::DicomField<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldss != NULL);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::DicomField<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK(testfieldst != NULL);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::DicomField<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK(testfieldtm != NULL);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::DicomField<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK(testfieldui != NULL);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::DicomField<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldul != NULL);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::DicomField<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK(testfieldus != NULL);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::DicomField<EVR_UT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldut != NULL);
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run
 */
BOOST_AUTO_TEST_CASE(Run)
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset dataset;
    auto testfield = dicomifier::translator::TestField::New();
    // Test VR = AE
    tagandrange._tag = DCM_PerformedStationAETitle;
    auto testfieldae =
            dicomifier::translator::DicomField<EVR_AE>::New(tagandrange,
                                                            testfield);
    testfieldae->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = AS
    tagandrange._tag = DCM_PatientAge;
    auto testfieldas =
            dicomifier::translator::DicomField<EVR_AS>::New(tagandrange,
                                                            testfield);
    testfieldas->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = AT
    tagandrange._tag = DCM_DimensionIndexPointer;
    auto testfieldat =
            dicomifier::translator::DicomField<EVR_AT>::New(tagandrange,
                                                            testfield);
    testfieldat->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = CS
    tagandrange._tag = DCM_Modality;
    auto testfieldcs =
            dicomifier::translator::DicomField<EVR_CS>::New(tagandrange,
                                                            testfield);
    testfieldcs->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = DA
    tagandrange._tag = DCM_StudyDate;
    auto testfieldda =
            dicomifier::translator::DicomField<EVR_DA>::New(tagandrange,
                                                            testfield);
    testfieldda->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = DS
    tagandrange._tag = DCM_PatientWeight;
    auto testfieldds =
            dicomifier::translator::DicomField<EVR_DS>::New(tagandrange,
                                                            testfield);
    testfieldds->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = DT
    tagandrange._tag = DCM_AcquisitionDateTime;
    auto testfielddt =
            dicomifier::translator::DicomField<EVR_DT>::New(tagandrange,
                                                            testfield);
    testfielddt->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = FL
    tagandrange._tag = DCM_StimulusArea;
    auto testfieldfl =
            dicomifier::translator::DicomField<EVR_FL>::New(tagandrange,
                                                            testfield);
    testfieldfl->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = FD
    tagandrange._tag = DCM_SteeringAngle;
    auto testfieldfd =
            dicomifier::translator::DicomField<EVR_FD>::New(tagandrange,
                                                            testfield);
    testfieldfd->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = IS
    tagandrange._tag = DCM_StageNumber;
    auto testfieldis =
            dicomifier::translator::DicomField<EVR_IS>::New(tagandrange,
                                                            testfield);
    testfieldis->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = LO
    tagandrange._tag = DCM_Manufacturer;
    auto testfieldlo =
            dicomifier::translator::DicomField<EVR_LO>::New(tagandrange,
                                                            testfield);
    testfieldlo->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = LT
    tagandrange._tag = DCM_AdditionalPatientHistory;
    auto testfieldlt =
            dicomifier::translator::DicomField<EVR_LT>::New(tagandrange,
                                                            testfield);
    testfieldlt->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    tagandrange._tag = DCM_PatientName;
    auto testfieldpn =
            dicomifier::translator::DicomField<EVR_PN>::New(tagandrange,
                                                            testfield);
    testfieldpn->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = SH
    tagandrange._tag = DCM_AccessionNumber;
    auto testfieldsh =
            dicomifier::translator::DicomField<EVR_SH>::New(tagandrange,
                                                            testfield);
    testfieldsh->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = SL
    tagandrange._tag = DCM_ReferencePixelX0;
    auto testfieldsl =
            dicomifier::translator::DicomField<EVR_SL>::New(tagandrange,
                                                            testfield);
    testfieldsl->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    tagandrange._tag = DCM_TagAngleSecondAxis;
    auto testfieldss =
            dicomifier::translator::DicomField<EVR_SS>::New(tagandrange,
                                                            testfield);
    testfieldss->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = ST
    tagandrange._tag = DCM_InstitutionAddress;
    auto testfieldst =
            dicomifier::translator::DicomField<EVR_ST>::New(tagandrange,
                                                            testfield);
    testfieldst->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = TM
    tagandrange._tag = DCM_StudyTime;
    auto testfieldtm =
            dicomifier::translator::DicomField<EVR_TM>::New(tagandrange,
                                                            testfield);
    testfieldtm->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = UI
    tagandrange._tag = DCM_SOPClassUID;
    auto testfieldui =
            dicomifier::translator::DicomField<EVR_UI>::New(tagandrange,
                                                            testfield);
    testfieldui->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = UL
    tagandrange._tag = DCM_RegionFlags;
    auto testfieldul =
            dicomifier::translator::DicomField<EVR_UL>::New(tagandrange,
                                                            testfield);
    testfieldul->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    tagandrange._tag = DCM_FailureReason;
    auto testfieldus =
            dicomifier::translator::DicomField<EVR_US>::New(tagandrange,
                                                            testfield);
    testfieldus->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
    
    // Test VR = UT
    tagandrange._tag = DCM_PixelDataProviderURL;
    auto testfieldut =
            dicomifier::translator::DicomField<EVR_UT>::New(tagandrange,
                                                            testfield);
    testfieldut->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run with SubTag
 */
BOOST_AUTO_TEST_CASE(RunWithSubTag)
{
    dicomifier::TagAndRange tagandrange;
    DcmDataset dataset;
    auto constantfieldat = dicomifier::translator::ConstantField<EVR_AT>::New(0);
    auto constantfieldcs =
            dicomifier::translator::ConstantField<EVR_CS>::New("TEST");
    // Test VR = AT
    tagandrange._tag = DCM_DimensionIndexPointer;
    auto testfieldat =
            dicomifier::translator::DicomField<EVR_AT>::New(tagandrange,
                                                            constantfieldat);
    testfieldat->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));

    // Test VR = CS
    tagandrange._tag = DCM_Modality;
    auto testfieldcs =
            dicomifier::translator::DicomField<EVR_CS>::New(tagandrange,
                                                            constantfieldcs);
    testfieldcs->run(NULL, dicomifier::FrameIndexGenerator({}), &dataset);
    BOOST_CHECK(dataset.tagExists(tagandrange._tag));
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Empty sub tag
 */
BOOST_AUTO_TEST_CASE(EmptySubTag)
{
    dicomifier::TagAndRange tagandrange;
    tagandrange._tag = DCM_Modality;
    DcmDataset dataset;
    auto testfieldcs =
            dicomifier::translator::DicomField<EVR_CS>::New(tagandrange, NULL);
    BOOST_REQUIRE_THROW(testfieldcs->run(NULL,
                                         dicomifier::FrameIndexGenerator({}),
                                         &dataset),
                        dicomifier::DicomifierException);
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Empty Dataset
 */
BOOST_AUTO_TEST_CASE(EmptyDataset)
{
    dicomifier::TagAndRange tagandrange;
    tagandrange._tag = DCM_Modality;
    auto testfield = dicomifier::translator::TestField::New();
    auto testfieldcs =
            dicomifier::translator::DicomField<EVR_CS>::New(tagandrange,
                                                            testfield);
    BOOST_REQUIRE_THROW(testfieldcs->run(NULL,
                                         dicomifier::FrameIndexGenerator({}),
                                         NULL),
                        dicomifier::DicomifierException);
}
