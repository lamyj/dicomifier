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
 * Nominal test case: Run (MRImageStorage)
 */
struct TestDataOK03
{
    std::string directorypath;
    std::string outputdirectory;
    std::string dictionary;
    std::vector<std::string> filestoremove;
    DcmDataset* dataset;
 
    TestDataOK03()
    {
        directorypath = "./test_ModuleEnhanceBrukerDicom";
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));

        outputdirectory = "./test_ModuleEnhanceBrukerDicom_out";
        boost::filesystem::create_directory(boost::filesystem::path(outputdirectory.c_str()));

        std::string file = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(file);
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
        filestoremove.push_back(file);

        std::string seriespath = directorypath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(seriespath.c_str()));

        file = seriespath + "/acqp";
        myfile.open(file);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        std::string pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(boost::filesystem::path(pdatapath.c_str()));
        std::string recopath = pdatapath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(recopath.c_str()));

        file = recopath + "/visu_pars";
        myfile.open(file);
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
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        // Write 2dseq file
        char* buffer = new char[64];
        file = recopath + "/2dseq";
        std::ofstream outfile(file, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(file);

        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

        dictionary = "./test_ModuleEnhanceBrukerDicom_dictionary.xml";
        myfile.open(dictionary);
        myfile << "<Dictionary>\n";
        myfile << "    <DicomField tag=\"0008,0008\" keyword=\"ImageType\" vr=\"CS\">\n";
        myfile << "        <ConstantField values=\"ORIGINAL\\PRIMARY\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0012\" keyword=\"InstanceCreationDate\" vr=\"DA\">\n";
        myfile << "        <DateGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0013\" keyword=\"InstanceCreationTime\" vr=\"TM\">\n";
        myfile << "        <TimeGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0016\" keyword=\"SOPClassUID\" vr=\"UI\">\n";
        myfile << "        <ConstantField values=\"1.2.840.10008.5.1.4.1.1.4\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0018\" keyword=\"SOPInstanceUID\" vr=\"UI\">\n";
        myfile << "        <UIDGenerator uidtype=\"SOPInstanceUID\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,1030\" keyword=\"StudyDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuStudyDescription\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,103e\" keyword=\"SeriesDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuAcquisitionProtocol\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0010\" keyword=\"PatientName\" vr=\"PN\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectName\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0020\" keyword=\"PatientID\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectId\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,0013\" keyword=\"InstanceNumber\" vr=\"IS\" >\n";
        myfile << "        <InstanceNumberDcmField />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,1002\" keyword=\"ImagesInAcquisition\" vr=\"IS\" >\n";
        myfile << "        <BrukerField name=\"VisuCoreFrameCount\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "</Dictionary>\n";
        myfile.close();
        filestoremove.push_back(dictionary);
    }
 
    ~TestDataOK03()
    {
        delete dataset;

        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(boost::filesystem::path(outputdirectory.c_str()));
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    // Process
    enhanceb2d->run();

    std::string const outputdicom = outputdirectory + "/Mouse^Mickey/1_/1_/1";

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
BOOST_FIXTURE_TEST_CASE(Run_EnhanceMRImageStorage, TestDataOK03)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_EnhancedMRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    // Process
    enhanceb2d->run();

    std::string const outputdicom = outputdirectory + "/Mouse^Mickey/1_/1_/1";

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

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: get_default_directory_name
 */
struct TestDataOK05
{
    TestDataOK05()
    {
        boost::filesystem::create_directory("./1");
    }

    ~TestDataOK05()
    {
        boost::filesystem::remove_all("./1");
    }
};

BOOST_FIXTURE_TEST_CASE(Get_Default_Directory, TestDataOK05)
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

/*************************** TEST OK 07 *******************************/
/**
 * Nominal test case: Run (Get_Default_Directory)
 */
BOOST_FIXTURE_TEST_CASE(Run_No_PatientName, TestDataOK03)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    dictionary = "./test_ModuleEnhanceBrukerDicom_dictionary.xml";
    std::ofstream myfile;
    myfile.open(dictionary);
    myfile << "<Dictionary>\n";
    myfile << "    <DicomField tag=\"0008,0008\" keyword=\"ImageType\" vr=\"CS\">\n";
    myfile << "        <ConstantField values=\"ORIGINAL\\PRIMARY\" />\n";
    myfile << "    </DicomField>\n";
    myfile << "    <DicomField tag=\"0008,0012\" keyword=\"InstanceCreationDate\" vr=\"DA\">\n";
    myfile << "        <DateGenerator />\n";
    myfile << "    </DicomField>\n";
    myfile << "    <DicomField tag=\"0008,0013\" keyword=\"InstanceCreationTime\" vr=\"TM\">\n";
    myfile << "        <TimeGenerator />\n";
    myfile << "    </DicomField>\n";
    myfile << "    <DicomField tag=\"0008,0016\" keyword=\"SOPClassUID\" vr=\"UI\">\n";
    myfile << "        <ConstantField values=\"1.2.840.10008.5.1.4.1.1.4\" />\n";
    myfile << "    </DicomField>\n";
    myfile << "    <DicomField tag=\"0008,0018\" keyword=\"SOPInstanceUID\" vr=\"UI\">\n";
    myfile << "        <UIDGenerator uidtype=\"SOPInstanceUID\" />\n";
    myfile << "    </DicomField>\n";
    myfile << "    <DicomField tag=\"0008,1030\" keyword=\"StudyDescription\" vr=\"LO\">\n";
    myfile << "        <BrukerField name=\"VisuStudyDescription\" />\n";
    myfile << "    </DicomField>\n";
    myfile << "    <DicomField tag=\"0008,103e\" keyword=\"SeriesDescription\" vr=\"LO\">\n";
    myfile << "        <BrukerField name=\"VisuAcquisitionProtocol\" />\n";
    myfile << "    </DicomField>\n";
    myfile << "    <DicomField tag=\"0020,0013\" keyword=\"InstanceNumber\" vr=\"IS\" >\n";
    myfile << "        <InstanceNumberDcmField />\n";
    myfile << "    </DicomField>\n";
    myfile << "    <DicomField tag=\"0020,1002\" keyword=\"ImagesInAcquisition\" vr=\"IS\" >\n";
    myfile << "        <BrukerField name=\"VisuCoreFrameCount\" />\n";
    myfile << "    </DicomField>\n";
    myfile << "</Dictionary>\n";
    myfile.close();

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    // Process
    enhanceb2d->run();

    std::string const outputdicom = outputdirectory + "/1/1_/1_/1";

    // Try to open Created Dataset
    DcmFileFormat fileformat;
    OFCondition cond = fileformat.loadFile(outputdicom.c_str());
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);

    DcmDataset * datasetout = fileformat.getAndRemoveDataset();
    BOOST_CHECK_EQUAL(datasetout != NULL, true);

    delete datasetout;
}

/*************************** TEST OK 08 *******************************/
/**
 * Nominal test case: Run (_32BIT_SGN_INT)
 */
struct TestDataOK08
{
    std::string directorypath;
    std::string outputdirectory;
    std::string dictionary;
    std::vector<std::string> filestoremove;
    DcmDataset* dataset;

    TestDataOK08()
    {
        directorypath = "./test_ModuleEnhanceBrukerDicom";
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));

        outputdirectory = "./test_ModuleEnhanceBrukerDicom_out";
        boost::filesystem::create_directory(boost::filesystem::path(outputdirectory.c_str()));

        std::string file = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(file);
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
        filestoremove.push_back(file);

        std::string seriespath = directorypath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(seriespath.c_str()));

        file = seriespath + "/acqp";
        myfile.open(file);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        std::string pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(boost::filesystem::path(pdatapath.c_str()));
        std::string recopath = pdatapath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(recopath.c_str()));

        file = recopath + "/visu_pars";
        myfile.open(file);
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
        myfile << "##$VisuCoreWordType=_32BIT_SGN_INT\n";
        myfile << "##$VisuCoreByteOrder=bigEndian\n";
        myfile << "##$VisuCoreSize=( 2 )\n";
        myfile << "8 8\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        // Write 2dseq file
        char* buffer = new char[64];
        file = recopath + "/2dseq";
        std::ofstream outfile(file, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(file);

        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

        dictionary = "./test_ModuleEnhanceBrukerDicom_dictionary.xml";
        myfile.open(dictionary);
        myfile << "<Dictionary>\n";
        myfile << "    <DicomField tag=\"0008,0008\" keyword=\"ImageType\" vr=\"CS\">\n";
        myfile << "        <ConstantField values=\"ORIGINAL\\PRIMARY\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0012\" keyword=\"InstanceCreationDate\" vr=\"DA\">\n";
        myfile << "        <DateGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0013\" keyword=\"InstanceCreationTime\" vr=\"TM\">\n";
        myfile << "        <TimeGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0016\" keyword=\"SOPClassUID\" vr=\"UI\">\n";
        myfile << "        <ConstantField values=\"1.2.840.10008.5.1.4.1.1.4\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0018\" keyword=\"SOPInstanceUID\" vr=\"UI\">\n";
        myfile << "        <UIDGenerator uidtype=\"SOPInstanceUID\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,1030\" keyword=\"StudyDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuStudyDescription\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,103e\" keyword=\"SeriesDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuAcquisitionProtocol\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0010\" keyword=\"PatientName\" vr=\"PN\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectName\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0020\" keyword=\"PatientID\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectId\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,0013\" keyword=\"InstanceNumber\" vr=\"IS\" >\n";
        myfile << "        <InstanceNumberDcmField />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,1002\" keyword=\"ImagesInAcquisition\" vr=\"IS\" >\n";
        myfile << "        <BrukerField name=\"VisuCoreFrameCount\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "</Dictionary>\n";
        myfile.close();
        filestoremove.push_back(dictionary);
    }

    ~TestDataOK08()
    {
        delete dataset;

        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(boost::filesystem::path(outputdirectory.c_str()));
    }
};

BOOST_FIXTURE_TEST_CASE(Run_32_BIT_SIGN, TestDataOK08)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    // Process
    enhanceb2d->run();

    std::string const outputdicom = outputdirectory + "/Mouse^Mickey/1_/1_/1";

    // Try to open Created Dataset
    DcmFileFormat fileformat;
    OFCondition cond = fileformat.loadFile(outputdicom.c_str());
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);

    DcmDataset * datasetout = fileformat.getAndRemoveDataset();
    BOOST_CHECK_EQUAL(datasetout != NULL, true);

    delete datasetout;
}

/*************************** TEST OK 09 *******************************/
/**
 * Nominal test case: Run (_8BIT_UNSGN_INT)
 */
struct TestDataOK09
{
    std::string directorypath;
    std::string outputdirectory;
    std::string dictionary;
    std::vector<std::string> filestoremove;
    DcmDataset* dataset;

    TestDataOK09()
    {
        directorypath = "./test_ModuleEnhanceBrukerDicom";
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));

        outputdirectory = "./test_ModuleEnhanceBrukerDicom_out";
        boost::filesystem::create_directory(boost::filesystem::path(outputdirectory.c_str()));

        std::string file = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(file);
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
        filestoremove.push_back(file);

        std::string seriespath = directorypath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(seriespath.c_str()));

        file = seriespath + "/acqp";
        myfile.open(file);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        std::string pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(boost::filesystem::path(pdatapath.c_str()));
        std::string recopath = pdatapath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(recopath.c_str()));

        file = recopath + "/visu_pars";
        myfile.open(file);
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
        myfile << "##$VisuCoreWordType=_8BIT_UNSGN_INT\n";
        myfile << "##$VisuCoreByteOrder=bigEndian\n";
        myfile << "##$VisuCoreSize=( 2 )\n";
        myfile << "8 8\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        // Write 2dseq file
        char* buffer = new char[64];
        file = recopath + "/2dseq";
        std::ofstream outfile(file, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(file);

        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

        dictionary = "./test_ModuleEnhanceBrukerDicom_dictionary.xml";
        myfile.open(dictionary);
        myfile << "<Dictionary>\n";
        myfile << "    <DicomField tag=\"0008,0008\" keyword=\"ImageType\" vr=\"CS\">\n";
        myfile << "        <ConstantField values=\"ORIGINAL\\PRIMARY\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0012\" keyword=\"InstanceCreationDate\" vr=\"DA\">\n";
        myfile << "        <DateGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0013\" keyword=\"InstanceCreationTime\" vr=\"TM\">\n";
        myfile << "        <TimeGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0016\" keyword=\"SOPClassUID\" vr=\"UI\">\n";
        myfile << "        <ConstantField values=\"1.2.840.10008.5.1.4.1.1.4\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0018\" keyword=\"SOPInstanceUID\" vr=\"UI\">\n";
        myfile << "        <UIDGenerator uidtype=\"SOPInstanceUID\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,1030\" keyword=\"StudyDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuStudyDescription\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,103e\" keyword=\"SeriesDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuAcquisitionProtocol\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0010\" keyword=\"PatientName\" vr=\"PN\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectName\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0020\" keyword=\"PatientID\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectId\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,0013\" keyword=\"InstanceNumber\" vr=\"IS\" >\n";
        myfile << "        <InstanceNumberDcmField />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,1002\" keyword=\"ImagesInAcquisition\" vr=\"IS\" >\n";
        myfile << "        <BrukerField name=\"VisuCoreFrameCount\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "</Dictionary>\n";
        myfile.close();
        filestoremove.push_back(dictionary);
    }

    ~TestDataOK09()
    {
        delete dataset;

        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(boost::filesystem::path(outputdirectory.c_str()));
    }
};

BOOST_FIXTURE_TEST_CASE(Run_8BIT_UNSGN_INT, TestDataOK09)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    // Process
    enhanceb2d->run();

    std::string const outputdicom = outputdirectory + "/Mouse^Mickey/1_/1_/1";

    // Try to open Created Dataset
    DcmFileFormat fileformat;
    OFCondition cond = fileformat.loadFile(outputdicom.c_str());
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);

    DcmDataset * datasetout = fileformat.getAndRemoveDataset();
    BOOST_CHECK_EQUAL(datasetout != NULL, true);

    delete datasetout;
}

/*************************** TEST OK 10 *******************************/
/**
 * Nominal test case: Run (_32BIT_FLOAT)
 */
struct TestDataOK10
{
    std::string directorypath;
    std::string outputdirectory;
    std::string dictionary;
    std::vector<std::string> filestoremove;
    DcmDataset* dataset;

    TestDataOK10()
    {
        directorypath = "./test_ModuleEnhanceBrukerDicom";
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));

        outputdirectory = "./test_ModuleEnhanceBrukerDicom_out";
        boost::filesystem::create_directory(boost::filesystem::path(outputdirectory.c_str()));

        std::string file = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(file);
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
        filestoremove.push_back(file);

        std::string seriespath = directorypath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(seriespath.c_str()));

        file = seriespath + "/acqp";
        myfile.open(file);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        std::string pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(boost::filesystem::path(pdatapath.c_str()));
        std::string recopath = pdatapath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(recopath.c_str()));

        file = recopath + "/visu_pars";
        myfile.open(file);
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
        myfile << "##$VisuCoreWordType=_32BIT_FLOAT\n";
        myfile << "##$VisuCoreByteOrder=bigEndian\n";
        myfile << "##$VisuCoreSize=( 2 )\n";
        myfile << "8 8\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        // Write 2dseq file
        char* buffer = new char[64];
        file = recopath + "/2dseq";
        std::ofstream outfile(file, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(file);

        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

        dictionary = "./test_ModuleEnhanceBrukerDicom_dictionary.xml";
        myfile.open(dictionary);
        myfile << "<Dictionary>\n";
        myfile << "    <DicomField tag=\"0008,0008\" keyword=\"ImageType\" vr=\"CS\">\n";
        myfile << "        <ConstantField values=\"ORIGINAL\\PRIMARY\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0012\" keyword=\"InstanceCreationDate\" vr=\"DA\">\n";
        myfile << "        <DateGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0013\" keyword=\"InstanceCreationTime\" vr=\"TM\">\n";
        myfile << "        <TimeGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0016\" keyword=\"SOPClassUID\" vr=\"UI\">\n";
        myfile << "        <ConstantField values=\"1.2.840.10008.5.1.4.1.1.4\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0018\" keyword=\"SOPInstanceUID\" vr=\"UI\">\n";
        myfile << "        <UIDGenerator uidtype=\"SOPInstanceUID\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,1030\" keyword=\"StudyDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuStudyDescription\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,103e\" keyword=\"SeriesDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuAcquisitionProtocol\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0010\" keyword=\"PatientName\" vr=\"PN\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectName\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0020\" keyword=\"PatientID\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectId\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,0013\" keyword=\"InstanceNumber\" vr=\"IS\" >\n";
        myfile << "        <InstanceNumberDcmField />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,1002\" keyword=\"ImagesInAcquisition\" vr=\"IS\" >\n";
        myfile << "        <BrukerField name=\"VisuCoreFrameCount\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "</Dictionary>\n";
        myfile.close();
        filestoremove.push_back(dictionary);
    }

    ~TestDataOK10()
    {
        delete dataset;

        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(boost::filesystem::path(outputdirectory.c_str()));
    }
};

BOOST_FIXTURE_TEST_CASE(Run_32BIT_FLOAT, TestDataOK10)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    // Process
    enhanceb2d->run();

    std::string const outputdicom = outputdirectory + "/Mouse^Mickey/1_/1_/1";

    // Try to open Created Dataset
    DcmFileFormat fileformat;
    OFCondition cond = fileformat.loadFile(outputdicom.c_str());
    BOOST_CHECK_EQUAL(cond == EC_Normal, true);

    DcmDataset * datasetout = fileformat.getAndRemoveDataset();
    BOOST_CHECK_EQUAL(datasetout != NULL, true);

    delete datasetout;
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
BOOST_FIXTURE_TEST_CASE(No_SeriesNumber, TestDataOK03)
{
    dataset->findAndDeleteElement(DCM_SeriesNumber, true);

    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);
        
    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Bad Series number
 */
BOOST_FIXTURE_TEST_CASE(Bad_SeriesNumber, TestDataOK03)
{
    dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("90009"), true);

    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 04 *******************************/
/**
 * Error test case: Bad VisuCoreFrameCount
 */
struct TestDataKO04
{
    std::string directorypath;
    std::string outputdirectory;
    std::string dictionary;
    std::vector<std::string> filestoremove;
    DcmDataset* dataset;

    TestDataKO04()
    {
        directorypath = "./test_ModuleEnhanceBrukerDicom";
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));

        outputdirectory = "./test_ModuleEnhanceBrukerDicom_out";
        boost::filesystem::create_directory(boost::filesystem::path(outputdirectory.c_str()));

        std::string file = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(file);
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
        filestoremove.push_back(file);

        std::string seriespath = directorypath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(seriespath.c_str()));

        file = seriespath + "/acqp";
        myfile.open(file);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        std::string pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(boost::filesystem::path(pdatapath.c_str()));
        std::string recopath = pdatapath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(recopath.c_str()));

        file = recopath + "/visu_pars";
        myfile.open(file);
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
        myfile << "##$VisuCoreWordType=_16BIT_SGN_INT\n";
        myfile << "##$VisuCoreByteOrder=littleEndian\n";
        myfile << "##$VisuCoreSize=( 2 )\n";
        myfile << "8 8\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        // Write 2dseq file
        char* buffer = new char[64];
        file = recopath + "/2dseq";
        std::ofstream outfile(file, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(file);

        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

        dictionary = "./test_ModuleEnhanceBrukerDicom_dictionary.xml";
        myfile.open(dictionary);
        myfile << "<Dictionary>\n";
        myfile << "    <DicomField tag=\"0008,0008\" keyword=\"ImageType\" vr=\"CS\">\n";
        myfile << "        <ConstantField values=\"ORIGINAL\\PRIMARY\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0012\" keyword=\"InstanceCreationDate\" vr=\"DA\">\n";
        myfile << "        <DateGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0013\" keyword=\"InstanceCreationTime\" vr=\"TM\">\n";
        myfile << "        <TimeGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0016\" keyword=\"SOPClassUID\" vr=\"UI\">\n";
        myfile << "        <ConstantField values=\"1.2.840.10008.5.1.4.1.1.4\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0018\" keyword=\"SOPInstanceUID\" vr=\"UI\">\n";
        myfile << "        <UIDGenerator uidtype=\"SOPInstanceUID\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,1030\" keyword=\"StudyDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuStudyDescription\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,103e\" keyword=\"SeriesDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuAcquisitionProtocol\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0010\" keyword=\"PatientName\" vr=\"PN\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectName\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0020\" keyword=\"PatientID\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectId\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,0013\" keyword=\"InstanceNumber\" vr=\"IS\" >\n";
        myfile << "        <InstanceNumberDcmField />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,1002\" keyword=\"ImagesInAcquisition\" vr=\"IS\" >\n";
        myfile << "        <BrukerField name=\"VisuCoreFrameCount\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "</Dictionary>\n";
        myfile.close();
        filestoremove.push_back(dictionary);
    }

    ~TestDataKO04()
    {
        delete dataset;

        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(boost::filesystem::path(outputdirectory.c_str()));
    }
};

BOOST_FIXTURE_TEST_CASE(Corrupted_Data, TestDataKO04)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 05 *******************************/
/**
 * Error test case: Bad SOP Class UID
 */
BOOST_FIXTURE_TEST_CASE(Bad_SOPClassUID, TestDataOK03)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, "BadValue", outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

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
BOOST_FIXTURE_TEST_CASE(No_PixelData_File, TestDataOK03)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    // Remove Pixel Data file and replace by a directory
    std::string pixelfile = directorypath + "/1/pdata/1/2dseq";
    remove(pixelfile.c_str());
    boost::filesystem::create_directory(boost::filesystem::path(pixelfile.c_str()));

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 08 *******************************/
/**
 * Error test case: Error while reading PixelData file
 */
BOOST_FIXTURE_TEST_CASE(Cant_Read_PixelData_File, TestDataOK03)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    // Change right of file
    std::string pixelfile = "chmod 000 " + directorypath + "/1/pdata/1/2dseq";
    std::system(pixelfile.c_str());

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);

    pixelfile = "chmod 666 " + directorypath + "/1/pdata/1/2dseq";
    std::system(pixelfile.c_str());
}

/*************************** TEST KO 09 *******************************/
/**
 * Error test case: Missing mandatory field VisuCoreSize
 */
struct TestDataKO09
{
    std::string directorypath;
    std::string outputdirectory;
    std::string dictionary;
    std::vector<std::string> filestoremove;
    DcmDataset* dataset;

    TestDataKO09()
    {
        directorypath = "./test_ModuleEnhanceBrukerDicom";
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));

        outputdirectory = "./test_ModuleEnhanceBrukerDicom_out";
        boost::filesystem::create_directory(boost::filesystem::path(outputdirectory.c_str()));

        std::string file = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(file);
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
        filestoremove.push_back(file);

        std::string seriespath = directorypath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(seriespath.c_str()));

        file = seriespath + "/acqp";
        myfile.open(file);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        std::string pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(boost::filesystem::path(pdatapath.c_str()));
        std::string recopath = pdatapath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(recopath.c_str()));

        file = recopath + "/visu_pars";
        myfile.open(file);
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
        filestoremove.push_back(file);

        // Write 2dseq file
        char* buffer = new char[64];
        file = recopath + "/2dseq";
        std::ofstream outfile(file, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(file);

        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

        dictionary = "./test_ModuleEnhanceBrukerDicom_dictionary.xml";
        myfile.open(dictionary);
        myfile << "<Dictionary>\n";
        myfile << "    <DicomField tag=\"0008,0008\" keyword=\"ImageType\" vr=\"CS\">\n";
        myfile << "        <ConstantField values=\"ORIGINAL\\PRIMARY\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0012\" keyword=\"InstanceCreationDate\" vr=\"DA\">\n";
        myfile << "        <DateGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0013\" keyword=\"InstanceCreationTime\" vr=\"TM\">\n";
        myfile << "        <TimeGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0016\" keyword=\"SOPClassUID\" vr=\"UI\">\n";
        myfile << "        <ConstantField values=\"1.2.840.10008.5.1.4.1.1.4\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0018\" keyword=\"SOPInstanceUID\" vr=\"UI\">\n";
        myfile << "        <UIDGenerator uidtype=\"SOPInstanceUID\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,1030\" keyword=\"StudyDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuStudyDescription\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,103e\" keyword=\"SeriesDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuAcquisitionProtocol\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0010\" keyword=\"PatientName\" vr=\"PN\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectName\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0020\" keyword=\"PatientID\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectId\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,0013\" keyword=\"InstanceNumber\" vr=\"IS\" >\n";
        myfile << "        <InstanceNumberDcmField />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,1002\" keyword=\"ImagesInAcquisition\" vr=\"IS\" >\n";
        myfile << "        <BrukerField name=\"VisuCoreFrameCount\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "</Dictionary>\n";
        myfile.close();
        filestoremove.push_back(dictionary);
    }

    ~TestDataKO09()
    {
        delete dataset;

        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(boost::filesystem::path(outputdirectory.c_str()));
    }
};

BOOST_FIXTURE_TEST_CASE(Missing_VisuCoreSize, TestDataKO09)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 10 *******************************/
/**
 * Error test case: Missing mandatory field VisuCoreSize
 */
struct TestDataKO10
{
    std::string directorypath;
    std::string outputdirectory;
    std::string dictionary;
    std::vector<std::string> filestoremove;
    DcmDataset* dataset;

    TestDataKO10()
    {
        directorypath = "./test_ModuleEnhanceBrukerDicom";
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));

        outputdirectory = "./test_ModuleEnhanceBrukerDicom_out";
        boost::filesystem::create_directory(boost::filesystem::path(outputdirectory.c_str()));

        std::string file = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(file);
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
        filestoremove.push_back(file);

        std::string seriespath = directorypath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(seriespath.c_str()));

        file = seriespath + "/acqp";
        myfile.open(file);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        std::string pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(boost::filesystem::path(pdatapath.c_str()));
        std::string recopath = pdatapath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(recopath.c_str()));

        file = recopath + "/visu_pars";
        myfile.open(file);
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
        filestoremove.push_back(file);

        // Write 2dseq file
        char* buffer = new char[64];
        file = recopath + "/2dseq";
        std::ofstream outfile(file, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(file);

        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

        dictionary = "./test_ModuleEnhanceBrukerDicom_dictionary.xml";
        myfile.open(dictionary);
        myfile << "<Dictionary>\n";
        myfile << "    <DicomField tag=\"0008,0008\" keyword=\"ImageType\" vr=\"CS\">\n";
        myfile << "        <ConstantField values=\"ORIGINAL\\PRIMARY\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0012\" keyword=\"InstanceCreationDate\" vr=\"DA\">\n";
        myfile << "        <DateGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0013\" keyword=\"InstanceCreationTime\" vr=\"TM\">\n";
        myfile << "        <TimeGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0016\" keyword=\"SOPClassUID\" vr=\"UI\">\n";
        myfile << "        <ConstantField values=\"1.2.840.10008.5.1.4.1.1.4\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0018\" keyword=\"SOPInstanceUID\" vr=\"UI\">\n";
        myfile << "        <UIDGenerator uidtype=\"SOPInstanceUID\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,1030\" keyword=\"StudyDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuStudyDescription\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,103e\" keyword=\"SeriesDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuAcquisitionProtocol\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0010\" keyword=\"PatientName\" vr=\"PN\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectName\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0020\" keyword=\"PatientID\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectId\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,0013\" keyword=\"InstanceNumber\" vr=\"IS\" >\n";
        myfile << "        <InstanceNumberDcmField />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,1002\" keyword=\"ImagesInAcquisition\" vr=\"IS\" >\n";
        myfile << "        <BrukerField name=\"VisuCoreFrameCount\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "</Dictionary>\n";
        myfile.close();
        filestoremove.push_back(dictionary);
    }

    ~TestDataKO10()
    {
        delete dataset;

        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(boost::filesystem::path(outputdirectory.c_str()));
    }
};

BOOST_FIXTURE_TEST_CASE(Missing_VisuCoreWordType, TestDataKO10)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

/*************************** TEST KO 10 *******************************/
/**
 * Error test case: Bad value for field VisuCoreWordType
 */
struct TestDataKO11
{
    std::string directorypath;
    std::string outputdirectory;
    std::string dictionary;
    std::vector<std::string> filestoremove;
    DcmDataset* dataset;

    TestDataKO11()
    {
        directorypath = "./test_ModuleEnhanceBrukerDicom";
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));

        outputdirectory = "./test_ModuleEnhanceBrukerDicom_out";
        boost::filesystem::create_directory(boost::filesystem::path(outputdirectory.c_str()));

        std::string file = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(file);
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
        filestoremove.push_back(file);

        std::string seriespath = directorypath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(seriespath.c_str()));

        file = seriespath + "/acqp";
        myfile.open(file);
        myfile << "##$ACQP_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        std::string pdatapath = seriespath + "/pdata";
        boost::filesystem::create_directory(boost::filesystem::path(pdatapath.c_str()));
        std::string recopath = pdatapath + "/1";
        boost::filesystem::create_directory(boost::filesystem::path(recopath.c_str()));

        file = recopath + "/visu_pars";
        myfile.open(file);
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
        filestoremove.push_back(file);

        // Write 2dseq file
        char* buffer = new char[64];
        file = recopath + "/2dseq";
        std::ofstream outfile(file, std::ofstream::binary);
        outfile.write(buffer, 64);
        outfile.close();
        delete[] buffer;
        filestoremove.push_back(file);

        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString("10001"));

        dictionary = "./test_ModuleEnhanceBrukerDicom_dictionary.xml";
        myfile.open(dictionary);
        myfile << "<Dictionary>\n";
        myfile << "    <DicomField tag=\"0008,0008\" keyword=\"ImageType\" vr=\"CS\">\n";
        myfile << "        <ConstantField values=\"ORIGINAL\\PRIMARY\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0012\" keyword=\"InstanceCreationDate\" vr=\"DA\">\n";
        myfile << "        <DateGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0013\" keyword=\"InstanceCreationTime\" vr=\"TM\">\n";
        myfile << "        <TimeGenerator />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0016\" keyword=\"SOPClassUID\" vr=\"UI\">\n";
        myfile << "        <ConstantField values=\"1.2.840.10008.5.1.4.1.1.4\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,0018\" keyword=\"SOPInstanceUID\" vr=\"UI\">\n";
        myfile << "        <UIDGenerator uidtype=\"SOPInstanceUID\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,1030\" keyword=\"StudyDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuStudyDescription\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0008,103e\" keyword=\"SeriesDescription\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuAcquisitionProtocol\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0010\" keyword=\"PatientName\" vr=\"PN\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectName\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0010,0020\" keyword=\"PatientID\" vr=\"LO\">\n";
        myfile << "        <BrukerField name=\"VisuSubjectId\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,0013\" keyword=\"InstanceNumber\" vr=\"IS\" >\n";
        myfile << "        <InstanceNumberDcmField />\n";
        myfile << "    </DicomField>\n";
        myfile << "    <DicomField tag=\"0020,1002\" keyword=\"ImagesInAcquisition\" vr=\"IS\" >\n";
        myfile << "        <BrukerField name=\"VisuCoreFrameCount\" />\n";
        myfile << "    </DicomField>\n";
        myfile << "</Dictionary>\n";
        myfile.close();
        filestoremove.push_back(dictionary);
    }

    ~TestDataKO11()
    {
        delete dataset;

        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
        boost::filesystem::remove_all(boost::filesystem::path(outputdirectory.c_str()));
    }
};

BOOST_FIXTURE_TEST_CASE(Bad_VisuCoreWordType, TestDataKO11)
{
    auto enhanceb2d = dicomifier::actions::EnhanceBrukerDicom::
            New(dataset, directorypath, UID_MRImageStorage, outputdirectory, "1");

    // Use specific dictionary
    enhanceb2d->set_dictionary(dictionary);

    BOOST_REQUIRE_THROW(enhanceb2d->run(), dicomifier::DicomifierException);
}

