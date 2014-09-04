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
    
static unsigned int const registration = Factory::get_instance().register_<EnhanceBrukerDicomCreator>();
    
EnhanceBrukerDicomCreator::EnhanceBrukerDicomCreator()
{
    // Nothing to do
}

EnhanceBrukerDicomCreator::~EnhanceBrukerDicomCreator()
{
    // Nothing to do
}

Object::Pointer 
EnhanceBrukerDicomCreator
::Create(boost::property_tree::ptree::value_type & value)
{
    // get 'dataset' attribut (optional)
    auto filename_ = value.second.get_optional<std::string>("<xmlattr>.dataset");
    std::string filename = filename_ ? filename_.get() : "NEW_DATASET";
    
    if (filename != "NEW_DATASET")
    {
        if (filename[0] != '#')
        {
            throw DicomifierException("Bad value for dataset attribut.");
        }
        filename = filename.replace(0,1,"");
    }
        
    if (this->_inputs->find(filename) == this->_inputs->end())
    {
        throw DicomifierException("No input dataset '" + filename + "'.");
    }
    DcmDataset* dataset = boost::any_cast<DcmDataset*>(this->_inputs->find(filename)->second);
    if (dataset == NULL)
    {
        throw DicomifierException("Unable to load dataset '" + filename + "'.");
    }
    
    // get 'seriesnumber' attribut (mandatory)
    int seriesnum = value.second.get<int>("<xmlattr>.seriesnumber"); // Warning: throw exception if attribut is missing
    
    // get 'studynumber' attribut (optional)
    auto studynum_ = value.second.get_optional<int>("<xmlattr>.studynumber");
    int studynum = studynum_ ? studynum_.get() : 0;
    
    // get 'brukerdir' attribut (mandatory)
    filename = value.second.get<std::string>("<xmlattr>.brukerdir"); // Warning: throw exception if attribut is missing
    
    if (filename[0] == '#')
    {
        filename = filename.replace(0,1,"");
        
        if (this->_inputs->find(filename) == this->_inputs->end())
        {
            throw DicomifierException("No input brukerdir '" + filename + "'.");
        }
        
        filename = boost::any_cast<std::string>(this->_inputs->find(filename)->second);
    }
    
    // get 'brukertodicomdictionary' attribut (optional)
    auto brukertodicomdictionary_ = 
        value.second.get_optional<std::string>("<xmlattr>.brukertodicomdictionary");
    std::string brukerToDicomDictionary = 
        brukertodicomdictionary_ ? brukertodicomdictionary_.get() : "./BrukerToDicom_Dictionary.xml";
    
    studynum = studynum % 10;       // only 1 byte
    seriesnum = seriesnum % 10000;  // only 4 bytes
    
    // Conversion: StudyNum (A) + SeriesNum (B) => ABBBB
    char temp[6];
    memset(&temp[0], 0, 6);
    snprintf(&temp[0], 6, "%01d%04d", studynum, seriesnum);
    std::string seriesnumber(temp);
    
    // Insert SeriesNumber => use to find Bruker data
    dataset->putAndInsertOFStringArray(DCM_SeriesNumber, OFString(seriesnumber.c_str()));
    
    return dicomifier::actions::EnhanceBrukerDicom::New(dataset, filename, 
                                                        brukerToDicomDictionary);
}
    
} // namespace factory

} // namespace dicomifier
