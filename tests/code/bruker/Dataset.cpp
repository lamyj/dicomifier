/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <iostream>
#include <fstream>

#define BOOST_TEST_MODULE ModuleDataset
#include <boost/test/unit_test.hpp>

#include "bruker/Dataset.h"
#include "core/DicomifierException.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor and load file
 */
struct TestDataOK01
{
    std::string filepath;

    TestDataOK01()
    {
        filepath = "./test_ModuleDataset_loadfile.txt";

        std::ofstream myfile;
        myfile.open(filepath);
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

BOOST_FIXTURE_TEST_CASE(LoadFile, TestDataOK01)
{
    dicomifier::bruker::Dataset* dataset =
            new dicomifier::bruker::Dataset();
    BOOST_CHECK_EQUAL(dataset != NULL, true);

    dataset->load(filepath);

    BOOST_CHECK_EQUAL(dataset->has_field("DATATYPE"), true);
    BOOST_CHECK_EQUAL(dataset->get_field("DATATYPE").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset->get_field("DATATYPE").get_string(0),
                      "Parameter Values");

    BOOST_CHECK_EQUAL(dataset->has_field("SUBJECT_id"), true);
    BOOST_CHECK_EQUAL(dataset->get_field("SUBJECT_id").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset->get_field("SUBJECT_id").get_string(0),
                      "Rat");

    delete dataset;
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: has_field
 */
BOOST_FIXTURE_TEST_CASE(HasField, TestDataOK01)
{
    dicomifier::bruker::Dataset dataset;
    dataset.load(filepath);

    BOOST_CHECK_EQUAL(dataset.has_field("DATATYPE"), true);
    BOOST_CHECK_EQUAL(dataset.has_field("SUBJECT_id"), true);

    BOOST_CHECK_EQUAL(dataset.has_field("Parameter Values"), false);
    BOOST_CHECK_EQUAL(dataset.has_field("not_a_good_field"), false);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: get_field and set_field
 */
BOOST_FIXTURE_TEST_CASE(GetAndSetField, TestDataOK01)
{
    dicomifier::bruker::Dataset dataset;
    dataset.load(filepath);

    BOOST_CHECK_EQUAL(dataset.get_field("DATATYPE").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("DATATYPE").get_string(0),
                      "Parameter Values");

    BOOST_CHECK_EQUAL(dataset.get_field("SUBJECT_id").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("SUBJECT_id").get_string(0),
                      "Rat");

    dicomifier::bruker::Field field;
    field.name = "SUBJECT_id";
    field.value.push_back("Mouse");
    dataset.set_field(field);

    BOOST_CHECK_EQUAL(dataset.get_field("SUBJECT_id").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("SUBJECT_id").get_string(0),
                      "Mouse");

    dicomifier::bruker::Field field2;
    field2.name = "SUBJECT_name";
    field2.value.push_back("Mortimer");
    dataset.set_field(field2);

    BOOST_CHECK_EQUAL(dataset.get_field("SUBJECT_name").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("SUBJECT_name").get_string(0),
                      "Mortimer");
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: update frame groups
 */
BOOST_FIXTURE_TEST_CASE(FrameGroups, TestDataOK01)
{
    dicomifier::bruker::Dataset dataset;
    dataset.load(filepath);

    auto const & framegroup = dataset.get_frame_groups();

    BOOST_CHECK_EQUAL(framegroup.size(), 0);

    dicomifier::bruker::Field fielddim;
    fielddim.name = "VisuFGOrderDescDim";
    fielddim.value.push_back((long)1);
    dataset.set_field(fielddim);

    BOOST_CHECK_EQUAL(framegroup.size(), 0);

    dicomifier::bruker::Field::Value vals;
    vals.push_back((long)19);
    vals.push_back("FG_SLICE");
    vals.push_back("");
    vals.push_back((long)0);
    vals.push_back((long)2);
    dicomifier::bruker::Field fielddesc;
    fielddesc.name = "VisuFGOrderDesc";
    fielddesc.value.push_back(vals);
    dataset.set_field(fielddesc);

    BOOST_CHECK_EQUAL(framegroup.size(), 0);

    dicomifier::bruker::Field::Value vals1;
    vals1.push_back("VisuCoreOrientation");
    vals1.push_back((long)0);
    dicomifier::bruker::Field::Value vals2;
    vals2.push_back("VisuCorePosition");
    vals2.push_back((long)0);
    dicomifier::bruker::Field fieldvals;
    fieldvals.name = "VisuGroupDepVals";
    fieldvals.value.push_back(vals1);
    fieldvals.value.push_back(vals2);
    dataset.set_field(fieldvals);

    BOOST_CHECK_EQUAL(framegroup.size(), 1);
    BOOST_CHECK_EQUAL(framegroup[0].name, "FG_SLICE");
    BOOST_CHECK_EQUAL(framegroup[0].comment, "");
    BOOST_CHECK_EQUAL(framegroup[0].size, 19);
    BOOST_CHECK_EQUAL(framegroup[0].parameters.size(), 2);
    BOOST_CHECK_EQUAL(framegroup[0].parameters[0].name, "VisuCoreOrientation");
    BOOST_CHECK_EQUAL(framegroup[0].parameters[0].start_index, 0);
    BOOST_CHECK_EQUAL(framegroup[0].parameters[1].name, "VisuCorePosition");
    BOOST_CHECK_EQUAL(framegroup[0].parameters[1].start_index, 0);
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: get index and start position
 */
struct TestDataOK05
{
    std::string filepath;

    TestDataOK05()
    {
        filepath = "./test_ModuleDataset_getindexforvalue.txt";

        std::ofstream myfile;
        myfile.open(filepath);
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##$VisuFGOrderDescDim=1\n";
        myfile << "##$VisuFGOrderDesc=( 1 )\n";
        myfile << "(19, <FG_SLICE>, <>, 0, 2)\n";
        myfile << "##$VisuGroupDepVals=( 2 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
        myfile << "##END=\n";
        myfile.close();
    }

    ~TestDataOK05()
    {
        remove(filepath.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(GetIndexForValue, TestDataOK05)
{
    dicomifier::bruker::Dataset dataset;
    dataset.load(filepath);

    int indexposition, startposition = -1;

    dataset.get_indexForValue("VisuCorePosition", indexposition,
                              startposition);

    BOOST_CHECK_EQUAL(indexposition, 0);
    BOOST_CHECK_EQUAL(startposition, 0);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Load bad file
 */
BOOST_AUTO_TEST_CASE(CouldNotOpenFile)
{
    dicomifier::bruker::Dataset dataset;
    BOOST_REQUIRE_THROW(dataset.load("Not_A_Good_File"),
                        dicomifier::DicomifierException);
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Parsing error
 */
struct TestDataKO02
{
    std::string filepath;

    TestDataKO02()
    {
        filepath = "./test_ModuleDataset_parsingerror.txt";

        std::ofstream myfile;
        myfile.open(filepath);
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat\n";
        myfile << "##$KEY=( 2 )\n";
        myfile << "(<Rat>, 15, 12.6) (<Mouse> , 47,)\n";
        myfile << "##END=\n";
        myfile.close();
    }

    ~TestDataKO02()
    {
        remove(filepath.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(ParsingError, TestDataKO02)
{
    dicomifier::bruker::Dataset dataset;
    BOOST_REQUIRE_THROW(dataset.load(filepath),
                        dicomifier::DicomifierException);
}

/*************************** TEST KO 03 *******************************/
/**
 * Error test case: Get unexisting field
 */
BOOST_FIXTURE_TEST_CASE(BadGet, TestDataOK01)
{
    dicomifier::bruker::Dataset dataset;
    dataset.load(filepath);

    BOOST_REQUIRE_THROW(dataset.get_field("not_a_good_field"),
                        dicomifier::DicomifierException);
}
