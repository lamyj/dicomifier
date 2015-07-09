/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDicomDirGenerator
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>

#include "dicom/DicomDirGenerator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor / Destructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    auto dicomdirgenerator = new dicomifier::DicomDirGenerator();

    BOOST_CHECK_EQUAL(dicomdirgenerator != NULL, true);

    delete dicomdirgenerator;
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Create DICOMDIR
 */
struct TestDataOK02
{
    dicomifier::DicomDirGenerator* dicomdirgenerator;

    TestDataOK02()
    {
        dicomdirgenerator = new dicomifier::DicomDirGenerator();
    }

    ~TestDataOK02()
    {
        delete dicomdirgenerator;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    dicomdirgenerator->enableMapFilenamesMode();

    OFCondition result =
        dicomdirgenerator->createNewDicomDir(dicomifier::DicomDirGenerator::AP_GeneralPurpose,
                                             "./DICOMDIR");
    BOOST_CHECK_EQUAL(result == EC_Normal, true);
    BOOST_CHECK_EQUAL(dicomdirgenerator->isDicomDirValid(), true);
}


/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Add extra attributs
 */
struct TestDataOK03
{
    dicomifier::DicomDirGenerator* dicomdirgenerator;

    TestDataOK03()
    {
        dicomdirgenerator = new dicomifier::DicomDirGenerator();
        dicomdirgenerator->enableMapFilenamesMode();

        OFCondition result =
            dicomdirgenerator->createNewDicomDir(dicomifier::DicomDirGenerator::AP_GeneralPurpose,
                                                 "./DICOMDIR");
    }

    ~TestDataOK03()
    {
        delete dicomdirgenerator;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    // patient_extra_attributes
    std::vector<DcmTagKey> patient_extra_attributes_cpp =
    {
        DCM_PatientAge
    };

    // study_extra_attributes
    std::vector<DcmTagKey> study_extra_attributes_cpp =
    {
        DCM_StudyDescription
    };

    // series_extra_attributes
    std::vector<DcmTagKey> series_extra_attributes_cpp =
    {
        DCM_SeriesDescription
    };

    dicomdirgenerator->setPatientExtraAttributes(patient_extra_attributes_cpp);
    dicomdirgenerator->setStudyExtraAttributes(study_extra_attributes_cpp);
    dicomdirgenerator->setSeriesExtraAttributes(series_extra_attributes_cpp);

    BOOST_CHECK_EQUAL(dicomdirgenerator->getPatientExtraAttributes().size(), 1);
    BOOST_CHECK_EQUAL(dicomdirgenerator->getStudyExtraAttributes().size(), 1);
    BOOST_CHECK_EQUAL(dicomdirgenerator->getSeriesExtraAttributes().size(), 1);
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Write DICOMDIR
 */
struct TestDataOK04
{
    dicomifier::DicomDirGenerator* dicomdirgenerator;

    TestDataOK04()
    {
        dicomdirgenerator = new dicomifier::DicomDirGenerator();
        dicomdirgenerator->enableMapFilenamesMode();

        OFCondition result =
            dicomdirgenerator->createNewDicomDir(dicomifier::DicomDirGenerator::AP_GeneralPurpose,
                                                 "./DICOMDIR");
    }

    ~TestDataOK04()
    {
        delete dicomdirgenerator;
        remove("./DICOMDIR");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
{
    OFCondition result = dicomdirgenerator->writeDicomDir();
    BOOST_CHECK_EQUAL(result == EC_Normal, true);
    BOOST_CHECK_EQUAL(boost::filesystem::exists("./DICOMDIR"), true);
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: BackUp DICOMDIR
 */
struct TestDataOK05
{
    dicomifier::DicomDirGenerator* dicomdirgenerator;
    dicomifier::DicomDirGenerator* backdicomdirgenerator;

    TestDataOK05()
    {
        dicomdirgenerator = new dicomifier::DicomDirGenerator();
        dicomdirgenerator->enableMapFilenamesMode();

        backdicomdirgenerator = new dicomifier::DicomDirGenerator();
        backdicomdirgenerator->enableMapFilenamesMode();
        backdicomdirgenerator->disableBackupMode(true);

        OFCondition result =
            dicomdirgenerator->createNewDicomDir(dicomifier::DicomDirGenerator::AP_GeneralPurpose,
                                                 "./DICOMDIR");
    }

    ~TestDataOK05()
    {
        delete dicomdirgenerator;
        delete backdicomdirgenerator;
        remove("./DICOMDIR");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_05, TestDataOK05)
{
    OFCondition result = dicomdirgenerator->writeDicomDir();
    BOOST_CHECK_EQUAL(result == EC_Normal, true);
    BOOST_CHECK_EQUAL(boost::filesystem::exists("./DICOMDIR"), true);

    result = backdicomdirgenerator->createNewDicomDir(dicomifier::DicomDirGenerator::AP_GeneralPurpose,
                                                      "./DICOMDIR");
    BOOST_CHECK_EQUAL(result == EC_Normal, true);

    result = backdicomdirgenerator->writeDicomDir();
    BOOST_CHECK_EQUAL(result == EC_Normal, true);
    BOOST_CHECK_EQUAL(boost::filesystem::exists("./DICOMDIR"), true);
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Add files
 */
struct TestDataOK06
{
    dicomifier::DicomDirGenerator* dicomdirgenerator;

    TestDataOK06()
    {
        dicomdirgenerator = new dicomifier::DicomDirGenerator();
        dicomdirgenerator->enableMapFilenamesMode();

        OFCondition result = dicomdirgenerator->createNewDicomDir(
                    dicomifier::DicomDirGenerator::AP_GeneralPurpose,
                    "./DICOMDIR");
        BOOST_CHECK_EQUAL(result == EC_Normal, true);

        DcmDataset * dataset = new DcmDataset();
        // generate unique SOP INSTANCE UID
        char uid_sop_instance[128];
        dcmGenerateUniqueIdentifier(uid_sop_instance, SITE_INSTANCE_UID_ROOT);

        dataset->putAndInsertOFStringArray(DCM_SOPInstanceUID, OFString(uid_sop_instance));
        dataset->putAndInsertOFStringArray(DCM_SOPClassUID, UID_MRImageStorage);
        dataset->putAndInsertOFStringArray(DCM_Modality, "MR");
        dataset->putAndInsertOFStringArray(DCM_PatientID, "patient_id");
        dataset->putAndInsertOFStringArray(DCM_PatientName, "patient^name");
        dataset->putAndInsertOFStringArray(DCM_StudyDate, "20150101");
        dataset->putAndInsertOFStringArray(DCM_StudyTime, "121212");
        dataset->putAndInsertOFStringArray(DCM_StudyInstanceUID, "1.2.3.4.5");
        dataset->putAndInsertOFStringArray(DCM_StudyID, "study_id");
        dataset->putAndInsertOFStringArray(DCM_SeriesInstanceUID, "1.2.3.4.5.6");
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, "1");
        dataset->putAndInsertOFStringArray(DCM_InstanceNumber, "1");

        DcmFileFormat fileformat(dataset);
        result = fileformat.saveFile("./ABCD1234", EXS_LittleEndianExplicit);
        BOOST_CHECK_EQUAL(result == EC_Normal, true);

        delete dataset;
    }

    ~TestDataOK06()
    {
        delete dicomdirgenerator;
        remove("./DICOMDIR");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_06, TestDataOK06)
{
    BOOST_CHECK_EQUAL(boost::filesystem::exists("./ABCD1234"), true);
    OFCondition result = dicomdirgenerator->addDicomFile("ABCD1234");
    BOOST_CHECK_EQUAL(result == EC_Normal, true);

    result = dicomdirgenerator->writeDicomDir();
    BOOST_CHECK_EQUAL(result == EC_Normal, true);
    BOOST_CHECK_EQUAL(boost::filesystem::exists("./DICOMDIR"), true);
}

/*************************** TEST OK 07 *******************************/
/**
 * Nominal test case: Update DICOMDIR
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_07, TestDataOK06)
{
    BOOST_CHECK_EQUAL(boost::filesystem::exists("./ABCD1234"), true);
    OFCondition result = dicomdirgenerator->addDicomFile("ABCD1234");
    BOOST_CHECK_EQUAL(result == EC_Normal, true);

    result = dicomdirgenerator->writeDicomDir();
    BOOST_CHECK_EQUAL(result == EC_Normal, true);
    BOOST_CHECK_EQUAL(boost::filesystem::exists("./DICOMDIR"), true);

    result = dicomdirgenerator->updateDicomDir(
                dicomifier::DicomDirGenerator::AP_GeneralPurpose,
                "./DICOMDIR");
    BOOST_CHECK_EQUAL(result == EC_Normal, true);
}

/*************************** TEST OK 08 *******************************/
/**
 * Nominal test case: Append to DICOMDIR
 */
BOOST_FIXTURE_TEST_CASE(TEST_OK_08, TestDataOK06)
{
    BOOST_CHECK_EQUAL(boost::filesystem::exists("./ABCD1234"), true);
    OFCondition result = dicomdirgenerator->addDicomFile("ABCD1234");
    BOOST_CHECK_EQUAL(result == EC_Normal, true);

    result = dicomdirgenerator->writeDicomDir();
    BOOST_CHECK_EQUAL(result == EC_Normal, true);
    BOOST_CHECK_EQUAL(boost::filesystem::exists("./DICOMDIR"), true);

    result = dicomdirgenerator->appendToDicomDir(
                dicomifier::DicomDirGenerator::AP_GeneralPurpose,
                "./DICOMDIR");
    BOOST_CHECK_EQUAL(result == EC_Normal, true);
}
