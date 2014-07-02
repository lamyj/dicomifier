/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

#include "dicom/conditions/ElementMatch.h"
#include "ElementMatchCreator.h"

namespace dicomifier
{

namespace factory
{
    
static unsigned int const registration = Factory::get_instance().register_<ElementMatchCreator>();
    
ElementMatchCreator::ElementMatchCreator()
{
    // Nothing to do
}

ElementMatchCreator::~ElementMatchCreator()
{
    // Nothing to do
}
    
Object::Pointer 
ElementMatchCreator
::Create(boost::property_tree::ptree::value_type & value) const
{
    // get the VR
    std::string const vrstr = value.second.get_child("<xmlattr>.VR").data();
    DcmVR vr(vrstr.c_str());
    DcmEVR const evr = vr.getEVR();
    
    // get value
    std::string const attrvalue = value.second.get_child("<xmlattr>.value").data();
    
    // get tag
    std::string const tag = value.second.get_child("<xmlattr>.tag").data();
    DcmTag dcmtag;
    OFCondition result = DcmTag::findTagFromName(tag.c_str(), dcmtag);
    if (result.good())
    {
        if      (evr == EVR_AE) return this->Create<EVR_AE>(dcmtag, attrvalue);
        else if (evr == EVR_AS) return this->Create<EVR_AS>(dcmtag, attrvalue);
// TODO: EVR_AT
        else if (evr == EVR_CS) return this->Create<EVR_CS>(dcmtag, attrvalue);
        else if (evr == EVR_DA) return this->Create<EVR_DA>(dcmtag, attrvalue);
        else if (evr == EVR_DS) return this->Create<EVR_DS>(dcmtag, attrvalue);
        else if (evr == EVR_DT) return this->Create<EVR_DT>(dcmtag, attrvalue);
        else if (evr == EVR_FD) return this->Create<EVR_FD>(dcmtag, attrvalue);
        else if (evr == EVR_FL) return this->Create<EVR_FL>(dcmtag, attrvalue);
        else if (evr == EVR_IS) return this->Create<EVR_IS>(dcmtag, attrvalue);
        else if (evr == EVR_LO) return this->Create<EVR_LO>(dcmtag, attrvalue);
        else if (evr == EVR_LT) return this->Create<EVR_LT>(dcmtag, attrvalue);
// TODO: OB
// TODO: OF
// TODO: OW
        else if (evr == EVR_PN) return this->Create<EVR_PN>(dcmtag, attrvalue);
        else if (evr == EVR_SH) return this->Create<EVR_SH>(dcmtag, attrvalue);
        else if (evr == EVR_SL) return this->Create<EVR_SL>(dcmtag, attrvalue);
// TODO: SQ
        else if (evr == EVR_SS) return this->Create<EVR_SS>(dcmtag, attrvalue);
        else if (evr == EVR_UI) return this->Create<EVR_UI>(dcmtag, attrvalue);
        else if (evr == EVR_TM) return this->Create<EVR_TM>(dcmtag, attrvalue);
        else if (evr == EVR_ST) return this->Create<EVR_ST>(dcmtag, attrvalue);
        else if (evr == EVR_UL) return this->Create<EVR_UL>(dcmtag, attrvalue);
// TODO: UN
        else if (evr == EVR_US) return this->Create<EVR_US>(dcmtag, attrvalue);
        else if (evr == EVR_UT) return this->Create<EVR_UT>(dcmtag, attrvalue);
    }
    return NULL;
}

template<DcmEVR VR>
Object::Pointer 
ElementMatchCreator
::Create(DcmTag const & tag, std::string const & value) const
{
    // create return object
    typename dicomifier::conditions::ElementMatch<VR>::Pointer elementmatch = 
        dicomifier::conditions::ElementMatch<VR>::New();
           
    // parse values
    typename dicomifier::conditions::ElementMatch<VR>::ArrayType values;
    
    std::vector<std::string> splitvalues;
    boost::split(splitvalues, value, boost::is_any_of("\\"), 
                 boost::algorithm::token_compress_on);
    
    // Convert string to 'ValueType'
    std::vector<std::string>::iterator it = splitvalues.begin();
    for (; it != splitvalues.end(); ++it)
    {
        values.push_back(boost::lexical_cast<typename dicomifier::conditions::ElementMatch<VR>::ValueType>(*it));
    }
    
    // set element (tag / value)
    elementmatch->set_tag(tag);
    elementmatch->set_value(values);
            
    return elementmatch;
}
   
} // namespace factory
    
} // namespace dicomifier
