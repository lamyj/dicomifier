/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "bruker/actions/EnhanceBrukerDicom.h"
#include "core/Factory.h"
#include "EnhanceBrukerDicomCreator.h"

namespace dicomifier
{

namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<EnhanceBrukerDicomCreator>();
    
EnhanceBrukerDicomCreator::EnhanceBrukerDicomCreator()
{
    // Nothing to do
}

EnhanceBrukerDicomCreator::~EnhanceBrukerDicomCreator()
{
    // Nothing to do
}

Object::Pointer 
EnhanceBrukerDicomCreator
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
    
    // get 'brukerdir' attribut
    filename = value.second.get<std::string>("<xmlattr>.brukerdir"); // Warning: throw exception if attribut is missing
    
    if (filename[0] == '#')
    {
        filename = filename.replace(0,1,"");
        
        if (this->_inputs->find(filename) == this->_inputs->end())
        {
            throw DicomifierException("No input brukerdir '" + filename + "'.");
        }
        
        filename = boost::any_cast<std::string>(this->_inputs->find(filename)->second);
    }
    
    return dicomifier::actions::EnhanceBrukerDicom::New(dataset, filename);
}
    
} // namespace factory

} // namespace dicomifier
