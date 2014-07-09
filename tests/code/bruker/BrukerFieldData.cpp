/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerFieldData
#include <boost/test/unit_test.hpp>

#include "bruker/BrukerFieldData.h"

BOOST_AUTO_TEST_CASE(Create)
{
    dicomifier::bruker::BrukerFieldData* field = new dicomifier::bruker::BrukerFieldData("value");
    
    BOOST_CHECK_EQUAL(field->GetValueToString(), "value");
    
    delete field;
    
    field = new dicomifier::bruker::BrukerFieldData(12);
    
    BOOST_CHECK_EQUAL(field->GetValueToString(), "12");
    
    delete field;
}

BOOST_AUTO_TEST_CASE(ParseString)
{
    dicomifier::bruker::BrukerFieldData* field = new dicomifier::bruker::BrukerFieldData();
    
    field->Parse("##$SUBJECT_id=( 60 )\n<Rat>");
    
    BOOST_CHECK_EQUAL(field->GetValueToString(true), "Rat");
    
    std::vector<std::string> vect = { "<Rat>" };
    BOOST_CHECK_EQUAL(field->GetStringValue() == vect, true);
    
    delete field;
}

BOOST_AUTO_TEST_CASE(ParseInt)
{
    dicomifier::bruker::BrukerFieldData* field = new dicomifier::bruker::BrukerFieldData();
    
    field->Parse("##$AdjStudyStateExpno=( 6 )\n1 1 1 3 3 3");
    
    BOOST_CHECK_EQUAL(field->GetValueToString(), "1\\1\\1\\3\\3\\3");
    
    std::vector<int> vect = { 1, 1, 1, 3, 3, 3 };
    BOOST_CHECK_EQUAL(field->GetIntValue() == vect, true);
    
    delete field;
}

BOOST_AUTO_TEST_CASE(ParseDouble)
{
    dicomifier::bruker::BrukerFieldData* field = new dicomifier::bruker::BrukerFieldData();
    
    field->Parse("##$NomDuTag=( 1 )\n26.5");
    
    BOOST_CHECK_EQUAL(field->GetValueToString(), "26.5");
    
    std::vector<double> vect = { 26.5 };
    BOOST_CHECK_EQUAL(field->GetDoubleValue() == vect, true);
    
    delete field;
}
