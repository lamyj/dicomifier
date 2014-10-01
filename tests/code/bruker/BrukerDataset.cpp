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

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor and load file
 */
struct TestDataOK01
{
    std::string filepath;
 
    TestDataOK01()
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
 
    ~TestDataOK01()
    {
        remove(filepath.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    dicomifier::bruker::BrukerDataset* dataset = 
            new dicomifier::bruker::BrukerDataset();
    dataset->LoadFile(filepath);
    BOOST_CHECK_EQUAL(dataset->HasFieldData("SUBJECT_id"), true);
    
    delete dataset;
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Add field
 */
struct TestDataOK02
{
    std::string filepath;
 
    TestDataOK02()
    {
        filepath = "./test_ModuleBrukerDataset.txt";
        
        std::ofstream myfile;
        myfile.open(filepath);
        myfile << "Writing this to a file.\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##END=\n";
        myfile.close();
    }
 
    ~TestDataOK02()
    {
        remove(filepath.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    dicomifier::bruker::BrukerDataset* dataset = 
            new dicomifier::bruker::BrukerDataset();
    dataset->LoadFile(filepath);
            
    dataset->SetFieldData("SUBJECT_id", 
                          dicomifier::bruker::BrukerFieldData("Mouse"));
            
    BOOST_CHECK_EQUAL(dataset->HasFieldData("SUBJECT_id"), true);
    
    BOOST_CHECK_EQUAL(dataset->toString(), 
                      "SUBJECT_id=(DimensionNumber=0,DataType=string,NumberOfElements=0,DimensionNumberValue=[],StringValue=[Mouse,])\n");
    
    delete dataset;
}
