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

struct TestData
{
    DcmDataset * dataset;
 
    std::string filepath;
    std::string secondfile;
 
    TestData()
    {
        dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, "10001");
        
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
        myfile << "##$SUBJECT_date=<2014-03-19T14:00:09,240+0100>\n";
        myfile << "##$SUBJECT_name_string=( 64 )\n";
        myfile << "<Gustave>\n";
        myfile << "##$DATTYPE=ip_int\n";
        myfile << "##$IM_SIX=96\n";
        myfile << "##$IM_SIY=96\n";
        myfile << "##$IM_SIZ=198\n";
        myfile << "##END=\n";
        myfile.close();
        
        boost::filesystem::create_directory("./1");
        boost::filesystem::create_directory("./1/pdata");
        boost::filesystem::create_directory("./1/pdata/1");
        
        secondfile = "./1/pdata/1/acqp";
        
        myfile.open(secondfile);
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
        myfile << "##END=\n";
        myfile.close();
    }
 
    ~TestData()
    {
        delete dataset;
        
        remove(filepath.c_str());
        remove(secondfile.c_str());
        
        boost::filesystem::remove_all("./1");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestData)
{
    auto testenhance = dicomifier::actions::EnhanceBrukerDicom::New(dataset, ".");
    
    testenhance->run();
        
    // check DCM_Modality create
    BOOST_CHECK_EQUAL(dataset->tagExists(DCM_Modality), true);
}


BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto testenhance = dicomifier::actions::EnhanceBrukerDicom::New();
    
    testenhance->set_dataset(new DcmDataset());
    testenhance->set_brukerDir("path");
        
    // check DCM_Modality create
    BOOST_CHECK_EQUAL(testenhance->get_dataset() != NULL, true);
    BOOST_CHECK_EQUAL(testenhance->get_brukerDir() != "", true);
}

BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto testenhance = dicomifier::actions::EnhanceBrukerDicom::New();
    
    testenhance->set_brukerDir("unknown path");
        
    // check DCM_Modality create
    BOOST_REQUIRE_THROW(testenhance->run(), dicomifier::DicomifierException);
}
