/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDicomFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "dicom/Dictionaries.h"
#include "translator/factory/fields/DicomFieldCreator.h"
#include "translator/fields/DicomField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor VR = AE
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;
 
    TestDataOK01()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0040,0241");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = dicomfieldcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::DicomField<EVR_AE>::Pointer dicomfieldAE = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(dicomfieldAE != NULL, true);
    }
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Constructor VR = AS
 */
struct TestDataOK02
{
    boost::property_tree::ptree ptr;
 
    TestDataOK02()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0010,1010");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = dicomfieldcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::DicomField<EVR_AS>::Pointer dicomfieldAS = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(dicomfieldAS != NULL, true);
    }
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Constructor VR = CS
 */
struct TestDataOK03
{
    boost::property_tree::ptree ptr;
 
    TestDataOK03()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,0060");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK03()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_03, TestDataOK03)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = dicomfieldcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::DicomField<EVR_CS>::Pointer dicomfieldCS = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(dicomfieldCS != NULL, true);
    }
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Constructor VR = DA
 */
struct TestDataOK04
{
    boost::property_tree::ptree ptr;
 
    TestDataOK04()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,0020");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK04()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_04, TestDataOK04)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = dicomfieldcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::DicomField<EVR_DA>::Pointer dicomfieldDA = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(dicomfieldDA != NULL, true);
    }
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: Constructor VR = DS
 */
struct TestDataOK05
{
    boost::property_tree::ptree ptr;
 
    TestDataOK05()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0010,1030");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK05()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_05, TestDataOK05)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = dicomfieldcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::DicomField<EVR_DS>::Pointer dicomfieldDS = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(dicomfieldDS != NULL, true);
    }
}

/*************************** TEST OK 06 *******************************/
/**
 * Nominal test case: Constructor VR = DT
 */
struct TestDataOK06
{
    boost::property_tree::ptree ptr;
 
    TestDataOK06()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,002a");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK06()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_06, TestDataOK06)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = dicomfieldcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::DicomField<EVR_DT>::Pointer dicomfieldDT = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(dicomfieldDT != NULL, true);
    }
}

/*************************** TEST OK 07 *******************************/
/**
 * Nominal test case: Constructor VR = FL
 */
struct TestDataOK07
{
    boost::property_tree::ptree ptr;
 
    TestDataOK07()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0024,0025");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK07()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_07, TestDataOK07)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = dicomfieldcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::DicomField<EVR_FL>::Pointer dicomfieldFL = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(dicomfieldFL != NULL, true);
    }
}

/*************************** TEST OK 08 *******************************/
/**
 * Nominal test case: Constructor VR = FD
 */
struct TestDataOK08
{
    boost::property_tree::ptree ptr;
 
    TestDataOK08()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0018,6036");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK08()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_08, TestDataOK08)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = dicomfieldcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::DicomField<EVR_FD>::Pointer dicomfieldFD = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(dicomfieldFD != NULL, true);
    }
}

/*************************** TEST OK 09 *******************************/
/**
 * Nominal test case: Constructor VR = IS
 */
struct TestDataOK09
{
    boost::property_tree::ptree ptr;
 
    TestDataOK09()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,2122");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK09()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_09, TestDataOK09)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = dicomfieldcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::DicomField<EVR_IS>::Pointer dicomfieldIS = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(dicomfieldIS != NULL, true);
    }
}

/*************************** TEST OK 10 *******************************/
/**
 * Nominal test case: Constructor VR = LO
 */
struct TestDataOK10
{
    boost::property_tree::ptree ptr;
 
    TestDataOK10()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,0070");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK10()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_10, TestDataOK10)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = dicomfieldcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::DicomField<EVR_LO>::Pointer dicomfieldLO = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(dicomfieldLO != NULL, true);
    }
}

/*************************** TEST OK 11 *******************************/
/**
 * Nominal test case: Constructor VR = LT
 */
struct TestDataOK11
{
    boost::property_tree::ptree ptr;
 
    TestDataOK11()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0010,21b0");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK11()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_11, TestDataOK11)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = dicomfieldcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::DicomField<EVR_LT>::Pointer dicomfieldLT = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(dicomfieldLT != NULL, true);
    }
}

/*************************** TEST OK 12 *******************************/
/**
 * Nominal test case: Constructor VR = PN
 */
struct TestDataOK12
{
    boost::property_tree::ptree ptr;
 
    TestDataOK12()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0010,0010");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK12()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_12, TestDataOK12)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = dicomfieldcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::DicomField<EVR_PN>::Pointer dicomfieldPN = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(dicomfieldPN != NULL, true);
    }
}

/*************************** TEST OK 13 *******************************/
/**
 * Nominal test case: Constructor VR = SH
 */
struct TestDataOK13
{
    boost::property_tree::ptree ptr;
 
    TestDataOK13()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,0050");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK13()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_13, TestDataOK13)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = dicomfieldcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::DicomField<EVR_SH>::Pointer dicomfieldSH = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(dicomfieldSH != NULL, true);
    }
}

/*************************** TEST OK 14 *******************************/
/**
 * Nominal test case: Constructor VR = SL
 */
struct TestDataOK14
{
    boost::property_tree::ptree ptr;
 
    TestDataOK14()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0018,6020");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK14()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_14, TestDataOK14)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = dicomfieldcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::DicomField<EVR_SL>::Pointer dicomfieldSL = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(dicomfieldSL != NULL, true);
    }
}

/*************************** TEST OK 15 *******************************/
/**
 * Nominal test case: Constructor VR = SS
 */
struct TestDataOK15
{
    boost::property_tree::ptree ptr;
 
    TestDataOK15()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0018,9219");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK15()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_15, TestDataOK15)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = dicomfieldcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::DicomField<EVR_SS>::Pointer dicomfieldSS = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(dicomfieldSS != NULL, true);
    }
}

/*************************** TEST OK 16 *******************************/
/**
 * Nominal test case: Constructor VR = ST
 */
struct TestDataOK16
{
    boost::property_tree::ptree ptr;
 
    TestDataOK16()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,0081");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK16()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_16, TestDataOK16)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = dicomfieldcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::DicomField<EVR_ST>::Pointer dicomfieldST = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(dicomfieldST != NULL, true);
    }
}

/*************************** TEST OK 17 *******************************/
/**
 * Nominal test case: Constructor VR = TM
 */
struct TestDataOK17
{
    boost::property_tree::ptree ptr;
 
    TestDataOK17()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,0030");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK17()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_17, TestDataOK17)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = dicomfieldcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::DicomField<EVR_TM>::Pointer dicomfieldTM = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(dicomfieldTM != NULL, true);
    }
}

/*************************** TEST OK 18 *******************************/
/**
 * Nominal test case: Constructor VR = UI
 */
struct TestDataOK18
{
    boost::property_tree::ptree ptr;
 
    TestDataOK18()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,0016");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK18()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_18, TestDataOK18)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = dicomfieldcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::DicomField<EVR_UI>::Pointer dicomfieldUI = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(dicomfieldUI != NULL, true);
    }
}

/*************************** TEST OK 19 *******************************/
/**
 * Nominal test case: Constructor VR = UL
 */
struct TestDataOK19
{
    boost::property_tree::ptree ptr;
 
    TestDataOK19()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0018,6016");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK19()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_19, TestDataOK19)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = dicomfieldcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::DicomField<EVR_UL>::Pointer dicomfieldUL = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(dicomfieldUL != NULL, true);
    }
}

/*************************** TEST OK 20 *******************************/
/**
 * Nominal test case: Constructor VR = US
 */
struct TestDataOK20
{
    boost::property_tree::ptree ptr;
 
    TestDataOK20()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0008,1197");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK20()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_20, TestDataOK20)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = dicomfieldcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::DicomField<EVR_US>::Pointer dicomfieldUS = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(dicomfieldUS != NULL, true);
    }
}

/*************************** TEST OK 21 *******************************/
/**
 * Nominal test case: Constructor VR = UT
 */
struct TestDataOK21
{
    boost::property_tree::ptree ptr;
 
    TestDataOK21()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0028,7fe0");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK21()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_21, TestDataOK21)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = dicomfieldcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::DicomField<EVR_UT>::Pointer dicomfieldUT = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(dicomfieldUT != NULL, true);
    }
}

/*************************** TEST OK 22 *******************************/
/**
 * Nominal test case: Constructor VR = CS and use private dictionary
 */
struct TestDataOK22
{
    std::string dictionaryfile;
    boost::property_tree::ptree ptr;
 
    TestDataOK22()
    {
        dictionaryfile = "./temp_deleteelementcreator_test_ok_10.xml";
        
        // Create private dictionary
        std::ofstream myfile;
        myfile.open (dictionaryfile);
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
        
        dicomifier::Dictionaries::get_instance().ParsePrivateDictionary(dictionaryfile);

        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0023,xx02");
        dicomfieldnode.put("<xmlattr>.private_creator", "MyPrivateDict");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK22()
    {
        remove(dictionaryfile.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_22, TestDataOK22)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = dicomfieldcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::DicomField<EVR_CS>::Pointer dicomfieldCS = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(dicomfieldCS != NULL, true);
    }
}
 
/*************************** TEST OK 23 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
struct TestDataOK23
{
    boost::property_tree::ptree ptr;
 
    TestDataOK23()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0010,1002");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK23()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_23, TestDataOK23)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = SQ
        dicomifier::translator::Tag::Pointer objectSQ = dicomfieldcreator->Create(v, NULL, EVR_SQ);
        dicomifier::translator::DicomSequenceField::Pointer dicomfieldSQ = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomSequenceField>(objectSQ);
        BOOST_CHECK_EQUAL(dicomfieldSQ != NULL, true);
    }
}
 
/*************************** TEST OK 24 *******************************/
/**
 * Error test case: Create with VR = SQ with range
 */
struct TestDataOK24
{
    boost::property_tree::ptree ptr;
 
    TestDataOK24()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0010,1002");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.put("<xmlattr>.range", "0,2");
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK24()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_24, TestDataOK24)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = SQ
        dicomifier::translator::Tag::Pointer objectSQ = dicomfieldcreator->Create(v, NULL, EVR_SQ);
        dicomifier::translator::DicomSequenceField::Pointer dicomfieldSQ = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomSequenceField>(objectSQ);
        BOOST_CHECK_EQUAL(dicomfieldSQ != NULL, true);
    }
}
 
/*************************** TEST OK 25 *******************************/
/**
 * Error test case: Create with VR = SQ with perFrame
 */
struct TestDataOK25
{
    boost::property_tree::ptree ptr;
 
    TestDataOK25()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.tag", "0010,1002");
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.put("<xmlattr>.perframe", "true");
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataOK25()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_25, TestDataOK25)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = SQ
        dicomifier::translator::Tag::Pointer objectSQ = dicomfieldcreator->Create(v, NULL, EVR_SQ);
        dicomifier::translator::DicomSequenceField::Pointer dicomfieldSQ = 
                std::dynamic_pointer_cast<dicomifier::translator::DicomSequenceField>(objectSQ);
        BOOST_CHECK_EQUAL(dicomfieldSQ != NULL, true);
    }
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Missing mandatory attribut 'tag'
 */
 struct TestDataKO01
{
    boost::property_tree::ptree ptr;
 
    TestDataKO01()
    {
        boost::property_tree::ptree dicomfieldnode;
        boost::property_tree::ptree testfieldnode;
        dicomfieldnode.put("<xmlattr>.private_creator", "public");
        dicomfieldnode.add_child("TestField", testfieldnode);
        ptr.add_child("DicomField", dicomfieldnode);
    }
 
    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto dicomfieldcreator = dicomifier::translator::factory::DicomFieldCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(dicomfieldcreator->Create(v, NULL, EVR_AE), 
                            std::runtime_error);
    }
}
