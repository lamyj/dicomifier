#define BOOST_TEST_MODULE ModuleNot
#include <boost/test/unit_test.hpp>

#include "core/conditions/Not.h"
#include "core/conditions/True.h"
#include "core/conditions/False.h"

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

BOOST_FIXTURE_TEST_SUITE(Not, TestData)
 
BOOST_AUTO_TEST_CASE(NotTrue)
{
    auto nottrue = router::conditions::Not::New(_true);
    BOOST_CHECK_EQUAL(nottrue->eval(), false);
}
 
BOOST_AUTO_TEST_CASE(NotFalse)
{
    auto notfalse = router::conditions::Not::New(_false);
    BOOST_CHECK_EQUAL(notfalse->eval(), true);
}
 
BOOST_AUTO_TEST_SUITE_END()