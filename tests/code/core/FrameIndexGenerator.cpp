/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleFrameIndexGenerator
#include <boost/test/unit_test.hpp>

#include "core/FrameIndexGenerator.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor / Destructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    auto generator = new dicomifier::FrameIndexGenerator({10, 2, 20});
    BOOST_CHECK_EQUAL(generator != NULL, true);
    delete generator;
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: One value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    auto generator = new dicomifier::FrameIndexGenerator({20});
    
    BOOST_CHECK_EQUAL(generator->done(), true);
    
    BOOST_CHECK_EQUAL(generator->next().size(), 1);
    BOOST_CHECK_EQUAL(generator->next()[0], 20);
    
    delete generator;
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Two value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    auto generator = new dicomifier::FrameIndexGenerator({2,2});
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    std::vector<int> values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 2);
    BOOST_CHECK_EQUAL(values[0], 0);
    BOOST_CHECK_EQUAL(values[1], 2);
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 2);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(values[1], 2);
    
    BOOST_CHECK_EQUAL(generator->done(), true);
    
    delete generator;
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Multiple (> 2) value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    auto generator = new dicomifier::FrameIndexGenerator({2,2,2,8});
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    std::vector<int> values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 4);
    BOOST_CHECK_EQUAL(values[0], 0);
    BOOST_CHECK_EQUAL(values[1], 0);
    BOOST_CHECK_EQUAL(values[2], 0);
    BOOST_CHECK_EQUAL(values[3], 8);
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 4);
    BOOST_CHECK_EQUAL(values[0], 0);
    BOOST_CHECK_EQUAL(values[1], 0);
    BOOST_CHECK_EQUAL(values[2], 1);
    BOOST_CHECK_EQUAL(values[3], 8);
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 4);
    BOOST_CHECK_EQUAL(values[0], 0);
    BOOST_CHECK_EQUAL(values[1], 1);
    BOOST_CHECK_EQUAL(values[2], 0);
    BOOST_CHECK_EQUAL(values[3], 8);
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 4);
    BOOST_CHECK_EQUAL(values[0], 0);
    BOOST_CHECK_EQUAL(values[1], 1);
    BOOST_CHECK_EQUAL(values[2], 1);
    BOOST_CHECK_EQUAL(values[3], 8);
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 4);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(values[1], 0);
    BOOST_CHECK_EQUAL(values[2], 0);
    BOOST_CHECK_EQUAL(values[3], 8);
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 4);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(values[1], 0);
    BOOST_CHECK_EQUAL(values[2], 1);
    BOOST_CHECK_EQUAL(values[3], 8);
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 4);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(values[1], 1);
    BOOST_CHECK_EQUAL(values[2], 0);
    BOOST_CHECK_EQUAL(values[3], 8);
    
    BOOST_CHECK_EQUAL(generator->done(), false);
    
    values = generator->next();
    BOOST_CHECK_EQUAL(values.size(), 4);
    BOOST_CHECK_EQUAL(values[0], 1);
    BOOST_CHECK_EQUAL(values[1], 1);
    BOOST_CHECK_EQUAL(values[2], 1);
    BOOST_CHECK_EQUAL(values[3], 8);
    
    BOOST_CHECK_EQUAL(generator->done(), true);
    
    delete generator;
}
