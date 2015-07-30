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
#include <dcmtk/dcmdata/dctk.h>

#include <dcmtkpp/DataSet.h>
#include <dcmtkpp/registry.h>

#include "bruker/actions/EnhanceBrukerDicom.h"
#include "core/DicomifierException.h"

struct TestEnvironment
{
    std::string directorypath;
    std::string outputdirectory;
    std::string dictionary;
    std::vector<std::string> filestoremove;
    dcmtkpp::DataSet dataset;

    std::string subjectfile;
    std::string seriespath;
    std::string acqpfile;
    std::string pdatapath;
    std::string recopath;
    std::string visuparsfile;
    std::string binaryfile;

    std::string outputdicom;

    TestEnvironment() :
        directorypath("./test_ModuleEnhanceBrukerDicom"),
        outputdirectory("./test_ModuleEnhanceBrukerDicom_out"),
        dictionary("./test_ModuleEnhanceBrukerDicom_dictionary.xml")
    {
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::create_directory(boost::filesystem::path(outputdirectory.c_str()));

        subjectfile = directorypath + "/subject";
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

        seriespath = directorypath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(seriespath.c_str()));

        acqpfile = seriespath + "/acqp";
        myfile.open(acqpfile);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(acqpfile);

        pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(boost::filesystem::path(pdatapath.c_str()));
        recopath = pdatapath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(recopath.c_str()));

        visuparsfile = recopath + "/visu_pars";
        myfile.open(visuparsfile);
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
        myfile << "##$VisuCoreSize=( 2 )\n";
        myfile << "8 8\n";
        myfile << "##$VisuStudyUid=( 65 )\n";
        myfile << "<2.25.309509301719836607967426822084991797794>\n";
        myfile << "##$VisuStudyId=( 65 )\n";
        myfile << "<Dicomifier>\n";
        myfile << "##$VisuAcquisitionProtocol=( 65 )\n";
        myfile << "<Protocol>\n";
        myfile << "##$VisuUid=( 65 )\n";
        myfile << "<2.25.78137108291313894466257645742394761300>\n";
        myfile << "##$VisuSeriesNumber=( 65 )\n";
        myfile << "<10001>\n";
        myfile << "##$VisuCoreOrientation=( 1, 9 )\n";
        myfile << "1 0 0 0 1 0\n";
        myfile << "##$VisuCorePosition=( 1, 3 )\n";
        myfile << "0 0 0\n";
        myfile << "##$VisuCoreExtent=( 2 )\n";
        myfile << "0 0\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(visuparsfile);

        // Write 2dseq file
        char* buffer = new char[64];
        binaryfile = recopath + "/2dseq";
        std::ofstream outfile(binaryfile, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(binaryfile);
        
        dataset.add(dcmtkpp::registry::SeriesNumber, {10001});

        outputdicom = outputdirectory + "/Mouse^Mickey/1_DICOMI/1_PROTOC/1";
        filestoremove.push_back(outputdicom);
    }

    ~TestEnvironment()
    {
        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(boost::filesystem::path(outputdirectory.c_str()));
    }
};

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::New();
    BOOST_CHECK_EQUAL(enhanceb2d != NULL, true);
    
    enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::New("", "", "", "", "");
    BOOST_CHECK_EQUAL(enhanceb2d != NULL, true);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(Accessors)
{
    auto testenhance = dicomifier::actions::EnhanceBrukerDicom::New();
    
    testenhance->set_brukerDir("path");
    testenhance->set_outputDir("outputdir");
    testenhance->set_SOPClassUID("SOPClass");
        
    BOOST_CHECK_EQUAL(testenhance->get_brukerDir() == "path", true);
    BOOST_CHECK_EQUAL(testenhance->get_outputDir() == "outputdir", true);
    BOOST_CHECK_EQUAL(testenhance->get_SOPClassUID() == "SOPClass", true);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run (MRImageStorage)
 */
BOOST_FIXTURE_TEST_CASE(Run_MRImageStorage, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "10001");

    // Process
    enhanceb2d->run();

    // Try to open Created Dataset
    DcmFileFormat fileformat;
    OFCondition cond = fileformat.loadFile(outputdicom.c_str());
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);

    DcmDataset * datasetout = fileformat.getAndRemoveDataset();
    BOOST_CHECK_EQUAL(datasetout != NULL, true);

    // Just looking for 2 informations
    OFString patient_name;
    cond = datasetout->findAndGetOFStringArray(DCM_PatientName, patient_name);
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);
    BOOST_CHECK_EQUAL(patient_name.compare(OFString("Mouse^Mickey")), 0);

    OFString patient_id;
    cond = datasetout->findAndGetOFStringArray(DCM_PatientID, patient_id);
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);
    BOOST_CHECK_EQUAL(patient_id.compare(OFString("subject_01")), 0);

    delete datasetout;
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Run (EnhanceMRImageStorage)
 */
/*
BOOST_DO_NOT_RUN_FIXTURE_TEST_CASE(Run_EnhanceMRImageStorage, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_EnhancedMRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    // Process
    enhanceb2d->run();

    // Try to open Created Dataset
    DcmFileFormat fileformat;
    OFCondition cond = fileformat.loadFile(outputdicom.c_str());
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);

    DcmDataset * datasetout = fileformat.getAndRemoveDataset();
    BOOST_CHECK_EQUAL(datasetout != NULL, true);

    // Just looking for 2 informations
    OFString patient_name;
    cond = datasetout->findAndGetOFStringArray(DCM_PatientName, patient_name);
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);
    BOOST_CHECK_EQUAL(patient_name.compare(OFString("Mouse^Mickey")), 0);

    OFString patient_id;
    cond = datasetout->findAndGetOFStringArray(DCM_PatientID, patient_id);
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);
    BOOST_CHECK_EQUAL(patient_id.compare(OFString("subject_01")), 0);

    delete datasetout;
}
*/

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: get_default_directory_name
 */
BOOST_AUTO_TEST_CASE(Get_Default_Directory)
{
    boost::filesystem::create_directory("./1");
    std::string defaultdir = dicomifier::actions::EnhanceBrukerDicom::
            get_default_directory_name(boost::filesystem::path("./1"));

    BOOST_CHECK_EQUAL(defaultdir, std::string("1"));

    boost::filesystem::create_directory("./1/1_");
    boost::filesystem::create_directory("./1/2_");

    defaultdir = dicomifier::actions::EnhanceBrukerDicom::
                get_default_directory_name(boost::filesystem::path("./1"));

    BOOST_CHECK_EQUAL(defaultdir, std::string("3"));

    boost::filesystem::remove_all("./1");
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: replace_unavailable_char
 */
BOOST_AUTO_TEST_CASE(Replace_Unavailable_Char)
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

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Bad Series number
 */
BOOST_FIXTURE_TEST_CASE(Bad_SeriesNumber, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "90009");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 04 *******************************/
/**
 * Error test case: Bad VisuCoreFrameCount
 */
BOOST_FIXTURE_TEST_CASE(Corrupted_Data, TestEnvironment)
{
    // Replace visu_pars file
    std::ofstream myfile;
    myfile.open(visuparsfile);
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

    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 05 *******************************/
/**
 * Error test case: Bad SOP Class UID
 */
BOOST_FIXTURE_TEST_CASE(Bad_SOPClassUID, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, "BadValue", outputdirectory, "1", "1");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 06 *******************************/
/**
 * Error test case: Unknown bruker Directory
 */
BOOST_AUTO_TEST_CASE(Get_Default_Directory_Name)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::New();
    std::string default_dir =
            enhanceb2d->get_default_directory_name("./unknown_path");
    BOOST_CHECK_EQUAL(default_dir == "1", true);
}

/*************************** TEST KO 07 *******************************/
/**
 * Error test case: Error while reading PixelData file
 */
BOOST_FIXTURE_TEST_CASE(No_PixelData_File, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    // Remove Pixel Data file and replace by a directory
    remove(binaryfile.c_str());
    boost::filesystem::create_directory(boost::filesystem::path(binaryfile.c_str()));

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 08 *******************************/
/**
 * Error test case: Error while reading PixelData file
 */
BOOST_FIXTURE_TEST_CASE(Cant_Read_PixelData_File, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    // Change right of file
    std::string pixelfile = "chmod 000 " + binaryfile;
    std::system(pixelfile.c_str());

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);

    pixelfile = "chmod 666 " + binaryfile;
    std::system(pixelfile.c_str());
}

/*************************** TEST KO 09 *******************************/
/**
 * Error test case: Missing mandatory field VisuCoreSize
 */
BOOST_FIXTURE_TEST_CASE(Missing_VisuCoreSize, TestEnvironment)
{
    // Replace visu_pars file
    std::ofstream myfile;
    myfile.open(visuparsfile);
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

    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 10 *******************************/
/**
 * Error test case: Missing mandatory field VisuCoreSize
 */
BOOST_FIXTURE_TEST_CASE(Missing_VisuCoreWordType, TestEnvironment)
{
    // Replace visu_pars file
    std::ofstream myfile;
    myfile.open(visuparsfile);
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

    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 10 *******************************/
/**
 * Error test case: Bad value for field VisuCoreWordType
 */
BOOST_FIXTURE_TEST_CASE(Bad_VisuCoreWordType, TestEnvironment)
{
    // Replace visu_pars file
    std::ofstream myfile;
    myfile.open(visuparsfile);
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

    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 11 *******************************/
/**
 * Error test case: Missing StudyDescription
 */
BOOST_FIXTURE_TEST_CASE(Missing_StudyDescription, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    BOOST_REQUIRE_THROW(enhanceb2d->get_destination_filename(dataset),
                        dcmtkpp::Exception);
}

/*************************** TEST KO 12 *******************************/
/**
 * Error test case: Missing SeriesDescription
 */
BOOST_FIXTURE_TEST_CASE(Missing_SeriesDescription, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    dataset.add(dcmtkpp::registry::StudyDescription, {"studydesc"});

    BOOST_REQUIRE_THROW(enhanceb2d->get_destination_filename(dataset),
                        dcmtkpp::Exception);
}

/*************************** TEST KO 13 *******************************/
/**
 * Error test case: Missing SeriesNumber
 */
BOOST_FIXTURE_TEST_CASE(Missing_SeriesNumber, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    dataset.add(dcmtkpp::registry::StudyDescription, {"studydesc"});
    dataset.add(dcmtkpp::registry::SeriesDescription, {"seriesdesc"});
    dataset.remove(dcmtkpp::registry::SeriesNumber);

    BOOST_REQUIRE_THROW(enhanceb2d->get_destination_filename(dataset),
                        dcmtkpp::Exception);
}

/*************************** TEST KO 14 *******************************/
/**
 * Error test case: Missing InstanceNumber
 */
BOOST_FIXTURE_TEST_CASE(Missing_InstanceNumber, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    dataset.add(dcmtkpp::registry::StudyDescription, {"studydesc"});
    dataset.add(dcmtkpp::registry::SeriesDescription, {"seriesdesc"});
    
    BOOST_REQUIRE_THROW(enhanceb2d->get_destination_filename(dataset),
                        dcmtkpp::Exception);
}

/*************************** TEST KO 15 *******************************/
/**
 * Error test case: Missing ImagesInAcquisition
 */
BOOST_FIXTURE_TEST_CASE(Missing_ImagesInAcquisition, TestEnvironment)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(directorypath, UID_MRImageStorage, outputdirectory, "1", "1");

    dataset.add(dcmtkpp::registry::StudyDescription, {"studydesc"});
    dataset.add(dcmtkpp::registry::SeriesDescription, {"seriesdesc"});
    dataset.add(dcmtkpp::registry::InstanceNumber, {1});

    BOOST_REQUIRE_THROW(enhanceb2d->get_destination_filename(dataset),
                        dcmtkpp::Exception);
}
