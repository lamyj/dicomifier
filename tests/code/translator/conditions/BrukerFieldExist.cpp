/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerFieldExist
#include <boost/test/unit_test.hpp>

#include "translator/conditions/BrukerFieldExist.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor and eval
 */
struct TestDataOK01
{
    std::string filename;
    dicomifier::bruker::BrukerDataset* brukerdataset;
 
    TestDataOK01()
    {
        brukerdataset = new dicomifier::bruker::BrukerDataset();
        
        filename = "./tmp_test_brukerfieldexistmodule";
        
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldexistmodule\n";
        myfile << "##MyBrukerField=ABCD\n";
        myfile << "##END=\n";
        myfile.close();
        
        brukerdataset->LoadFile(filename);
    }
 
    ~TestDataOK01()
    {
        remove(filename.c_str());
        delete brukerdataset;
    }
};

BOOST_FIXTURE_TEST_CASE(TEST_OK_01, TestDataOK01)
{
    auto fieldexist = dicomifier::translator::BrukerFieldExist::New("MyBrukerField");
    BOOST_CHECK_EQUAL(fieldexist->eval(NULL, brukerdataset), true);
    
    auto fieldnotexist = dicomifier::translator::BrukerFieldExist::New("UnknownField");
    BOOST_CHECK_EQUAL(fieldnotexist->eval(NULL, brukerdataset), false);
}
 
/*************************** TEST KO 01 *******************************/
/**
 * Error test case: Missing mandatory attribut 'name'
 */
BOOST_AUTO_TEST_CASE(TEST_KO_01)
{
    auto fieldexist = dicomifier::translator::BrukerFieldExist::New();
    
    BOOST_REQUIRE_THROW(fieldexist->eval(NULL, NULL), 
                        dicomifier::DicomifierException);
}

