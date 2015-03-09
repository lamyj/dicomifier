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

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Constructor and load file
 */
struct TestDataOK06
{
    std::string filepath;

    TestDataOK06()
    {
        filepath = "./test_ModuleDataset_loadfile.txt";

        std::ofstream myfile;
        myfile.open(filepath);
        /// HEADER
        myfile << "##TITLE=Parameter List, ParaVision 6.0\n";
        myfile << "##JCAMPDX=4.24\n";
        myfile << "##DATATYPE=Parameter Values\n";
        myfile << "##ORIGIN=Bruker BioSpin MRI GmbH\n";
        /// COMMENT
        myfile << "$$ @vis= VisuVersion VisuUid VisuCreator VisuCreatorVersion VisuCreationDate\n";
        /// INT
        myfile << "##$VisuCoreSlicePacksSliceDist=( 1 )\n";
        myfile << "0\n";
        myfile << "##$VisuCoreDim=2\n";
        myfile << "##$VisuCoreSize=( 2 )\n";
        myfile << "128 128\n";
        myfile << "##$RECO_map_range=( 2 )\n";
        myfile << "-2147483647 2147483647\n";
        myfile << "##$VisuCoreOrientation=( 21, 9 )\n";
        myfile << "1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 \n";
        myfile << "0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 \n";
        myfile << "0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 \n";
        myfile << "1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 \n";
        myfile << "0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1 1 0 0 0 1 0 0 0 1\n";
        /// FLOAT
        myfile << "##$VisuCoreFrameThickness=( 1 )\n";
        myfile << "0.8\n";
        myfile << "##$VisuSubjectWeight=0.001\n";
        myfile << "##$RECO_map_percentile=( 2 )\n";
        myfile << "56.48 99.99\n";
        myfile << "##$RECO_map_=56.48 99.99\n";
        myfile << "##$VisuCoreDataMin=( 21 )\n";
        myfile << "3.1706781523995 2.77249173395076 0.952132235440035 3.25413494820826 \n";
        myfile << "3.92037159508005 1.207218673639 5.86692056748907 2.76005383363701 \n";
        myfile << "1.12071806202037 2.78396015802596 2.30326290846129 4.77108733249778 \n";
        myfile << "1.7888528200565 4.58205897778897 2.1052482888003 2.68549336737838 \n";
        myfile << "1.48487587865813 1.97248423355083 5.3497871204252 1.41844765168263 \n";
        myfile << "1.98272138197972\n";
        myfile << "##$VisuCorePosition=( 21, 3 )\n";
        myfile << "-7.359431 -8.782918 -7.857651 -7.359431 -8.782918 -7.057651 -7.359431 \n";
        myfile << "-8.782918 -6.257651 -7.359431 -8.782918 -5.457651 -7.359431 -8.782918 \n";
        myfile << "-4.657651 -7.359431 -8.782918 -3.857651 -7.359431 -8.782918 -3.057651 \n";
        myfile << "-7.359431 -8.782918 -2.257651 -7.359431 -8.782918 -1.457651 -7.359431 \n";
        myfile << "-8.782918 -0.657651 -7.359431 -8.782918 0.142349 -7.359431 -8.782918 0.942349 \n";
        myfile << "-7.359431 -8.782918 1.742349 -7.359431 -8.782918 2.542349 -7.359431 -8.782918 \n";
        myfile << "3.342349 -7.359431 -8.782918 4.142349 -7.359431 -8.782918 4.942349 -7.359431 \n";
        myfile << "-8.782918 5.742349 -7.359431 -8.782918 6.542349 -7.359431 -8.782918 7.342349 \n";
        myfile << "-7.359431 -8.782918 8.142349\n";
        /// STRING
        myfile << "##$SUBJECT_id=( 60 )\n";
        myfile << "<Rat>\n";
        myfile << "##$VisuSubjectSex=MALE\n";
        myfile << "##$VisuUid=( 65 )\n";
        myfile << "<2.16.756.5.5.100.1333920868.24905.1424336801.1>\n";
        myfile << "##$VisuCreatorVersion=( 65 )\n";
        myfile << "<6.0>\n";
        myfile << "##$VisuCreationDate=<2015-02-19T10:06:41,708+0100>\n";
        myfile << "##$VisuSubjectBirthDate=( 9 )\n";
        myfile << "<20150219>\n";
        myfile << "##$VisuCoreDimDesc=( 2 )\n";
        myfile << "spatial temporel\n";
        myfile << "##$VisuCoreUnits=( 2, 65 )\n";
        myfile << "<mm> <km>\n";
        myfile << "##$VisuStudyDescription=( 2048 )\n";
        myfile << "<\\\n";
        myfile << ">\n";
        /// STRUCT
        myfile << "##$VisuCoreSlicePacksDef=(0, 1)\n";
        myfile << "##$VisuCoreSlicePacksSlices=( 1 )\n";
        myfile << "(0, 21)\n";
        myfile << "##$VisuFGOrderDesc=( 1 )\n";
        myfile << "(21, <FG_SLICE>, <>, 0, 2)\n";
        myfile << "##$VisuGroupDepVals=( 2 )\n";
        myfile << "(<VisuCoreOrientation>, 0) (<VisuCorePosition>, 0)\n";
        myfile << "##$VisuSubjectInstanceCreationDate=(1424334602, 92, 60)\n";
        myfile << "##$RecoStageEdges=( 17 )\n";
        myfile << "(<input>, 0, <Q-\\>S>) (<compute>, 0, <Q0-\\>CAST0>) (<compute>, 0, \n";
        myfile << "<CAST0-\\>FTS0>) (<compute>, 0, <FTS0-\\>FT0>) (<compute>, 0, <FT0-\\>REORD0>) \n";
        myfile << "(<compute>, 0, <REORD0-\\>S0>) (<compute>, 1, <Q0-\\>FTS0>) (<compute>, 1, \n";
        myfile << "<FTS0-\\>FT0>) (<compute>, 1, <FT0-\\>S0>) (<compute>, 2, <Q0-\\>G0>) (<compute>,\n";
        myfile << " 2, <G0-\\>M0>) (<compute>, 2, <M0-\\>S0>) (<compute>, 3, <Q0-\\>MAP0>) \n";
        myfile << "(<compute>, 3, <MAP0-\\>CAST0>) (<compute>, 3, <CAST0-\\>S0>) (<output>, 3, \n";
        myfile << "<Q-\\>DISP>) (<output>, 3, <DISP-\\>S>)\n";
        myfile << "##END=\n";
        myfile.close();
    }

    ~TestDataOK06()
    {
        remove(filepath.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(Load_Complete_File, TestDataOK06)
{
    dicomifier::bruker::Dataset dataset;

    dataset.load(filepath);

    // HEADER
    BOOST_CHECK_EQUAL(dataset.has_field("DATATYPE"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("DATATYPE").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("DATATYPE").get_string(0),
                      "Parameter Values");

    BOOST_CHECK_EQUAL(dataset.has_field("JCAMPDX"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("JCAMPDX").get_size(), 1);
    BOOST_CHECK_CLOSE(dataset.get_field("JCAMPDX").get_float(0), 4.24, 0.001);

    // COMMENT
    BOOST_CHECK_EQUAL(dataset.has_field("vis"), false);
    BOOST_CHECK_EQUAL(dataset.has_field("@vis"), false);

    // INT
    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreSlicePacksSliceDist"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreSlicePacksSliceDist").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreSlicePacksSliceDist").get_int(0), 0);

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreDim"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreDim").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreDim").get_int(0), 2);

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreSize"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreSize").get_size(), 2);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreSize").get_int(0), 128);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreSize").get_int(1), 128);

    BOOST_CHECK_EQUAL(dataset.has_field("RECO_map_range"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("RECO_map_range").get_size(), 2);
    BOOST_CHECK_EQUAL(dataset.get_field("RECO_map_range").get_int(0), -2147483647);
    BOOST_CHECK_EQUAL(dataset.get_field("RECO_map_range").get_int(1), 2147483647);

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreOrientation"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreOrientation").get_size(), 189);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreOrientation").get_int(0), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreOrientation").get_int(12), 0);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreOrientation").get_int(188), 1);

    // FLOAT
    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreFrameThickness"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreFrameThickness").get_size(), 1);
    BOOST_CHECK_CLOSE(dataset.get_field("VisuCoreFrameThickness").get_float(0), 0.8, 0.001);

    BOOST_CHECK_EQUAL(dataset.has_field("VisuSubjectWeight"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuSubjectWeight").get_size(), 1);
    BOOST_CHECK_CLOSE(dataset.get_field("VisuSubjectWeight").get_float(0), 0.001, 0.001);

    BOOST_CHECK_EQUAL(dataset.has_field("RECO_map_percentile"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("RECO_map_percentile").get_size(), 2);
    BOOST_CHECK_CLOSE(dataset.get_field("RECO_map_percentile").get_float(0), 56.48, 0.001);
    BOOST_CHECK_CLOSE(dataset.get_field("RECO_map_percentile").get_float(1), 99.99, 0.001);

    // Not see in Bruker Data, parser read this as 1 single string, not as 2 float
    /*BOOST_CHECK_EQUAL(dataset.has_field("RECO_map_"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("RECO_map_").get_size(), 2);
    BOOST_CHECK_CLOSE(dataset.get_field("RECO_map_").get_float(0), 56.48, 0.001);
    BOOST_CHECK_CLOSE(dataset.get_field("RECO_map_").get_float(1), 99.99, 0.001);*/

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreDataMin"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreDataMin").get_size(), 21);
    BOOST_CHECK_CLOSE(dataset.get_field("VisuCoreDataMin").get_float(0), 3.1706781523995, 0.001);
    BOOST_CHECK_CLOSE(dataset.get_field("VisuCoreDataMin").get_float(10), 2.30326290846129, 0.001);
    BOOST_CHECK_CLOSE(dataset.get_field("VisuCoreDataMin").get_float(20), 1.98272138197972, 0.001);

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCorePosition"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCorePosition").get_size(), 63);
    BOOST_CHECK_CLOSE(dataset.get_field("VisuCorePosition").get_float(0), -7.359431, 0.001);
    BOOST_CHECK_CLOSE(dataset.get_field("VisuCorePosition").get_float(26), -1.45765102, 0.001);
    BOOST_CHECK_CLOSE(dataset.get_field("VisuCorePosition").get_float(62), 8.142349, 0.001);

    // STRING
    BOOST_CHECK_EQUAL(dataset.has_field("SUBJECT_id"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("SUBJECT_id").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("SUBJECT_id").get_string(0), "Rat");

    BOOST_CHECK_EQUAL(dataset.has_field("VisuSubjectSex"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuSubjectSex").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuSubjectSex").get_string(0), "MALE");

    BOOST_CHECK_EQUAL(dataset.has_field("VisuUid"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuUid").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuUid").get_string(0),
                      "2.16.756.5.5.100.1333920868.24905.1424336801.1");

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCreatorVersion"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCreatorVersion").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCreatorVersion").get_string(0), "6.0");

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCreationDate"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCreationDate").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCreationDate").get_string(0), "2015-02-19T10:06:41,708+0100");

    BOOST_CHECK_EQUAL(dataset.has_field("VisuSubjectBirthDate"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuSubjectBirthDate").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuSubjectBirthDate").get_string(0), "20150219");

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreDimDesc"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreDimDesc").get_size(), 2);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreDimDesc").get_string(0), "spatial");
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreDimDesc").get_string(1), "temporel");

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreUnits"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreUnits").get_size(), 2);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreUnits").get_string(0), "mm");
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreUnits").get_string(1), "km");

    BOOST_CHECK_EQUAL(dataset.has_field("VisuStudyDescription"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuStudyDescription").get_size(), 1);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuStudyDescription").get_string(0), "");

    // STRUCT
    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreSlicePacksDef"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreSlicePacksDef").get_size(), 1);
    auto const & struct_01 = dataset.get_field("VisuCoreSlicePacksDef").get_struct(0);
    BOOST_CHECK_EQUAL(struct_01.size(), 2);
    BOOST_CHECK_EQUAL(boost::get<long>(struct_01[0]), 0);
    BOOST_CHECK_EQUAL(boost::get<long>(struct_01[1]), 1);

    BOOST_CHECK_EQUAL(dataset.has_field("VisuCoreSlicePacksSlices"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuCoreSlicePacksSlices").get_size(), 1);
    auto const & struct_02 = dataset.get_field("VisuCoreSlicePacksSlices").get_struct(0);
    BOOST_CHECK_EQUAL(struct_02.size(), 2);
    BOOST_CHECK_EQUAL(boost::get<long>(struct_02[0]), 0);
    BOOST_CHECK_EQUAL(boost::get<long>(struct_02[1]), 21);

    BOOST_CHECK_EQUAL(dataset.has_field("VisuFGOrderDesc"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuFGOrderDesc").get_size(), 1);
    auto const & struct_03 = dataset.get_field("VisuFGOrderDesc").get_struct(0);
    BOOST_CHECK_EQUAL(struct_03.size(), 5);
    BOOST_CHECK_EQUAL(boost::get<long>(struct_03[0]), 21);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_03[1]), "FG_SLICE");
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_03[2]), "");
    BOOST_CHECK_EQUAL(boost::get<long>(struct_03[3]), 0);
    BOOST_CHECK_EQUAL(boost::get<long>(struct_03[4]), 2);

    BOOST_CHECK_EQUAL(dataset.has_field("VisuGroupDepVals"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuGroupDepVals").get_size(), 2);
    auto const & struct_04 = dataset.get_field("VisuGroupDepVals").get_struct(0);
    BOOST_CHECK_EQUAL(struct_04.size(), 2);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_04[0]), "VisuCoreOrientation");
    BOOST_CHECK_EQUAL(boost::get<long>(struct_04[1]), 0);
    auto const & struct_05 = dataset.get_field("VisuGroupDepVals").get_struct(1);
    BOOST_CHECK_EQUAL(struct_05.size(), 2);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_05[0]), "VisuCorePosition");
    BOOST_CHECK_EQUAL(boost::get<long>(struct_05[1]), 0);

    BOOST_CHECK_EQUAL(dataset.has_field("VisuSubjectInstanceCreationDate"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("VisuSubjectInstanceCreationDate").get_size(), 1);
    auto const & struct_06 = dataset.get_field("VisuSubjectInstanceCreationDate").get_struct(0);
    BOOST_CHECK_EQUAL(struct_06.size(), 3);
    BOOST_CHECK_EQUAL(boost::get<long>(struct_06[0]), 1424334602);
    BOOST_CHECK_EQUAL(boost::get<long>(struct_06[1]), 92);
    BOOST_CHECK_EQUAL(boost::get<long>(struct_06[2]), 60);

    BOOST_CHECK_EQUAL(dataset.has_field("RecoStageEdges"), true);
    BOOST_CHECK_EQUAL(dataset.get_field("RecoStageEdges").get_size(), 17);
    auto const & struct_07 = dataset.get_field("RecoStageEdges").get_struct(0);
    BOOST_CHECK_EQUAL(struct_07.size(), 3);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_07[0]), "input");
    BOOST_CHECK_EQUAL(boost::get<long>(struct_07[1]), 0);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_07[2]), "Q->S");
    auto const & struct_08 = dataset.get_field("RecoStageEdges").get_struct(1);
    BOOST_CHECK_EQUAL(struct_08.size(), 3);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_08[0]), "compute");
    BOOST_CHECK_EQUAL(boost::get<long>(struct_08[1]), 0);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_08[2]), "Q0->CAST0");
    auto const & struct_09 = dataset.get_field("RecoStageEdges").get_struct(9);
    BOOST_CHECK_EQUAL(struct_09.size(), 3);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_09[0]), "compute");
    BOOST_CHECK_EQUAL(boost::get<long>(struct_09[1]), 2);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_09[2]), "Q0->G0");
    auto const & struct_10 = dataset.get_field("RecoStageEdges").get_struct(16);
    BOOST_CHECK_EQUAL(struct_10.size(), 3);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_10[0]), "output");
    BOOST_CHECK_EQUAL(boost::get<long>(struct_10[1]), 3);
    BOOST_CHECK_EQUAL(boost::get<std::string>(struct_10[2]), "DISP->S");
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
