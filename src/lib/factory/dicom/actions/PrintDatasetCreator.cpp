/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/Factory.h"
#include "dicom/actions/PrintDataset.h"
#include "PrintDatasetCreator.h"

namespace dicomifier
{

namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<PrintDatasetCreator>();
    
PrintDatasetCreator
::PrintDatasetCreator()
{
    // Nothing to do
}

PrintDatasetCreator
::~PrintDatasetCreator()
{
    // Nothing to do
}
    
Object::Pointer 
PrintDatasetCreator
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
    
    // get 'outputfile' attribut
    filename = value.second.get<std::string>("<xmlattr>.outputfile"); // Warning: throw exception if attribut is missing
    if (filename[0] == '#')
    {
        filename = filename.replace(0,1,"");
        
        if (this->_outputs->find(filename) == this->_outputs->end())
        {
            throw DicomifierException("No output with name='" + filename + "'.");
        }
        
        filename = boost::any_cast<std::string>(this->_outputs->find(filename)->second);
    }
    
    return dicomifier::actions::PrintDataset::New(dataset, filename);
}

} // namespace factory

} // namespace dicomifier
