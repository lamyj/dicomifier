/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleFactory
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include "core/Factory.h"
#include "core/Object.h"

BOOST_AUTO_TEST_CASE(Can_create)
{
	std::string const true_ = "True";
    BOOST_CHECK_EQUAL(dicomifier::Factory::get_instance().can_create(true_), true);
	std::string const badnode = "UnknownNode";
    BOOST_CHECK_EQUAL(dicomifier::Factory::get_instance().can_create(badnode), false);
}

BOOST_AUTO_TEST_CASE(Create)
{
	boost::property_tree::ptree emptynode;
	
	boost::property_tree::ptree ptrOK;
	ptrOK.add_child("True", emptynode);
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v1, ptrOK)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v1, NULL, NULL);
        BOOST_CHECK_EQUAL(object != NULL, true);
    }
    
	boost::property_tree::ptree ptrKO;
	ptrKO.add_child("UnknownNode", emptynode);
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v2, ptrKO)
    {
        dicomifier::Object::Pointer object = dicomifier::Factory::get_instance().create(v2, NULL, NULL);
        BOOST_CHECK_EQUAL(object == NULL, true);
    }
}
