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
    
static unsigned int const registration = Factory::get_instance().register_<EmptyElementCreator>();
    
EmptyElementCreator::EmptyElementCreator()
{
    // Nothing to do
}

EmptyElementCreator::~EmptyElementCreator()
{
    // Nothing to do
}

Object::Pointer 
EmptyElementCreator
::Create(boost::property_tree::ptree::value_type & value) const
{
    // Get 'tag' attribut:
    std::string const second = value.second.get<std::string>("tag");
    DcmTag dcmtag;
    OFCondition status = DcmTag::findTagFromName(second.c_str(), dcmtag);
    if (status.bad())
    {
        throw DicomifierException("Error: Unknown tag '" + second + "'.");
    }
    
    // get dataset
    std::string const filename = value.second.get<std::string>("dataset");
    DcmFileFormat fileformat;
    status = fileformat.loadFile(filename.c_str());
    if (status.bad())
    {
        throw DicomifierException("Error: Unable to load dataset '" + filename + "'.");
    }
    
    DcmDataset* dataset = fileformat.getAndRemoveDataset();
    
    return dicomifier::actions::EmptyElement::New(dataset, dcmtag, true);
}
    
} // namespace factory
    
} // namespace dicomifier
