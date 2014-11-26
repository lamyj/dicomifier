/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "RegExFilterCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration =
        TranslatorFactory::get_instance().register_<RegExFilterCreator>();

RegExFilterCreator
::RegExFilterCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

RegExFilterCreator
::~RegExFilterCreator()
{
    // Nothing to do
}

Tag::Pointer 
RegExFilterCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{    
    // get attribut 'expression' (mandatory)
    std::string const expression = value.second.get<std::string>("<xmlattr>.expression"); // Warning: throw exception if attribut is missing
    
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
            
    TranslatorRegExFilterCreator action;
    action.pttag = pttag;
    action.expression = expression;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.regexfilter;
}

template<>
void 
RegExFilterCreator::TranslatorRegExFilterCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Create SQ Element");
}

template<DcmEVR VR> 
void 
RegExFilterCreator::TranslatorRegExFilterCreator
::run() const
{
    regexfilter = dicomifier::translator::RegExFilter<VR>::New(pttag[0], expression);
}
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
    
