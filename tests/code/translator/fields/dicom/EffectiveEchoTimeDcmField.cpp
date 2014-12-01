/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleEffectiveEchoTimeDcmField
#include <boost/test/unit_test.hpp>

#include "translator/fields/dicom/EffectiveEchoTimeDcmField.h"
#include "core/FrameIndexGenerator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AE>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = AS
    auto testfieldas = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AS>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = AT
    auto testfieldat = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AT>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldat->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_CS>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = DA
    auto testfieldda = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DA>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = DS
    auto testfieldds = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DS>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = DT
    auto testfielddt = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DT>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = FL
    auto testfieldfl = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FL>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = FD
    auto testfieldfd = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FD>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = IS
    auto testfieldis = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_IS>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = LO
    auto testfieldlo = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_LO>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = LT
    auto testfieldlt = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_LT>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented

    // Test VR = PN
    auto testfieldpn = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_PN>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = SH
    auto testfieldsh = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SH>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = SL
    auto testfieldsl = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SL>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = SQ => Not implemented

    // Test VR = SS
    auto testfieldss = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SS>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = ST
    auto testfieldst = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_ST>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = TM
    auto testfieldtm = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_TM>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = UI
    auto testfieldui = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UI>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = UL
    auto testfieldul = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UL>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = UN => Not implemented

    // Test VR = US
    auto testfieldus = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_US>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);

    // Test VR = UT
    auto testfieldut = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UT>::New();
    // Pointer exists and class type is EffectiveEchoTimeDcmField
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_EffectiveEchoTimeDcmField);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run
 */
struct TestDataOK02
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataOK02()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();

        filename = "./tmp_test_ModuleEffectiveEchoTimeDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_ModuleEffectiveEchoTimeDcmField\n";
        myfile << "##$VisuAcqImagePhaseEncDir=( 15 )\n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (3, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=15\n";
        myfile << "##$VisuAcqEchoTime=( 1 )\n";
        myfile << "33\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset->LoadFile(filename);

        int coreFrameCount = 0;
        std::vector<int> indexlists = brukerdataset->create_frameGroupLists(coreFrameCount);

        generator = new dicomifier::FrameIndexGenerator(indexlists);
    }

    ~TestDataOK02()
    {
        remove(filename.c_str());
        delete brukerdataset;
        delete generator;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    // Test VR = FD
    auto testfieldul = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FD>::New();
    testfieldul->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldul->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldul->get_array()[0], 33);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run (multi echo)
 */
struct TestDataOK03
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataOK03()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();

        filename = "./tmp_test_ModuleEffectiveEchoTimeDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_ModuleEffectiveEchoTimeDcmField\n";
        myfile << "##$VisuFGOrderDescDim=1\n";
        myfile << "##$VisuFGOrderDesc=( 1 )\n";
        myfile << "(2, <FG_ECHO>, <FieldMap>, 0, 3)\n";
        myfile << "$$ @vis= VisuCoreByteOrder VisuCoreDiskSliceOrder VisuPixel VisuFGOrderDescDim\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuAcqEchoTime>, 0) (<VisuFGElemComment>, 0) (<VisuCoreDataUnits>, 0)\n";
        myfile << "##$VisuCoreFrameCount=15\n";
        myfile << "##$VisuAcqEchoTime=( 2 )\n";
        myfile << "1.43 5.43\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset->LoadFile(filename);

        int coreFrameCount = 0;
        std::vector<int> indexlists = brukerdataset->create_frameGroupLists(coreFrameCount);

        generator = new dicomifier::FrameIndexGenerator(indexlists);
    }

    ~TestDataOK03()
    {
        remove(filename.c_str());
        delete brukerdataset;
        delete generator;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    // Test VR = FD
    auto testfieldul = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FD>::New();
    testfieldul->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldul->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldul->get_array()[0], 1.43);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Bad VR for Image Position Patient Tag
 */

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK02)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AE>::New();
    BOOST_REQUIRE_THROW(testfieldae->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = AS
    auto testfieldas = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AS>::New();
    BOOST_REQUIRE_THROW(testfieldas->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = AT
    auto testfieldat = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AT>::New();
    BOOST_REQUIRE_THROW(testfieldat->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_CS>::New();
    BOOST_REQUIRE_THROW(testfieldcs->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = DA
    auto testfieldda = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DA>::New();
    BOOST_REQUIRE_THROW(testfieldda->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = DS
    auto testfieldds = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DS>::New();
    BOOST_REQUIRE_THROW(testfieldds->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = DT
    auto testfielddt = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DT>::New();
    BOOST_REQUIRE_THROW(testfielddt->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = FL
    auto testfieldfl = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FL>::New();
    BOOST_REQUIRE_THROW(testfieldfl->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = IS
    auto testfieldis = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_IS>::New();
    BOOST_REQUIRE_THROW(testfieldis->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = LO
    auto testfieldlo = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_LO>::New();
    BOOST_REQUIRE_THROW(testfieldlo->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = LT
    auto testfieldlt = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_LT>::New();
    BOOST_REQUIRE_THROW(testfieldlt->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented

    // Test VR = PN
    auto testfieldpn = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_PN>::New();
    BOOST_REQUIRE_THROW(testfieldpn->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = SH
    auto testfieldsh = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SH>::New();
    BOOST_REQUIRE_THROW(testfieldsh->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = SL
    auto testfieldsl = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SL>::New();
    BOOST_REQUIRE_THROW(testfieldsl->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = SQ => Not implemented

    // Test VR = SS
    auto testfieldss = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SS>::New();
    BOOST_REQUIRE_THROW(testfieldss->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = ST
    auto testfieldst = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_ST>::New();
    BOOST_REQUIRE_THROW(testfieldst->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = TM
    auto testfieldtm = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_TM>::New();
    BOOST_REQUIRE_THROW(testfieldtm->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UI
    auto testfieldui = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UI>::New();
    BOOST_REQUIRE_THROW(testfieldui->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = US
    auto testfieldus = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_US>::New();
    BOOST_REQUIRE_THROW(testfieldus->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UL
    auto testfieldfd = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UL>::New();
    BOOST_REQUIRE_THROW(testfieldfd->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UN => Not implemented

    // Test VR = UT
    auto testfieldut = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UT>::New();
    BOOST_REQUIRE_THROW(testfieldut->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Empty Bruker Dataset
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataOK02)
{
    // Test VR = FD
    auto testfieldUL = dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FD>::New();
    BOOST_REQUIRE_THROW(testfieldUL->run(NULL, *generator, NULL),
                        dicomifier::DicomifierException);
}

