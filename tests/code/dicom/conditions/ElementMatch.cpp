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

/********************************* TEST ELEMENT TYPE AE *********************************/

struct TestDataAE
{
    DcmDataset * dataset;
 
    TestDataAE()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_RetrieveAETitle, "test_AE");
    }
 
    ~TestDataAE()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchAE01, TestDataAE)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_AE>::New(dataset, 
                                                      DCM_RetrieveAETitle, 
                                                      "test_AE");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE AS *********************************/

struct TestDataAS
{
    DcmDataset * dataset;
 
    TestDataAS()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_PatientAge, "test_AS");
    }
 
    ~TestDataAS()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchAS01, TestDataAS)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_AS>::New(dataset, 
                                                      DCM_PatientAge, 
                                                      "test_AS");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE CS *********************************/

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

/********************************* TEST ELEMENT TYPE DA *********************************/

struct TestDataDA
{
    DcmDataset * dataset;
 
    TestDataDA()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_PatientBirthDate, "01/01/2001");
    }
 
    ~TestDataDA()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchDA01, TestDataDA)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_DA>::New(dataset, 
                                                      DCM_PatientBirthDate, 
                                                      "01/01/2001");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE DS *********************************/

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

/********************************* TEST ELEMENT TYPE DT *********************************/

struct TestDataDT
{
    DcmDataset * dataset;
 
    TestDataDT()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_FrameAcquisitionDateTime, "01/01/2001 09:09:09");
    }
 
    ~TestDataDT()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchDT01, TestDataDT)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_DT>::New(dataset, 
                                                      DCM_FrameAcquisitionDateTime, 
                                                      "01/01/2001 09:09:09");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE FD *********************************/

struct TestDataFD
{
    DcmDataset * dataset;
 
    TestDataFD()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertFloat64(DCM_PupilSize, 42.5);
    }
 
    ~TestDataFD()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchFD01, TestDataFD)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_FD>::New(dataset, 
                                                      DCM_PupilSize, 
                                                      42.5);
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE FL *********************************/

struct TestDataFL
{
    DcmDataset * dataset;
 
    TestDataFL()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertFloat32(DCM_RecommendedDisplayFrameRateInFloat, 15.2);
    }
 
    ~TestDataFL()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchFL01, TestDataFL)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_FL>::New(dataset, 
                                                      DCM_RecommendedDisplayFrameRateInFloat, 
                                                      15.2);
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE IS *********************************/

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

/********************************* TEST ELEMENT TYPE LO *********************************/

struct TestDataLO
{
    DcmDataset * dataset;
 
    TestDataLO()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_Manufacturer, "MyManufacturer");
    }
 
    ~TestDataLO()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchLO01, TestDataLO)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_LO>::New(dataset, 
                                                      DCM_Manufacturer, 
                                                      "MyManufacturer");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE LT *********************************/

struct TestDataLT
{
    DcmDataset * dataset;
 
    TestDataLT()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_AdditionalPatientHistory, "test_valueLT");
    }
 
    ~TestDataLT()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchLT01, TestDataLT)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_LT>::New(dataset, 
                                                      DCM_AdditionalPatientHistory, 
                                                      "test_valueLT");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE PN *********************************/

struct TestDataPN
{
    DcmDataset * dataset;
 
    TestDataPN()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_PatientName, "Doe^John");       // insert PN
    }
 
    ~TestDataPN()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchPN01, TestDataPN)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_PN>::New(dataset, 
                                                      DCM_PatientName, 
                                                      "Doe^John");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE SH *********************************/

struct TestDataSH
{
    DcmDataset * dataset;
 
    TestDataSH()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_EthnicGroup, "test_valueSH");
    }
 
    ~TestDataSH()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchSH01, TestDataSH)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_SH>::New(dataset, 
                                                      DCM_EthnicGroup, 
                                                      "test_valueSH");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE SL *********************************/

struct TestDataSL
{
    DcmDataset * dataset;
 
    TestDataSL()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertSint32(DCM_ReferencePixelX0, 10);
    }
 
    ~TestDataSL()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchSL01, TestDataSL)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_SL>::New(dataset, 
                                                      DCM_ReferencePixelX0, 
                                                      10);
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE SS *********************************/

struct TestDataSS
{
    DcmDataset * dataset;
 
    TestDataSS()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertSint16(DCM_TagAngleSecondAxis, 10);
    }
 
    ~TestDataSS()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchSS01, TestDataSS)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_SS>::New(dataset, 
                                                      DCM_TagAngleSecondAxis, 
                                                      10);
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE UI *********************************/

struct TestDataUI
{
    DcmDataset * dataset;
 
    TestDataUI()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_SOPClassUID, "1.2.3.4.5.6");
    }
 
    ~TestDataUI()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchUI01, TestDataUI)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_UI>::New(dataset, 
                                                      DCM_SOPClassUID, 
                                                      "1.2.3.4.5.6");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE TM *********************************/

struct TestDataTM
{
    DcmDataset * dataset;
 
    TestDataTM()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_InstanceCreationTime, "08:08:08");
    }
 
    ~TestDataTM()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchTM01, TestDataTM)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_TM>::New(dataset, 
                                                      DCM_InstanceCreationTime, 
                                                      "08:08:08");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE ST *********************************/

struct TestDataST
{
    DcmDataset * dataset;
 
    TestDataST()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_InstitutionAddress, "MyAdress");
    }
 
    ~TestDataST()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchST01, TestDataST)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_ST>::New(dataset, 
                                                      DCM_InstitutionAddress, 
                                                      "MyAdress");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE UL *********************************/

struct TestDataUL
{
    DcmDataset * dataset;
 
    TestDataUL()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertUint32(DCM_SimpleFrameList, 11);
    }
 
    ~TestDataUL()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchUL01, TestDataUL)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_UL>::New(dataset, 
                                                      DCM_SimpleFrameList, 
                                                      11);
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE US *********************************/

struct TestDataUS
{
    DcmDataset * dataset;
 
    TestDataUS()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertUint16(DCM_FailureReason, 5);
    }
 
    ~TestDataUS()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchUS01, TestDataUS)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_US>::New(dataset, 
                                                      DCM_FailureReason, 
                                                      5);
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ELEMENT TYPE UT *********************************/

struct TestDataUT
{
    DcmDataset * dataset;
 
    TestDataUT()
    {
        dataset = new DcmDataset();
        // Insert testing value
        dataset->putAndInsertOFStringArray(DCM_PixelDataProviderURL, "test_valueUT");
    }
 
    ~TestDataUT()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(MatchUT01, TestDataUT)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_UT>::New(dataset, 
                                                      DCM_PixelDataProviderURL, 
                                                      "test_valueUT");
    BOOST_CHECK_EQUAL(testmatch->eval(), true);
}

/********************************* TEST ERROR *********************************/

struct TestDataError
{
    DcmDataset * dataset;
 
    TestDataError()
    {
        dataset = new DcmDataset();
        // Insert testing value
        std::string test = "value1";
        dataset->putAndInsertOFStringArray(DCM_Modality, test.c_str());
    }
 
    ~TestDataError()
    {
        delete dataset;
    }
};

BOOST_FIXTURE_TEST_CASE(Error_nodataset, TestDataError)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_CS>::New(NULL, 
                                                      DCM_Modality, 
                                                      "value1");
    BOOST_CHECK_EQUAL(testmatch->eval(), false);
}

BOOST_FIXTURE_TEST_CASE(Error_badtag, TestDataError)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_CS>::New(dataset, 
                                                      DCM_PatientSex, 
                                                      "value1");
    BOOST_CHECK_EQUAL(testmatch->eval(), false);
}

BOOST_FIXTURE_TEST_CASE(Error_badvalue, TestDataError)
{
    auto testmatch = 
        dicomifier::conditions::ElementMatch<EVR_CS>::New(dataset, 
                                                      DCM_Modality, 
                                                      "badvalue");
    BOOST_CHECK_EQUAL(testmatch->eval(), false);
}
