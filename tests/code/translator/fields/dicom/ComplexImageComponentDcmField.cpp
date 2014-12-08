/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleComplexImageComponentDcmField
#include <boost/test/unit_test.hpp>

#include "translator/fields/dicom/ComplexImageComponentDcmField.h"
#include "core/FrameIndexGenerator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::ComplexImageComponentDcmField<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldae != NULL, true);

    // Test VR = AS
    auto testfieldas = dicomifier::translator::ComplexImageComponentDcmField<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldas != NULL, true);

    // Test VR = AT
    auto testfieldat = dicomifier::translator::ComplexImageComponentDcmField<EVR_AT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldat != NULL, true);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldcs != NULL, true);

    // Test VR = DA
    auto testfieldda = dicomifier::translator::ComplexImageComponentDcmField<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldda != NULL, true);

    // Test VR = DS
    auto testfieldds = dicomifier::translator::ComplexImageComponentDcmField<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldds != NULL, true);

    // Test VR = DT
    auto testfielddt = dicomifier::translator::ComplexImageComponentDcmField<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfielddt != NULL, true);

    // Test VR = FL
    auto testfieldfl = dicomifier::translator::ComplexImageComponentDcmField<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfl != NULL, true);

    // Test VR = FD
    auto testfieldfd = dicomifier::translator::ComplexImageComponentDcmField<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfd != NULL, true);

    // Test VR = IS
    auto testfieldis = dicomifier::translator::ComplexImageComponentDcmField<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldis != NULL, true);

    // Test VR = LO
    auto testfieldlo = dicomifier::translator::ComplexImageComponentDcmField<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlo != NULL, true);

    // Test VR = LT
    auto testfieldlt = dicomifier::translator::ComplexImageComponentDcmField<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlt != NULL, true);

    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented

    // Test VR = PN
    auto testfieldpn = dicomifier::translator::ComplexImageComponentDcmField<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldpn != NULL, true);

    // Test VR = SH
    auto testfieldsh = dicomifier::translator::ComplexImageComponentDcmField<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsh != NULL, true);

    // Test VR = SL
    auto testfieldsl = dicomifier::translator::ComplexImageComponentDcmField<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsl != NULL, true);

    // Test VR = SQ => Not implemented

    // Test VR = SS
    auto testfieldss = dicomifier::translator::ComplexImageComponentDcmField<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldss != NULL, true);

    // Test VR = ST
    auto testfieldst = dicomifier::translator::ComplexImageComponentDcmField<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldst != NULL, true);

    // Test VR = TM
    auto testfieldtm = dicomifier::translator::ComplexImageComponentDcmField<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldtm != NULL, true);

    // Test VR = UI
    auto testfieldui = dicomifier::translator::ComplexImageComponentDcmField<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldui != NULL, true);

    // Test VR = UL
    auto testfieldul = dicomifier::translator::ComplexImageComponentDcmField<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldul != NULL, true);

    // Test VR = UN => Not implemented

    // Test VR = US
    auto testfieldus = dicomifier::translator::ComplexImageComponentDcmField<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldus != NULL, true);

    // Test VR = UT
    auto testfieldut = dicomifier::translator::ComplexImageComponentDcmField<EVR_UT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldut != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run (MAGNITUDE)
 */
struct TestDataOK02
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataOK02()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();

        filename = "./tmp_test_ModuleComplexImageComponentDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuCoreOrientation=( 5, 9 )\n";
        myfile << "1 6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 \n";
        myfile << "6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 \n";
        myfile << "0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##$VisuCoreFrameType=MAGNITUDE_IMAGE\n";
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
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>::New();
    testfieldcs->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "MAGNITUDE");
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run (PHASE)
 */
struct TestDataOK03
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataOK03()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();

        filename = "./tmp_test_ModuleComplexImageComponentDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuCoreOrientation=( 5, 9 )\n";
        myfile << "1 6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 \n";
        myfile << "6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 \n";
        myfile << "0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##$VisuCoreFrameType=PHASE_IMAGE\n";
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
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>::New();
    testfieldcs->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "PHASE");
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Run (REAL)
 */
struct TestDataOK04
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataOK04()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();

        filename = "./tmp_test_ModuleComplexImageComponentDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuCoreOrientation=( 5, 9 )\n";
        myfile << "1 6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 \n";
        myfile << "6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 \n";
        myfile << "0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##$VisuCoreFrameType=REAL_IMAGE\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset->LoadFile(filename);

        int coreFrameCount = 0;
        std::vector<int> indexlists = brukerdataset->create_frameGroupLists(coreFrameCount);

        generator = new dicomifier::FrameIndexGenerator(indexlists);
    }

    ~TestDataOK04()
    {
        remove(filename.c_str());
        delete brukerdataset;
        delete generator;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
{
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>::New();
    testfieldcs->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "REAL");
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Run (IMAGINARY)
 */
struct TestDataOK05
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataOK05()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();

        filename = "./tmp_test_ModuleComplexImageComponentDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuCoreOrientation=( 5, 9 )\n";
        myfile << "1 6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 \n";
        myfile << "6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 \n";
        myfile << "0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##$VisuCoreFrameType=IMAGINARY_IMAGE\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset->LoadFile(filename);

        int coreFrameCount = 0;
        std::vector<int> indexlists = brukerdataset->create_frameGroupLists(coreFrameCount);

        generator = new dicomifier::FrameIndexGenerator(indexlists);
    }

    ~TestDataOK05()
    {
        remove(filename.c_str());
        delete brukerdataset;
        delete generator;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_05, TestDataOK05)
{
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>::New();
    testfieldcs->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "IMAGINARY");
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Run (MIXED)
 */
struct TestDataOK06
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataOK06()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();

        filename = "./tmp_test_ModuleComplexImageComponentDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuCoreOrientation=( 5, 9 )\n";
        myfile << "1 6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 \n";
        myfile << "6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 \n";
        myfile << "0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##$VisuCoreFrameType=MIXED_IMAGE\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset->LoadFile(filename);

        int coreFrameCount = 0;
        std::vector<int> indexlists = brukerdataset->create_frameGroupLists(coreFrameCount);

        generator = new dicomifier::FrameIndexGenerator(indexlists);
    }

    ~TestDataOK06()
    {
        remove(filename.c_str());
        delete brukerdataset;
        delete generator;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_06, TestDataOK06)
{
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>::New();
    testfieldcs->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "MIXED");
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Bad VR for Image Position Patient Tag
 */

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK02)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::ComplexImageComponentDcmField<EVR_AE>::New();
    BOOST_REQUIRE_THROW(testfieldae->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = AS
    auto testfieldas = dicomifier::translator::ComplexImageComponentDcmField<EVR_AS>::New();
    BOOST_REQUIRE_THROW(testfieldas->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = AT
    auto testfieldat = dicomifier::translator::ComplexImageComponentDcmField<EVR_AT>::New();
    BOOST_REQUIRE_THROW(testfieldat->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = DA
    auto testfieldda = dicomifier::translator::ComplexImageComponentDcmField<EVR_DA>::New();
    BOOST_REQUIRE_THROW(testfieldda->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = DS
    auto testfieldds = dicomifier::translator::ComplexImageComponentDcmField<EVR_DS>::New();
    BOOST_REQUIRE_THROW(testfieldds->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = DT
    auto testfielddt = dicomifier::translator::ComplexImageComponentDcmField<EVR_DT>::New();
    BOOST_REQUIRE_THROW(testfielddt->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = FL
    auto testfieldfl = dicomifier::translator::ComplexImageComponentDcmField<EVR_FL>::New();
    BOOST_REQUIRE_THROW(testfieldfl->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = FD
    auto testfieldfd = dicomifier::translator::ComplexImageComponentDcmField<EVR_FD>::New();
    BOOST_REQUIRE_THROW(testfieldfd->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = IS
    auto testfieldis = dicomifier::translator::ComplexImageComponentDcmField<EVR_IS>::New();
    BOOST_REQUIRE_THROW(testfieldis->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = LO
    auto testfieldlo = dicomifier::translator::ComplexImageComponentDcmField<EVR_LO>::New();
    BOOST_REQUIRE_THROW(testfieldlo->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = LT
    auto testfieldlt = dicomifier::translator::ComplexImageComponentDcmField<EVR_LT>::New();
    BOOST_REQUIRE_THROW(testfieldlt->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented

    // Test VR = PN
    auto testfieldpn = dicomifier::translator::ComplexImageComponentDcmField<EVR_PN>::New();
    BOOST_REQUIRE_THROW(testfieldpn->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = SH
    auto testfieldsh = dicomifier::translator::ComplexImageComponentDcmField<EVR_SH>::New();
    BOOST_REQUIRE_THROW(testfieldsh->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = SL
    auto testfieldsl = dicomifier::translator::ComplexImageComponentDcmField<EVR_SL>::New();
    BOOST_REQUIRE_THROW(testfieldsl->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = SQ => Not implemented

    // Test VR = SS
    auto testfieldss = dicomifier::translator::ComplexImageComponentDcmField<EVR_SS>::New();
    BOOST_REQUIRE_THROW(testfieldss->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = ST
    auto testfieldst = dicomifier::translator::ComplexImageComponentDcmField<EVR_ST>::New();
    BOOST_REQUIRE_THROW(testfieldst->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = TM
    auto testfieldtm = dicomifier::translator::ComplexImageComponentDcmField<EVR_TM>::New();
    BOOST_REQUIRE_THROW(testfieldtm->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UI
    auto testfieldui = dicomifier::translator::ComplexImageComponentDcmField<EVR_UI>::New();
    BOOST_REQUIRE_THROW(testfieldui->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UL
    auto testfieldul = dicomifier::translator::ComplexImageComponentDcmField<EVR_UL>::New();
    BOOST_REQUIRE_THROW(testfieldul->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UN => Not implemented

    // Test VR = US
    auto testfieldus = dicomifier::translator::ComplexImageComponentDcmField<EVR_US>::New();
    BOOST_REQUIRE_THROW(testfieldus->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UT
    auto testfieldut = dicomifier::translator::ComplexImageComponentDcmField<EVR_UT>::New();
    BOOST_REQUIRE_THROW(testfieldut->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Empty Bruker Dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_02)
{
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>::New();
    BOOST_REQUIRE_THROW(testfieldcs->run(NULL,
                                         dicomifier::FrameIndexGenerator({2}),
                                         NULL),
                        dicomifier::DicomifierException);
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Bad value for VisuCoreFrameType
 */
struct TestDataKO03
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataKO03()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();

        filename = "./tmp_test_ModuleComplexImageComponentDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuCoreOrientation=( 5, 9 )\n";
        myfile << "1 6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 \n";
        myfile << "6.12303176911189e-17 0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 \n";
        myfile << "0 -6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1 1 6.12303176911189e-17 0 \n";
        myfile << "-6.12303176911189e-17 1 0 0 0 1\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##$VisuCoreFrameType=BAD_VALUE\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset->LoadFile(filename);

        int coreFrameCount = 0;
        std::vector<int> indexlists = brukerdataset->create_frameGroupLists(coreFrameCount);

        generator = new dicomifier::FrameIndexGenerator(indexlists);
    }

    ~TestDataKO03()
    {
        remove(filename.c_str());
        delete brukerdataset;
        delete generator;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataKO03)
{
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>::New();
    BOOST_REQUIRE_THROW(testfieldcs->run(brukerdataset,
                                         *generator,
                                         NULL),
                        dicomifier::DicomifierException);
}
