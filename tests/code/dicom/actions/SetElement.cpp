/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleSetElement
#include <boost/test/unit_test.hpp>

#include <dcmtk/dcmdata/dctk.h>

#include "dicom/actions/SetElement.h"

struct TestData
{
    DcmDataset * dataset;
 
    TestData()
    {
        dataset = new DcmDataset();
    }
 
    ~TestData()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(SetCS01, TestData)
{
    auto cs_single = dicomifier::actions::SetElement<EVR_CS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tag(DCM_Modality);
    cs_single->set_value("MR");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_Modality, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "MR");
}

BOOST_FIXTURE_TEST_CASE(SetCS02, TestData)
{
    auto cs_single = dicomifier::actions::SetElement<EVR_CS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tag(DCM_SelectorCSValue);
    cs_single->set_value({"AB", "CD"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SelectorCSValue, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "AB\\CD");
}
/*int main()
{
    DcmDataset * dataset = new DcmDataset();

    dicomifier::actions::SetElement<EVR_DS>::New(dataset, DCM_PatientWeight, 75.57)->run();
    dicomifier::actions::SetElement<EVR_DS>::New(dataset, DCM_RadialPosition, {1.23, -4.56})->run();

    dicomifier::actions::SetElement<EVR_FD>::New(dataset, DCM_SteeringAngle, 1.23)->run();
    dicomifier::actions::SetElement<EVR_FD>::New(dataset, DCM_SelectorFDValue, {1.23, -4.56})->run();

    dicomifier::actions::SetElement<EVR_FL>::New(dataset, DCM_StimulusArea, 1.23)->run();
    dicomifier::actions::SetElement<EVR_FL>::New(dataset, DCM_SelectorFLValue, {1.23, -4.56})->run();

    dicomifier::actions::SetElement<EVR_IS>::New(dataset, DCM_StageNumber, 123)->run();
    dicomifier::actions::SetElement<EVR_IS>::New(dataset, DCM_SelectorISValue, {123, -456})->run();

    dicomifier::actions::SetElement<EVR_SL>::New(dataset, DCM_ReferencePixelX0, -123456789)->run();
    dicomifier::actions::SetElement<EVR_SL>::New(dataset, DCM_SelectorSLValue, {-123456789, 12345678})->run();

    dicomifier::actions::SetElement<EVR_SS>::New(dataset, DCM_TagAngleSecondAxis, -123)->run();
    dicomifier::actions::SetElement<EVR_SS>::New(dataset, DCM_SelectorSSValue, {-1, 2, -3})->run();

    dicomifier::actions::SetElement<EVR_UL>::New(dataset, DCM_RegionFlags, 1234567890)->run();
    dicomifier::actions::SetElement<EVR_UL>::New(dataset, DCM_SelectorULValue, {1234567890, 1234567891 })->run();

    dicomifier::actions::SetElement<EVR_US>::New(dataset, DCM_FailureReason, 456)->run();
    dicomifier::actions::SetElement<EVR_US>::New(dataset, DCM_SelectorUSValue, {456, 789})->run();

}*/
