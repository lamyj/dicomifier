/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "bruker/actions/EnhanceBrukerDicom.h"
#include "core/Factory.h"
#include "EnhanceBrukerDicomCreator.h"

namespace dicomifier
{

namespace factory
{
    
static unsigned int const registration =
        Factory::get_instance().register_<EnhanceBrukerDicomCreator>();
    
EnhanceBrukerDicomCreator
::EnhanceBrukerDicomCreator():
    CreatorBase()
{
    // Nothing to do
}

EnhanceBrukerDicomCreator
::~EnhanceBrukerDicomCreator()
{
    // Nothing to do
}

Object::Pointer 
EnhanceBrukerDicomCreator
::Create(boost::property_tree::ptree::value_type & value)
{
    // get 'reconumber' attribut (mandatory)
    int reconum = value.second.get<int>("<xmlattr>.reconumber"); // Warning: throw exception if attribut is missing
    
    // get 'seriesnumber' attribut (optional)
    auto seriesnum_ = value.second.get_optional<int>("<xmlattr>.seriesnumber");
    int seriesnum = seriesnum_ ? seriesnum_.get() : 0;

    // get 'studynumber' attribut (optional)
    auto studynumber_ = value.second.get_optional<std::string>("<xmlattr>.studynumber");
    std::string studynumber = studynumber_ ? studynumber_.get() : "1";
    
    // get 'brukerdir' attribut (mandatory)
    std::string filename = value.second.get<std::string>("<xmlattr>.brukerdir"); // Warning: throw exception if attribut is missing
    if (filename[0] == '#')
    {
        filename = filename.replace(0,1,"");
        
        if (this->_inputs->find(filename) == this->_inputs->end())
        {
            throw DicomifierException("No input brukerdir '" + filename + "'.");
        }
        
        filename = boost::any_cast<std::string>(this->_inputs->find(filename)->second);
    }
    
    // get 'sopclassuid' attribut (mandatory)
    std::string sopclassuid = value.second.get<std::string>("<xmlattr>.sopclassuid"); // Warning: throw exception if attribut is missing

    // get 'outputdirectory' attribut (mandatory)
    std::string outputdirectory = value.second.get<std::string>("<xmlattr>.outputdirectory"); // Warning: throw exception if attribut is missing
    if (outputdirectory[0] == '#')
    {
        outputdirectory = outputdirectory.replace(0,1,"");

        if (this->_outputs->find(outputdirectory) == this->_outputs->end())
        {
            throw DicomifierException("No output directory '" + outputdirectory + "'.");
        }

        outputdirectory = boost::any_cast<std::string>(this->_outputs->find(outputdirectory)->second);
    }

    seriesnum = seriesnum % 100;      // only 2 byte
    reconum = reconum % 10000;  // only 4 bytes

    std::string mask = seriesnum < 10 ? "%01d%04d" : "%02d%04d";
    
    // Conversion: seriesnum (A) + reconum (B) => AABBBB
    char temp[7];
    memset(&temp[0], 0, 7);
    snprintf(&temp[0], 7, mask.c_str(), seriesnum, reconum);
    std::string seriesnumber(temp);
    
    // Insert SeriesNumber => use to find Bruker data
    //dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString(seriesnumber.c_str()));

    return dicomifier::actions::EnhanceBrukerDicom::New(
        filename, sopclassuid, outputdirectory, studynumber, seriesnumber);
}
    
} // namespace factory

} // namespace dicomifier
