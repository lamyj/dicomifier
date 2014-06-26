#define BOOST_TEST_MODULE ModuleAll
#include <boost/test/unit_test.hpp>

#include "core/conditions/All.h"
#include "core/conditions/False.h"
#include "core/conditions/True.h"

struct TestData
{
    router::conditions::True::Pointer _true;
    router::conditions::False::Pointer _false;
 
    TestData()
    {
        _true = router::conditions::True::New();
        _false = router::conditions::False::New();
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(TrueAndTrue, TestData)
{
    auto allTT = router::conditions::All::New(_true, _true);
    BOOST_CHECK_EQUAL(allTT->eval(), true);
}
 
BOOST_FIXTURE_TEST_CASE(TrueAndFalse, TestData)
{
    auto allTF = router::conditions::All::New(_true, _false);
    BOOST_CHECK_EQUAL(allTF->eval(), false);
}

BOOST_FIXTURE_TEST_CASE(FalseAndTrue, TestData)
{
    auto allFT = router::conditions::All::New(_false, _true);
    BOOST_CHECK_EQUAL(allFT->eval(), false);
}

BOOST_FIXTURE_TEST_CASE(FalseAndFalse, TestData)
{
    auto allFF = router::conditions::All::New(_false, _false);
    BOOST_CHECK_EQUAL(allFF->eval(), false);
}
