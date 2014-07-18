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

/*************************************** TEST ELEMENT TYPE AE ****************************************/

BOOST_FIXTURE_TEST_CASE(SetAE01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PerformedStationAETitle, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_AE>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("AB");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PerformedStationAETitle, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "AB");
}

BOOST_FIXTURE_TEST_CASE(SetAE02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_RetrieveAETitle, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_AE>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"AB", "CD"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_RetrieveAETitle, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "AB\\CD");
}

/*************************************** TEST ELEMENT TYPE AS ****************************************/

BOOST_FIXTURE_TEST_CASE(SetAS01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PatientAge, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_AS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("42Y");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PatientAge, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "42Y");
}

BOOST_FIXTURE_TEST_CASE(SetAS02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PatientAge, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_AS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"AB", "CD"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PatientAge, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "AB\\CD");
}

/*************************************** TEST ELEMENT TYPE CS ****************************************/

BOOST_FIXTURE_TEST_CASE(SetCS01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_Modality, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_CS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("MR");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_Modality, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "MR");
}

BOOST_FIXTURE_TEST_CASE(SetCS02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SelectorCSValue, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_CS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"AB", "CD"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SelectorCSValue, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "AB\\CD");
}

/*************************************** TEST ELEMENT TYPE DA ****************************************/

BOOST_FIXTURE_TEST_CASE(SetDA01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_StudyDate, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_DA>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("12122012");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_StudyDate, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "12122012");
}

BOOST_FIXTURE_TEST_CASE(SetDA02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_DateOfLastCalibration, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_DA>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"12122012", "12122013"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_DateOfLastCalibration, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "12122012\\12122013");
}

/*************************************** TEST ELEMENT TYPE DS ****************************************/

BOOST_FIXTURE_TEST_CASE(SetDS01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PatientWeight, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_DS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value(75.57);
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PatientWeight, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "75.57");
}

BOOST_FIXTURE_TEST_CASE(SetDS02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_EventElapsedTimes, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_DS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({1.23, -4.56});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_EventElapsedTimes, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "1.23\\-4.56");
}

/*************************************** TEST ELEMENT TYPE DT ****************************************/

BOOST_FIXTURE_TEST_CASE(SetDT01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_AcquisitionDateTime, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_DT>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("01234501122012");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_AcquisitionDateTime, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "01234501122012");
}

BOOST_FIXTURE_TEST_CASE(SetDT02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_AcquisitionDateTime, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_DT>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"01234501122012", "01234501122013"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_AcquisitionDateTime, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "01234501122012\\01234501122013");
}

/*************************************** TEST ELEMENT TYPE FD ****************************************/

BOOST_FIXTURE_TEST_CASE(SetFD01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SteeringAngle, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_FD>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value(1.23);
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SteeringAngle, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "1.23");
}

BOOST_FIXTURE_TEST_CASE(SetFD02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SelectorFDValue, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_FD>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({1.23, -4.56});
    cs_single->run();
    
    Float64 temp;
    dataset->findAndGetFloat64(DCM_SelectorFDValue, temp, 0);
    BOOST_CHECK_EQUAL(temp, 1.23);
    
    dataset->findAndGetFloat64(DCM_SelectorFDValue, temp, 1);
    BOOST_CHECK_EQUAL(temp, -4.56);
    
    OFCondition cond = dataset->findAndGetFloat64(DCM_SelectorFDValue, temp, 2);
    BOOST_CHECK_EQUAL(cond.bad(), true);
}

/*************************************** TEST ELEMENT TYPE FL ****************************************/

BOOST_FIXTURE_TEST_CASE(SetFL01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_StimulusArea, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_FL>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value(1.23);
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_StimulusArea, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "1.23");
}

BOOST_FIXTURE_TEST_CASE(SetFL02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SelectorFLValue, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_FL>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({(Float32)(1.23), (Float32)(-4.56)});
    cs_single->run();
    
    Float32 temp = 0;
    dataset->findAndGetFloat32(DCM_SelectorFLValue, temp, 0);
    BOOST_CHECK_EQUAL(temp, (Float32)(1.23));
    
    temp = 0;
    dataset->findAndGetFloat32(DCM_SelectorFLValue, temp, 1);
    BOOST_CHECK_EQUAL(temp, (Float32)(-4.56));
    
    OFCondition cond = dataset->findAndGetFloat32(DCM_SelectorFLValue, temp, 2);
    BOOST_CHECK_EQUAL(cond.bad(), true);
}

/*************************************** TEST ELEMENT TYPE IS ****************************************/

BOOST_FIXTURE_TEST_CASE(SetIS01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_StageNumber, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_IS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value(123);
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_StageNumber, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "123");
}

BOOST_FIXTURE_TEST_CASE(SetIS02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SelectorISValue, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_IS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({123, -456});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SelectorISValue, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "123\\-456");
}

/*************************************** TEST ELEMENT TYPE LO ****************************************/

BOOST_FIXTURE_TEST_CASE(SetLO01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_Manufacturer, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_LO>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("BRUKER");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_Manufacturer, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "BRUKER");
}

BOOST_FIXTURE_TEST_CASE(SetLO02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_AdmittingDiagnosesDescription, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_LO>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"AB", "CD"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_AdmittingDiagnosesDescription, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "AB\\CD");
}

/*************************************** TEST ELEMENT TYPE LT ****************************************/

BOOST_FIXTURE_TEST_CASE(SetLT01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_AdditionalPatientHistory, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_LT>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("ABCD");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_AdditionalPatientHistory, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "ABCD");
}

BOOST_FIXTURE_TEST_CASE(SetLT02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_AdditionalPatientHistory, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_LT>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"AB", "CD"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_AdditionalPatientHistory, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "AB\\CD");
}

/*************************************** TEST ELEMENT TYPE PN ****************************************/

BOOST_FIXTURE_TEST_CASE(SetPN01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PatientName, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_PN>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("NAME");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PatientName, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "NAME");
}

BOOST_FIXTURE_TEST_CASE(SetPN02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PhysiciansOfRecord, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_PN>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"AB", "CD"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PhysiciansOfRecord, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "AB\\CD");
}

/*************************************** TEST ELEMENT TYPE SH ****************************************/

BOOST_FIXTURE_TEST_CASE(SetSH01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_AccessionNumber, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_SH>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("12345");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_AccessionNumber, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "12345");
}

BOOST_FIXTURE_TEST_CASE(SetSH02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_ReferringPhysicianTelephoneNumbers, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_SH>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"1234", "5678"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_ReferringPhysicianTelephoneNumbers, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "1234\\5678");
}

/*************************************** TEST ELEMENT TYPE SL ****************************************/

BOOST_FIXTURE_TEST_CASE(SetSL01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_ReferencePixelX0, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_SL>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value(-123456789);
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_ReferencePixelX0, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "-123456789");
}

BOOST_FIXTURE_TEST_CASE(SetSL02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SelectorSLValue, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_SL>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({-123456789, 12345678});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SelectorSLValue, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "-123456789\\12345678");
}

/*************************************** TEST ELEMENT TYPE SQ ****************************************/

// Impossible to create SQ SetElement

/*************************************** TEST ELEMENT TYPE SS ****************************************/

BOOST_FIXTURE_TEST_CASE(SetSS01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_TagAngleSecondAxis, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_SS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value(-123);
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_TagAngleSecondAxis, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "-123");
}

BOOST_FIXTURE_TEST_CASE(SetSS02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SelectorSSValue, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_SS>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({-1, 2, -3});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SelectorSSValue, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "-1\\2\\-3");
}

/*************************************** TEST ELEMENT TYPE UI ****************************************/

BOOST_FIXTURE_TEST_CASE(SetUI01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SOPClassUID, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_UI>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("12345");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SOPClassUID, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "12345");
}

BOOST_FIXTURE_TEST_CASE(SetUI02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SOPClassesInStudy, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_UI>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"1234", "5678"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SOPClassesInStudy, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "1234\\5678");
}

/*************************************** TEST ELEMENT TYPE TM ****************************************/

BOOST_FIXTURE_TEST_CASE(SetTM01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_StudyTime, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_TM>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("012345");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_StudyTime, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "012345");
}

BOOST_FIXTURE_TEST_CASE(SetTM02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_TimeOfLastCalibration, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_TM>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"012345", "022345"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_TimeOfLastCalibration, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "012345\\022345");
}

/*************************************** TEST ELEMENT TYPE ST ****************************************/

BOOST_FIXTURE_TEST_CASE(SetST01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_InstitutionAddress, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_ST>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("abcde");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_InstitutionAddress, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "abcde");
}

BOOST_FIXTURE_TEST_CASE(SetST02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_InstitutionAddress, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_ST>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"abcde", "fghij"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_InstitutionAddress, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "abcde\\fghij");
}

/*************************************** TEST ELEMENT TYPE UL ****************************************/

BOOST_FIXTURE_TEST_CASE(SetUL01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_RegionFlags, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_UL>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value(1234567890);
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_RegionFlags, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "1234567890");
}

BOOST_FIXTURE_TEST_CASE(SetUL02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SelectorULValue, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_UL>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({1234567890, 1234567891});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SelectorULValue, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "1234567890\\1234567891");
}

/*************************************** TEST ELEMENT TYPE US ****************************************/

BOOST_FIXTURE_TEST_CASE(SetUS01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_FailureReason, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_US>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value(456);
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_FailureReason, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "456");
}

BOOST_FIXTURE_TEST_CASE(SetUS02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_SelectorUSValue, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_US>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({456, 789});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_SelectorUSValue, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "456\\789");
}
    
/*************************************** TEST ELEMENT TYPE UT ****************************************/

BOOST_FIXTURE_TEST_CASE(SetUT01, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PixelDataProviderURL, dicomifier::Range(0,1)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_UT>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value("abcde");
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PixelDataProviderURL, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "abcde");
}

BOOST_FIXTURE_TEST_CASE(SetUT02, TestData)
{
    std::vector<dicomifier::TagAndRange> vect;
    vect.push_back(dicomifier::TagAndRange(DCM_PixelDataProviderURL, dicomifier::Range(0,2)));
    
    auto cs_single = dicomifier::actions::SetElement<EVR_UT>::New();
    cs_single->set_dataset(dataset);
    cs_single->set_tags(vect);
    cs_single->set_value({"abcde", "fghij"});
    cs_single->run();
    
    OFString str;
    OFCondition cond = dataset->findAndGetOFStringArray(DCM_PixelDataProviderURL, str);
    BOOST_CHECK_EQUAL(cond.good(), true);
    BOOST_CHECK_EQUAL(str, "abcde\\fghij");
}
