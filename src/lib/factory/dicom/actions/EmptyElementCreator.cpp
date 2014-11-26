/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "core/Factory.h"
#include "dicom/actions/EmptyElement.h"
#include "EmptyElementCreator.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration =
        Factory::get_instance().register_<EmptyElementCreator>();
    
EmptyElementCreator
::EmptyElementCreator():
    DicomCreatorBase()
{
    // Nothing to do
}

EmptyElementCreator
::~EmptyElementCreator()
{
    // Nothing to do
}

Object::Pointer 
EmptyElementCreator
::Create(boost::property_tree::ptree::value_type & value)
{
    // Get 'private' attribut:
    auto private_ = value.second.get_optional<std::string>("<xmlattr>.private_creator");
    std::string const privatedict = private_ ? private_.get() : "public";
    
    // get 'dataset' attribut
    std::string filename = value.second.get<std::string>("<xmlattr>.dataset"); // Warning: throw exception if attribut is missing
    if (filename[0] != '#')
    {
        throw DicomifierException("Bad value for dataset attribut.");
    }
    filename = filename.replace(0,1,"");

    if (this->_inputs->find(filename) == this->_inputs->end())
    {
        throw DicomifierException("No input dataset '" + filename + "'.");
    }
    DcmDataset* dataset = boost::any_cast<DcmDataset*>(this->_inputs->find(filename)->second);
    if (dataset == NULL)
    {
        throw DicomifierException("Unable to load dataset '" + filename + "'.");
    }
    
    Uint16 element;
    if (private_)
    {
        element = dicomifier::Dictionaries::get_instance().FindCreatorElementNumber(privatedict, dataset);
    }
    
    // Get 'tag' attribut:
    std::string const second = value.second.get<std::string>("<xmlattr>.tag"); // Warning: throw exception if attribut is missing
    auto vect = DicomCreatorBase::Parse_Tag(second, privatedict, element);
    
    return dicomifier::actions::EmptyElement::New(dataset, vect);
}
    
} // namespace factory
    
} // namespace dicomifier
