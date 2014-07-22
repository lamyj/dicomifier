/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDeleteElementCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/DicomifierException.h"
#include "core/Object.h"
#include "dicom/actions/DeleteElement.h"
#include "factory/dicom/actions/DeleteElementCreator.h"

/**************************** TEST OK 01 ******************************/
/**
 * Test with tag key XXXX,XXXX in public dictionary
 * No Sequence
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK01()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "0010,0010");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 02 ******************************/
/**
 * Test with keyword in public dictionary
 * No Sequence
 */
struct TestDataOK02
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK02()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        dataset->putAndInsertOFStringArray(DCM_PatientID, "123\\456\\789\\101");
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientID");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 03 ******************************/
/**
 * Test with keyword[:Max] in public dictionary
 * No Sequence
 */
struct TestDataOK03
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK03()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1\\value2\\value3\\value4");
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "Modality[:2]");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 04 ******************************/
/**
 * Test with keyword[Min:] in public dictionary
 * No Sequence
 */
struct TestDataOK04
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK04()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1\\value2\\value3\\value4");
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "Modality[1:]");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK04()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 05 ******************************/
/**
 * Test with keyword[:] in public dictionary
 * No Sequence
 */
struct TestDataOK05
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK05()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1\\value2\\value3\\value4");
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "Modality[:]");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK05()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_05, TestDataOK05)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 06 ******************************/
/**
 * Test with keyword[value] in public dictionary
 * No Sequence
 */
struct TestDataOK06
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK06()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1\\value2\\value3\\value4");
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "Modality[2]");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK06()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_06, TestDataOK06)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 07 ******************************/
/**
 * Test with keyword[Min:Max] in public dictionary
 * No Sequence
 */
struct TestDataOK07
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK07()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        dataset->putAndInsertOFStringArray(DCM_Modality, "value1\\value2\\value3\\value4");
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "Modality[1:3]");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK07()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_07, TestDataOK07)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 08 ******************************/
/**
 * Test with keyword in public dictionary
 * With Sequence keyword
 */
struct TestDataOK08
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK08()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        item->putAndInsertOFStringArray(DCM_PatientID, "123\\456\\789");
        dataset->insertSequenceItem(DCM_OtherPatientIDsSequence, item);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "OtherPatientIDsSequence.PatientID[0:1]");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK08()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_08, TestDataOK08)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 09 ******************************/
/**
 * Test with keyword in public dictionary
 * With Sequence tag
 */
struct TestDataOK09
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK09()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        DcmItem* item = new DcmItem(DCM_OtherPatientIDsSequence);
        item->putAndInsertOFStringArray(DCM_PatientID, "123\\456\\789");
        dataset->insertSequenceItem(DCM_OtherPatientIDsSequence, item);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "0010,1002[0:2].PatientID[0:1]");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK09()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_09, TestDataOK09)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 10 ******************************/
/**
 * Test with tagkey in private dictionary
 * With Sequence
 */
struct TestDataOK10
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK10()
    {
        // Create private dictionary
        std::ofstream myfile;
        myfile.open ("temp_deleteelementcreator_test_ok_10.xml");
        myfile << "<book>\n";
        myfile << "    <title>MyPrivateDict</title>\n";
        myfile << "    <chapter>\n";
        myfile << "        <table>\n";
        myfile << "            <tbody>\n";
        myfile << "                <tr>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>(0023,xx01)</para>\n";
        myfile << "                    </td>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>MySequence</para>\n";
        myfile << "                    </td>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>MySequence</para>\n";
        myfile << "                    </td>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>SQ</para>\n";
        myfile << "                    </td>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>1</para>\n";
        myfile << "                    </td>\n";
        myfile << "                </tr>\n";
        myfile << "                <tr>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>(0023,xx02)</para>\n";
        myfile << "                    </td>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>MyVariable</para>\n";
        myfile << "                    </td>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>MyVariable</para>\n";
        myfile << "                    </td>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>CS</para>\n";
        myfile << "                    </td>\n";
        myfile << "                    <td>\n";
        myfile << "                        <para>1</para>\n";
        myfile << "                    </td>\n";
        myfile << "                </tr>\n";
        myfile << "            </tbody>\n";
        myfile << "        </table>\n";
        myfile << "    </chapter>\n";
        myfile << "</book>\n";
        myfile.close();
        
        dicomifier::Dictionaries::get_instance().ParsePrivateDictionary("./temp_deleteelementcreator_test_ok_10.xml");
        
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "0023,xx01.0023,xx02");
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.private_creator", "MyPrivateDict");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK10()
    {
        remove("./temp_deleteelementcreator_test_ok_10.xml");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_10, TestDataOK10)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testdelete->Create(v);
        
        dicomifier::actions::DeleteElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::DeleteElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}


/**************************** TEST KO 01 ******************************/
/**
 * Test with key not in dictionary
 * No Sequence
 */
struct TestDataKO01
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO01()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "bad tag");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testdelete->Create(v), dicomifier::DicomifierException);
    }
}

/**************************** TEST KO 02 ******************************/
/**
 * Test with input dataset missing
 * No Sequence
 */
struct TestDataKO02
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO02()
    {        
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientName");
        emptynode.put("<xmlattr>.dataset", "#unknownfile");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataKO02)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testdelete->Create(v), dicomifier::DicomifierException);
    }
}

/**************************** TEST KO 03 ******************************/
/**
 * Test with input dataset not linked
 * No Sequence
 */
struct TestDataKO03
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO03()
    {        
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientName");
        emptynode.put("<xmlattr>.dataset", "input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataKO03)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testdelete->Create(v), dicomifier::DicomifierException);
    }
}

struct TestDataKO04
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataKO04()
    {        
        // Create Test file
        DcmDataset* dataset = NULL;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientName");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("DeleteElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO04()
    {
    }
};

/**************************** TEST KO 04 ******************************/
/**
 * Test with dataset NULL
 * No Sequence
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_04, TestDataKO04)
{
    auto testdelete = dicomifier::factory::DeleteElementCreator::New();
    testdelete->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testdelete->Create(v), dicomifier::DicomifierException);
    }
}
