/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include "ConstantFieldCreator.h"
#include "translator/fields/ConstantField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration =
        TranslatorFactory::get_instance().register_<ConstantFieldCreator>();

ConstantFieldCreator
::ConstantFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

ConstantFieldCreator
::~ConstantFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
ConstantFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    // get values
    std::string const attrvalue = value.second.get<std::string>("<xmlattr>.values"); // Warning: throw exception if attribut is missing
    
    TranslatorConstantFieldCreator action;
    action.value = attrvalue;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.constantField;
}

template<>
void 
ConstantFieldCreator::TranslatorConstantFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<>
void
ConstantFieldCreator::TranslatorConstantFieldCreator
::run<EVR_AT>() const
{
    // parse values
    std::vector<std::string> splitvalues;
    boost::split(splitvalues, value, boost::is_any_of("\\,"));
    
    // Convert string to 'ValueType'
    typename dicomifier::translator::ConstantField<EVR_AT>::ArrayType values;
    for (auto it = splitvalues.begin(); it != splitvalues.end(); ++it)
    {
        std::stringstream stream(*it);
        typename dicomifier::translator::ConstantField<EVR_AT>::ValueType item;
        stream >> std::hex >> item;
        values.push_back(item);
    }
    constantField = dicomifier::translator::ConstantField<EVR_AT>::New(values);
}

template<DcmEVR VR> 
void 
ConstantFieldCreator::TranslatorConstantFieldCreator
::run() const
{
    // parse values
    std::vector<std::string> splitvalues;
    boost::split(splitvalues, value, boost::is_any_of("\\"));
    
    // Convert string to 'ValueType'
    typename dicomifier::translator::ConstantField<VR>::ArrayType values;
    for (auto it = splitvalues.begin(); it != splitvalues.end(); ++it)
    {
        std::stringstream stream(*it);
        typename dicomifier::translator::ConstantField<VR>::ValueType item;
        stream >> item;
        values.push_back(item);
    }
    constantField = dicomifier::translator::ConstantField<VR>::New(values);
}

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
