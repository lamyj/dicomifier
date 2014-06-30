/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleNot
#include <boost/test/unit_test.hpp>

#include "lib/core/conditions/False.h"
#include "lib/core/conditions/Not.h"
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

BOOST_FIXTURE_TEST_CASE(NotTrue, TestData)
{
    auto nottrue = dicomifier::conditions::Not::New(_true);
    BOOST_CHECK_EQUAL(nottrue->eval(), false);
}
 
BOOST_FIXTURE_TEST_CASE(NotFalse, TestData)
{
    auto notfalse = dicomifier::conditions::Not::New(_false);
    BOOST_CHECK_EQUAL(notfalse->eval(), true);
}
