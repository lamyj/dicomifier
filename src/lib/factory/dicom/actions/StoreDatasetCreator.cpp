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
    std::string const port = value.second.get<std::string>("<xmlattr>.port"); // Warning: throw exception if attribut is missing
    
    // get 'aeremote' optionnal attribut
    auto opt_aeremote = value.second.get_optional<std::string>("<xmlattr>.aeremote");
    std::string const aeremote = opt_aeremote ? opt_aeremote.get() : "";
    
    // get 'aelocal' optionnal attribut
    auto opt_aelocal = value.second.get_optional<std::string>("<xmlattr>.aelocal");
    std::string const aelocal = opt_aelocal ? opt_aelocal.get() : "";
    
    return dicomifier::actions::StoreDataset::New(dataset, address, port, aeremote, aelocal);
}

} // namespace factory
    
} // namespace dicomifier
