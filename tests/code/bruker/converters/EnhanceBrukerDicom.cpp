/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <memory>
#include <iostream>
#include <stdlib.h>
#include <string>

#define BOOST_TEST_MODULE ModuleEnhanceBrukerDicom
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dcuid.h>

#include <odil/DataSet.h>
#include <odil/Reader.h>
#include <odil/registry.h>

#include "bruker/converters/EnhanceBrukerDicom.h"
#include "core/DicomifierException.h"

struct TestEnvironment
{
    std::string directorypath;
    std::string outputdirectory;
    std::vector<std::string> filestoremove;
    odil::DataSet dataset;

    std::string pdatapath;

    std::string outputdicom;

    TestEnvironment() :
        directorypath("./test_ModuleEnhanceBrukerDicom"),
        outputdirectory("./test_ModuleEnhanceBrukerDicom_out")
    {
        boost::filesystem::create_directory(
                    boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::create_directory(
                    boost::filesystem::path(outputdirectory.c_str()));

        std::string const subjectfile = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(subjectfile);
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
        filestoremove.push_back(subjectfile);

        std::string const seriespath = directorypath + "/1";
        boost::filesystem::create_directory(
                    boost::filesystem::path(seriespath.c_str()));

        std::string const acqpfile = seriespath + "/acqp";
        myfile.open(acqpfile);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(acqpfile);

        pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(
                    boost::filesystem::path(pdatapath.c_str()));

        std::vector<std::pair<std::string, double> > word_type_list;
        word_type_list.push_back(
                    std::pair<std::string, double>("_16BIT_SGN_INT", 1));
        word_type_list.push_back(
                    std::pair<std::string, double>("_32BIT_SGN_INT", 2));
        word_type_list.push_back(
                    std::pair<std::string, double>("_8BIT_UNSGN_INT", 0.5));
        word_type_list.push_back(
                    std::pair<std::string, double>("_32BIT_FLOAT", 2));

        unsigned int i = 0;
        for (std::string const byteorder : { "littleEndian", "bigEndian" })
        {
            for (auto item : word_type_list)
            {
                ++i;
                create_visupars(pdatapath, i, item.first, item.second,
                                byteorder);
            }
        }
        
        dataset.add(odil::registry::SeriesNumber, {10001});

        outputdicom = outputdirectory + "/Mouse^Mickey/1_DICOMI/1_PROTOC/1";
        filestoremove.push_back(outputdicom);
    }

    void create_visupars(std::string const & pdatapath, int reco_num,
                         std::string const & word_type, double ratio,
                         std::string const & byte_order)
    {
        std::stringstream reco_path;
        reco_path << pdatapath << "/" << reco_num;
        boost::filesystem::create_directory
                (boost::filesystem::path(reco_path.str().c_str()));

        std::string visuparsfile = reco_path.str() + "/visu_pars";
        std::ofstream myfile;
        myfile.open(visuparsfile);
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n"
               << "##JCAMPDX=4.24\n"
               << "##DATATYPE=Parameter Values\n"
               << "##ORIGIN=Bruker BioSpin MRI GmbH\n"
               << "##$SUBJECT_id=( 60 )\n"
               << "<Rat>\n"
               << "##$VisuSubjectName=( 65 )\n"
               << "<Mouse^Mickey>\n"
               << "##$VisuSubjectId=( 65 )\n"
               << "<subject_01>\n"
               << "##$ACQ_scan_name=( 64 )\n"
               << "<1_Localizer>\n"
               << "##$ACQ_method=( 40 )\n"
               << "<Bruker:FLASH>\n"
               << "##$SUBJECT_study_name=( 64 )\n"
               << "<rat 3>\n"
               << "##$PVM_SPackArrSliceDistance=( 3 )\n"
               << "2 2 2\n"
               << "##$VisuAcqImagePhaseEncDir=( 1 )\n"
               << "col_dir\n"
               << "##$VisuFGOrderDescDim=1\n"
               << "##$VisuFGOrderDesc=( 1 )\n"
               << "(1, <FG_SLICE>, <>, 0, 2)\n"
               << "##$VisuGroupDepVals=( 2 )\n"
               << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n"
               << "##$VisuCoreFrameCount=1\n"
               << "##$VisuCoreWordType=" << word_type << "\n"
               << "##$VisuCoreByteOrder=" << byte_order << "\n"
               << "##$VisuCoreSize=( 2 )\n"
               << "8 8\n"
               << "##$VisuStudyUid=( 65 )\n"
               << "<2.25.309509301719836607967426822084991797794>\n"
               << "##$VisuStudyId=( 65 )\n"
               << "<Dicomifier>\n"
               << "##$VisuAcquisitionProtocol=( 65 )\n"
               << "<Protocol>\n"
               << "##$VisuUid=( 65 )\n"
               << "<2.25.78137108291313894466257645742394761300>\n"
               << "##$VisuSeriesNumber=( 65 )\n"
               << "<1000" << reco_num << ">\n"
               << "##$VisuCoreOrientation=( 1, 9 )\n"
               << "1 6.12303176911189e-17 0 0 1 0\n"
               << "##$VisuCorePosition=( 1, 3 )\n"
               << "0 0 0\n"
               << "##$VisuCoreExtent=( 2 )\n"
               << "0 0\n"
               << "##$VisuAcqDate=<2015-02-19T09:59:21,271+0100>\n"
               << "##$VisuAcqScanTime=12800\n"
               << "##$VisuAcqImagedNucleus=( 8 )\n"
               << "<1H>\n"
               << "##$VisuCoreFrameType=( 1 )\n"
               << "MAGNITUDE_IMAGE\n"
               << "##$VisuCoreDim=2\n"
               << "##$VisuCoreFrameThickness=( 1 )\n"
               << "1\n"
               << "##$VisuAcqRepetitionTime=( 1 )\n"
               << "100\n"
               << "##$VisuAcqFlipAngle=30\n"
               << "##$VisuAcqEchoTrainLength=1\n"
               << "##END=\n";
        myfile.close();
        filestoremove.push_back(visuparsfile);

        // Write 2dseq file
        int size = 64*ratio;
        char* buffer = new char[size];
        std::string const binaryfile = reco_path.str() + "/2dseq";
        std::ofstream outfile(binaryfile, std::ofstream::binary);
        outfile.write(buffer, size);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(binaryfile);
    }

    std::string create_visupars_file() const
    {
        std::string const recopath = pdatapath + "/1";
        boost::filesystem::create_directory
                (boost::filesystem::path(recopath.c_str()));
        std::string const visuparsfile = recopath + "/visu_pars";

        return visuparsfile;
    }

    ~TestEnvironment()
    {
        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(
                    boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(
                    boost::filesystem::path(outputdirectory.c_str()));
    }
};

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::New();
    BOOST_CHECK_EQUAL(enhanceb2d != NULL, true);
    
    enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::New("", "", "", "", "");
    BOOST_CHECK_EQUAL(enhanceb2d != NULL, true);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(Accessors)
{
    auto testenhance = dicomifier::bruker::EnhanceBrukerDicom::New();
    
    testenhance->set_brukerDir("path");
    testenhance->set_outputDir("outputdir");
    testenhance->set_SOPClassUID("SOPClass");
        
    BOOST_CHECK_EQUAL(testenhance->get_brukerDir() == "path", true);
    BOOST_CHECK_EQUAL(testenhance->get_outputDir() == "outputdir", true);
    BOOST_CHECK_EQUAL(testenhance->get_SOPClassUID() == "SOPClass", true);
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Run (MRImageStorage)
 */
BOOST_FIXTURE_TEST_CASE(Run_MRImageStorage, TestEnvironment)
{
    std::vector<std::string> seriesnb = { "10001", "10002", "10003", "10004",
                                          "10005", "10006", "10007", "10008"};
    for (auto item : seriesnb)
    {
        auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
                New(directorypath, UID_MRImageStorage,
                    outputdirectory, "1", item);

        // Process
        enhanceb2d->run();

        std::ifstream stream(boost::filesystem::path(outputdicom).c_str(),
                             std::ios::in | std::ios::binary);

        std::pair<odil::DataSet, odil::DataSet> file =
                odil::Reader::read_file(stream);

        BOOST_REQUIRE(!file.second.empty());
        BOOST_REQUIRE_EQUAL(file.second.as_string(
                                odil::registry::SOPClassUID)[0],
                            UID_MRImageStorage);

        BOOST_REQUIRE_EQUAL(file.second.as_string(
                                odil::registry::PatientName)[0],
                            "Mouse^Mickey");
        BOOST_REQUIRE_EQUAL(file.second.as_string(
                                odil::registry::PatientID)[0],
                            "subject_01");

        odil::Value::Reals expectedResult({1, 6.12303176911189e-17, 0});
        for (unsigned int i = 0; i < expectedResult.size(); ++i)
        {
            BOOST_CHECK_CLOSE(expectedResult[i],
                              file.second.as_real(
                                  odil::registry::ImageOrientationPatient)[i],
                              0.0001);
        }
    }
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: Run (EnhanceMRImageStorage)
 */
BOOST_FIXTURE_TEST_CASE(Run_EnhanceMRImageStorage, TestEnvironment)
{
    std::vector<std::string> seriesnb = { "10001", "10002", "10003", "10004",
                                          "10005", "10006", "10007", "10008"};
    for (auto item : seriesnb)
    {
        auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
                New(directorypath, UID_EnhancedMRImageStorage,
                    outputdirectory, "1", item);

        // Process
        enhanceb2d->run();

        std::ifstream stream(boost::filesystem::path(outputdicom).c_str(),
                             std::ios::in | std::ios::binary);

        std::pair<odil::DataSet, odil::DataSet> file =
                odil::Reader::read_file(stream);

        BOOST_REQUIRE(!file.second.empty());
        BOOST_REQUIRE_EQUAL(file.second.as_string(
                                odil::registry::SOPClassUID)[0],
                            UID_EnhancedMRImageStorage);

        BOOST_REQUIRE_EQUAL(file.second.as_string(
                                odil::registry::PatientName)[0],
                            "Mouse^Mickey");
        BOOST_REQUIRE_EQUAL(file.second.as_string(
                                odil::registry::PatientID)[0],
                            "subject_01");

        BOOST_REQUIRE(file.second.has(
                          odil::registry::SharedFunctionalGroupsSequence));
        BOOST_REQUIRE(file.second.has(
                          odil::registry::PerFrameFunctionalGroupsSequence));
    }
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: get_default_directory_name
 */
BOOST_AUTO_TEST_CASE(Get_Default_Directory)
{
    boost::filesystem::create_directory("./1");
    std::string defaultdir = dicomifier::bruker::EnhanceBrukerDicom::
            get_default_directory_name(boost::filesystem::path("./1"));

    BOOST_CHECK_EQUAL(defaultdir, std::string("1"));

    boost::filesystem::create_directory("./1/1_");
    boost::filesystem::create_directory("./1/2_");

    defaultdir = dicomifier::bruker::EnhanceBrukerDicom::
                get_default_directory_name(boost::filesystem::path("./1"));

    BOOST_CHECK_EQUAL(defaultdir, std::string("3"));

    boost::filesystem::remove_all("./1");
}

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: replace_unavailable_char
 */
BOOST_AUTO_TEST_CASE(Replace_Unavailable_Char)
{
    std::string stringtest = "1_5-a@b;C.D";
    dicomifier::bruker::EnhanceBrukerDicom::replace_unavailable_char(stringtest);

    BOOST_CHECK_EQUAL(stringtest, std::string("1_5_A_B_C_D"));
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Unknown bruker Directory
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto testenhance = dicomifier::bruker::EnhanceBrukerDicom::New();
    
    testenhance->set_brukerDir("unknown path");
        
    BOOST_REQUIRE_THROW(testenhance->run(), dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Bad Series number
 */
BOOST_FIXTURE_TEST_CASE(Bad_SeriesNumber, TestEnvironment)
{
    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage,
                outputdirectory, "1", "90009");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Bad VisuCoreFrameCount
 */
BOOST_FIXTURE_TEST_CASE(Corrupted_Data, TestEnvironment)
{
    // Replace visu_pars file
    std::ofstream myfile;
    myfile.open(create_visupars_file());
    myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
    myfile << "##JCAMPDX=4.24\n";
    myfile << "##DATATYPE=Parameter Values\n";
    myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
    myfile << "##$SUBJECT_id=( 60 )\n";
    myfile << "<Rat>\n";
    myfile << "##$VisuSubjectName=( 65 )\n";
    myfile << "<Mouse^Mickey>\n";
    myfile << "##$VisuSubjectId=( 65 )\n";
    myfile << "<subject_01>\n";
    myfile << "##$ACQ_scan_name=( 64 )\n";
    myfile << "<1_Localizer>\n";
    myfile << "##$ACQ_method=( 40 )\n";
    myfile << "<Bruker:FLASH>\n";
    myfile << "##$SUBJECT_study_name=( 64 )\n";
    myfile << "<rat 3>\n";
    myfile << "##$PVM_SPackArrSliceDistance=( 3 )\n";
    myfile << "2 2 2\n";
    myfile << "##$VisuAcqImagePhaseEncDir=( 1 )\n";
    myfile << "col_dir\n";
    myfile << "##$VisuFGOrderDescDim=1\n";
    myfile << "##$VisuFGOrderDesc=( 1 )\n";
    myfile << "(1, <FG_SLICE>, <>, 0, 2)\n";
    myfile << "##$VisuGroupDepVals=( 2 )\n";
    myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
    myfile << "##$VisuCoreFrameCount=33\n"; // BAD VALUE FOR VISUCOREFRAMECOUNT
    myfile << "##$VisuCoreWordType=_32BIT_FLOAT\n";
    myfile << "##$VisuCoreByteOrder=bigEndian\n";
    myfile << "##$VisuCoreSize=( 2 )\n";
    myfile << "8 8\n";
    myfile << "##END=\n";
    myfile.close();

    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage,
                outputdirectory, "1", "10001");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Bad SOP Class UID
 */
BOOST_FIXTURE_TEST_CASE(Bad_SOPClassUID, TestEnvironment)
{
    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
            New(directorypath, "BadValue", outputdirectory, "1", "10001");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Unknown bruker Directory
 */
BOOST_AUTO_TEST_CASE(Get_Default_Directory_Name)
{
    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::New();
    std::string default_dir =
            enhanceb2d->get_default_directory_name("./unknown_path");
    BOOST_CHECK_EQUAL(default_dir == "1", true);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Error while reading PixelData file
 */
BOOST_FIXTURE_TEST_CASE(No_PixelData_File, TestEnvironment)
{
    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage,
                outputdirectory, "1", "10001");

    // Remove Pixel Data file and replace by a directory
    std::string const binaryfile_ = pdatapath + "/1/2dseq";
    remove(binaryfile_.c_str());
    boost::filesystem::create_directory(
                boost::filesystem::path(binaryfile_.c_str()));

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);

    boost::filesystem::remove_all(boost::filesystem::path(binaryfile_.c_str()));
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Error while reading PixelData file
 */
BOOST_FIXTURE_TEST_CASE(Cant_Read_PixelData_File, TestEnvironment)
{
    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage,
                outputdirectory, "1", "10001");

    // Change right of file
    std::string const binaryfile_ = pdatapath + "/1/2dseq";
    std::string pixelfile = "chmod 000 " + binaryfile_;
    std::system(pixelfile.c_str());

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);

    pixelfile = "chmod 666 " + binaryfile_;
    std::system(pixelfile.c_str());
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Missing mandatory field VisuCoreSize
 */
BOOST_FIXTURE_TEST_CASE(Missing_VisuCoreSize, TestEnvironment)
{
    // Replace visu_pars file
    std::ofstream myfile;
    myfile.open(create_visupars_file());
    myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
    myfile << "##JCAMPDX=4.24\n";
    myfile << "##DATATYPE=Parameter Values\n";
    myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
    myfile << "##$SUBJECT_id=( 60 )\n";
    myfile << "<Rat>\n";
    myfile << "##$VisuSubjectName=( 65 )\n";
    myfile << "<Mouse^Mickey>\n";
    myfile << "##$VisuSubjectId=( 65 )\n";
    myfile << "<subject_01>\n";
    myfile << "##$ACQ_scan_name=( 64 )\n";
    myfile << "<1_Localizer>\n";
    myfile << "##$ACQ_method=( 40 )\n";
    myfile << "<Bruker:FLASH>\n";
    myfile << "##$SUBJECT_study_name=( 64 )\n";
    myfile << "<rat 3>\n";
    myfile << "##$PVM_SPackArrSliceDistance=( 3 )\n";
    myfile << "2 2 2\n";
    myfile << "##$VisuAcqImagePhaseEncDir=( 1 )\n";
    myfile << "col_dir\n";
    myfile << "##$VisuFGOrderDescDim=1\n";
    myfile << "##$VisuFGOrderDesc=( 1 )\n";
    myfile << "(1, <FG_SLICE>, <>, 0, 2)\n";
    myfile << "##$VisuGroupDepVals=( 2 )\n";
    myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
    myfile << "##$VisuCoreFrameCount=1\n";
    myfile << "##$VisuCoreWordType=_16BIT_SGN_INT\n";
    myfile << "##$VisuCoreByteOrder=littleEndian\n";
    myfile << "##END=\n";
    myfile.close();

    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage,
                outputdirectory, "1", "10001");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Missing mandatory field VisuCoreSize
 */
BOOST_FIXTURE_TEST_CASE(Missing_VisuCoreWordType, TestEnvironment)
{
    // Replace visu_pars file
    std::ofstream myfile;
    myfile.open(create_visupars_file());
    myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
    myfile << "##JCAMPDX=4.24\n";
    myfile << "##DATATYPE=Parameter Values\n";
    myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
    myfile << "##$SUBJECT_id=( 60 )\n";
    myfile << "<Rat>\n";
    myfile << "##$VisuSubjectName=( 65 )\n";
    myfile << "<Mouse^Mickey>\n";
    myfile << "##$VisuSubjectId=( 65 )\n";
    myfile << "<subject_01>\n";
    myfile << "##$ACQ_scan_name=( 64 )\n";
    myfile << "<1_Localizer>\n";
    myfile << "##$ACQ_method=( 40 )\n";
    myfile << "<Bruker:FLASH>\n";
    myfile << "##$SUBJECT_study_name=( 64 )\n";
    myfile << "<rat 3>\n";
    myfile << "##$PVM_SPackArrSliceDistance=( 3 )\n";
    myfile << "2 2 2\n";
    myfile << "##$VisuAcqImagePhaseEncDir=( 1 )\n";
    myfile << "col_dir\n";
    myfile << "##$VisuFGOrderDescDim=1\n";
    myfile << "##$VisuFGOrderDesc=( 1 )\n";
    myfile << "(1, <FG_SLICE>, <>, 0, 2)\n";
    myfile << "##$VisuGroupDepVals=( 2 )\n";
    myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
    myfile << "##$VisuCoreFrameCount=1\n";
    myfile << "##$VisuCoreSize=( 2 )\n";
    myfile << "8 8\n";
    myfile << "##END=\n";
    myfile.close();

    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage,
                outputdirectory, "1", "10001");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/******************************* TEST Error ************************************/
/**
 * Error test case: Bad value for field VisuCoreWordType
 */
BOOST_FIXTURE_TEST_CASE(Bad_VisuCoreWordType, TestEnvironment)
{
    // Replace visu_pars file
    std::ofstream myfile;
    myfile.open(create_visupars_file());
    myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
    myfile << "##JCAMPDX=4.24\n";
    myfile << "##DATATYPE=Parameter Values\n";
    myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
    myfile << "##$SUBJECT_id=( 60 )\n";
    myfile << "<Rat>\n";
    myfile << "##$VisuSubjectName=( 65 )\n";
    myfile << "<Mouse^Mickey>\n";
    myfile << "##$VisuSubjectId=( 65 )\n";
    myfile << "<subject_01>\n";
    myfile << "##$ACQ_scan_name=( 64 )\n";
    myfile << "<1_Localizer>\n";
    myfile << "##$ACQ_method=( 40 )\n";
    myfile << "<Bruker:FLASH>\n";
    myfile << "##$SUBJECT_study_name=( 64 )\n";
    myfile << "<rat 3>\n";
    myfile << "##$PVM_SPackArrSliceDistance=( 3 )\n";
    myfile << "2 2 2\n";
    myfile << "##$VisuAcqImagePhaseEncDir=( 1 )\n";
    myfile << "col_dir\n";
    myfile << "##$VisuFGOrderDescDim=1\n";
    myfile << "##$VisuFGOrderDesc=( 1 )\n";
    myfile << "(1, <FG_SLICE>, <>, 0, 2)\n";
    myfile << "##$VisuGroupDepVals=( 2 )\n";
    myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
    myfile << "##$VisuCoreFrameCount=1\n";
    myfile << "##$VisuCoreWordType=BAD_VALUE\n";
    myfile << "##$VisuCoreByteOrder=littleEndian\n";
    myfile << "##$VisuCoreSize=( 2 )\n";
    myfile << "8 8\n";
    myfile << "##END=\n";
    myfile.close();

    auto enhanceb2d = dicomifier::bruker::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage,
                outputdirectory, "1", "10001");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}
