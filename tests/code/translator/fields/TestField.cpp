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

/****************************** TEST Nominal *********************************/
/**
 * Nominal test case: Constructor and Run
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    // creation: no error expected
    auto testfield = dicomifier::translator::TestField::New();
    
    // Pointer exists
    BOOST_CHECK(testfield != NULL);
    
    // no error expected
    testfield->run(NULL, dicomifier::FrameIndexGenerator({}), NULL);
}
