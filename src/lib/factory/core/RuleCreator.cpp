/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/Factory.h"
#include "core/Rule.h"
#include "RuleCreator.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<RuleCreator>();
    
RuleCreator::RuleCreator()
{
    // Nothing to do
}

RuleCreator::~RuleCreator()
{
    // Nothing to do
}

Object::Pointer 
RuleCreator
::Create(boost::property_tree::ptree::value_type & value)
{
    this->_inputs = std::make_shared<CreatorBase::InOutPutType>();

    // Parsing <Input />
    BOOST_FOREACH(boost::property_tree::ptree::value_type &input, 
              value.second.equal_range("Input"))
    {
        std::string type = input.second.get("<xmlattr>.type","");
        std::string name = input.second.get("<xmlattr>.name","");
        std::string value = input.second.get("<xmlattr>.value","");

        boost::any obj = CreateAnyObject(type, name, value);
        this->_inputs->insert(std::pair<std::string, boost::any>(name, obj));
    }
    
    this->_outputs = std::make_shared<CreatorBase::InOutPutType>();

    // Parsing <Output />
    BOOST_FOREACH(boost::property_tree::ptree::value_type &output, 
                  value.second.equal_range("Output"))
    {
        std::string type = output.second.get("<xmlattr>.type","");
        std::string name = output.second.get("<xmlattr>.name","");
        std::string value = output.second.get("<xmlattr>.value","");
        
        boost::any obj = CreateAnyObject(type, name, value);
        this->_outputs->insert(std::pair<std::string, boost::any>(name, obj));
    }
    
    dicomifier::Rule::Pointer rule = dicomifier::Rule::New();
    
    // Parsing <Condition />
    auto conditions = value.second.equal_range("Condition");
    // throw exception if value Condition element is missing.
    if (conditions.first == conditions.second)
    {
        throw DicomifierException("Missing Condition element.");
    }
    auto it = conditions.first;
    it++;
    // throw exception if value contains several Condition elements.
    if (it != conditions.second)
    {
        throw DicomifierException("Too many Condition element.");
    }
    
    bool alreadyset = false;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            value.second.get_child("Condition"))
    {
        if ( ! alreadyset)
        {
            Object::Pointer object = Factory::get_instance().create(v, this->_inputs, this->_outputs);
            dicomifier::conditions::Condition::Pointer cond = 
                std::dynamic_pointer_cast<dicomifier::conditions::Condition>(object);
            if (cond != NULL)
            {
                rule->set_condition(cond);
                alreadyset = true; // only one condition
            }
        }
    }
    
    // Parsing <Actions />
    auto actions = value.second.equal_range("Actions");
    // throw exception if value Actions element is missing.
    if (actions.first == actions.second)
    {
        throw DicomifierException("Missing Actions element.");
    }
    auto it_action = actions.first;
    it_action++;
    // throw exception if value contains several Actions elements.
    if (it_action != actions.second)
    {
        throw DicomifierException("Too many Actions element.");
    }
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v,
            value.second.get_child("Actions"))
    {
        Object::Pointer object = Factory::get_instance().create(v, this->_inputs, this->_outputs);
        dicomifier::actions::Action::Pointer act = 
            std::dynamic_pointer_cast<dicomifier::actions::Action>(object);
        if (act != NULL)
        {
            rule->add_action(act);
        }
    }
    
    return rule;
}

boost::any 
RuleCreator
::CreateAnyObject(std::string const & type, 
                  std::string const & name, 
                  std::string const & value)
{
    if (type == "dataset")
    {
        DcmFileFormat fileformat;
        fileformat.loadFile(value.c_str());
        DcmDataset * dataset = fileformat.getAndRemoveDataset();
        return boost::any(dataset);
    }
    else if (type == "file")
    {
        return boost::any(value);
    }

    throw DicomifierException("Unknown type '" + type + "' for Input or Output element.");
}
   
} // namespace factory

} // namespace dicomifier
