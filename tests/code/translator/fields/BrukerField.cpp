/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerField
#include <boost/test/unit_test.hpp>

#include "translator/fields/BrukerField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::BrukerField<EVR_AE>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldae->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::BrukerField<EVR_AS>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldas->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::BrukerField<EVR_CS>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldcs->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::BrukerField<EVR_DA>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldda->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::BrukerField<EVR_DS>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldds->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::BrukerField<EVR_DT>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfielddt->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::BrukerField<EVR_FL>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldfl->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::BrukerField<EVR_FD>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldfd->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::BrukerField<EVR_IS>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldis->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::BrukerField<EVR_LO>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldlo->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::BrukerField<EVR_LT>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldlt->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::BrukerField<EVR_PN>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldpn->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::BrukerField<EVR_SH>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldsh->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::BrukerField<EVR_SL>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldsl->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::BrukerField<EVR_SS>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldss->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::BrukerField<EVR_ST>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldst->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::BrukerField<EVR_TM>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldtm->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::BrukerField<EVR_UI>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldui->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::BrukerField<EVR_UL>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldul->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::BrukerField<EVR_US>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldus->get_class_type(), dicomifier::translator::ECT_BrukerField);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::BrukerField<EVR_UT>::New();
    // Pointer exists and class type is BrukerField
    BOOST_CHECK_EQUAL(testfieldut->get_class_type(), dicomifier::translator::ECT_BrukerField);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run
 */
struct TestDataOK02
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;
 
    TestDataOK02()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();
        
        filename = "./tmp_test_brukerfieldmodule";
        
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##fieldAE=ABCD\n";
        myfile << "##fieldAS=42Y\n";
        myfile << "##fieldCS=ABCD\n";
        myfile << "##fieldDA=<10122014>\n";
        myfile << "##fieldDS=1.23\n";
        myfile << "##fieldDT=<01234501122012>\n";
        myfile << "##fieldFL=1.23\n";
        myfile << "##fieldFD=1.23\n";
        myfile << "##fieldIS=123\n";
        myfile << "##fieldLO=ABCD\n";
        myfile << "##fieldLT=ABCD\n";
        myfile << "##fieldPN=ABCD\n";
        myfile << "##fieldSH=<1234>\n";
        myfile << "##fieldSL=12345678\n";
        myfile << "##fieldSS=2\n";
        myfile << "##fieldST=ABCD\n";
        myfile << "##fieldTM=<012345>\n";
        myfile << "##fieldUI=<1.2.3>\n";
        myfile << "##fieldUL=1234567890\n";
        myfile << "##fieldUS=456\n";
        myfile << "##fieldUT=ABCD\n";
        myfile << "##END=\n";
        myfile.close();
        
        brukerdataset->LoadFile(filename);
    }
 
    ~TestDataOK02()
    {
        remove(filename.c_str());
        delete brukerdataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::BrukerField<EVR_AE>::New("fieldAE");
    testfieldae->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldae->get_array().size(), 1);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::BrukerField<EVR_AS>::New("fieldAS");
    testfieldas->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldas->get_array().size(), 1);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::BrukerField<EVR_CS>::New("fieldCS");
    testfieldcs->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::BrukerField<EVR_DA>::New("fieldDA");
    testfieldda->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldda->get_array().size(), 1);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::BrukerField<EVR_DS>::New("fieldDS");
    testfieldds->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldds->get_array().size(), 1);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::BrukerField<EVR_DT>::New("fieldDT");
    testfielddt->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfielddt->get_array().size(), 1);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::BrukerField<EVR_FL>::New("fieldFL");
    testfieldfl->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldfl->get_array().size(), 1);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::BrukerField<EVR_FD>::New("fieldFD");
    testfieldfd->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldfd->get_array().size(), 1);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::BrukerField<EVR_IS>::New("fieldIS");
    testfieldis->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldis->get_array().size(), 1);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::BrukerField<EVR_LO>::New("fieldLO");
    testfieldlo->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldlo->get_array().size(), 1);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::BrukerField<EVR_LT>::New("fieldLT");
    testfieldlt->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldlt->get_array().size(), 1);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::BrukerField<EVR_PN>::New("fieldPN");
    testfieldpn->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldpn->get_array().size(), 1);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::BrukerField<EVR_SH>::New("fieldSH");
    testfieldsh->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldsh->get_array().size(), 1);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::BrukerField<EVR_SL>::New("fieldSL");
    testfieldsl->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldsl->get_array().size(), 1);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::BrukerField<EVR_SS>::New("fieldSS");
    testfieldss->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldss->get_array().size(), 1);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::BrukerField<EVR_ST>::New("fieldST");
    testfieldst->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldst->get_array().size(), 1);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::BrukerField<EVR_TM>::New("fieldTM");
    testfieldtm->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldtm->get_array().size(), 1);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::BrukerField<EVR_UI>::New("fieldUI");
    testfieldui->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldui->get_array().size(), 1);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::BrukerField<EVR_UL>::New("fieldUL");
    testfieldul->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldul->get_array().size(), 1);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::BrukerField<EVR_US>::New("fieldUS");
    testfieldus->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 1);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::BrukerField<EVR_UT>::New("fieldUT");
    testfieldut->run(brukerdataset, {}, NULL);
    BOOST_CHECK_EQUAL(testfieldut->get_array().size(), 1);
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Empty BrukerDataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto testfieldcs = dicomifier::translator::BrukerField<EVR_CS>::New();
    BOOST_REQUIRE_THROW(testfieldcs->run(NULL, {}, NULL), dicomifier::DicomifierException);
}
