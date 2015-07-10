/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleInPlanePhaseEncodingDirectionDcmField
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/fields/dicom/InPlanePhaseEncodingDirectionDcmField.h"
#include "core/FrameIndexGenerator.h"

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK(testfieldae != NULL);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldas != NULL);
    
    // Test VR = AT
    auto testfieldat = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_AT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldat != NULL);
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldcs != NULL);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK(testfieldda != NULL);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldds != NULL);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK(testfielddt != NULL);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldfl != NULL);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK(testfieldfd != NULL);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldis != NULL);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK(testfieldlo != NULL);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldlt != NULL);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK(testfieldpn != NULL);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK(testfieldsh != NULL);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldsl != NULL);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldss != NULL);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK(testfieldst != NULL);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK(testfieldtm != NULL);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK(testfieldui != NULL);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldul != NULL);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK(testfieldus != NULL);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_UT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldut != NULL);
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (ROW)
 */
struct TestDataOK02
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;
 
    TestDataOK02() :
        filename("./tmp_test_ModuleInPlanePhaseEncodingDirectionDcmField")
    {
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_ModuleInPlanePhaseEncodingDirectionDcmField\n";
        myfile << "##$VisuFGOrderDescDim=1\n";
        myfile << "##$VisuFGOrderDesc=( 1 )\n";
        myfile << "(3, <FG_SLICE>, <>, 0, 2)\n";
        myfile << "##$VisuGroupDepVals=( 2 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
        myfile << "##$VisuCoreFrameCount=3\n";
        myfile << "##$VisuAcqImagePhaseEncDir=( 3 )\n";
        myfile << "row_dir row_dir row_dir\n";
        myfile << "##END=\n";
        myfile.close();
        
        brukerdataset.load(filename);
    }
 
    ~TestDataOK02()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(RunRow, TestDataOK02)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
        InPlanePhaseEncodingDirectionDcmField<EVR_CS>::New();
    testfieldcs->run(&brukerdataset, generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "ROW");
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (COL)
 */
struct TestDataOK03
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataOK03() :
        filename("./tmp_test_ModuleInPlanePhaseEncodingDirectionDcmField")
    {
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_ModuleInPlanePhaseEncodingDirectionDcmField\n";
        myfile << "##$VisuFGOrderDescDim=1\n";
        myfile << "##$VisuFGOrderDesc=( 1 )\n";
        myfile << "(3, <FG_SLICE>, <>, 0, 2)\n";
        myfile << "##$VisuGroupDepVals=( 2 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
        myfile << "##$VisuCoreFrameCount=3\n";
        myfile << "##$VisuAcqImagePhaseEncDir=( 3 )\n";
        myfile << "col_dir col_dir col_dir\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset.load(filename);
    }

    ~TestDataOK03()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(RunColumn, TestDataOK03)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
        InPlanePhaseEncodingDirectionDcmField<EVR_CS>::New();
    testfieldcs->run(&brukerdataset, generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "COL");
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Run (No VisuAcqImagePhaseEncDir)
 */
struct TestDataOK04
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataOK04() :
        filename("./tmp_test_ModuleInPlanePhaseEncodingDirectionDcmField")
    {
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_ModuleInPlanePhaseEncodingDirectionDcmField\n";
        myfile << "##$VisuFGOrderDescDim=1\n";
        myfile << "##$VisuFGOrderDesc=( 1 )\n";
        myfile << "(3, <FG_SLICE>, <>, 0, 2)\n";
        myfile << "##$VisuGroupDepVals=( 2 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
        myfile << "##$VisuCoreFrameCount=3\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset.load(filename);
    }

    ~TestDataOK04()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(RunWithoutVisuAcqImagePhaseEncDir, TestDataOK04)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
        InPlanePhaseEncodingDirectionDcmField<EVR_CS>::New();
    testfieldcs->run(&brukerdataset, generator, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "");
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Bad VR for Image Position Patient Tag
 */

BOOST_FIXTURE_TEST_CASE(BadValueRepresentation, TestDataOK02)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = AE
    auto testfieldae = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_AE>::New();
    BOOST_REQUIRE_THROW(testfieldae->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_AS>::New();
    BOOST_REQUIRE_THROW(testfieldas->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = AT
    auto testfieldat = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_AT>::New();
    BOOST_REQUIRE_THROW(testfieldat->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_DA>::New();
    BOOST_REQUIRE_THROW(testfieldda->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_DS>::New();
    BOOST_REQUIRE_THROW(testfieldds->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
                        
    // Test VR = DT
    auto testfielddt = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_DT>::New();
    BOOST_REQUIRE_THROW(testfielddt->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_FL>::New();
    BOOST_REQUIRE_THROW(testfieldfl->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_FD>::New();
    BOOST_REQUIRE_THROW(testfieldfd->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_IS>::New();
    BOOST_REQUIRE_THROW(testfieldis->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_LO>::New();
    BOOST_REQUIRE_THROW(testfieldlo->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_LT>::New();
    BOOST_REQUIRE_THROW(testfieldlt->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_PN>::New();
    BOOST_REQUIRE_THROW(testfieldpn->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_SH>::New();
    BOOST_REQUIRE_THROW(testfieldsh->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_SL>::New();
    BOOST_REQUIRE_THROW(testfieldsl->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_SS>::New();
    BOOST_REQUIRE_THROW(testfieldss->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_ST>::New();
    BOOST_REQUIRE_THROW(testfieldst->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_TM>::New();
    BOOST_REQUIRE_THROW(testfieldtm->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_UI>::New();
    BOOST_REQUIRE_THROW(testfieldui->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_UL>::New();
    BOOST_REQUIRE_THROW(testfieldul->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_US>::New();
    BOOST_REQUIRE_THROW(testfieldus->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::
            InPlanePhaseEncodingDirectionDcmField<EVR_UT>::New();
    BOOST_REQUIRE_THROW(testfieldut->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Corrupted data
 */
struct TestDataKO02
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataKO02() :
        filename("./tmp_test_ModuleInPlanePhaseEncodingDirectionDcmField")
    {
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_ModuleInPlanePhaseEncodingDirectionDcmField\n";
        myfile << "##$VisuFGOrderDescDim=1\n";
        myfile << "##$VisuFGOrderDesc=( 1 )\n";
        myfile << "(3, <FG_SLICE>, <>, 0, 2)\n";
        myfile << "##$VisuGroupDepVals=( 2 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
        myfile << "##$VisuCoreFrameCount=3\n";
        myfile << "##$VisuAcqImagePhaseEncDir=( 3 )\n";
        myfile << "bad_val col_dir col_dir\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset.load(filename);
    }

    ~TestDataKO02()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(CorruptedData, TestDataKO02)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
        InPlanePhaseEncodingDirectionDcmField<EVR_CS>::New();
    BOOST_REQUIRE_THROW(testfieldcs->run(&brukerdataset, generator, NULL),
                        dicomifier::DicomifierException);
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Empty Bruker Dataset
 */
BOOST_FIXTURE_TEST_CASE(EmptyBrukerDataset, TestDataOK02)
{
    std::vector<int> indexlists;
    for(auto const & frame_group: brukerdataset.get_frame_groups())
    {
        indexlists.push_back(frame_group.size);
    }
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
        InPlanePhaseEncodingDirectionDcmField<EVR_CS>::New();
    BOOST_REQUIRE_THROW(testfieldcs->run(NULL, generator, NULL),
                        dicomifier::DicomifierException);
}
