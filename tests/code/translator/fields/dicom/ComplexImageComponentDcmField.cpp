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

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_AE>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldae != NULL);

    // Test VR = AS
    auto testfieldas = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_AS>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldas != NULL);

    // Test VR = AT
    auto testfieldat = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_AT>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldat != NULL);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_CS>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldcs != NULL);

    // Test VR = DA
    auto testfieldda = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_DA>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldda != NULL);

    // Test VR = DS
    auto testfieldds = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_DS>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldds != NULL);

    // Test VR = DT
    auto testfielddt = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_DT>::New(true);
    // Pointer exists
    BOOST_CHECK(testfielddt != NULL);

    // Test VR = FL
    auto testfieldfl = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_FL>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldfl != NULL);

    // Test VR = FD
    auto testfieldfd = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_FD>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldfd != NULL);

    // Test VR = IS
    auto testfieldis = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_IS>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldis != NULL);

    // Test VR = LO
    auto testfieldlo = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_LO>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldlo != NULL);

    // Test VR = LT
    auto testfieldlt = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_LT>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldlt != NULL);

    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented

    // Test VR = PN
    auto testfieldpn = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_PN>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldpn != NULL);

    // Test VR = SH
    auto testfieldsh = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_SH>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldsh != NULL);

    // Test VR = SL
    auto testfieldsl = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_SL>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldsl != NULL);

    // Test VR = SQ => Not implemented

    // Test VR = SS
    auto testfieldss = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_SS>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldss != NULL);

    // Test VR = ST
    auto testfieldst = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_ST>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldst != NULL);

    // Test VR = TM
    auto testfieldtm = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_TM>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldtm != NULL);

    // Test VR = UI
    auto testfieldui = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_UI>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldui != NULL);

    // Test VR = UL
    auto testfieldul = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_UL>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldul != NULL);

    // Test VR = UN => Not implemented

    // Test VR = US
    auto testfieldus = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_US>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldus != NULL);

    // Test VR = UT
    auto testfieldut = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_UT>::New(true);
    // Pointer exists
    BOOST_CHECK(testfieldut != NULL);
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (MAGNITUDE)
 */
struct TestDataOK02
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataOK02() : filename("./tmp_test_ModuleComplexImageComponentDcmField")
    {
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

        brukerdataset.load(filename);
    }

    ~TestDataOK02()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(RunMagnitude, TestDataOK02)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_CS>::New(true);
    testfieldcs->run(&brukerdataset, generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "MAGNITUDE");
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (PHASE)
 */
struct TestDataOK03
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataOK03() : filename("./tmp_test_ModuleComplexImageComponentDcmField")
    {
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

        brukerdataset.load(filename);
    }

    ~TestDataOK03()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(RunPhase, TestDataOK03)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_CS>::New(true);
    testfieldcs->run(&brukerdataset, generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "PHASE");
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (REAL)
 */
struct TestDataOK04
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataOK04() : filename("./tmp_test_ModuleComplexImageComponentDcmField")
    {
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

        brukerdataset.load(filename);
    }

    ~TestDataOK04()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(RunReal, TestDataOK04)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_CS>::New(true);
    testfieldcs->run(&brukerdataset, generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "REAL");
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (IMAGINARY)
 */
struct TestDataOK05
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataOK05() : filename("./tmp_test_ModuleComplexImageComponentDcmField")
    {
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

        brukerdataset.load(filename);
    }

    ~TestDataOK05()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(RunImaginary, TestDataOK05)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_CS>::New(true);
    testfieldcs->run(&brukerdataset, generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "IMAGINARY");
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (MIXED)
 */
struct TestDataOK06
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataOK06() : filename("./tmp_test_ModuleComplexImageComponentDcmField")
    {
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

        brukerdataset.load(filename);
    }

    ~TestDataOK06()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(RunMixed, TestDataOK06)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_CS>::New(true);
    testfieldcs->run(&brukerdataset, generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "MIXED");
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Bad VR for Image Position Patient Tag
 */

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK02)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = AE
    auto testfieldae = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_AE>::New(true);
    BOOST_REQUIRE_THROW(testfieldae->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = AS
    auto testfieldas = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_AS>::New(true);
    BOOST_REQUIRE_THROW(testfieldas->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = AT
    auto testfieldat = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_AT>::New(true);
    BOOST_REQUIRE_THROW(testfieldat->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = DA
    auto testfieldda = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_DA>::New(true);
    BOOST_REQUIRE_THROW(testfieldda->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = DS
    auto testfieldds = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_DS>::New(true);
    BOOST_REQUIRE_THROW(testfieldds->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = DT
    auto testfielddt = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_DT>::New(true);
    BOOST_REQUIRE_THROW(testfielddt->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = FL
    auto testfieldfl = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_FL>::New(true);
    BOOST_REQUIRE_THROW(testfieldfl->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = FD
    auto testfieldfd = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_FD>::New(true);
    BOOST_REQUIRE_THROW(testfieldfd->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = IS
    auto testfieldis = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_IS>::New(true);
    BOOST_REQUIRE_THROW(testfieldis->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = LO
    auto testfieldlo = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_LO>::New(true);
    BOOST_REQUIRE_THROW(testfieldlo->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = LT
    auto testfieldlt = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_LT>::New(true);
    BOOST_REQUIRE_THROW(testfieldlt->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented

    // Test VR = PN
    auto testfieldpn = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_PN>::New(true);
    BOOST_REQUIRE_THROW(testfieldpn->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = SH
    auto testfieldsh = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_SH>::New(true);
    BOOST_REQUIRE_THROW(testfieldsh->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = SL
    auto testfieldsl = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_SL>::New(true);
    BOOST_REQUIRE_THROW(testfieldsl->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = SQ => Not implemented

    // Test VR = SS
    auto testfieldss = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_SS>::New(true);
    BOOST_REQUIRE_THROW(testfieldss->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = ST
    auto testfieldst = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_ST>::New(true);
    BOOST_REQUIRE_THROW(testfieldst->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = TM
    auto testfieldtm = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_TM>::New(true);
    BOOST_REQUIRE_THROW(testfieldtm->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UI
    auto testfieldui = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_UI>::New(true);
    BOOST_REQUIRE_THROW(testfieldui->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UL
    auto testfieldul = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_UL>::New(true);
    BOOST_REQUIRE_THROW(testfieldul->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UN => Not implemented

    // Test VR = US
    auto testfieldus = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_US>::New(true);
    BOOST_REQUIRE_THROW(testfieldus->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);

    // Test VR = UT
    auto testfieldut = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_UT>::New(true);
    BOOST_REQUIRE_THROW(testfieldut->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Empty Bruker Dataset
 */
BOOST_AUTO_TEST_CASE(EmptyBrukerDataset)
{
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_CS>::New(true);
    BOOST_REQUIRE_THROW(testfieldcs->run(NULL,
                                         dicomifier::FrameIndexGenerator({2}),
                                         NULL),
                        dicomifier::DicomifierException);
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Bad value for VisuCoreFrameType
 */
struct TestDataKO03
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataKO03() : filename("./tmp_test_ModuleComplexImageComponentDcmField")
    {
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

        brukerdataset.load(filename);
    }

    ~TestDataKO03()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(UnknownVisuCoreFrameType, TestDataKO03)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            ComplexImageComponentDcmField<EVR_CS>::New(true);
    BOOST_REQUIRE_THROW(testfieldcs->run(&brukerdataset,
                                         generator,
                                         NULL),
                        dicomifier::DicomifierException);
}
