/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleAny
#include <boost/test/unit_test.hpp>

#include "lib/core/conditions/Any.h"
#include "lib/core/conditions/False.h"
#include "lib/core/conditions/True.h"

struct TestData
{
    dicomifier::conditions::True::Pointer _true;
    dicomifier::conditions::False::Pointer _false;
 
    TestData()
    {
        _true = dicomifier::conditions::True::New();
        _false = dicomifier::conditions::False::New();
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TrueOrTrue, TestData)
{
    auto anyTT = dicomifier::conditions::Any::New(_true, _true);
    BOOST_CHECK_EQUAL(anyTT->eval(), true);
}
 
BOOST_FIXTURE_TEST_CASE(TrueOrFalse, TestData)
{
    auto anyTF = dicomifier::conditions::Any::New(_true, _false);
    BOOST_CHECK_EQUAL(anyTF->eval(), true);
}

BOOST_FIXTURE_TEST_CASE(FalseOrTrue, TestData)
{
    auto anyFT = dicomifier::conditions::Any::New(_false, _true);
    BOOST_CHECK_EQUAL(anyFT->eval(), true);
}

BOOST_FIXTURE_TEST_CASE(FalseOrFalse, TestData)
{
    auto anyFF = dicomifier::conditions::Any::New(_false, _false);
    BOOST_CHECK_EQUAL(anyFF->eval(), false);
}

