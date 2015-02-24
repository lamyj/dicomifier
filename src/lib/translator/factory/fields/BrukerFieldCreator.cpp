/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "BrukerFieldCreator.h"
#include "translator/fields/BrukerField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration =
        TranslatorFactory::get_instance().register_<BrukerFieldCreator>();

BrukerFieldCreator
::BrukerFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

BrukerFieldCreator
::~BrukerFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
BrukerFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    // Warning: throw exception if attribut is missing
    std::string const brukerfieldname = value.second.get<std::string>("<xmlattr>.name");
    
    // Get 'range' attribut (optional):
    auto range_ = value.second.get_optional<std::string>("<xmlattr>.range");
    
    Range range;
    if (range_)
    {
        std::string rangestr = range_.get();
        std::string minstr = rangestr.substr(0, rangestr.find(","));
        std::string maxstr = rangestr.substr(rangestr.find(",") + 1,
                                             rangestr.length() - 1);
        
        range._min = atoi(minstr.c_str());
        range._max = atoi(maxstr.c_str());
    }
    else
    {
        range._max = std::numeric_limits<int>::max();
    }
    
    TranslatorBrukerFieldCreator action;
    action.brukerfieldname = brukerfieldname;
    action.range = range;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.brukerField;
}

template<>
void 
BrukerFieldCreator::TranslatorBrukerFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Set SQ Element");
}

template<DcmEVR VR> 
void 
BrukerFieldCreator::TranslatorBrukerFieldCreator
::run() const
{
    brukerField = dicomifier::translator::BrukerField<VR>::New(brukerfieldname,
                                                               range);
}

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
