/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>

#define BOOST_TEST_MODULE ModuleEnhanceBrukerDicom
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "bruker/actions/EnhanceBrukerDicom.h"
#include "core/DicomifierException.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::New();
    BOOST_CHECK_EQUAL(enhanceb2d != NULL, true);
    
    enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::New(NULL, "",
                                                              "", "", "");
    BOOST_CHECK_EQUAL(enhanceb2d != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto testenhance = dicomifier::actions::EnhanceBrukerDicom::New();
    
    DcmDataset* dataset = new DcmDataset();

    testenhance->set_dataset(dataset);
    testenhance->set_brukerDir("path");
    testenhance->set_outputDir("outputdir");
    testenhance->set_SOPClassUID("SOPClass");
        
    BOOST_CHECK_EQUAL(testenhance->get_dataset() != NULL, true);
    BOOST_CHECK_EQUAL(testenhance->get_brukerDir() == "path", true);
    BOOST_CHECK_EQUAL(testenhance->get_outputDir() == "outputdir", true);
    BOOST_CHECK_EQUAL(testenhance->get_SOPClassUID() == "SOPClass", true);

    delete dataset;
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run
 */
struct TestDataOK03
{
    DcmDataset * dataset;
 
    std::string subjectfilepath;
    std::string visuparsfile;
    std::string binaryfile;
 
    TestDataOK03()
    {
        dataset = new DcmDataset();
        
        subjectfilepath = "./subject";
        
        std::ofstream myfile;
        myfile.open(subjectfilepath);
        myfile << "Writing this to a file.\n";
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##$SUBJECT_date=<2014-03-19T14:00:09,240+0100>\n";
        myfile << "##$SUBJECT_name_string=( 64 )\n";
        myfile << "<Gustave>\n";
        myfile << "##$DATTYPE=ip_int\n";
        myfile << "##$IM_SIX=8\n";
        myfile << "##$IM_SIY=8\n";
        myfile << "##$IM_SIZ=1\n";
        myfile << "##END=\n";
        myfile.close();
        
        boost::filesystem::create_directory("./1");
        boost::filesystem::create_directory("./1/pdata");
        boost::filesystem::create_directory("./1/pdata/1");
        
        visuparsfile = "./1/pdata/1/visu_pars";
        
        myfile.open(visuparsfile);
        myfile << "Writing this to a file.\n";
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##$ACQ_scan_name=( 64 )\n";
        myfile << "<1_Localizer>\n";
        myfile << "##$ACQ_method=( 40 )\n";
        myfile << "<Bruker:FLASH>\n";
        myfile << "##$SUBJECT_study_name=( 64 )\n";
        myfile << "<rat 3>\n";
        myfile << "##$PVM_SPackArrSliceDistance=( 3 )\n";
        myfile << "2 2 2\n";
        myfile << "##$VisuAcqImagePhaseEncDir=( 15 )\n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (3, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=15\n";
        myfile << "##END=\n";
        myfile.close();
        
        // Write 2dseq file
        char* buffer = new char[64];
        binaryfile = "./1/pdata/1/2dseq";
        std::ofstream outfile(binaryfile, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;

        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));
    }
 
    ~TestDataOK03()
    {
        delete dataset;
        
        remove(visuparsfile.c_str());
        remove(subjectfilepath.c_str());
        remove(binaryfile.c_str());
        
        boost::filesystem::remove_all("./1");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    // TODO
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: get_default_directory_name
 */
struct TestDataOK04
{
    TestDataOK04()
    {
        boost::filesystem::create_directory("./1");
    }

    ~TestDataOK04()
    {
        boost::filesystem::remove_all("./1");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
{
    std::string defaultdir = dicomifier::actions::EnhanceBrukerDicom::
            get_default_directory_name(boost::filesystem::path("./1"));

    BOOST_CHECK_EQUAL(defaultdir, std::string("1"));

    boost::filesystem::create_directory("./1/1_");
    boost::filesystem::create_directory("./1/2_");

    defaultdir = dicomifier::actions::EnhanceBrukerDicom::
                get_default_directory_name(boost::filesystem::path("./1"));

    BOOST_CHECK_EQUAL(defaultdir, std::string("3"));
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: replace_unavailable_char
 */
BOOST_AUTO_TEST_CASE(TEST_OK_05)
{
    std::string stringtest = "1_5-a@b;C.D";
    dicomifier::actions::EnhanceBrukerDicom::replace_unavailable_char(stringtest);

    BOOST_CHECK_EQUAL(stringtest, std::string("1_5_A_B_C_D"));
}


/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Unknown bruker Directory
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto testenhance = dicomifier::actions::EnhanceBrukerDicom::New();
    
    testenhance->set_brukerDir("unknown path");
        
    BOOST_REQUIRE_THROW(testenhance->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: No Series number
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataOK03)
{
    dataset->findAndDeleteElement(DCM_SeriesNumber, true);

    auto testenhance = 
        dicomifier::actions::EnhanceBrukerDicom::New(dataset, ".", 
                                                     "MRImageStorage", ".",
                                                     "1");
        
    BOOST_REQUIRE_THROW(testenhance->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Bad Series number
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataOK03)
{
    dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("90009"), true);

    auto testenhance =
        dicomifier::actions::EnhanceBrukerDicom::New(dataset, ".",
                                                     "MRImageStorage", ".",
                                                     "1");

    BOOST_REQUIRE_THROW(testenhance->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 04 *******************************/
/**
 * Error test case: Bad VisuCoreFrameCount
 */
struct TestDataKO04
{
    DcmDataset * dataset;

    std::string subjectfilepath;
    std::string visuparsfile;
    std::string dictionaryfile;
    std::string binaryfile;

    TestDataKO04()
    {
        dataset = new DcmDataset();

        subjectfilepath = "./subject";

        std::ofstream myfile;
        myfile.open(subjectfilepath);
        myfile << "Writing this to a file.\n";
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##$SUBJECT_date=<2014-03-19T14:00:09,240+0100>\n";
        myfile << "##$SUBJECT_name_string=( 64 )\n";
        myfile << "<Gustave>\n";
        myfile << "##$DATTYPE=ip_int\n";
        myfile << "##$IM_SIX=8\n";
        myfile << "##$IM_SIY=8\n";
        myfile << "##$IM_SIZ=1\n";
        myfile << "##END=\n";
        myfile.close();

        boost::filesystem::create_directory("./1");
        boost::filesystem::create_directory("./1/pdata");
        boost::filesystem::create_directory("./1/pdata/1");

        visuparsfile = "./1/pdata/1/visu_pars";

        myfile.open(visuparsfile);
        myfile << "Writing this to a file.\n";
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##$ACQ_scan_name=( 64 )\n";
        myfile << "<1_Localizer>\n";
        myfile << "##$ACQ_method=( 40 )\n";
        myfile << "<Bruker:FLASH>\n";
        myfile << "##$SUBJECT_study_name=( 64 )\n";
        myfile << "<rat 3>\n";
        myfile << "##$PVM_SPackArrSliceDistance=( 3 )\n";
        myfile << "2 2 2\n";
        myfile << "##$VisuAcqImagePhaseEncDir=( 15 )\n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "col_dir col_dir col_dir col_dir col_dir col_dir \n";
        myfile << "##$VisuFGOrderDescDim=2\n";
        myfile << "##$VisuFGOrderDesc=( 2 )\n";
        myfile << "(5, <FG_SLICE>, <>, 0, 2) (3, <FG_MOVIE>, <Selective Inversion>, 2, 1)\n";
        myfile << "##$VisuGroupDepVals=( 3 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0) (<VisuAcqInversionTime>, 0)\n";
        myfile << "##$VisuCoreFrameCount=10\n";
        myfile << "##END=\n";
        myfile.close();

        // Write 2dseq file
        char* buffer = new char[64];
        binaryfile = "./1/pdata/1/2dseq";
        std::ofstream outfile(binaryfile, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
    }

    ~TestDataKO04()
    {
        delete dataset;

        remove(visuparsfile.c_str());
        remove(subjectfilepath.c_str());
        remove(dictionaryfile.c_str());
        remove(binaryfile.c_str());

        boost::filesystem::remove_all("./1");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_04, TestDataKO04)
{
    dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

    auto testenhance =
        dicomifier::actions::EnhanceBrukerDicom::New(dataset, ".",
                                                     "MRImageStorage", ".",
                                                     "1");

    BOOST_REQUIRE_THROW(testenhance->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 05 *******************************/
/**
 * Error test case: Bad SOP Class UID
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_05, TestDataOK03)
{
    dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

    auto testenhance =
        dicomifier::actions::EnhanceBrukerDicom::New(dataset, ".",
                                                     "badvalue", ".",
                                                     "1");

    BOOST_REQUIRE_THROW(testenhance->run(), dicomifier::DicomifierException);
}
