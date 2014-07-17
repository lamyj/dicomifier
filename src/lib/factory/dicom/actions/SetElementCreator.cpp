/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include "dicom/actions/SetElement.h"
#include "SetElementCreator.h"

namespace dicomifier
{
    
namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<SetElementCreator>();
    
SetElementCreator::SetElementCreator()
{
    // Nothing to do
}

SetElementCreator::~SetElementCreator()
{
    // Nothing to do
}
    
Object::Pointer 
SetElementCreator
::Create(boost::property_tree::ptree::value_type & value)
{
    // get tag
    std::string const tag = value.second.get<std::string>("<xmlattr>.tag"); // Warning: throw exception if attribut is missing
    auto vect = DicomCreatorBase::Parse_Tag(tag);
    
    // get dataset
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
    if (dataset != NULL)
    {
        // get the VR
        std::string const vrstr = value.second.get<std::string>("<xmlattr>.VR"); // Warning: throw exception if attribut is missing
        DcmVR vr(vrstr.c_str());
        DcmEVR const evr = vr.getEVR();
        
        // get value
        std::string const attrvalue = value.second.get<std::string>("<xmlattr>.value"); // Warning: throw exception if attribut is missing
        
        CreateSetElement action;
        action.dataset =  dataset;
        action.tags = vect;
        action.value = attrvalue;
        
        dicomifier::vr_dispatch(action, evr);
        
        return action.setElement;
    }
    else
    {
        throw DicomifierException("No input dataset '" + filename + "'.");
    }
    return NULL;
}

template<>
void 
SetElementCreator::CreateSetElement
::run<EVR_SQ>() const
{
}

template<DcmEVR VR> 
void 
SetElementCreator::CreateSetElement
::run() const
{
    // parse values
    std::vector<std::string> splitvalues;
    boost::split(splitvalues, value, boost::is_any_of("\\"));
    
    // Convert string to 'ValueType'
    typename dicomifier::actions::SetElement<VR>::ArrayType values;
    for (auto it = splitvalues.begin(); it != splitvalues.end(); ++it)
    {
        std::stringstream stream(*it);
        typename dicomifier::actions::SetElement<VR>::ValueType item;
        stream >> item;
        values.push_back(item);
    }
    
    DcmDataset* dcmdataset = dynamic_cast<DcmDataset*>(dataset);
    
    setElement = dicomifier::actions::SetElement<VR>::New(dcmdataset, tags, values);
}

} // namespace factory
    
} // namespace dicomifier
