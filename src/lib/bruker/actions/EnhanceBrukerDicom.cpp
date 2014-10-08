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
    
    // TODO: read VisuFGOrderDescDim (int), VisuFGOrderDesc (string) and VisuGroupDepVals (string)
    // First look the VisuFGOrderDescDim attribut (Number of frame groups)
    /*if (!brukerdataset->HasFieldData("VisuFGOrderDescDim"))
    {
        throw dicomifier::DicomifierException("Corrupted Bruker Data");
    }
    int frameGroupDim = brukerdataset->GetFieldData("VisuFGOrderDescDim")->get_int(0);
    
    std::vector<VISU_FRAMEGROUP_TYPE> frameGroupLists;
    if (frameGroupDim > 0)
    {
        // VisuFGOrderDesc should exist (Frame group description)
        if (!brukerdataset->HasFieldData("VisuFGOrderDesc"))
        {
            throw dicomifier::DicomifierException("Corrupted Bruker Data");
        }
        
        // Parse VisuFGOrderDesc values
        for (std::string currentvalue : brukerdataset->GetFieldData("VisuFGOrderDesc").GetStringValue())
        {
            // search ')'
            int pos = 0;
            while (pos < currentvalue.length()-1)
            {
                int findpos = currentvalue.find(')', pos);
                if (findpos == std::string::npos)
                {
                    pos = currentvalue.length();
                }
                else
                {
                    std::string findGroup = currentvalue.substr(pos, findpos+1-pos);
                    
                    boost::replace_all(findGroup, "(", "");
                    boost::replace_all(findGroup, ")", "");
                    boost::replace_all(findGroup, "<", "");
                    boost::replace_all(findGroup, ">", "");
                    
                    std::vector<std::string> splitvalues;
                    boost::split(splitvalues, findGroup, boost::is_any_of(","));
                    
                    VISU_FRAMEGROUP_TYPE frameGroup;
                    
                    pos = findpos+1;
                }
            }
        }
    }
    std::cout << brukerdataset->GetFieldData("VisuFGOrderDesc").GetStringValue()[0] << std::endl;
    std::cout << brukerdataset->GetFieldData("VisuGroupDepVals").GetStringValue()[0] << std::endl;
    std::cout << brukerdataset->GetFieldData("VisuGroupDepVals").GetStringValue().size() << std::endl;*/
    
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
    int size = brukerdataset->GetFieldData("IM_SIX")->get_int(0);
    size *= brukerdataset->GetFieldData("IM_SIY")->get_int(0);
    size *= brukerdataset->GetFieldData("VisuCoreFrameCount")->get_int(0);
    int pixelSize;
    brukerdirectory->getImhDataType(brukerdataset->GetFieldData("DATTYPE"), pixelSize);
    size *= pixelSize;
    
    std::ifstream is(brukerdataset->GetFieldData("PIXELDATA")->get_string(0), 
                     std::ifstream::binary);
    char * binarydata = new char[size];
    memset(binarydata, 0, size);
    is.read(binarydata, size);
    
    // TODO: who managers the buffer ?
    this->_dataset->putAndInsertUint8Array(DCM_PixelData, (Uint8*)binarydata, size);
    // TODO (maybe) delete[] binarydata;
    
    delete brukerdirectory;
}
    
} // namespace actions

} // namespace dicomifier
