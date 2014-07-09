/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#include <iostream>
#include <fstream>

#define BOOST_TEST_MODULE ModuleBrukerDataset
#include <boost/test/unit_test.hpp>

#include "bruker/BrukerDataset.h"

struct TestData
{
    std::string filepath;
 
    TestData()
    {
        filepath = "./test_ModuleBrukerDataset.txt";
        
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
    }
 
    ~TestData()
    {
        remove(filepath.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(LoadFile, TestData)
{
    dicomifier::bruker::BrukerDataset* dataset = new dicomifier::bruker::BrukerDataset();
    
    dataset->LoadFile(filepath);
    
    BOOST_CHECK_EQUAL(dataset->HasFieldData("SUBJECT_id"), true);
}
