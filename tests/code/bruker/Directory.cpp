/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <fstream>

#define BOOST_TEST_MODULE ModuleDirectory
#include <boost/test/unit_test.hpp>

#include "bruker/Directory.h"
#include "core/DicomifierException.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor and load directory
 */
struct TestDataOK01
{
    std::string directorypath;
    std::vector<std::string> filestoremove;

    TestDataOK01()
    {
        directorypath = "./test_ModuleDirectory_load_dir";
        boost::filesystem::create_directory(boost::filesystem::path(directorypath.c_str()));

        std::string file = directorypath + "/subject";
        std::ofstream myfile;
        myfile.open(file);
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
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
        myfile << "##$VISU_param=( 60 )\n";
        myfile << "<param_value>\n";
        myfile << "##$VisuFGOrderDescDim=1\n";
        myfile << "##$VisuFGOrderDesc=( 1 )\n";
        myfile << "(19, <FG_SLICE>, <>, 0, 2)\n";
        myfile << "##$VisuGroupDepVals=( 2 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
        myfile << "##END=\n";
        myfile.close();
        filestoremove.push_back(file);

        file = recopath + "/2dseq";
        myfile.open(file);
        myfile << "\0\0\0\0\0\0\0\0\n";
        myfile.close();
        filestoremove.push_back(file);
    }

    ~TestDataOK01()
    {
        for (auto file : filestoremove)
        {
            remove(file.c_str());
        }

        boost::filesystem::remove_all(boost::filesystem::path(directorypath.c_str()));
    }
};

BOOST_FIXTURE_TEST_CASE(Load, TestDataOK01)
{
    dicomifier::bruker::Directory* directory =
            new dicomifier::bruker::Directory();
    BOOST_CHECK_EQUAL(directory != NULL, true);

    directory->load(directorypath);

    BOOST_CHECK_EQUAL(directory->has_dataset("10001"), true);

    delete directory;
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Get dataset
 */
BOOST_FIXTURE_TEST_CASE(GetDataset, TestDataOK01)
{
    dicomifier::bruker::Directory directory;
    directory.load(directorypath);

    BOOST_CHECK_EQUAL(directory.has_dataset("10001"), true);

    auto dataset = directory.get_dataset("10001");
    BOOST_CHECK_EQUAL(dataset.has_field("VISU_param"), true);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: No dataset
 */
BOOST_FIXTURE_TEST_CASE(GetBadDataset, TestDataOK01)
{
    dicomifier::bruker::Directory directory;
    directory.load(directorypath);
    BOOST_REQUIRE_THROW(directory.get_dataset("90009"),
                        dicomifier::DicomifierException);
}
