/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleRule
#include <boost/test/unit_test.hpp>

#include "core/Rule.h"
#include "core/conditions/False.h"
#include "core/conditions/True.h"
#include "core/actions/None.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    auto rule = dicomifier::Rule::New();

    BOOST_CHECK_EQUAL(rule != NULL, true);

    BOOST_CHECK_EQUAL(rule->Execute(), true);
}
 
/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Execute good condition
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto rule = dicomifier::Rule::New();
    
    rule->set_condition(dicomifier::conditions::True::New());
    rule->add_action(dicomifier::actions::None::New());

    BOOST_CHECK_EQUAL(rule->Execute(), true);
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Execute bad condition
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    auto rule = dicomifier::Rule::New();
    
    rule->set_condition(dicomifier::conditions::False::New());
    rule->add_action(dicomifier::actions::None::New());

    BOOST_CHECK_EQUAL(rule->Execute(), false);
}
