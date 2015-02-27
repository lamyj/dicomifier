/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleAcquisitionMatrixDcmField
#include <boost/test/unit_test.hpp>

#include "translator/fields/ConstantField.h"
#include "translator/fields/dicom/AcquisitionMatrixDcmField.h"
#include "core/FrameIndexGenerator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::AcquisitionMatrixDcmField<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldae != NULL, true);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::AcquisitionMatrixDcmField<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldas != NULL, true);
    
    // Test VR = AT
    auto testfieldat = dicomifier::translator::AcquisitionMatrixDcmField<EVR_AT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldat != NULL, true);
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::AcquisitionMatrixDcmField<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldcs != NULL, true);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::AcquisitionMatrixDcmField<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldda != NULL, true);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::AcquisitionMatrixDcmField<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldds != NULL, true);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::AcquisitionMatrixDcmField<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfielddt != NULL, true);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::AcquisitionMatrixDcmField<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfl != NULL, true);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::AcquisitionMatrixDcmField<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldfd != NULL, true);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::AcquisitionMatrixDcmField<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldis != NULL, true);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::AcquisitionMatrixDcmField<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlo != NULL, true);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::AcquisitionMatrixDcmField<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldlt != NULL, true);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::AcquisitionMatrixDcmField<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldpn != NULL, true);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::AcquisitionMatrixDcmField<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsh != NULL, true);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::AcquisitionMatrixDcmField<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldsl != NULL, true);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::AcquisitionMatrixDcmField<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldss != NULL, true);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::AcquisitionMatrixDcmField<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldst != NULL, true);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::AcquisitionMatrixDcmField<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldtm != NULL, true);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::AcquisitionMatrixDcmField<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldui != NULL, true);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::AcquisitionMatrixDcmField<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldul != NULL, true);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::AcquisitionMatrixDcmField<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldus != NULL, true);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::AcquisitionMatrixDcmField<EVR_UT>::New();
    // Pointer exists
    BOOST_CHECK_EQUAL(testfieldut != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run (COL)
 */
struct TestDataOK02
{
    std::string filename;
    dicomifier::bruker::Dataset* brukerdataset;
    
    dicomifier::FrameIndexGenerator* generator;
 
    TestDataOK02()
    {
        brukerdataset = new dicomifier::bruker::Dataset();
        
        filename = "./tmp_test_ModuleAcquisitionMatrixDcmField";
        
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuAcqImagePhaseEncDir=( 75 )\n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir\n";
        myfile << "##$VisuAcqSize=( 2 )\n";
        myfile << "128 256\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##END=\n";
        myfile.close();
        
        brukerdataset->load(filename);
        
        std::vector<int> indexlists;
        for(auto const & frame_group: brukerdataset->get_frame_groups())
        {
            indexlists.push_back(frame_group.size);
        }
        
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
    // Test VR = US
    auto testfieldus = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_US>::New();
    testfieldus->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 4);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[0], 128);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[1], 0);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[2], 0);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[3], 256);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run (ROW)
 */
struct TestDataOK03
{
    std::string filename;
    dicomifier::bruker::Dataset* brukerdataset;
    
    dicomifier::FrameIndexGenerator* generator;
 
    TestDataOK03()
    {
        brukerdataset = new dicomifier::bruker::Dataset();
        
        filename = "./tmp_test_ModuleAcquisitionMatrixDcmField";
        
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuAcqImagePhaseEncDir=( 75 )\n";
        myfile << "row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir \n";
        myfile << "row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir \n";
        myfile << "row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir \n";
        myfile << "row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir \n";
        myfile << "row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir \n";
        myfile << "row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir \n";
        myfile << "row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir \n";
        myfile << "row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir row_dir \n";
        myfile << "row_dir row_dir row_dir\n";
        myfile << "##$VisuAcqSize=( 2 )\n";
        myfile << "128 256\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##END=\n";
        myfile.close();
        
        brukerdataset->load(filename);
        
        std::vector<int> indexlists;
        for(auto const & frame_group: brukerdataset->get_frame_groups())
        {
            indexlists.push_back(frame_group.size);
        }
        
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
    // Test VR = US
    auto testfieldus = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_US>::New();
    testfieldus->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 4);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[0], 0);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[1], 128);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[2], 256);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[3], 0);
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Run (No VisuAcqImagePhaseEncDir)
 */
struct TestDataOK04
{
    std::string filename;
    dicomifier::bruker::Dataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataOK04()
    {
        brukerdataset = new dicomifier::bruker::Dataset();

        filename = "./tmp_test_ModuleAcquisitionMatrixDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuAcqSize=( 2 )\n";
        myfile << "128 256\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset->load(filename);

        std::vector<int> indexlists;
        for(auto const & frame_group: brukerdataset->get_frame_groups())
        {
            indexlists.push_back(frame_group.size);
        }

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
    // Test VR = US
    auto testfieldus = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_US>::New();
    testfieldus->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 4);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[0], 0);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[1], 0);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[2], 0);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[3], 0);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Bad VR for Image Position Patient Tag
 */

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK02)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_AE>::New();
    BOOST_REQUIRE_THROW(testfieldae->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_AS>::New();
    BOOST_REQUIRE_THROW(testfieldas->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = AT
    auto testfieldat = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_AT>::New();
    BOOST_REQUIRE_THROW(testfieldat->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_CS>::New();
    BOOST_REQUIRE_THROW(testfieldcs->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_DA>::New();
    BOOST_REQUIRE_THROW(testfieldda->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
                        
    // Test VR = DS
    auto testfieldds = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_DS>::New();
    BOOST_REQUIRE_THROW(testfieldds->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_DT>::New();
    BOOST_REQUIRE_THROW(testfielddt->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_FL>::New();
    BOOST_REQUIRE_THROW(testfieldfl->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_FD>::New();
    BOOST_REQUIRE_THROW(testfieldfd->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_IS>::New();
    BOOST_REQUIRE_THROW(testfieldis->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_LO>::New();
    BOOST_REQUIRE_THROW(testfieldlo->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_LT>::New();
    BOOST_REQUIRE_THROW(testfieldlt->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_PN>::New();
    BOOST_REQUIRE_THROW(testfieldpn->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_SH>::New();
    BOOST_REQUIRE_THROW(testfieldsh->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_SL>::New();
    BOOST_REQUIRE_THROW(testfieldsl->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_SS>::New();
    BOOST_REQUIRE_THROW(testfieldss->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_ST>::New();
    BOOST_REQUIRE_THROW(testfieldst->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_TM>::New();
    BOOST_REQUIRE_THROW(testfieldtm->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_UI>::New();
    BOOST_REQUIRE_THROW(testfieldui->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_UL>::New();
    BOOST_REQUIRE_THROW(testfieldul->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UN => Not implemented
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_UT>::New();
    BOOST_REQUIRE_THROW(testfieldut->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
}
 
/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Empty Bruker Dataset
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataOK02)
{
    // Test VR = US
    auto testfieldUS = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_US>::New();
    BOOST_REQUIRE_THROW(testfieldUS->run(NULL, *generator, NULL), 
                        dicomifier::DicomifierException);
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Corrupted data
 */
struct TestDataKO03
{
    std::string filename;
    dicomifier::bruker::Dataset* brukerdataset;

    dicomifier::FrameIndexGenerator* generator;

    TestDataKO03()
    {
        brukerdataset = new dicomifier::bruker::Dataset();

        filename = "./tmp_test_ModuleAcquisitionMatrixDcmField";

        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$VisuAcqImagePhaseEncDir=( 75 )\n";
        myfile << "bad_val col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir\n";
        myfile << "##$VisuAcqSize=( 2 )\n";
        myfile << "128 256\n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset->load(filename);

        std::vector<int> indexlists;
        for(auto const & frame_group: brukerdataset->get_frame_groups())
        {
            indexlists.push_back(frame_group.size);
        }

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
    // Test VR = US
    auto testfieldUS = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_US>::New();
    BOOST_REQUIRE_THROW(testfieldUS->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
}
