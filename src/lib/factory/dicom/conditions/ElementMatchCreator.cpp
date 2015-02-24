/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include "core/DicomifierException.h"
#include "dicom/conditions/ElementMatch.h"
#include "ElementMatchCreator.h"

namespace dicomifier
{

namespace factory
{
    
static unsigned int const registration =
        Factory::get_instance().register_<ElementMatchCreator>();
    
ElementMatchCreator
::ElementMatchCreator():
    DicomCreatorBase()
{
    // Nothing to do
}

ElementMatchCreator
::~ElementMatchCreator()
{
    // Nothing to do
}

Object::Pointer 
ElementMatchCreator
::Create(boost::property_tree::ptree::value_type & value)
{
    // Get 'private' attribut:
    auto private_ = value.second.get_optional<std::string>("<xmlattr>.private_creator");
    std::string const privatedict = private_ ? private_.get() : "public";
    
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
        Uint16 element;
        if (private_)
        {
            element = dicomifier::Dictionaries::get_instance().FindCreatorElementNumber(privatedict, dataset);
        }
    
        // get tag
        std::string const tag = value.second.get<std::string>("<xmlattr>.tag"); // Warning: throw exception if attribut is missing
        auto vect = DicomCreatorBase::Parse_Tag(tag, privatedict, element);
        
        // get the VR
        std::string const vrstr = value.second.get<std::string>("<xmlattr>.VR"); // Warning: throw exception if attribut is missing
        DcmVR vr(vrstr.c_str());
        DcmEVR const evr = vr.getEVR();
        
        // get value
        std::string const attrvalue = value.second.get<std::string>("<xmlattr>.value"); // Warning: throw exception if attribut is missing

        ActionElementMatchCreator action;
        action.dataset =  dataset;
        action.tags = vect;
        action.value = attrvalue;
        
        dicomifier::vr_dispatch(action, evr);
        
        return action.matchElement;
    }
    else
    {
        throw DicomifierException("No input dataset '" + filename + "'.");
    }
    
    // never happend
    return NULL;
}
    
template<>
void 
ElementMatchCreator::ActionElementMatchCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Match SQ Element");
}

template<DcmEVR VR> 
void 
ElementMatchCreator::ActionElementMatchCreator
::run() const
{
    // parse values
    std::vector<std::string> splitvalues;
    boost::split(splitvalues, value, boost::is_any_of("\\"));
    
    // Convert string to 'ValueType'
    typename dicomifier::conditions::ElementMatch<VR>::ArrayType values;
    for (auto it = splitvalues.begin(); it != splitvalues.end(); ++it)
    {
        std::stringstream stream(*it);
        typename dicomifier::conditions::ElementMatch<VR>::ValueType item;
        stream >> item;
        values.push_back(item);
    }
    
    DcmDataset* dcmdataset = dynamic_cast<DcmDataset*>(dataset);
    
    matchElement = dicomifier::conditions::ElementMatch<VR>::New(dcmdataset, tags, values);
}
   
} // namespace factory
    
} // namespace dicomifier
