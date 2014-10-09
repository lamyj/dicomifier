/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _eed21ce4_7b03_4376_adb6_858e49c9bd12
#define _eed21ce4_7b03_4376_adb6_858e49c9bd12

#include <boost/algorithm/string.hpp>

namespace dicomifier
{
    
const std::string VerificationSOPClass          = "1.2.840.10008.1.1";
const std::string MRImageStorage                = "1.2.840.10008.5.1.4.1.1.4";
const std::string EnhancedMRImageStorage        = "1.2.840.10008.5.1.4.1.1.4.1";
const std::string MRSpectroscopyStorage         = "1.2.840.10008.5.1.4.1.1.4.2";
    
static std::string get_SOPClassUID_from_name(std::string const & name)
{
    std::string name_no_blank = name;
    boost::replace_all(name_no_blank, " ", "");
    
    if      (name_no_blank == "VerificationSOPClass")    return VerificationSOPClass;
    else if (name_no_blank == "MRImageStorage")          return MRImageStorage;
    else if (name_no_blank == "EnhancedMRImageStorage")  return EnhancedMRImageStorage;
    else if (name_no_blank == "MRSpectroscopyStorage")   return MRSpectroscopyStorage;
    
    else return name_no_blank;
}

} // namespace dicomifier

#endif // _eed21ce4_7b03_4376_adb6_858e49c9bd12
