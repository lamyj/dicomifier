/*************************************************************************
 * creaBruker - Copyright (C) CREATIS
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#define BOOST_TEST_MODULE ModuleBrukerDataset
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "core/Object.h"
#include "bruker/actions/EnhanceBrukerDicom.h"
#include "factory/bruker/actions/EnhanceBrukerDicomCreator.h"

struct TestData
{
    boost::property_tree::ptree ptr;
    std::shared_ptr<dicomifier::factory::CreatorBase::InOutPutType> inputs;
 
    TestData()
    {
        // Create Test file
        DcmDataset* dataset = new DcmDataset();
        OFString name("John");
        dataset->putAndInsertOFStringArray(DCM_PatientName, name, true);
        
        // Create XML tree
        boost::property_tree::ptree emptynode;
        emptynode.put("<xmlattr>.brukerdir", "#inputdir");
        emptynode.put("<xmlattr>.dataset", "#input");
        ptr.add_child("EnhanceBrukerDicom", emptynode);
        
        std::string text = "./temp";
        
        inputs = std::make_shared<dicomifier::factory::CreatorBase::InOutPutType>();
        inputs->insert(std::pair<std::string, boost::any>("input", boost::any(dataset)));
        inputs->insert(std::pair<std::string, boost::any>("inputdir", boost::any(text)));
    }
 
    ~TestData()
    {
    }
};

BOOST_FIXTURE_TEST_CASE(Creation, TestData)
{
    auto test = dicomifier::factory::EnhanceBrukerDicomCreator::New();
    test->set_inputs(inputs);
    
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, ptr)
    {
        dicomifier::Object::Pointer object = test->Create(v);
        
        dicomifier::actions::EnhanceBrukerDicom::Pointer act = 
                std::dynamic_pointer_cast<dicomifier::actions::EnhanceBrukerDicom>(object);
        
        BOOST_CHECK_EQUAL(act != NULL, true);
    }
}
