/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleSOPClass
#include <boost/test/unit_test.hpp>

#include "dicom/SOPClass.h"

/******************************* TEST Nominal **********************************/
/**
 * Nominal test case: get_SOPClassUID_from_name
 */
BOOST_AUTO_TEST_CASE(get_SOPClassUID_from_name)
{
    BOOST_CHECK_EQUAL(
                dicomifier::get_SOPClassUID_from_name("VerificationSOPClass"),
                UID_VerificationSOPClass);

    BOOST_CHECK_EQUAL(
                dicomifier::get_SOPClassUID_from_name("MRImageStorage"),
                UID_MRImageStorage);

    BOOST_CHECK_EQUAL(
                dicomifier::get_SOPClassUID_from_name("EnhancedMRImageStorage"),
                UID_EnhancedMRImageStorage);

    BOOST_CHECK_EQUAL(
                dicomifier::get_SOPClassUID_from_name("MRSpectroscopyStorage"),
                UID_MRSpectroscopyStorage);

    BOOST_CHECK_EQUAL(
                dicomifier::get_SOPClassUID_from_name(UID_MRImageStorage),
                UID_MRImageStorage);
}
