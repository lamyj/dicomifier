/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerDirectory
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "bruker/BrukerDirectory.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestData
{
    std::string filepath;
    std::string firstfile;
    std::string secondfile;
 
    TestData()
    {
        filepath = "./subject";
        
        std::ofstream myfile;
        myfile.open(filepath);
        myfile << "Writing this to a file.\n";
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##END=\n";
        myfile.close();

        boost::filesystem::create_directories(boost::filesystem::path("./1/pdata/1"));

        firstfile = "./1/method";

        myfile.open(firstfile);
        myfile << "Writing this to a file.\n";
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##END=\n";
        myfile.close();

        secondfile = "./1/pdata/1/acqp";
        
        myfile.open(secondfile);
        myfile << "Writing this to a file.\n";
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##END=\n";
        myfile.close();
    }
 
    ~TestData()
    {
        remove(filepath.c_str());
        remove(firstfile.c_str());
        remove(secondfile.c_str());
        
        boost::filesystem::remove_all("./1");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestData)
{
    dicomifier::bruker::BrukerDirectory* brukerdirectory =
            new dicomifier::bruker::BrukerDirectory();

    BOOST_CHECK_EQUAL(brukerdirectory != NULL, true);
    
    BOOST_CHECK_EQUAL(brukerdirectory->CreateMap("."), 1);
    
    delete brukerdirectory;
}

/*************************** TEST OK 02 *******************************/
/**
 * Error test case: Get Dataset
 */

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestData)
{
    dicomifier::bruker::BrukerDirectory* brukerdirectory =
            new dicomifier::bruker::BrukerDirectory();

    brukerdirectory->CreateMap(".");

    BOOST_CHECK_EQUAL(brukerdirectory->get_brukerDataset("10001") != NULL, true);

    BOOST_CHECK_EQUAL(brukerdirectory->get_brukerDataset("90009") == NULL, true);

    delete brukerdirectory;
}
