#define BOOST_TEST_MODULE ModuleAny
#include <boost/test/unit_test.hpp>

#include "core/conditions/Any.h"
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

