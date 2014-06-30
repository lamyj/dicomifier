/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleElementMatch
#include <boost/test/unit_test.hpp>

#include <dcmtk/dcmdata/dctk.h>

#include "dicom/conditions/ElementMatch.h"

struct TestDataCS
{
    DcmDataset * dataset;
 
    TestDataCS()
    {
        dataset = new DcmDataset();
        // Insert testing value
        std::string test = "value1\\value2\\value3";
        dataset->putAndInsertOFStringArray(DCM_Modality, test.c_str());     // insert CS
    }
 
    ~TestDataCS()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchCS01, TestDataCS)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_CS>::New(dataset, 
                                                      DCM_Modality, 
                                                      {"value1", "value2", "value3"});
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

BOOST_FIXTURE_TEST_CASE(MatchCS02, TestDataCS)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_CS>::New(dataset, 
                                                      DCM_Modality, 
                                                      {"value1", "badValue", "value3"});
    BOOST_CHECK_EQUAL(testmatch->eval(), false);
}

BOOST_FIXTURE_TEST_CASE(MatchCS03, TestDataCS)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_CS>::New(dataset, 
                                                      DCM_PatientSex, 
                                                      {"value1", "value2", "value3"});
    BOOST_CHECK_EQUAL(testmatch->eval(), false);
}

struct TestDataDS
{
    DcmDataset * dataset;
 
    TestDataDS()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_PatientWeight, "60.5");        // insert DS
    }
 
    ~TestDataDS()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchDS01, TestDataDS)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_DS>::New(dataset, 
                                                      DCM_PatientWeight, 
                                                      60.5);
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

struct TestDataIS
{
    DcmDataset * dataset;
 
    TestDataIS()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_StageNumber, "12");          // insert IS
    }
 
    ~TestDataIS()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchIS01, TestDataIS)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_IS>::New(dataset, 
                                                      DCM_StageNumber, 
                                                      12);
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}
