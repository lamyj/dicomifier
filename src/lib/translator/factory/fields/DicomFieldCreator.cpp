/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "dicom/Dictionaries.h"
#include "DicomFieldCreator.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
static unsigned int const registration = TranslatorFactory::get_instance().register_<DicomFieldCreator>(); 

DicomFieldCreator
::DicomFieldCreator()
    :TranslationCreatorBase()
{
    // Nothing to do
}

DicomFieldCreator
::~DicomFieldCreator()
{
    // Nothing to do
}

Tag::Pointer 
DicomFieldCreator
::Create(boost::property_tree::ptree::value_type & value, 
         DcmDataset* dataset, 
         DcmEVR evr)
{
    // Get 'private' attribut:
    auto private_ = value.second.get_optional<std::string>("<xmlattr>.private_creator");
    std::string const privatedict = private_ ? private_.get() : "public";
    
    Uint16 element;
    if (private_)
    {
        element = dicomifier::Dictionaries::get_instance().FindCreatorElementNumber(privatedict, dataset);
    }
        
    // get tag
    std::string const tag = value.second.get<std::string>("<xmlattr>.tag"); // Warning: throw exception if attribut is missing
    
    DcmTag dcmtag = dicomifier::Dictionaries::get_instance().GetTagFromKey(tag, privatedict);
    
    if (privatedict != "public")
    {
        Uint16 ele = element * 256 + dcmtag.getElement();
        dcmtag.setElement(ele);
    }
    
    std::vector<dicomifier::translator::Tag::Pointer> pttag;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &child, value.second)
    {
        if (dicomifier::translator::
                TranslatorFactory::get_instance().can_create(child.first.data()))
        {
            pttag.push_back(dicomifier::translator::
                    TranslatorFactory::get_instance().create(child,
                                                             dataset,
                                                             dcmtag.getEVR()));
        }
    }
            
    dicomifier::Range range;
    TranslatorDicomFieldCreator action;
    action.tagrange = dicomifier::TagAndRange(dcmtag, range);
    action.pttag = pttag;
    
    dicomifier::vr_dispatch(action, dcmtag.getEVR());
    
    return action.dicomfield;
}

template<>
void 
DicomFieldCreator::TranslatorDicomFieldCreator
::run<EVR_SQ>() const
{
    throw DicomifierException("Impossible to Create SQ Element");
}

template<DcmEVR VR> 
void 
DicomFieldCreator::TranslatorDicomFieldCreator
::run() const
{
    dicomfield = dicomifier::translator::DicomField<VR>::New(tagrange, pttag[0]);
}
    
} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier
