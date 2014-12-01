/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/Factory.h"
#include "dicom/actions/StoreDataset.h"
#include "dicom/SCU.h"
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
    boost::property_tree::ptree const & tree = value.second;
    
    // get 'dataset' attribut
    std::string filename = this->_get<std::string>(tree, "<xmlattr>.dataset");
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
    std::string const address = this->_get<std::string>(tree, "<xmlattr>.address");
    
    // get 'port' attribut
    uint16_t const port = this->_get<uint16_t>(tree, "<xmlattr>.port");
    
    // get 'aeremote' optionnal attribut
    std::string const aeremote = this->_get<std::string>(tree, "<xmlattr>.aeremote");
    
    // get 'aelocal' optionnal attribut
    std::string const aelocal = this->_get<std::string>(tree, "<xmlattr>.aelocal");
    
    // Get credential informations
    UserIdentityType user_identity_type = UserIdentityType::None;
    std::string user_identity_primary_field = "";
    std::string user_identity_secondary_field = "";
    
    try
    {
        user_identity_primary_field = this->_get<std::string>(
            tree, "<xmlattr>.user");
        user_identity_type = UserIdentityType::Username;
        
        try
        {
            user_identity_secondary_field = this->_get<std::string>(
                tree, "<xmlattr>.password");
            user_identity_type = UserIdentityType::UsernameAndPassword;
        }
        catch(DicomifierException)
        {
            // No password, do nothing
        }
    }
    catch(DicomifierException)
    {
        // No user, do nothing
    }
    
    return dicomifier::actions::StoreDataset::New(
        dataset, address, port, 
        aeremote, aelocal, 
        user_identity_type, 
        user_identity_primary_field, user_identity_secondary_field);
}

} // namespace factory
    
} // namespace dicomifier
