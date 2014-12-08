/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "DateGeneratorCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration =
        TranslatorFactory::get_instance().register_<DateGeneratorCreator>();

DateGeneratorCreator
::DateGeneratorCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

DateGeneratorCreator
::~DateGeneratorCreator()
{
    // Nothing to do
}

Tag::Pointer 
DateGeneratorCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    // Get 'inputformat' attribut:
    auto inputformat_ = value.second.get_optional<std::string>("<xmlattr>.inputformat");
    std::string const inputformat = inputformat_ ? inputformat_.get() : "";
    
    // Get 'outputformat' attribut:
    auto outputformat_ = value.second.get_optional<std::string>("<xmlattr>.outputformat");
    std::string const outputformat = outputformat_ ? outputformat_.get() : "%Y%m%d";
    
    std::vector<dicomifier::translator::Tag::Pointer> pttag;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &child, value.second)
    {
        if (dicomifier::translator::
                TranslatorFactory::get_instance().can_create(child.first.data()))
        {
            pttag.push_back(dicomifier::translator::
                    TranslatorFactory::get_instance().create(child,
                                                             dataset,
                                                             evr));
        }
    }
    
    TranslatorDateGeneratorCreator action;
    action.pttag = pttag;
    action.inputformat = inputformat;
    action.outputformat = outputformat;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.dategenerator;
}

template<>
void 
DateGeneratorCreator::TranslatorDateGeneratorCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Create SQ Element");
}

template<DcmEVR VR> 
void 
DateGeneratorCreator::TranslatorDateGeneratorCreator
::run() const
{
    if (pttag.size() > 0)
    {
        dategenerator = 
            dicomifier::translator::DateGenerator<VR>::New(pttag[0], 
                                                           inputformat, 
                                                           outputformat);
    }
    else
    {
        dategenerator = 
            dicomifier::translator::DateGenerator<VR>::New(NULL, 
                                                           inputformat, 
                                                           outputformat);
    }
}
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
