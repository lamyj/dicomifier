/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleComplexImageComponentDcmFieldCreator
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "translator/factory/fields/dicom/ComplexImageComponentDcmFieldCreator.h"
#include "translator/fields/dicom/ComplexImageComponentDcmField.h"

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
        ptr.add_child("ComplexImageComponentDcmField", emptynode);
    }

    ~TestDataOK01()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto compleximagecomponentcreator = dicomifier::translator::factory::ComplexImageComponentDcmFieldCreator::New();

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        // Test VR = AE
        dicomifier::translator::Tag::Pointer objectAE = compleximagecomponentcreator->Create(v, NULL, EVR_AE);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_AE>::Pointer compleximagecomponentAE =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_AE>>(objectAE);
        BOOST_CHECK_EQUAL(compleximagecomponentAE != NULL, true);

        // Test VR = AS
        dicomifier::translator::Tag::Pointer objectAS = compleximagecomponentcreator->Create(v, NULL, EVR_AS);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_AS>::Pointer compleximagecomponentAS =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_AS>>(objectAS);
        BOOST_CHECK_EQUAL(compleximagecomponentAS != NULL, true);

        // Test VR = AT
        dicomifier::translator::Tag::Pointer objectAT = compleximagecomponentcreator->Create(v, NULL, EVR_AT);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_AT>::Pointer compleximagecomponentAT =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_AT>>(objectAT);
        BOOST_CHECK_EQUAL(compleximagecomponentAT != NULL, true);

        // Test VR = CS
        dicomifier::translator::Tag::Pointer objectCS = compleximagecomponentcreator->Create(v, NULL, EVR_CS);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>::Pointer compleximagecomponentCS =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_CS>>(objectCS);
        BOOST_CHECK_EQUAL(compleximagecomponentCS != NULL, true);

        // Test VR = DA
        dicomifier::translator::Tag::Pointer objectDA = compleximagecomponentcreator->Create(v, NULL, EVR_DA);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_DA>::Pointer compleximagecomponentDA =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_DA>>(objectDA);
        BOOST_CHECK_EQUAL(compleximagecomponentDA != NULL, true);

        // Test VR = DS
        dicomifier::translator::Tag::Pointer objectDS = compleximagecomponentcreator->Create(v, NULL, EVR_DS);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_DS>::Pointer compleximagecomponentDS =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_DS>>(objectDS);
        BOOST_CHECK_EQUAL(compleximagecomponentDS != NULL, true);

        // Test VR = DT
        dicomifier::translator::Tag::Pointer objectDT = compleximagecomponentcreator->Create(v, NULL, EVR_DT);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_DT>::Pointer compleximagecomponentDT =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_DT>>(objectDT);
        BOOST_CHECK_EQUAL(compleximagecomponentDT != NULL, true);

        // Test VR = FL
        dicomifier::translator::Tag::Pointer objectFL = compleximagecomponentcreator->Create(v, NULL, EVR_FL);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_FL>::Pointer compleximagecomponentFL =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_FL>>(objectFL);
        BOOST_CHECK_EQUAL(compleximagecomponentFL != NULL, true);

        // Test VR = FD
        dicomifier::translator::Tag::Pointer objectFD = compleximagecomponentcreator->Create(v, NULL, EVR_FD);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_FD>::Pointer compleximagecomponentFD =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_FD>>(objectFD);
        BOOST_CHECK_EQUAL(compleximagecomponentFD != NULL, true);

        // Test VR = IS
        dicomifier::translator::Tag::Pointer objectIS = compleximagecomponentcreator->Create(v, NULL, EVR_IS);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_IS>::Pointer compleximagecomponentIS =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_IS>>(objectIS);
        BOOST_CHECK_EQUAL(compleximagecomponentIS != NULL, true);

        // Test VR = LO
        dicomifier::translator::Tag::Pointer objectLO = compleximagecomponentcreator->Create(v, NULL, EVR_LO);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_LO>::Pointer compleximagecomponentLO =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_LO>>(objectLO);
        BOOST_CHECK_EQUAL(compleximagecomponentLO != NULL, true);

        // Test VR = LT
        dicomifier::translator::Tag::Pointer objectLT = compleximagecomponentcreator->Create(v, NULL, EVR_LT);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_LT>::Pointer compleximagecomponentLT =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_LT>>(objectLT);
        BOOST_CHECK_EQUAL(compleximagecomponentLT != NULL, true);

        // Test VR = PN
        dicomifier::translator::Tag::Pointer objectPN = compleximagecomponentcreator->Create(v, NULL, EVR_PN);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_PN>::Pointer compleximagecomponentPN =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_PN>>(objectPN);
        BOOST_CHECK_EQUAL(compleximagecomponentPN != NULL, true);

        // Test VR = SH
        dicomifier::translator::Tag::Pointer objectSH = compleximagecomponentcreator->Create(v, NULL, EVR_SH);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_SH>::Pointer compleximagecomponentSH =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_SH>>(objectSH);
        BOOST_CHECK_EQUAL(compleximagecomponentSH != NULL, true);

        // Test VR = SL
        dicomifier::translator::Tag::Pointer objectSL = compleximagecomponentcreator->Create(v, NULL, EVR_SL);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_SL>::Pointer compleximagecomponentSL =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_SL>>(objectSL);
        BOOST_CHECK_EQUAL(compleximagecomponentSL != NULL, true);

        // Test VR = SS
        dicomifier::translator::Tag::Pointer objectSS = compleximagecomponentcreator->Create(v, NULL, EVR_SS);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_SS>::Pointer compleximagecomponentSS =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_SS>>(objectSS);
        BOOST_CHECK_EQUAL(compleximagecomponentSS != NULL, true);

        // Test VR = ST
        dicomifier::translator::Tag::Pointer objectST = compleximagecomponentcreator->Create(v, NULL, EVR_ST);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_ST>::Pointer compleximagecomponentST =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_ST>>(objectST);
        BOOST_CHECK_EQUAL(compleximagecomponentST != NULL, true);

        // Test VR = TM
        dicomifier::translator::Tag::Pointer objectTM = compleximagecomponentcreator->Create(v, NULL, EVR_TM);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_TM>::Pointer compleximagecomponentTM =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_TM>>(objectTM);
        BOOST_CHECK_EQUAL(compleximagecomponentTM != NULL, true);

        // Test VR = UI
        dicomifier::translator::Tag::Pointer objectUI = compleximagecomponentcreator->Create(v, NULL, EVR_UI);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_UI>::Pointer compleximagecomponentUI =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_UI>>(objectUI);
        BOOST_CHECK_EQUAL(compleximagecomponentUI != NULL, true);

        // Test VR = UL
        dicomifier::translator::Tag::Pointer objectUL = compleximagecomponentcreator->Create(v, NULL, EVR_UL);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_UL>::Pointer compleximagecomponentUL =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_UL>>(objectUL);
        BOOST_CHECK_EQUAL(compleximagecomponentUL != NULL, true);

        // Test VR = US
        dicomifier::translator::Tag::Pointer objectUS = compleximagecomponentcreator->Create(v, NULL, EVR_US);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_US>::Pointer compleximagecomponentUS =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_US>>(objectUS);
        BOOST_CHECK_EQUAL(compleximagecomponentUS != NULL, true);

        // Test VR = UT
        dicomifier::translator::Tag::Pointer objectUT = compleximagecomponentcreator->Create(v, NULL, EVR_UT);
        dicomifier::translator::ComplexImageComponentDcmField<EVR_UT>::Pointer compleximagecomponentUT =
                std::dynamic_pointer_cast<dicomifier::translator::ComplexImageComponentDcmField<EVR_UT>>(objectUT);
        BOOST_CHECK_EQUAL(compleximagecomponentUT != NULL, true);
    }
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Create with VR = SQ
 */
BOOST_FIXTURE_TEST_CASE(TEST_KO_01, TestDataOK01)
{
    auto compleximagecomponentcreator = dicomifier::translator::factory::ComplexImageComponentDcmFieldCreator::New();

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        BOOST_REQUIRE_THROW(compleximagecomponentcreator->Create(v, NULL, EVR_SQ),
                            dicomifier::DicomifierException);
    }
}


