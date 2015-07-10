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

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: eval
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    auto brukerfieldexist =
            dicomifier::translator::BrukerFieldExist::New("MyBrukerField");
    BOOST_REQUIRE(brukerfieldexist != NULL);
}

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Eval
 */
struct TestDataOK01
{
    std::string filename;
    dicomifier::bruker::Dataset brukerdataset;
 
    TestDataOK01() : filename("./tmp_test_brukerfieldexistmodule")
    {
        std::ofstream myfile;
        myfile.open(filename);
        myfile << "##TITLE=tmp_test_brukerfieldexistmodule\n";
        myfile << "##MyBrukerField=ABCD\n";
        myfile << "##END=\n";
        myfile.close();
        
        brukerdataset.load(filename);
    }
 
    ~TestDataOK01()
    {
        remove(filename.c_str());
    }
};

BOOST_FIXTURE_TEST_CASE(Eval, TestDataOK01)
{
    auto fieldexist =
            dicomifier::translator::BrukerFieldExist::New("MyBrukerField");
    BOOST_REQUIRE(fieldexist->eval(NULL, &brukerdataset));
    
    auto fieldnotexist =
            dicomifier::translator::BrukerFieldExist::New("UnknownField");
    BOOST_REQUIRE(!fieldnotexist->eval(NULL, &brukerdataset));
}

/****************************** TEST Error ***********************************/
/**
 * Error test case: Missing mandatory attribut 'name'
 */
BOOST_AUTO_TEST_CASE(MissingAttributeName)
{
    auto fieldexist = dicomifier::translator::BrukerFieldExist::New();
    
    BOOST_REQUIRE_THROW(fieldexist->eval(NULL, NULL), 
                        dicomifier::DicomifierException);
}

