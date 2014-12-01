/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleEffectiveEchoTimeDcmFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/dicom/EffectiveEchoTimeDcmFieldCreator.h"
#include "translator/fields/dicom/EffectiveEchoTimeDcmField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
struct TestDataOK01
{
    boost::property_tree::ptree ptr;

    TestDataOK01()
    {
        boost::property_tree::ptree emptynode;
        ptr.add_child("EffectiveEchoTimeDcmField", emptynode);
    }

    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto effectiveechotimecreator = dicomifier::translator::factory::EffectiveEchoTimeDcmFieldCreator::New();

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = effectiveechotimecreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AE>::Pointer EffectiveEchoTimeAE =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeAE != NULL, true);

        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = effectiveechotimecreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AS>::Pointer EffectiveEchoTimeAS =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeAS != NULL, true);

        // Test VR = AT
        dicomifier::translator::Tag::Pointer objectAT = effectiveechotimecreator->Create(v, NULL, EVR_AT);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AT>::Pointer EffectiveEchoTimeAT =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_AT>>(objectAT);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeAT != NULL, true);

        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = effectiveechotimecreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_CS>::Pointer EffectiveEchoTimeCS =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeCS != NULL, true);

        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = effectiveechotimecreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DA>::Pointer EffectiveEchoTimeDA =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeDA != NULL, true);

        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = effectiveechotimecreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DS>::Pointer EffectiveEchoTimeDS =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeDS != NULL, true);

        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = effectiveechotimecreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DT>::Pointer EffectiveEchoTimeDT =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeDT != NULL, true);

        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = effectiveechotimecreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FL>::Pointer EffectiveEchoTimeFL =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeFL != NULL, true);

        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = effectiveechotimecreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FD>::Pointer EffectiveEchoTimeFD =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeFD != NULL, true);

        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = effectiveechotimecreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_IS>::Pointer EffectiveEchoTimeIS =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeIS != NULL, true);

        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = effectiveechotimecreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_LO>::Pointer EffectiveEchoTimeLO =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeLO != NULL, true);

        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = effectiveechotimecreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_LT>::Pointer EffectiveEchoTimeLT =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeLT != NULL, true);

        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = effectiveechotimecreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_PN>::Pointer EffectiveEchoTimePN =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(EffectiveEchoTimePN != NULL, true);

        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = effectiveechotimecreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SH>::Pointer EffectiveEchoTimeSH =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeSH != NULL, true);

        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = effectiveechotimecreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SL>::Pointer EffectiveEchoTimeSL =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeSL != NULL, true);

        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = effectiveechotimecreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SS>::Pointer EffectiveEchoTimeSS =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeSS != NULL, true);

        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = effectiveechotimecreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_ST>::Pointer EffectiveEchoTimeST =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeST != NULL, true);

        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = effectiveechotimecreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_TM>::Pointer EffectiveEchoTimeTM =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeTM != NULL, true);

        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = effectiveechotimecreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UI>::Pointer EffectiveEchoTimeUI =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeUI != NULL, true);

        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = effectiveechotimecreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UL>::Pointer EffectiveEchoTimeUL =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeUL != NULL, true);

        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = effectiveechotimecreator->Create(v, NULL, EVR_US);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_US>::Pointer EffectiveEchoTimeUS =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeUS != NULL, true);

        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = effectiveechotimecreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UT>::Pointer EffectiveEchoTimeUT =
                std::dynamic_pointer_cast<dicomifier::translator::EffectiveEchoTimeDcmField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(EffectiveEchoTimeUT != NULL, true);
    }
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK01)
{
    auto effectiveechotimecreator = dicomifier::translator::factory::EffectiveEchoTimeDcmFieldCreator::New();

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(effectiveechotimecreator->Create(v, NULL, EVR_SQ),
                            dicomifier::DicomifierException);
    }
}


