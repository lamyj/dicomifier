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

#include "core/DicomifierException.h"
#include "core/FrameIndexGenerator.h"
#include "EnhanceBrukerDicom.h"
#include "translator/fields/DicomField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace actions
{
    
EnhanceBrukerDicom::EnhanceBrukerDicom():
    _dataset(NULL), _brukerDir(""), _SOPClassUID("")
{
    // Nothing to do
}

EnhanceBrukerDicom::EnhanceBrukerDicom(DcmDataset * dataset, 
                                       std::string const & brukerDir,
                                       std::string const & sopclassuid):
    _dataset(dataset), _brukerDir(brukerDir), _SOPClassUID(sopclassuid)
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

std::string const & 
EnhanceBrukerDicom
::get_SOPClassUID() const
{
    return this->_SOPClassUID;
}

void 
EnhanceBrukerDicom
::set_SOPClassUID(std::string const & sopclassuid)
{
    this->_SOPClassUID = sopclassuid;
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
    
    // read VisuFGOrderDescDim (int), VisuFGOrderDesc (string) and VisuGroupDepVals (string)
    if (!brukerdataset->HasFieldData("VisuFGOrderDescDim")  ||
        !brukerdataset->HasFieldData("VisuFGOrderDesc")     ||
        !brukerdataset->HasFieldData("VisuGroupDepVals"))
    {
        throw dicomifier::DicomifierException("Corrupted Bruker Data");
    }
    // First: look the VisuFGOrderDescDim attribut (Number of frame groups)
    int frameGroupDim = brukerdataset->GetFieldData("VisuFGOrderDescDim")->get_int(0);

    int coreFrameCount = 1;
    
    std::vector<VISU_FRAMEGROUP_TYPE> frameGroupLists;
    std::vector<int> indexlists;
    // Second: look the VisuFGOrderDesc to compute frame count
    for (auto count = 0; count < frameGroupDim; count++)
    {
        VISU_FRAMEGROUP_TYPE currentGroup;
        
        dicomifier::bruker::BrukerFieldData::Pointer fielddata = 
            brukerdataset->GetFieldData("VisuFGOrderDesc")->get_struct(count);
            
        currentGroup.length = fielddata->get_int(0);
        int start   = fielddata->get_int(3);
        int number  = fielddata->get_int(4);
        
        for (auto gdvcount = start; gdvcount < start+number; gdvcount++)
        {
            currentGroup.groupDepVals.push_back
            (
                brukerdataset->GetFieldData("VisuGroupDepVals")->get_struct(gdvcount)->get_string(0)
            );
        }
        indexlists.push_back(currentGroup.length);
        coreFrameCount *= currentGroup.length;
        
        frameGroupLists.push_back(currentGroup);
    }
    
    // Check frame count
    if (brukerdataset->HasFieldData("VisuCoreFrameCount"))
    {
        if (coreFrameCount != brukerdataset->GetFieldData("VisuCoreFrameCount")->get_int(0))
        {
            throw DicomifierException("Corrupted Bruker Data");
        }
    }
    
    indexlists.push_back(coreFrameCount);
    
    // Create DICOM
    std::string sopclassuid = dicomifier::get_SOPClassUID_from_name(this->_SOPClassUID);
    if (sopclassuid == dicomifier::MRImageStorage)
    {
        this->create_MRImageStorage(brukerdataset, indexlists, 
                                    str.c_str(), coreFrameCount);
    }
    else
    {
        throw DicomifierException("Unkown SOP Class UID '" + this->_SOPClassUID + "'");
    }
    
    delete brukerdirectory;
}
    
void 
EnhanceBrukerDicom
::create_MRImageStorage(dicomifier::bruker::BrukerDataset* brukerdataset,
                        std::vector<int> indexlists,
                        std::string const & seriesnumber,
                        int framesNumber) const
{
    // Load Dictionary
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml("/home/lahaxe/dicomifier/BrukerToDicom_Dictionary.xml", pt); // TODO: mettre en conf le chemin
    
    // Read binary data
    int size = brukerdataset->GetFieldData("IM_SIX")->get_int(0);
    size *= brukerdataset->GetFieldData("IM_SIY")->get_int(0);
    int pixelSize;
    dicomifier::bruker::BrukerDirectory::
        getImhDataType(brukerdataset->GetFieldData("DATTYPE"), pixelSize);
    size *= pixelSize;
    
    std::ifstream is(brukerdataset->GetFieldData("PIXELDATA")->get_string(0), 
                     std::ifstream::binary);
    char * binarydata = new char[size*framesNumber];
    memset(binarydata, 0, size*framesNumber);
    is.read(binarydata, size*framesNumber);
    
    dicomifier::FrameIndexGenerator generator(indexlists);
    
    // Process
    while (!generator.done())
    //for (auto count = 0; count < framesNumber; count++)
    {
        std::vector<int> indexes = generator.next();
        int count = 0;
        // Create a new Dataset
        DcmDataset* dataset = new DcmDataset();
        
        std::stringstream stream;
        stream << count;
        
        // Set Frame information
        // Insert SeriesNumber => use to find Bruker data
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, 
                                           OFString(seriesnumber.c_str()));
        // Set Instance Number
        dataset->putAndInsertOFStringArray(DCM_InstanceNumber, 
                                           OFString(stream.str().c_str()));
        // Set Acquisition Number
        dataset->putAndInsertOFStringArray(DCM_AcquisitionNumber, 
                                           OFString(stream.str().c_str()));
        
        // Parse and run all dictionary entries
        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt) // Tag Dictionary
        {
            BOOST_FOREACH(boost::property_tree::ptree::value_type &dicomfield, 
                      v.second.equal_range("DicomField"))
            {
                auto rule = dicomifier::translator::
                    TranslatorFactory::get_instance().create(dicomfield,
                                                             dataset,
                                                             EVR_UN);
                
                if (rule != NULL)
                {
                    rule->run(brukerdataset, indexes, dataset);
                }
                else
                {
                    throw DicomifierException("Bad dictionary Bruker to Dicom");
                }
            }
        }
        
        // Add binary Data
        // TODO: who managers the buffer ?
        dataset->putAndInsertUint8Array(DCM_PixelData, 
                                        (Uint8*)(binarydata+count*size), 
                                        size);
        // TODO (maybe) delete[] binarydata;
        
        // Write DICOM Dataset
        // Create path:
        char temp[256];
        memset(&temp[0], 0, 256);
        snprintf(&temp[0], 256, "%s%04d", 
                 "/home/lahaxe/resultDICOM/dicom_", count); // TODO: changer le chemin et le nom du fichier
        // write file
        DcmFileFormat fileformat(dataset);
        OFCondition result = fileformat.saveFile(&temp[0], 
                                                 EXS_LittleEndianExplicit);
        if (result.bad())
        {
            throw DicomifierException("Unable to save dataset: " + 
                                      std::string(result.text()));
        }
    }
}
    
} // namespace actions

} // namespace dicomifier
