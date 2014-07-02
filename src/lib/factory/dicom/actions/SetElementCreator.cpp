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
SetElementCreator
::Create(DcmTag const & tag, std::string const & value) const
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
    
    return dicomifier::actions::SetElement<VR>::New(NULL, tag, values);
}

} // namespace factory
    
} // namespace dicomifier
