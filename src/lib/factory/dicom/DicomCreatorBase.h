/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _58196402_72bc_4f18_90ee_7f955d5dac9f
#define _58196402_72bc_4f18_90ee_7f955d5dac9f

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include "boost/regex.hpp"

#include "dicom/Dictionaries.h"
#include "dicom/TagAndRange.h"
#include "factory/core/CreatorBase.h"

namespace dicomifier
{
    
namespace factory
{
    
const boost::regex RegEx_tag("^\\s*([^\\[]+)\\[(\\d*:?\\d*)\\]\\s*$");
    
class DicomCreatorBase : public CreatorBase
{
public:
    virtual ~DicomCreatorBase() {}

protected:
    DicomCreatorBase() {}
    
    static std::vector<dicomifier::TagAndRange> Parse_Tag(std::string const & tag, 
                                                          std::string const & privatedict = "public", 
                                                          Uint16 element = 0x0000)
    {
        std::vector<dicomifier::TagAndRange> vect;
        
        // Sequences are separate by '.'
        std::vector<std::string> tagsStr;
        boost::split(tagsStr, tag, boost::is_any_of("."), boost::token_compress_on);
        for (auto value : tagsStr) 
        {
            std::string tagstr;
            dicomifier::Range range;
            
            boost::cmatch what;
            if (regex_match(value.c_str(), what, RegEx_tag))
            {// match, value type = MyValue[x:y]
                tagstr = what[1];
                std::vector<std::string> rangevect;
                std::string rangeStr = what[2];
                boost::split(rangevect, rangeStr, boost::is_any_of(":"), boost::token_compress_on);
                
                range._min = rangevect[0] == "" ? 0 : std::stoi(rangevect[0]);
                if (rangevect.size() == 2)
                {
                    if (rangevect[1] == "")
                    {
                        range._max = std::numeric_limits<int>::max();
                    }
                    else
                    {
                        range._max = std::stoi(rangevect[1]);
                    }
                }
                else
                {
                    range._max = range._min + 1;
                }
            }
            else
            {// no match, value type = MyValue
                tagstr = value;
                range._min = 0;
                range._max = std::numeric_limits<int>::max();
            }
            
            DcmTag dcmtag;
            bool finalypublic = false;
            if (tagstr.find(",") != std::string::npos)
            {
                dcmtag = dicomifier::Dictionaries::get_instance().GetTagFromKey(tagstr, privatedict, finalypublic);
            }
            else
            {
                dcmtag = dicomifier::Dictionaries::get_instance().GetTagFromName(tagstr, privatedict, finalypublic);
            }
            
            if (privatedict != "public" && !finalypublic)
            {
                Uint16 ele = element * 256 + dcmtag.getElement();
                dcmtag.setElement(ele);
            }
            
            vect.push_back(dicomifier::TagAndRange(dcmtag, range));
        }
        return vect;
    }
    
private:
  
};
  
} // namespace factory

} // namespace dicomifier

#endif // _58196402_72bc_4f18_90ee_7f955d5dac9f
