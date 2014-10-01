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

/*************************** TEST OK 01 *******************************/
/**
 * Nominal test case: Constructor
 */
BOOST_AUTO_TEST_CASE(TEST_OK_01)
{
    // String
    dicomifier::bruker::BrukerFieldData* field = 
        new dicomifier::bruker::BrukerFieldData("value");
    BOOST_CHECK_EQUAL(field->GetValueToString(), "value");
    delete field;
    
    // Int
    field = new dicomifier::bruker::BrukerFieldData(12);
    BOOST_CHECK_EQUAL(field->GetValueToString(), "12");
    delete field;
}

/*************************** TEST OK 02 *******************************/
/**
 * Nominal test case: Parse String value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_02)
{
    dicomifier::bruker::BrukerFieldData* field = 
            new dicomifier::bruker::BrukerFieldData();
    
    field->Parse("##$SUBJECT_id=( 60 )\n<Rat>");
    
    BOOST_CHECK_EQUAL(field->GetValueToString(true), "Rat");
    
    std::vector<std::string> vect = { "<Rat>" };
    BOOST_CHECK_EQUAL(field->GetStringValue() == vect, true);
    
    delete field;
}

/*************************** TEST OK 03 *******************************/
/**
 * Nominal test case: Parse Int value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_03)
{
    dicomifier::bruker::BrukerFieldData* field = 
            new dicomifier::bruker::BrukerFieldData();
    
    field->Parse("##$AdjStudyStateExpno=( 6 )\n1 1 1 3 3 3");
    
    BOOST_CHECK_EQUAL(field->GetValueToString(), "1\\1\\1\\3\\3\\3");
    
    std::vector<int> vect = { 1, 1, 1, 3, 3, 3 };
    BOOST_CHECK_EQUAL(field->GetIntValue() == vect, true);
    
    delete field;
}

/*************************** TEST OK 04 *******************************/
/**
 * Nominal test case: Parse Double value
 */
BOOST_AUTO_TEST_CASE(TEST_OK_04)
{
    dicomifier::bruker::BrukerFieldData* field = 
            new dicomifier::bruker::BrukerFieldData();
    
    field->Parse("##$NomDuTag=( 1 )\n26.5");
    
    BOOST_CHECK_EQUAL(field->GetValueToString(), "26.5");
    
    std::vector<double> vect = { 26.5 };
    BOOST_CHECK_EQUAL(field->GetDoubleValue() == vect, true);
    
    delete field;
}

/*************************** TEST OK 05 *******************************/
/**
 * Nominal test case: toString function
 */
BOOST_AUTO_TEST_CASE(TEST_OK_05)
{
    // Print String
    dicomifier::bruker::BrukerFieldData* field = 
            new dicomifier::bruker::BrukerFieldData();
    field->Parse("##$SUBJECT_id=( 60 )\n<Rat>");
    BOOST_CHECK_EQUAL(field->toString(), 
        "(DimensionNumber=0,DataType=string,NumberOfElements=1,DimensionNumberValue=[0,],StringValue=[<Rat>,])");
    delete field;
    
    // Print Int
    field = new dicomifier::bruker::BrukerFieldData();
    field->Parse("##$AdjStudyStateExpno=( 6 )\n1 1 1 3 3 3");
    BOOST_CHECK_EQUAL(field->toString(), 
        "(DimensionNumber=1,DataType=int,NumberOfElements=6,DimensionNumberValue=[0,6,],IntValue=[1,1,1,3,3,3,])");
    delete field;
    
    // Print Double
    field = new dicomifier::bruker::BrukerFieldData();
    field->Parse("##$NomDuTag=( 1 )\n26.5");
    BOOST_CHECK_EQUAL(field->toString(), 
        "(DimensionNumber=1,DataType=float,NumberOfElements=1,DimensionNumberValue=[0,1,],DoubleValue=[26.5,])");
    delete field;
}
