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
    
    int coreFrameCount = 0;
    
    std::vector<int> indexlists = brukerdataset->create_frameGroupLists(coreFrameCount);
    
    // Check frame count
    if (brukerdataset->HasFieldData("VisuCoreFrameCount"))
    {
        if (coreFrameCount != brukerdataset->GetFieldData("VisuCoreFrameCount")->get_int(0))
        {
            throw DicomifierException("Corrupted Bruker Data");
        }
    }
    
    // Create DICOM
    std::string sopclassuid = dicomifier::get_SOPClassUID_from_name(this->_SOPClassUID);
    if (sopclassuid == UID_MRImageStorage)
    {
        this->create_MRImageStorage(brukerdataset, indexlists, 
                                    str.c_str());
    }
    else
    {
        throw DicomifierException("Unkown SOP Class UID '" + this->_SOPClassUID + "'");
    }
    
    delete brukerdirectory;
}

void 
EnhanceBrukerDicom
::convert_32to16bits(char* inputbuffer, int inputbuffersize,
                     char* outputbuffer,
                     double & rescaleintercept, double & rescaleslope) const
{
    // search min and max
    Sint32 min = (Sint32)(exp2(32.)-1);
    Sint32 max = (Sint32)(-exp2(32.));
    for (auto i = 0; i < inputbuffersize; i += sizeof(Sint32))
    {
        Sint32* value = (Sint32*)(inputbuffer+i);
        if (*value > max)
        {
            max = *value;
        }
        if (*value < min)
        {
            min = *value;
        }
    }
    
    // Compute DICOM element 0028,1052 and 0028,1053
    rescaleintercept = (double)min;
    rescaleslope = (max-min) / exp2(16.0);
    
    // Convert data
    for (auto i = 0; i < inputbuffersize; i += sizeof(Sint32))
    {
        Sint32* value = (Sint32*)(inputbuffer+i);
        
        Sint16 dicomvalue = (*value - min) * exp2(16.0) / (max - min) - exp2(15);
        
        memcpy(outputbuffer+i/2, (char*)(&dicomvalue), sizeof(Sint16));
    }
}
    
void 
EnhanceBrukerDicom
::create_MRImageStorage(dicomifier::bruker::BrukerDataset* brukerdataset,
                        std::vector<int> indexlists,
                        std::string const & seriesnumber) const
{
    // Load Dictionary
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml("/home/lahaxe/dicomifier/BrukerToDicom_Dictionary.xml", pt); // TODO: mettre en conf le chemin
    
    dicomifier::FrameIndexGenerator generator(indexlists);
    
    // Get binary data information
    int pixelSize, bitsallocated, bitsstored, highbit, pixelrepresentation;
    dicomifier::bruker::BrukerDirectory::
        getImhDataType(brukerdataset->GetFieldData("VisuCoreWordType")->get_string(0), 
                       brukerdataset->GetFieldData("VisuCoreByteOrder")->get_string(0),
                       pixelSize, bitsallocated, bitsstored, highbit,
                       pixelrepresentation);
                       
    // Compute buffer size
    int size = brukerdataset->GetFieldData("VisuCoreSize")->get_int(0);
    size    *= brukerdataset->GetFieldData("VisuCoreSize")->get_int(1);
    size    *= pixelSize;
    
    // Read binary data
    std::ifstream is(brukerdataset->GetFieldData("PIXELDATA")->get_string(0), 
                     std::ifstream::binary);
    char * binarydata = new char[size*generator.get_countMax()];
    memset(binarydata, 0, size*generator.get_countMax());
    is.read(binarydata, size*generator.get_countMax());
    
    bool addtransformationsequence = false;
    double rescaleintercept, rescaleslope;
    if (bitsstored == 32)
    {
        // Create new buffer 16bits
        char * outputbuffer = new char[size*generator.get_countMax()/2];
    
        this->convert_32to16bits(binarydata, size*generator.get_countMax(), 
                                 outputbuffer, rescaleintercept, rescaleslope);
        
        // size / 2
        size /= 2;
        bitsstored /= 2;
        bitsallocated /= 2;
        if (highbit != 0)
        {
            highbit = (highbit + 1) / 2 - 1;
        }
        
        // Delete buffer 32bits
        delete [] binarydata;
        // Replace by buffer 16bits
        binarydata = outputbuffer;
        
        addtransformationsequence = true;
    }
    
    // Process
    while (!generator.done())
    {
        // Create a new Dataset
        DcmDataset* dataset = new DcmDataset();
        
        // Set Frame information
        // Insert SeriesNumber => use to find Bruker data
        dataset->putAndInsertOFStringArray(DCM_SeriesNumber, 
                                           OFString(seriesnumber.c_str()));
                                           
        // Set binary data information
        dataset->putAndInsertUint16(DCM_BitsAllocated, bitsallocated);
        dataset->putAndInsertUint16(DCM_BitsStored, bitsstored);
        dataset->putAndInsertUint16(DCM_HighBit, highbit);
        dataset->putAndInsertUint16(DCM_PixelRepresentation, pixelrepresentation);
        
        // Add Pixel Value Transformation Sequence
        if (addtransformationsequence)
        {
            DcmItem* item = NULL;
            dataset->findOrCreateSequenceItem(DCM_PixelValueTransformationSequence, 
                                              item, 0);
            
            std::stringstream stream;
            stream << rescaleintercept;
            item->putAndInsertOFStringArray(DCM_RescaleIntercept, 
                                            OFString(stream.str().c_str()));
            
            std::stringstream stream2;
            stream2 << rescaleslope;
            item->putAndInsertOFStringArray(DCM_RescaleSlope, 
                                            OFString(stream2.str().c_str()));
            
            item->putAndInsertOFStringArray(DCM_RescaleType, OFString("US"));
        }
        
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
                    rule->run(brukerdataset, generator, dataset);
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
                                        (Uint8*)(binarydata+generator.get_step()*size), 
                                        size);
        // TODO (maybe) delete[] binarydata;
        
        // Write DICOM Dataset
        // Create path:
        char temp[256];
        memset(&temp[0], 0, 256);
        snprintf(&temp[0], 256, "%s%04d", 
                 "/home/lahaxe/resultDICOM/dicom_", (generator.get_step() + 1)); // TODO: changer le chemin et le nom du fichier
        // write file
        DcmFileFormat fileformat(dataset);
        OFCondition result = fileformat.saveFile(&temp[0], 
                                                 EXS_LittleEndianExplicit);
        if (result.bad())
        {
            throw DicomifierException("Unable to save dataset: " + 
                                      std::string(result.text()));
        }
        
        generator.next();
    }
}
    
} // namespace actions

} // namespace dicomifier
