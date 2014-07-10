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
::Create(boost::property_tree::ptree::value_type & value)
{
    // get tag
    std::string const tag = value.second.get<std::string>("<xmlattr>.tag"); // Warning: throw exception if attribut is missing
    DcmTag dcmtag;
    OFCondition result = DcmTag::findTagFromName(tag.c_str(), dcmtag);
    if (result.good())
    {
        // get dataset
        std::string filename = value.second.get<std::string>("<xmlattr>.dataset"); // Warning: throw exception if attribut is missing
        if (filename[0] != '#')
        {
			throw DicomifierException("Error: bad value for dataset attribut.");
		}
        filename = filename.replace(0,1,"");
        
        if (this->_inputs->find(filename) == this->_inputs->end())
        {
            throw DicomifierException("Error: no input dataset '" + filename + "'.");
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
  
            if      (evr == EVR_AE) return this->Create<EVR_AE>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_AS) return this->Create<EVR_AS>(dataset, dcmtag, attrvalue);
            // TODO: EVR_AT
            else if (evr == EVR_CS) return this->Create<EVR_CS>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_DA) return this->Create<EVR_DA>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_DS) return this->Create<EVR_DS>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_DT) return this->Create<EVR_DT>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_FD) return this->Create<EVR_FD>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_FL) return this->Create<EVR_FL>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_IS) return this->Create<EVR_IS>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_LO) return this->Create<EVR_LO>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_LT) return this->Create<EVR_LT>(dataset, dcmtag, attrvalue);
            // TODO: OB
            // TODO: OF
            // TODO: OW
            else if (evr == EVR_PN) return this->Create<EVR_PN>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_SH) return this->Create<EVR_SH>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_SL) return this->Create<EVR_SL>(dataset, dcmtag, attrvalue);
            // TODO: SQ
            else if (evr == EVR_SS) return this->Create<EVR_SS>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_UI) return this->Create<EVR_UI>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_TM) return this->Create<EVR_TM>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_ST) return this->Create<EVR_ST>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_UL) return this->Create<EVR_UL>(dataset, dcmtag, attrvalue);
            // TODO: UN
            else if (evr == EVR_US) return this->Create<EVR_US>(dataset, dcmtag, attrvalue);
            else if (evr == EVR_UT) return this->Create<EVR_UT>(dataset, dcmtag, attrvalue);
            
            else throw DicomifierException("Error: Unknown VR '" + vrstr + "'.");
        }
        else
        {
            throw DicomifierException("Error: no input dataset '" + filename + "'.");
        }
    }
    else
    {
        throw DicomifierException("Error: Unknown tag '" + tag + "'.");
    }
    
    // never happend
    return NULL;
}

template<DcmEVR VR>
Object::Pointer 
ElementMatchCreator
::Create(DcmDataset* dataset, DcmTag const & tag, std::string const & value)
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
            
    return dicomifier::conditions::ElementMatch<VR>::New(dataset, tag, values, true);
}
   
} // namespace factory
    
} // namespace dicomifier
