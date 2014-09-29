/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "bruker/BrukerDirectory.h"
#include "core/DicomifierException.h"
#include "EnhanceBrukerDicom.h"
#include "translator/fields/DicomField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace actions
{
    
EnhanceBrukerDicom::EnhanceBrukerDicom():
    _dataset(NULL), _brukerDir(""), _brukerToDicomDictionary("")
{
    // Nothing to do
}

EnhanceBrukerDicom::EnhanceBrukerDicom(DcmDataset * dataset, std::string brukerDir,
                                       std::string const & brukerToDicomDictionary):
    _dataset(dataset), _brukerDir(brukerDir), 
    _brukerToDicomDictionary(brukerToDicomDictionary)
{
    // Nothing to do
}

EnhanceBrukerDicom::~EnhanceBrukerDicom()
{
    // Nothing to do
}

DcmDataset * 
EnhanceBrukerDicom
::get_dataset() const
{
    return this->_dataset;
}

void 
EnhanceBrukerDicom
::set_dataset(DcmDataset * dataset)
{
    this->_dataset = dataset;
}

std::string const & 
EnhanceBrukerDicom
::get_brukerDir() const
{
    return this->_brukerDir;
}

void 
EnhanceBrukerDicom
::set_brukerDir(std::string const & brukerDir)
{
    this->_brukerDir = brukerDir;
}

void 
EnhanceBrukerDicom
::run() const
{
    // ----- Check input directory name -----
    if ( ! boost::filesystem::is_directory(this->_brukerDir) )
    {
        throw DicomifierException("Input not a Directory: " + this->_brukerDir);
    }
    
    dicomifier::bruker::BrukerDirectory* brukerdirectory = new dicomifier::bruker::BrukerDirectory();
    
    // Parse input bruker directory
    int result = brukerdirectory->CreateMap(this->_brukerDir);
    
    // Search SeriesNumber dicom element
    OFString str;
    OFCondition cond = this->_dataset->findAndGetOFStringArray(DCM_SeriesNumber, str);
    if (cond.bad())
    {
        throw dicomifier::DicomifierException("Can't read SeriesNumber attribut, error = " + 
                                              std::string(cond.text()));
    }
    
    // Search corresponding Bruker Dataset
    dicomifier::bruker::BrukerDataset* brukerdataset = brukerdirectory->get_brukerDataset(str.c_str());
    
    // Load Dictionary
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(this->_brukerToDicomDictionary, pt);
    
    // Parse and run all dictionary entries
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt) // Tag Dictionary
    {
        BOOST_FOREACH(boost::property_tree::ptree::value_type &dicomfield, 
                  v.second.equal_range("DicomField"))
        {
            auto rule = dicomifier::translator::
                TranslatorFactory::get_instance().create(dicomfield,
                                                         this->_dataset,
                                                         EVR_UN);
                                                         
            if (rule != NULL)
            {
                rule->run(this->_dataset, brukerdataset);
            }
            else
            {
                throw DicomifierException("Bad dictionary Bruker to Dicom");
            }
        }
    }
    
    // Adding binary data:
    int size = brukerdataset->GetFieldData("IM_SIX").GetIntValue()[0];
    size *= brukerdataset->GetFieldData("IM_SIY").GetIntValue()[0];
    size *= brukerdataset->GetFieldData("VisuCoreFrameCount").GetIntValue()[0];
    int pixelSize;
    brukerdirectory->getImhDataType(brukerdataset->GetFieldData("DATTYPE"), pixelSize);
    size *= pixelSize;
    
    char binarydata[size];
    memset(&binarydata[0], 0, size);
    std::ifstream is (brukerdataset->GetFieldData("PIXELDATA").GetStringValue()[0], std::ifstream::binary);
    is.read (&binarydata[0], size);
    
    //this->_dataset->putAndInsertUint8Array(DCM_PixelData, (Uint8*)&binarydata[0], size);
    
    delete brukerdirectory;
}
    
} // namespace actions

} // namespace dicomifier
