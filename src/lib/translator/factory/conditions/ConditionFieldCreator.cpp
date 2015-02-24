/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "ConditionFieldCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration =
        TranslatorFactory::get_instance().register_<ConditionFieldCreator>();

ConditionFieldCreator
::ConditionFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

ConditionFieldCreator
::~ConditionFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
ConditionFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    // Parsing <If />
    auto iftag = value.second.equal_range("If");
    // throw exception if value If element is missing.
    if (iftag.first == iftag.second)
    {
        throw DicomifierException("Missing 'If' element.");
    }
    auto it = iftag.first;
    it++;
    // throw exception if value contains several If elements.
    if (it != iftag.second)
    {
        throw DicomifierException("Too many 'If' element.");
    }
    
    std::vector<dicomifier::translator::Tag::Pointer> pttag_cond;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &child,
            value.second.get_child("If"))
    {
        pttag_cond.push_back(dicomifier::translator::
                    TranslatorFactory::get_instance().create(child,
                                                             dataset,
                                                             evr));
    }
    
    // Parsing <Then />
    auto thentag = value.second.equal_range("Then");
    // throw exception if value Then element is missing.
    if (thentag.first == thentag.second)
    {
        throw DicomifierException("Missing 'Then' element.");
    }
    auto itthentag = thentag.first;
    itthentag++;
    // throw exception if value contains several Then elements.
    if (itthentag != thentag.second)
    {
        throw DicomifierException("Too many 'Then' element.");
    }
    
    dicomifier::translator::Tag::Pointer pttag_true;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &child,
            value.second.get_child("Then"))
    {
        pttag_true = dicomifier::translator::
                    TranslatorFactory::get_instance().create(child,
                                                             dataset,
                                                             evr);
    }
    
    // Parsing <Else />
    auto elsetag = value.second.equal_range("Else");
    // throw exception if value Else element is missing.
    if (elsetag.first == elsetag.second)
    {
        throw DicomifierException("Missing 'Else' element.");
    }
    auto itelsetag = elsetag.first;
    itelsetag++;
    // throw exception if value contains several Else elements.
    if (itelsetag != elsetag.second)
    {
        throw DicomifierException("Too many 'Else' element.");
    }
    
    dicomifier::translator::Tag::Pointer pttag_false;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &child,
            value.second.get_child("Else"))
    {
        pttag_false = dicomifier::translator::
                    TranslatorFactory::get_instance().create(child,
                                                             dataset,
                                                             evr);
    }
    
    TranslatorConditionFieldCreator action;
    action.pttag_cond = pttag_cond;
    action.pttag_true = pttag_true;
    action.pttag_false = pttag_false;
    
    dicomifier::vr_dispatch(action, evr);
    
    return action.conditionfield;
}

template<>
void 
ConditionFieldCreator::TranslatorConditionFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Create SQ Element");
}

template<DcmEVR VR> 
void 
ConditionFieldCreator::TranslatorConditionFieldCreator
::run() const
{
    conditionfield = dicomifier::translator::ConditionField<VR>::New(pttag_cond,
                                                                     pttag_true,
                                                                     pttag_false);
}

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
