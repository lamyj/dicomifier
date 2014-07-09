/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleElementMatchCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"
#include "dicom/conditions/ElementMatch.h"
#include "factory/dicom/conditions/ElementMatchCreator.h"

/*************************************** TEST ELEMENT TYPE AE ****************************************/

struct TestDataAE
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataAE()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_PerformedStationAETitle, OFString("ABCD"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PerformedStationAETitle");
        emptynode.put("<xmlattr>.value", "ABCD");
        emptynode.put("<xmlattr>.VR", "AE");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataAE()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationAE, TestDataAE)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_AE>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_AE>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE AS ****************************************/

struct TestDataAS
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataAS()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_PatientAge, OFString("20Y"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientAge");
        emptynode.put("<xmlattr>.value", "20Y");
        emptynode.put("<xmlattr>.VR", "AS");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataAS()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationAS, TestDataAS)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_AS>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_AS>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE CS ****************************************/

struct TestDataCS
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataCS()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_PatientSex, OFString("M"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientSex");
        emptynode.put("<xmlattr>.value", "M");
        emptynode.put("<xmlattr>.VR", "CS");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataCS()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationCS, TestDataCS)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
       
        dicomifier::conditions::ElementMatch<EVR_CS>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_CS>>(object);    
                   
        BOOST_CHECK_EQUAL(cond != NULL, true);
    } 
}

/*************************************** TEST ELEMENT TYPE DA ****************************************/

struct TestDataDA
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataDA()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_StudyDate, OFString("02052014"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "StudyDate");
        emptynode.put("<xmlattr>.value", "02052014");
        emptynode.put("<xmlattr>.VR", "DA");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataDA()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationDA, TestDataDA)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_DA>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_DA>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE DS ****************************************/

struct TestDataDS
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataDS()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertFloat64(DCM_PatientWeight, 35.5, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientWeight");
        emptynode.put("<xmlattr>.value", "35.5");
        emptynode.put("<xmlattr>.VR", "DS");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataDS()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationDS, TestDataDS)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_DS>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_DS>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE DT ****************************************/

struct TestDataDT
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataDT()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_AcquisitionDateTime, OFString("02153202062013"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "AcquisitionDateTime");
        emptynode.put("<xmlattr>.value", "02153202062013");
        emptynode.put("<xmlattr>.VR", "DT");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataDT()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationDT, TestDataDT)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_DT>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_DT>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE FD ****************************************/

struct TestDataFD
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataFD()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertFloat64(DCM_SteeringAngle, 1.23, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "SteeringAngle");
        emptynode.put("<xmlattr>.value", "1.23");
        emptynode.put("<xmlattr>.VR", "FD");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataFD()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationFD, TestDataFD)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_FD>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_FD>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE FL ****************************************/

struct TestDataFL
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataFL()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertFloat32(DCM_StimulusArea, 1.23, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "StimulusArea");
        emptynode.put("<xmlattr>.value", "1.23");
        emptynode.put("<xmlattr>.VR", "FL");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataFL()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationFL, TestDataFL)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_FL>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_FL>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE IS ****************************************/

struct TestDataIS
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataIS()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertSint32(DCM_StageNumber, 123, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "StageNumber");
        emptynode.put("<xmlattr>.value", "123");
        emptynode.put("<xmlattr>.VR", "IS");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataIS()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationIS, TestDataIS)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_IS>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_IS>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE LO ****************************************/

struct TestDataLO
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataLO()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_Manufacturer, OFString("Machine1"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "Manufacturer");
        emptynode.put("<xmlattr>.value", "Machine1");
        emptynode.put("<xmlattr>.VR", "LO");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataLO()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationLO, TestDataLO)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_LO>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_LO>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE LT ****************************************/

struct TestDataLT
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataLT()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_AdditionalPatientHistory, OFString("abc"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "AdditionalPatientHistory");
        emptynode.put("<xmlattr>.value", "abc");
        emptynode.put("<xmlattr>.VR", "LT");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataLT()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationLT, TestDataLT)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_LT>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_LT>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE PN ****************************************/

struct TestDataPN
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataPN()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "0010,0010");
        emptynode.put("<xmlattr>.value", "John");
        emptynode.put("<xmlattr>.VR", "PN");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataPN()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationPN, TestDataPN)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_PN>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_PN>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE SH ****************************************/

struct TestDataSH
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataSH()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_AccessionNumber, OFString("1234"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "AccessionNumber");
        emptynode.put("<xmlattr>.value", "1234");
        emptynode.put("<xmlattr>.VR", "SH");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataSH()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationSH, TestDataSH)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_SH>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_SH>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE SL ****************************************/

struct TestDataSL
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataSL()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertSint32(DCM_ReferencePixelX0, 123, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "ReferencePixelX0");
        emptynode.put("<xmlattr>.value", "123");
        emptynode.put("<xmlattr>.VR", "SL");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataSL()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationSL, TestDataSL)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_SL>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_SL>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE SS ****************************************/

struct TestDataSS
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataSS()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertSint16(DCM_TagAngleSecondAxis, 123, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "TagAngleSecondAxis");
        emptynode.put("<xmlattr>.value", "123");
        emptynode.put("<xmlattr>.VR", "SS");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataSS()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationSS, TestDataSS)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_SS>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_SS>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE UI ****************************************/

struct TestDataUI
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataUI()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_SOPClassUID, OFString("12345678"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "SOPClassUID");
        emptynode.put("<xmlattr>.value", "12345678");
        emptynode.put("<xmlattr>.VR", "UI");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataUI()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationUI, TestDataUI)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_UI>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_UI>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE TM ****************************************/

struct TestDataTM
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataTM()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_StudyTime, OFString("012345"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "StudyTime");
        emptynode.put("<xmlattr>.value", "012345");
        emptynode.put("<xmlattr>.VR", "TM");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataTM()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationTM, TestDataTM)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_TM>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_TM>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE ST ****************************************/

struct TestDataST
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataST()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_InstitutionAddress, OFString("ABC"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "InstitutionAddress");
        emptynode.put("<xmlattr>.value", "ABC");
        emptynode.put("<xmlattr>.VR", "ST");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataST()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationST, TestDataST)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_ST>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_ST>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE UL ****************************************/

struct TestDataUL
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataUL()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertUint32(DCM_RegionFlags, 123, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "RegionFlags");
        emptynode.put("<xmlattr>.value", "123");
        emptynode.put("<xmlattr>.VR", "UL");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataUL()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationUL, TestDataUL)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_UL>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_UL>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE US ****************************************/

struct TestDataUS
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataUS()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertUint16(DCM_FailureReason, 123, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "FailureReason");
        emptynode.put("<xmlattr>.value", "123");
        emptynode.put("<xmlattr>.VR", "US");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataUS()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationUS, TestDataUS)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_US>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_US>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ELEMENT TYPE UT ****************************************/

struct TestDataUT
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataUT()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("myUnlimitedText");
        dataset->putAndInsertOFStringArray(DCM_PixelDataProviderURL, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PixelDataProviderURL");
        emptynode.put("<xmlattr>.value", "myUnlimitedText");
        emptynode.put("<xmlattr>.VR", "UT");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataUT()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(CreationUT, TestDataUT)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testmatch->Create(v);
        
        dicomifier::conditions::ElementMatch<EVR_UT>::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::ElementMatch<EVR_UT>>(object);
        
        BOOST_CHECK_EQUAL(cond != NULL, true);
    }
}

/*************************************** TEST ERROR ****************************************/

struct TestDataBadTag
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataBadTag()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "bad tag");
        emptynode.put("<xmlattr>.value", "John");
        emptynode.put("<xmlattr>.VR", "PN");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataBadTag()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowBadTag, TestDataBadTag)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testmatch->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataBadFile
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataBadFile()
    {        
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientName");
        emptynode.put("<xmlattr>.value", "John");
        emptynode.put("<xmlattr>.VR", "PN");
        emptynode.put("<xmlattr>.dataset", "#unknownfile");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataBadFile()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowBadFile, TestDataBadFile)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testmatch->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataError01
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataError01()
    {        
        // Create Test file
        DcmDataset* dataset = NULL;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientSex");
        emptynode.put("<xmlattr>.value", "M");
        emptynode.put("<xmlattr>.VR", "CS");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataError01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowError01, TestDataError01)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testmatch->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataError02
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataError02()
    {        
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        dataset->putAndInsertOFStringArray(DCM_PatientName, OFString("John"), true);
        dataset->putAndInsertOFStringArray(DCM_PatientSex, OFString("M"), true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientSex");
        emptynode.put("<xmlattr>.value", "M");
        emptynode.put("<xmlattr>.VR", "CS");
        emptynode.put("<xmlattr>.dataset", "input");
        ptr.add_child("ElementMatch", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataError02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ThrowError02, TestDataError02)
{
    auto testmatch = dicomifier::factory::ElementMatchCreator::New();
    testmatch->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testmatch->Create(v), dicomifier::DicomifierException);
    }
}
