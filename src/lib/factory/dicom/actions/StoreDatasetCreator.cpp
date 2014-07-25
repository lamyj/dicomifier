/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/Factory.h"
#include "dicom/actions/StoreDataset.h"
#include "StoreDatasetCreator.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<StoreDatasetCreator>();

StoreDatasetCreator::StoreDatasetCreator()
{
    // Nothing to do
}

StoreDatasetCreator::~StoreDatasetCreator()
{
    // Nothing to do
}
    
Object::Pointer 
StoreDatasetCreator
::Create(boost::property_tree::ptree::value_type & value)
{
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
    
    // get 'address' attribut
    std::string const address = value.second.get<std::string>("<xmlattr>.address"); // Warning: throw exception if attribut is missing
    
    // get 'port' attribut
    std::string const portstr = value.second.get<std::string>("<xmlattr>.port"); // Warning: throw exception if attribut is missing
    Uint16 port = std::strtol(portstr.c_str(), NULL, 10);
    
    // get 'aeremote' optionnal attribut
    std::string const aeremote = value.second.get<std::string>("<xmlattr>.aeremote"); // Warning: throw exception if attribut is missing
    
    // get 'aelocal' optionnal attribut
    std::string const aelocal = value.second.get<std::string>("<xmlattr>.aelocal"); // Warning: throw exception if attribut is missing
    
    // get 'user' attribut
    std::string const user = value.second.get<std::string>("<xmlattr>.user"); // Warning: throw exception if attribut is missing
    
    // get 'password' attribut
    std::string const password = value.second.get<std::string>("<xmlattr>.password"); // Warning: throw exception if attribut is missing
    
    return dicomifier::actions::StoreDataset::New(dataset, address, port, aeremote, aelocal, user, password);
}

} // namespace factory
    
} // namespace dicomifier
