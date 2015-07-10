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
BOOST_AUTO_TEST_CASE(Constructor)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::BrukerField<EVR_AE>::New();
    // Pointer exists
    BOOST_CHECK(testfieldae != NULL);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::BrukerField<EVR_AS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldas != NULL);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::BrukerField<EVR_CS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldcs != NULL);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::BrukerField<EVR_DA>::New();
    // Pointer exists
    BOOST_CHECK(testfieldda != NULL);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::BrukerField<EVR_DS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldds != NULL);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::BrukerField<EVR_DT>::New();
    // Pointer exists
    BOOST_CHECK(testfielddt != NULL);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::BrukerField<EVR_FL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldfl != NULL);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::BrukerField<EVR_FD>::New();
    // Pointer exists
    BOOST_CHECK(testfieldfd != NULL);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::BrukerField<EVR_IS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldis != NULL);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::BrukerField<EVR_LO>::New();
    // Pointer exists
    BOOST_CHECK(testfieldlo != NULL);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::BrukerField<EVR_LT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldlt != NULL);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::BrukerField<EVR_PN>::New();
    // Pointer exists
    BOOST_CHECK(testfieldpn != NULL);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::BrukerField<EVR_SH>::New();
    // Pointer exists
    BOOST_CHECK(testfieldsh != NULL);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::BrukerField<EVR_SL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldsl != NULL);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::BrukerField<EVR_SS>::New();
    // Pointer exists
    BOOST_CHECK(testfieldss != NULL);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::BrukerField<EVR_ST>::New();
    // Pointer exists
    BOOST_CHECK(testfieldst != NULL);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::BrukerField<EVR_TM>::New();
    // Pointer exists
    BOOST_CHECK(testfieldtm != NULL);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::BrukerField<EVR_UI>::New();
    // Pointer exists
    BOOST_CHECK(testfieldui != NULL);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::BrukerField<EVR_UL>::New();
    // Pointer exists
    BOOST_CHECK(testfieldul != NULL);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::BrukerField<EVR_US>::New();
    // Pointer exists
    BOOST_CHECK(testfieldus != NULL);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::BrukerField<EVR_UT>::New();
    // Pointer exists
    BOOST_CHECK(testfieldut != NULL);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Run
 */
struct TestDataOK02
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;
 
    TestDataOK02() : filename("./tmp_test_brukerfieldmodule")
    {
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
        
        brukerdataset.load(filename);
    }
 
    ~TestDataOK02()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_02, TestDataOK02)
{
    // Test VR = AE
    auto testfieldae = dicomifier::translator::BrukerField<EVR_AE>::New("fieldAE");
    testfieldae->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldae->get_array().size(), 1);
    
    // Test VR = AS
    auto testfieldas = dicomifier::translator::BrukerField<EVR_AS>::New("fieldAS");
    testfieldas->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldas->get_array().size(), 1);
    
    // Test VR = AT => Not implemented
    
    // Test VR = CS
    auto testfieldcs = dicomifier::translator::BrukerField<EVR_CS>::New("fieldCS");
    testfieldcs->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    
    // Test VR = DA
    auto testfieldda = dicomifier::translator::BrukerField<EVR_DA>::New("fieldDA");
    testfieldda->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldda->get_array().size(), 1);
    
    // Test VR = DS
    auto testfieldds = dicomifier::translator::BrukerField<EVR_DS>::New("fieldDS");
    testfieldds->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldds->get_array().size(), 1);
    
    // Test VR = DT
    auto testfielddt = dicomifier::translator::BrukerField<EVR_DT>::New("fieldDT");
    testfielddt->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfielddt->get_array().size(), 1);
    
    // Test VR = FL
    auto testfieldfl = dicomifier::translator::BrukerField<EVR_FL>::New("fieldFL");
    testfieldfl->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldfl->get_array().size(), 1);
    
    // Test VR = FD
    auto testfieldfd = dicomifier::translator::BrukerField<EVR_FD>::New("fieldFD");
    testfieldfd->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldfd->get_array().size(), 1);
    
    // Test VR = IS
    auto testfieldis = dicomifier::translator::BrukerField<EVR_IS>::New("fieldIS");
    testfieldis->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldis->get_array().size(), 1);
    
    // Test VR = LO
    auto testfieldlo = dicomifier::translator::BrukerField<EVR_LO>::New("fieldLO");
    testfieldlo->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldlo->get_array().size(), 1);
    
    // Test VR = LT
    auto testfieldlt = dicomifier::translator::BrukerField<EVR_LT>::New("fieldLT");
    testfieldlt->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldlt->get_array().size(), 1);
    
    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented
    
    // Test VR = PN
    auto testfieldpn = dicomifier::translator::BrukerField<EVR_PN>::New("fieldPN");
    testfieldpn->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldpn->get_array().size(), 1);
    
    // Test VR = SH
    auto testfieldsh = dicomifier::translator::BrukerField<EVR_SH>::New("fieldSH");
    testfieldsh->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldsh->get_array().size(), 1);
    
    // Test VR = SL
    auto testfieldsl = dicomifier::translator::BrukerField<EVR_SL>::New("fieldSL");
    testfieldsl->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldsl->get_array().size(), 1);
    
    // Test VR = SQ => Not implemented
    
    // Test VR = SS
    auto testfieldss = dicomifier::translator::BrukerField<EVR_SS>::New("fieldSS");
    testfieldss->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldss->get_array().size(), 1);
    
    // Test VR = ST
    auto testfieldst = dicomifier::translator::BrukerField<EVR_ST>::New("fieldST");
    testfieldst->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldst->get_array().size(), 1);
    
    // Test VR = TM
    auto testfieldtm = dicomifier::translator::BrukerField<EVR_TM>::New("fieldTM");
    testfieldtm->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldtm->get_array().size(), 1);
    
    // Test VR = UI
    auto testfieldui = dicomifier::translator::BrukerField<EVR_UI>::New("fieldUI");
    testfieldui->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldui->get_array().size(), 1);
    
    // Test VR = UL
    auto testfieldul = dicomifier::translator::BrukerField<EVR_UL>::New("fieldUL");
    testfieldul->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldul->get_array().size(), 1);
    
    // Test VR = UN => Not implemented
    
    // Test VR = US
    auto testfieldus = dicomifier::translator::BrukerField<EVR_US>::New("fieldUS");
    testfieldus->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 1);
    
    // Test VR = UT
    auto testfieldut = dicomifier::translator::BrukerField<EVR_UT>::New("fieldUT");
    testfieldut->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldut->get_array().size(), 1);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Run
 */
struct TestDataOK03
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;

    TestDataOK03() : filename("./tmp_test_brukerfieldmodule")
    {
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldmodule\n";
        myfile << "##$fieldAE=( 3 )ABCD EFGH IJKL\n";
        myfile << "##$fieldAS=( 3, 64 )<42Y> <32Y> <22Y>\n";
        myfile << "##$fieldCS=( 3, 64 )<ABCD> <EFGH> <IJKL>\n";
        myfile << "##$fieldDA=( 3, 64 )<10122014> <11122014> <12122014>\n";
        myfile << "##$fieldDS=( 3 )1.23 2.24 3.25\n";
        myfile << "##$fieldDT=( 3, 64 )<01234501122012> <02234501122013> <03234501122014>\n";
        myfile << "##$fieldFL=( 3 )1.23 2.24 3.25\n";
        myfile << "##$fieldFD=( 3 )1.23 2.24 3.25\n";
        myfile << "##$fieldIS=( 3 )123 456 789\n";
        myfile << "##$fieldLO=( 3 )ABCD EFGH IJKL\n";
        myfile << "##$fieldLT=( 3 )ABCD EFGH IJKL\n";
        myfile << "##$fieldPN=( 3 )ABCD EFGH IJKL\n";
        myfile << "##$fieldSH=( 3, 64 )<1234> <4567> <7890>\n";
        myfile << "##$fieldSL=( 3 )12345678 12445789 13546879\n";
        myfile << "##$fieldSS=( 3 )2 4 6\n";
        myfile << "##$fieldST=( 3 )ABCD EFGH IJKL\n";
        myfile << "##$fieldTM=( 3, 64 )<124554> <112352> <102615>\n";
        myfile << "##$fieldUI=( 3, 64 )<1.2.3> <4.5.6> <7.8.9>\n";
        //myfile << "##$fieldUL=( 3 )1324657980 2315648970 3126459780\n"; // Warning: for 32bits, cannot test value > 2^31
        myfile << "##$fieldUL=( 3 )1324657980 1324655980 1324657780\n";
        myfile << "##$fieldUS=( 3 )123 456 789\n";
        myfile << "##$fieldUT=( 3 )ABCD EFGH IJKL\n";
        myfile << "##END=\n";
        myfile.close();

        brukerdataset.load(filename);
    }

    ~TestDataOK03()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(Run_Range, TestDataOK03)
{
    // Test VR = AE
    auto testfieldae =
            dicomifier::translator::BrukerField<EVR_AE>::New("fieldAE",
                                                             dicomifier::Range(1,2));
    testfieldae->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldae->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldae->get_array()[0], "EFGH");

    // Test VR = AS
    auto testfieldas =
            dicomifier::translator::BrukerField<EVR_AS>::New("fieldAS",
                                                             dicomifier::Range(1,2));
    testfieldas->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldas->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldas->get_array()[0], "32Y");

    // Test VR = AT => Not implemented

    // Test VR = CS
    auto testfieldcs =
            dicomifier::translator::BrukerField<EVR_CS>::New("fieldCS",
                                                             dicomifier::Range(1,2));
    testfieldcs->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldcs->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldcs->get_array()[0], "EFGH");

    // Test VR = DA
    auto testfieldda =
            dicomifier::translator::BrukerField<EVR_DA>::New("fieldDA",
                                                             dicomifier::Range(1,2));
    testfieldda->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldda->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldda->get_array()[0], "11122014");

    // Test VR = DS
    auto testfieldds =
            dicomifier::translator::BrukerField<EVR_DS>::New("fieldDS",
                                                             dicomifier::Range(1,2));
    testfieldds->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldds->get_array().size(), 1);
    BOOST_CHECK_CLOSE(testfieldds->get_array()[0], 2.24, 0.001);

    // Test VR = DT
    auto testfielddt =
            dicomifier::translator::BrukerField<EVR_DT>::New("fieldDT",
                                                             dicomifier::Range(1,2));
    testfielddt->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfielddt->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfielddt->get_array()[0], "02234501122013");

    // Test VR = FL
    auto testfieldfl =
            dicomifier::translator::BrukerField<EVR_FL>::New("fieldFL",
                                                             dicomifier::Range(1,2));
    testfieldfl->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldfl->get_array().size(), 1);
    BOOST_CHECK_CLOSE(testfieldfl->get_array()[0], 2.24, 0.001);

    // Test VR = FD
    auto testfieldfd =
            dicomifier::translator::BrukerField<EVR_FD>::New("fieldFD",
                                                             dicomifier::Range(1,2));
    testfieldfd->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldfd->get_array().size(), 1);
    BOOST_CHECK_CLOSE(testfieldfd->get_array()[0], 2.24, 0.001);

    // Test VR = IS
    auto testfieldis =
            dicomifier::translator::BrukerField<EVR_IS>::New("fieldIS",
                                                             dicomifier::Range(1,2));
    testfieldis->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldis->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldis->get_array()[0], 456);

    // Test VR = LO
    auto testfieldlo =
            dicomifier::translator::BrukerField<EVR_LO>::New("fieldLO",
                                                             dicomifier::Range(1,2));
    testfieldlo->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldlo->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldlo->get_array()[0], "EFGH");

    // Test VR = LT
    auto testfieldlt =
            dicomifier::translator::BrukerField<EVR_LT>::New("fieldLT",
                                                             dicomifier::Range(1,2));
    testfieldlt->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldlt->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldlt->get_array()[0], "EFGH");

    // Test VR = OB => Not implemented
    // Test VR = OD => Not implemented
    // Test VR = OF => Not implemented
    // Test VR = OW => Not implemented

    // Test VR = PN
    auto testfieldpn =
            dicomifier::translator::BrukerField<EVR_PN>::New("fieldPN",
                                                             dicomifier::Range(1,2));
    testfieldpn->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldpn->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldpn->get_array()[0], "EFGH");

    // Test VR = SH
    auto testfieldsh =
            dicomifier::translator::BrukerField<EVR_SH>::New("fieldSH",
                                                             dicomifier::Range(1,2));
    testfieldsh->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldsh->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldsh->get_array()[0], "4567");

    // Test VR = SL
    auto testfieldsl =
            dicomifier::translator::BrukerField<EVR_SL>::New("fieldSL",
                                                             dicomifier::Range(1,2));
    testfieldsl->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldsl->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldsl->get_array()[0], 12445789);

    // Test VR = SQ => Not implemented

    // Test VR = SS
    auto testfieldss =
            dicomifier::translator::BrukerField<EVR_SS>::New("fieldSS",
                                                             dicomifier::Range(1,2));
    testfieldss->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldss->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldss->get_array()[0], 4);

    // Test VR = ST
    auto testfieldst =
            dicomifier::translator::BrukerField<EVR_ST>::New("fieldST",
                                                             dicomifier::Range(1,2));
    testfieldst->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldst->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldst->get_array()[0], "EFGH");

    // Test VR = TM
    auto testfieldtm =
            dicomifier::translator::BrukerField<EVR_TM>::New("fieldTM",
                                                             dicomifier::Range(1,2));
    testfieldtm->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldtm->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldtm->get_array()[0], "112352");

    // Test VR = UI
    auto testfieldui =
            dicomifier::translator::BrukerField<EVR_UI>::New("fieldUI",
                                                             dicomifier::Range(1,2));
    testfieldui->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldui->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldui->get_array()[0], "4.5.6");

    // Test VR = UL
    auto testfieldul =
            dicomifier::translator::BrukerField<EVR_UL>::New("fieldUL",
                                                             dicomifier::Range(1,2));
    testfieldul->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldul->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldul->get_array()[0], 1324655980);

    // Test VR = UN => Not implemented

    // Test VR = US
    auto testfieldus =
            dicomifier::translator::BrukerField<EVR_US>::New("fieldUS",
                                                             dicomifier::Range(1,2));
    testfieldus->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldus->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldus->get_array()[0], 456);

    // Test VR = UT
    auto testfieldut =
            dicomifier::translator::BrukerField<EVR_UT>::New("fieldUT",
                                                             dicomifier::Range(1,2));
    testfieldut->run(&brukerdataset, dicomifier::FrameIndexGenerator({}), NULL);
    BOOST_CHECK_EQUAL(testfieldut->get_array().size(), 1);
    BOOST_CHECK_EQUAL(testfieldut->get_array()[0], "EFGH");
}

/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Empty Dataset
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto testfieldcs = dicomifier::translator::BrukerField<EVR_CS>::New();
    BOOST_REQUIRE_THROW(testfieldcs->run(NULL,
                                         dicomifier::FrameIndexGenerator({}),
                                         NULL),
                        dicomifier::DicomifierException);
}
