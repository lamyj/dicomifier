/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDicomifierException
#include <boost/test/unit_test.hpp>

#include "core/DicomifierException.h"

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Throw
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    BOOST_REQUIRE_THROW(throw dicomifier::DicomifierException("Error"), 
                        dicomifier::DicomifierException);
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Message
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    try
    {
        throw dicomifier::DicomifierException("Error");
    }
    catch (dicomifier::DicomifierException& exc)
    {
        BOOST_CHECK_EQUAL(exc.what(), "Error");
    }
}
