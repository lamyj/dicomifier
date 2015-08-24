/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleDicom2Nifti
#include <boost/test/unit_test.hpp>

#include "core/DicomifierException.h"
#include "nifti/Dicom2Nifti.h"

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(Constructor)
{
    auto d2n = dicomifier::nifti::Dicom2Nifti::New();
    BOOST_CHECK(d2n != NULL);

    d2n = dicomifier::nifti::Dicom2Nifti::New("", "");
    BOOST_CHECK(d2n != NULL);
}

/*************************** TEST Nominal *******************************/
/**
 * Nominal test case: Get/Set
 */
BOOST_AUTO_TEST_CASE(Accessors)
{
    auto testdicom2nifti = dicomifier::nifti::Dicom2Nifti::New();

    BOOST_CHECK_EQUAL(testdicom2nifti->get_dicomDir(), "");
    BOOST_CHECK_EQUAL(testdicom2nifti->get_outputDir(), "");

    testdicom2nifti->set_dicomDir("inputDir");
    testdicom2nifti->set_outputDir("outputdir");

    BOOST_CHECK_EQUAL(testdicom2nifti->get_dicomDir(), "inputDir");
    BOOST_CHECK_EQUAL(testdicom2nifti->get_outputDir(), "outputdir");
}

/*************************** TEST Error *********************************/
/**
 * Error test case: Input directory is not available
 */
BOOST_AUTO_TEST_CASE(Missing_InputDirectory)
{
    auto d2n = dicomifier::nifti::Dicom2Nifti::New();
    BOOST_REQUIRE_THROW(d2n->run(), dicomifier::DicomifierException);
}
