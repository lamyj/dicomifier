/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/
 
#include <iostream>
#include <fstream>

#define BOOST_TEST_MODULE ModuleEmptyElementCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include "core/DicomifierException.h"
#include "core/Object.h"
#include "dicom/actions/EmptyElement.h"
#include "factory/dicom/actions/EmptyElementCreator.h"

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
        ptr.add_child("EmptyElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto testempty = dicomifier::factory::EmptyElementCreator::New();
    testempty->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testempty->Create(v);
        
        dicomifier::actions::EmptyElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::EmptyElement>(object);
        
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
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "PatientName");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("EmptyElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    auto testempty = dicomifier::factory::EmptyElementCreator::New();
    testempty->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testempty->Create(v);
        
        dicomifier::actions::EmptyElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::EmptyElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 03 ******************************/
/**
 * Test with tagkey in public dictionary
 * With Sequence
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
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "0010,1002[0:1].0010,0020[0:2]");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("EmptyElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    auto testempty = dicomifier::factory::EmptyElementCreator::New();
    testempty->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testempty->Create(v);
        
        dicomifier::actions::EmptyElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::EmptyElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}

/**************************** TEST OK 04 ******************************/
/**
 * Test with tagkey in private dictionary
 * With Sequence
 */
struct TestDataOK04
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestDataOK04()
    {
        // Create private dictionary
        std::ofstream myfile;
        myfile.open ("temp_emptyelementcreator_test_ok_04.xml");
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
        
        dicomifier::Dictionaries::get_instance().ParsePrivateDictionary("./temp_emptyelementcreator_test_ok_04.xml");
        
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.tag", "0023,xx01.0023,xx02");
        emptynode.put("<xmlattr>.dataset", "#input");
        emptynode.put("<xmlattr>.private_creator", "MyPrivateDict");
        ptr.add_child("EmptyElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataOK04()
    {
        remove("./temp_emptyelementcreator_test_ok_04.xml");
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
{
    auto testempty = dicomifier::factory::EmptyElementCreator::New();
    testempty->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testempty->Create(v);
        
        dicomifier::actions::EmptyElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::EmptyElement>(object);
        
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
        ptr.add_child("EmptyElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto testempty = dicomifier::factory::EmptyElementCreator::New();
    testempty->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testempty->Create(v), dicomifier::DicomifierException);
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
        ptr.add_child("EmptyElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataKO02)
{
    auto testempty = dicomifier::factory::EmptyElementCreator::New();
    testempty->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testempty->Create(v), dicomifier::DicomifierException);
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
        ptr.add_child("EmptyElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_03, TestDataKO03)
{
    auto testempty = dicomifier::factory::EmptyElementCreator::New();
    testempty->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testempty->Create(v), dicomifier::DicomifierException);
    }
}

/**************************** TEST KO 04 ******************************/
/**
 * Test with dataset NULL
 * No Sequence
 */
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
        ptr.add_child("EmptyElement", emptynode);
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
    }
 
    ~TestDataKO04()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_04, TestDataKO04)
{
    auto testempty = dicomifier::factory::EmptyElementCreator::New();
    testempty->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(testempty->Create(v), dicomifier::DicomifierException);
    }
}

