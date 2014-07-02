/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleEmptyElementCreator
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>

#include "core/Object.h"
#include "dicom/actions/EmptyElement.h"
#include "factory/dicom/actions/EmptyElementCreator.h"

struct TestData
{
    boost::property_tree::ptree ptr;
 
    TestData()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        dataset->saveFile("./tempfile", EXS_LittleEndianExplicit);
        delete dataset;
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("tag", "0010,0010");
        emptynode.put("dataset", "./tempfile");
        ptr.add_child("EmptyElement", emptynode);
    }
 
    ~TestData()
    {
        // Delete Test file
        remove("./tempfile");
    }
};

BOOST_FIXTURE_TEST_CASE(Creation, TestData)
{
    auto testempty = dicomifier::factory::EmptyElementCreator::New();
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = testempty->Create(v);
        
        dicomifier::actions::EmptyElement::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::EmptyElement>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}



