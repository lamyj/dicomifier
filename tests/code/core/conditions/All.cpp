#define BOOST_TEST_MODULE ModuleAll
#include <boost/test/unit_test.hpp>

#include "core/conditions/All.h"
#include "core/conditions/False.h"
#include "core/conditions/True.h"

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

BOOST_FIXTURE_TEST_CASE(TrueAndTrue, TestData)
{
    auto allTT = dicomifier::conditions::All::New(_true, _true);
    BOOST_CHECK_EQUAL(allTT->eval(), true);
}
 
BOOST_FIXTURE_TEST_CASE(TrueAndFalse, TestData)
{
    auto allTF = dicomifier::conditions::All::New(_true, _false);
    BOOST_CHECK_EQUAL(allTF->eval(), false);
}

BOOST_FIXTURE_TEST_CASE(FalseAndTrue, TestData)
{
    auto allFT = dicomifier::conditions::All::New(_false, _true);
    BOOST_CHECK_EQUAL(allFT->eval(), false);
}

BOOST_FIXTURE_TEST_CASE(FalseAndFalse, TestData)
{
    auto allFF = dicomifier::conditions::All::New(_false, _false);
    BOOST_CHECK_EQUAL(allFF->eval(), false);
}
