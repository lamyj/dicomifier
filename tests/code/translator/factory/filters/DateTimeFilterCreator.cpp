/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDateTimeFilterCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/filters/DateTimeFilterCreator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;

    TestDataOK01()
    {
        boost::property_tree::ptree datetimefilternode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        datetimefilternode.add_child("ConstantField", constantfield);
        datetimefilternode.put("<xmlattr>.outputformat", "%H%M%S");
        ptr.add_child("DateTimeFilter", datetimefilternode);
    }

    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto datetimefiltercreator = dicomifier::translator::factory::DateTimeFilterCreator::New();

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = datetimefiltercreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::DateTimeFilter<EVR_AE>::Pointer datetimefilterAE =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(datetimefilterAE != NULL, true);

        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = datetimefiltercreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::DateTimeFilter<EVR_AS>::Pointer datetimefilterAS =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(datetimefilterAS != NULL, true);

        // Test VR = AT
        dicomifier::translator::Tag::Pointer objectAT = datetimefiltercreator->Create(v, NULL, EVR_AT);
        dicomifier::translator::DateTimeFilter<EVR_AT>::Pointer datetimefilterAT =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_AT>>(objectAT);
        BOOST_CHECK_EQUAL(datetimefilterAT != NULL, true);

        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = datetimefiltercreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::DateTimeFilter<EVR_CS>::Pointer datetimefilterCS =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(datetimefilterCS != NULL, true);

        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = datetimefiltercreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::DateTimeFilter<EVR_DA>::Pointer datetimefilterDA =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(datetimefilterDA != NULL, true);

        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = datetimefiltercreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::DateTimeFilter<EVR_DS>::Pointer datetimefilterDS =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(datetimefilterDS != NULL, true);

        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = datetimefiltercreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::DateTimeFilter<EVR_DT>::Pointer datetimefilterDT =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(datetimefilterDT != NULL, true);

        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = datetimefiltercreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::DateTimeFilter<EVR_FL>::Pointer datetimefilterFL =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(datetimefilterFL != NULL, true);

        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = datetimefiltercreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::DateTimeFilter<EVR_FD>::Pointer datetimefilterFD =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(datetimefilterFD != NULL, true);

        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = datetimefiltercreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::DateTimeFilter<EVR_IS>::Pointer datetimefilterIS =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(datetimefilterIS != NULL, true);

        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = datetimefiltercreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::DateTimeFilter<EVR_LO>::Pointer datetimefilterLO =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(datetimefilterLO != NULL, true);

        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = datetimefiltercreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::DateTimeFilter<EVR_LT>::Pointer datetimefilterLT =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(datetimefilterLT != NULL, true);

        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = datetimefiltercreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::DateTimeFilter<EVR_PN>::Pointer datetimefilterPN =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(datetimefilterPN != NULL, true);

        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = datetimefiltercreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::DateTimeFilter<EVR_SH>::Pointer datetimefilterSH =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(datetimefilterSH != NULL, true);

        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = datetimefiltercreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::DateTimeFilter<EVR_SL>::Pointer datetimefilterSL =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(datetimefilterSL != NULL, true);

        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = datetimefiltercreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::DateTimeFilter<EVR_SS>::Pointer datetimefilterSS =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(datetimefilterSS != NULL, true);

        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = datetimefiltercreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::DateTimeFilter<EVR_ST>::Pointer datetimefilterST =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(datetimefilterST != NULL, true);

        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = datetimefiltercreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::DateTimeFilter<EVR_TM>::Pointer datetimefilterTM =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(datetimefilterTM != NULL, true);

        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = datetimefiltercreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::DateTimeFilter<EVR_UI>::Pointer datetimefilterUI =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(datetimefilterUI != NULL, true);

        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = datetimefiltercreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::DateTimeFilter<EVR_UL>::Pointer datetimefilterUL =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(datetimefilterUL != NULL, true);

        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = datetimefiltercreator->Create(v, NULL, EVR_US);
        dicomifier::translator::DateTimeFilter<EVR_US>::Pointer datetimefilterUS =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(datetimefilterUS != NULL, true);

        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = datetimefiltercreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::DateTimeFilter<EVR_UT>::Pointer datetimefilterUT =
                std::dynamic_pointer_cast<dicomifier::translator::DateTimeFilter<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(datetimefilterUT != NULL, true);
    }
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create SQ element
 */
struct TestDataKO01
{
    boost::property_tree::ptree ptr;

    TestDataKO01()
    {
        boost::property_tree::ptree datetimefilternode;
        boost::property_tree::ptree dicomfield;
        dicomfield.put("<xmlattr>.tag", "0018,9114");
        dicomfield.put("<xmlattr>.keyword", "MREchoSequence");
        dicomfield.put("<xmlattr>.vr", "SQ");
        datetimefilternode.add_child("DicomField", dicomfield);
        datetimefilternode.put("<xmlattr>.outputformat", "%H%M%S");
        ptr.add_child("DateTimeFilter", datetimefilternode);
    }

    ~TestDataKO01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataKO01)
{
    auto datetimefiltercreator =
        dicomifier::translator::factory::DateTimeFilterCreator::New();

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = SQ
        BOOST_REQUIRE_THROW(datetimefiltercreator->Create(v, NULL, EVR_SQ),
                            dicomifier::DicomifierException);
    }
}

/*************************** TEST KO 02 *******************************/
/**
 * Error test case: Missing mandatory attribut 'outputformat'
 */
struct TestDataKO02
{
    boost::property_tree::ptree ptr;

    TestDataKO02()
    {
        boost::property_tree::ptree datetimefilternode;
        boost::property_tree::ptree constantfield;
        constantfield.put("<xmlattr>.values", "1");
        datetimefilternode.add_child("ConstantField", constantfield);
        ptr.add_child("DateTimeFilter", datetimefilternode);
    }

    ~TestDataKO02()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_KO_02, TestDataKO02)
{
    auto datetimefiltercreator = dicomifier::translator::factory::DateTimeFilterCreator::New();

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = DA
        BOOST_REQUIRE_THROW(datetimefiltercreator->Create(v, NULL, EVR_DA),
                            std::runtime_error);
    }
}
