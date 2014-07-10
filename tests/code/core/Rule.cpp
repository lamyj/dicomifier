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
#include "core/conditions/True.h"
#include "core/actions/None.h"

BOOST_AUTO_TEST_CASE(Execute)
{
    auto rule = dicomifier::Rule::New();

    rule->set_condition(dicomifier::conditions::True::New());
    rule->add_action(dicomifier::actions::None::New());

    rule->Execute();
}
 
