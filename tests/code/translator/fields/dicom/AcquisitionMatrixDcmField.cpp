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
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::AcquisitionMatrixDcmField<EVR_AS>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::AcquisitionMatrixDcmField<EVR_CS>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::AcquisitionMatrixDcmField<EVR_DA>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::AcquisitionMatrixDcmField<EVR_DS>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::AcquisitionMatrixDcmField<EVR_DT>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::AcquisitionMatrixDcmField<EVR_FL>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::AcquisitionMatrixDcmField<EVR_FD>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::AcquisitionMatrixDcmField<EVR_IS>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::AcquisitionMatrixDcmField<EVR_LO>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::AcquisitionMatrixDcmField<EVR_LT>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::AcquisitionMatrixDcmField<EVR_PN>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::AcquisitionMatrixDcmField<EVR_SH>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::AcquisitionMatrixDcmField<EVR_SL>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::AcquisitionMatrixDcmField<EVR_SS>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::AcquisitionMatrixDcmField<EVR_ST>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::AcquisitionMatrixDcmField<EVR_TM>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::AcquisitionMatrixDcmField<EVR_UI>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::AcquisitionMatrixDcmField<EVR_UL>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::AcquisitionMatrixDcmField<EVR_US>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::AcquisitionMatrixDcmField<EVR_UT>::New();
    // Pointer exists and class type is AcquisitionMatrixDcmField
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_AcquisitionMatrixDcmField);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run (COL)
 */
struct TestDataOK02
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;
    
    dicomifier::FrameIndexGenerator* generator;
 
    TestDataOK02()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();
        
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
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
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
    // Test VR = US
    auto testfieldus = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_US>::New(dicomifier::translator::
                            ConstantField<EVR_US>::New({128,256}));
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
    dicomifier::bruker::BrukerDataset* brukerdataset;
    
    dicomifier::FrameIndexGenerator* generator;
 
    TestDataOK03()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();
        
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
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (15, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=75\n";
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
    // Test VR = US
    auto testfieldus = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_US>::New(dicomifier::translator::
                            ConstantField<EVR_US>::New({128,256}));
    testfieldus->run(brukerdataset, *generator, NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 4);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[0], 0);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[1], 128);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[2], 256);
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
        AcquisitionMatrixDcmField<EVR_AE>::New(dicomifier::translator::
                            ConstantField<EVR_AE>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldae->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_AS>::New(dicomifier::translator::
                            ConstantField<EVR_AS>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldas->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_CS>::New(dicomifier::translator::
                            ConstantField<EVR_CS>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldcs->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_DA>::New(dicomifier::translator::
                            ConstantField<EVR_DA>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldda->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
                        
    // Test VR = DS
    auto testfieldds = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_DS>::New(dicomifier::translator::
                            ConstantField<EVR_DS>::New({128,256}));
    BOOST_REQUIRE_THROW(testfieldds->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_DT>::New(dicomifier::translator::
                            ConstantField<EVR_DT>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfielddt->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_FL>::New(dicomifier::translator::
                            ConstantField<EVR_FL>::New({128,256}));
    BOOST_REQUIRE_THROW(testfieldfl->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_FD>::New(dicomifier::translator::
                            ConstantField<EVR_FD>::New({128,256}));
    BOOST_REQUIRE_THROW(testfieldfd->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_IS>::New(dicomifier::translator::
                            ConstantField<EVR_IS>::New({128,256}));
    BOOST_REQUIRE_THROW(testfieldis->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_LO>::New(dicomifier::translator::
                            ConstantField<EVR_LO>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldlo->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_LT>::New(dicomifier::translator::
                            ConstantField<EVR_LT>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldlt->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_PN>::New(dicomifier::translator::
                            ConstantField<EVR_PN>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldpn->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_SH>::New(dicomifier::translator::
                            ConstantField<EVR_SH>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldsh->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_SL>::New(dicomifier::translator::
                            ConstantField<EVR_SL>::New({128,256}));
    BOOST_REQUIRE_THROW(testfieldsl->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_SS>::New(dicomifier::translator::
                            ConstantField<EVR_SS>::New({128,256}));
    BOOST_REQUIRE_THROW(testfieldss->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_ST>::New(dicomifier::translator::
                            ConstantField<EVR_ST>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldst->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_TM>::New(dicomifier::translator::
                            ConstantField<EVR_TM>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldtm->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_UI>::New(dicomifier::translator::
                            ConstantField<EVR_UI>::New("128\\256"));
    BOOST_REQUIRE_THROW(testfieldui->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_UL>::New(dicomifier::translator::
                            ConstantField<EVR_UL>::New({128,256}));
    BOOST_REQUIRE_THROW(testfieldul->run(brukerdataset, *generator, NULL),
                        dicomifier::DicomifierException);
    
    // Test VR = UN => Not implemented
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_UT>::New(dicomifier::translator::
                            ConstantField<EVR_UT>::New("128\\256"));
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
        AcquisitionMatrixDcmField<EVR_US>::New(dicomifier::translator::
                            ConstantField<EVR_US>::New({128,256}));
    BOOST_REQUIRE_THROW(testfieldUS->run(NULL, *generator, NULL), 
                        dicomifier::DicomifierException);
}
 
/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Missing Sub Tag
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataOK02)
{
    // Test VR = US
    auto testfieldUS = dicomifier::translator::
        AcquisitionMatrixDcmField<EVR_US>::New();
    BOOST_REQUIRE_THROW(testfieldUS->run(brukerdataset, *generator, NULL), 
                        dicomifier::DicomifierException);
}
