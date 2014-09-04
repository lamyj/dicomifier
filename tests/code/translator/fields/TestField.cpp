/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleTestField
#include <boost/test/unit_test.hpp>

#include "translator/fields/TestField.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor + get_class_type + run
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // creation: no error expected
    auto testfield = dicomifier::translator::TestField::New();
    
    // Pointer exists and class type is TestField
    BOOST_CHECK_EQUAL(testfield->get_class_type(), dicomifier::translator::ECT_TestField);
    
    // no error expected
    testfield->run(NULL, NULL);
}
