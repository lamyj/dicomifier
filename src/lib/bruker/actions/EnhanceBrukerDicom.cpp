/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "EnhanceBrukerDicom.h"

#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "bruker/Directory.h"
#include "core/DicomifierException.h"
#include "core/Endian.h"
#include "core/Hashcode.h"
#include "translator/fields/DicomField.h"
#include "translator/TranslatorFactory.h"

namespace dicomifier
{
    
namespace actions
{
    
EnhanceBrukerDicom::EnhanceBrukerDicom():
    _dataset(NULL), _brukerDir(""), _SOPClassUID(""), _outputDir("")
{
    // Nothing to do
}

EnhanceBrukerDicom::EnhanceBrukerDicom(DcmDataset * dataset, 
                                       std::string const & brukerDir,
                                       std::string const & sopclassuid,
                                       std::string const & outputDir):
    _dataset(dataset), _brukerDir(brukerDir), _SOPClassUID(sopclassuid),
    _outputDir(outputDir)
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

const std::string &
EnhanceBrukerDicom
::get_outputDir() const
{
    return this->_outputDir;
}

void
EnhanceBrukerDicom
::set_outputDir(const std::string &outputDir)
{
    this->_outputDir = outputDir;
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
    
    // Parse input bruker directory
    bruker::Directory brukerdirectory;
    brukerdirectory.load(this->_brukerDir);
    
    // Search SeriesNumber dicom element
    OFString string;
    OFCondition const cond = this->_dataset->findAndGetOFStringArray(
        DCM_SeriesNumber, string);
    if (cond.bad())
    {
        throw dicomifier::DicomifierException("Can't read SeriesNumber attribut, error = " + 
                                              std::string(cond.text()));
    }
    
    std::string const series_number(string.c_str());

    // Search corresponding Bruker Dataset
    if(!brukerdirectory.has_dataset(series_number))
    {
        throw DicomifierException("Bruker Dataset is NULL");
    }
    
    bruker::Dataset const & brukerdataset = 
        brukerdirectory.get_dataset(series_number);

    std::vector<bruker::FrameGroup> const & frame_groups = 
        brukerdataset.get_frame_groups();
        
    int coreFrameCount = 1;
    std::vector<int> indexlists;
    for(auto const & frame_group: frame_groups)
    {
        indexlists.push_back(frame_group.size);
        coreFrameCount *= frame_group.size;
    }

    // Check frame count
    if (brukerdataset.has_field("VisuCoreFrameCount"))
    {
        if (coreFrameCount != brukerdataset.get_field("VisuCoreFrameCount").get_int(0))
        {
            throw DicomifierException("Corrupted Bruker Data");
        }
    }
    
    // Create DICOM
    DicomCreator creator=NULL;
    std::string sopclassuid = dicomifier::get_SOPClassUID_from_name(this->_SOPClassUID);
    if (sopclassuid == UID_MRImageStorage)
    {
        creator = &EnhanceBrukerDicom::create_MRImageStorage;
    }
    else if (sopclassuid == UID_EnhancedMRImageStorage)
    {
        creator = &EnhanceBrukerDicom::create_EnhancedMRImageStorage;
    }
    
    if(creator == NULL)
    {
        throw DicomifierException("Unkown SOP Class UID '" + this->_SOPClassUID + "'");
    }
    
    (this->*creator)(brukerdataset, indexlists, series_number);
}

template<typename T>
std::vector<T>
read_pixel_data(bruker::Dataset const & dataset)
{
    // Read the pixel data in the native type
    std::string const filename = dataset.get_field("PIXELDATA").get_string(0);
    std::ifstream stream(filename, std::ifstream::binary);
    
    if(!stream.good())
    {
        std::ostringstream message;
        message << "Could not open file " << filename;
        throw DicomifierException(message.str());
    }

    auto const & frame_size = dataset.get_field("VisuCoreSize");
    long const items_count = 
        frame_size.get_int(0) * frame_size.get_int(1) *
        dataset.get_field("VisuCoreFrameCount").get_int(0);

    std::vector<T> native(items_count);
    stream.read((char*)(&native[0]), sizeof(T)*items_count);
    
    if(stream.bad())
    {
        std::ostringstream message;
        message << "Could not read data from " << filename;
        throw DicomifierException(message.str());
    }
    
    // Switch endianness if required
    std::string const endianness = 
        dataset.get_field("VisuCoreByteOrder").get_string(0);
    if(endianness == "bigEndian")
    {
        endian::from_big_endian(native.begin(), native.end());
    }
    else
    {
        endian::from_little_endian(native.begin(), native.end());
    }
    
    return native;
}

template<typename T>
void rescale(std::vector<T> const & native, std::vector<Uint16> & pixel_data, 
    double slope, double intercept)
{
    pixel_data.resize(native.size());
    typename std::vector<T>::const_iterator source=native.begin();
    typename std::vector<Uint16>::iterator destination=pixel_data.begin();
    while(destination != pixel_data.end())
    {
        *destination = static_cast<Uint16>((*source-intercept)/slope);
        ++source;
        ++destination;
    }
}

void 
EnhanceBrukerDicom
::_get_pixel_data(bruker::Dataset const & dataset, std::vector<Uint16> & pixel_data, 
    double & rescaleintercept, double & rescaleslope) const
{
    std::string const wordtype = dataset.get_field("VisuCoreWordType").get_string(0);
    std::string const byteorder = dataset.get_field("VisuCoreByteOrder").get_string(0);

    if (wordtype == "_32BIT_SGN_INT")
    {
        std::vector<Sint32> native = read_pixel_data<Sint32>(dataset);

        Sint32 min = *std::min_element(native.begin(), native.end());
        Sint32 max = *std::max_element(native.begin(), native.end());

        // Compute DICOM element 0028,1052 and 0028,1053
        rescaleintercept = min;
        rescaleslope     = double(max-min) / exp2(16.0);
        
        rescale(native, pixel_data, rescaleslope, rescaleintercept);
    }
    else if (wordtype == "_16BIT_SGN_INT")
    {
        std::vector<Sint16> native = read_pixel_data<Sint16>(dataset);
        
        // Compute DICOM element 0028,1052 and 0028,1053
        rescaleintercept = -exp2(15);
        rescaleslope     = 1;
        
        rescale(native, pixel_data, rescaleslope, rescaleintercept);
    }
    else if (wordtype == "_8BIT_UNSGN_INT")
    {
        std::vector<Uint8> native = read_pixel_data<Uint8>(dataset);
        
        // Compute DICOM element 0028,1052 and 0028,1053
        rescaleintercept = 0;
        rescaleslope     = 1;
        
        rescale(native, pixel_data, rescaleslope, rescaleintercept);
    }
    else if (wordtype == "_32BIT_FLOAT")
    {
        std::vector<float> native = read_pixel_data<float>(dataset);
        
        float min = *(std::min_element(native.begin(), native.end()));
        float max = *(std::max_element(native.begin(), native.end()));

        // Compute DICOM element 0028,1052 and 0028,1053
        rescaleintercept = (double)min;
        rescaleslope     = (max-min) / exp2(16.0);

        rescale(native, pixel_data, rescaleslope, rescaleintercept);
    }
    else
    {
        throw DicomifierException("Unknown VisuCoreWordType");
    }
}

boost::filesystem::path
EnhanceBrukerDicom
::get_destination_filename(DcmDataset *dataset) const
{
    OFString patientid;
    OFCondition resultdcm = dataset->findAndGetOFStringArray(DCM_PatientID, patientid);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot retrieve PatientID: " +
                                  std::string(resultdcm.text()));
    }
    OFString study_instance_uid;
    resultdcm = dataset->findAndGetOFStringArray(DCM_StudyInstanceUID, study_instance_uid);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot retrieve StudyInstanceUID: " +
                                  std::string(resultdcm.text()));
    }
    OFString series_instance_uid;
    resultdcm = dataset->findAndGetOFStringArray(DCM_SeriesInstanceUID, series_instance_uid);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot retrieve SeriesInstanceUID: " +
                                  std::string(resultdcm.text()));
    }
    OFString sop_instance_uid;
    resultdcm = dataset->findAndGetOFStringArray(DCM_SOPInstanceUID, sop_instance_uid);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot retrieve SOPInstanceUID: " +
                                  std::string(resultdcm.text()));
    }

    std::string const subject_hash =
            dicomifier::hashcode::hashToString(dicomifier::hashcode::hashCode(patientid));
    std::string const study_hash =
            dicomifier::hashcode::hashToString(dicomifier::hashcode::hashCode(study_instance_uid));
    std::string const series_hash =
            dicomifier::hashcode::hashToString(dicomifier::hashcode::hashCode(series_instance_uid));
    std::string const sop_instance_hash =
            dicomifier::hashcode::hashToString(dicomifier::hashcode::hashCode(sop_instance_uid));

    boost::filesystem::path const destination =
        boost::filesystem::path(this->_outputDir)
            /subject_hash/study_hash/series_hash/sop_instance_hash;
    boost::filesystem::create_directories(destination.parent_path());

    return destination;
}
    
void 
EnhanceBrukerDicom
::create_MRImageStorage(dicomifier::bruker::Dataset const & brukerdataset,
                        std::vector<int> indexlists,
                        std::string const & seriesnumber) const
{
    std::string conffile = "../configuration/Dictionary_BrukerToDICOM/MRImageStorage.xml";
    if ( ! boost::filesystem::exists(boost::filesystem::path(conffile.c_str())) )
    {
        conffile = "/etc/dicomifier/Dictionary_BrukerToDICOM/MRImageStorage.xml";
    }
    // Load Dictionary
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(conffile, pt);
    
    dicomifier::FrameIndexGenerator generator(indexlists);

    // Get binary data information
    int const highbit = dicomifier::endian::is_big_endian() ? 0 : 15;
    double rescaleintercept, rescaleslope;
    std::vector<Uint16> binarydata;
    this->_get_pixel_data(
        brukerdataset, binarydata, rescaleintercept, rescaleslope);

    // Compute frame size
    int const frame_size = 
        brukerdataset.get_field("VisuCoreSize").get_int(0) * 
        brukerdataset.get_field("VisuCoreSize").get_int(1);

    // Process
    while (!generator.done())
    {
        OFCondition resultdcm = EC_Normal;

        // Create a new Dataset
        DcmDataset* dataset = new DcmDataset();
        
        // Set Frame information
        // Insert SeriesNumber => use to find Bruker data
        resultdcm = dataset->putAndInsertOFStringArray(DCM_SeriesNumber,
                                                       OFString(seriesnumber.c_str()));
        if (resultdcm.bad())
        {
            throw DicomifierException("MRImageStorage cannot insert SeriesNumber: " +
                                      std::string(resultdcm.text()));
        }
                                           
        // Set binary data information
        resultdcm = dataset->putAndInsertUint16(DCM_BitsAllocated, 16);
        if (resultdcm.bad())
        {
            throw DicomifierException("MRImageStorage cannot insert BitsAllocated: " +
                                      std::string(resultdcm.text()));
        }
        resultdcm = dataset->putAndInsertUint16(DCM_BitsStored, 16);
        if (resultdcm.bad())
        {
            throw DicomifierException("MRImageStorage cannot insert BitsStored: " +
                                      std::string(resultdcm.text()));
        }
        resultdcm = dataset->putAndInsertUint16(DCM_HighBit, highbit);
        if (resultdcm.bad())
        {
            throw DicomifierException("MRImageStorage cannot insert HighBit: " +
                                      std::string(resultdcm.text()));
        }
        resultdcm = dataset->putAndInsertUint16(DCM_PixelRepresentation, 0);
        if (resultdcm.bad())
        {
            throw DicomifierException("MRImageStorage cannot insert PixelRepresentation: " +
                                      std::string(resultdcm.text()));
        }

        // Add Pixel Value Transformation Sequence
        if (rescaleintercept != 0 || rescaleslope != 1)
        {
            DcmItem* item = NULL;
            //dataset->findOrCreateSequenceItem(DCM_PixelValueTransformationSequence, 
            //                                  item, 0);
            
            std::stringstream stream;
            stream << rescaleintercept;
            resultdcm = dataset->putAndInsertOFStringArray(DCM_RescaleIntercept,
                                                           OFString(stream.str().c_str()));
            if (resultdcm.bad())
            {
                throw DicomifierException("MRImageStorage cannot insert RescaleIntercept: " +
                                          std::string(resultdcm.text()));
            }
            
            std::stringstream stream2;
            stream2 << rescaleslope;
            resultdcm = dataset->putAndInsertOFStringArray(DCM_RescaleSlope,
                                                           OFString(stream2.str().c_str()));
            if (resultdcm.bad())
            {
                throw DicomifierException("MRImageStorage cannot insert RescaleSlope: " +
                                          std::string(resultdcm.text()));
            }
            
            resultdcm = dataset->putAndInsertOFStringArray(DCM_RescaleType, OFString("US"));
            if (resultdcm.bad())
            {
                throw DicomifierException("MRImageStorage cannot insert RescaleType: " +
                                          std::string(resultdcm.text()));
            }
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
                    rule->run(const_cast<bruker::Dataset*>(&brukerdataset), generator, dataset);
                }
                else
                {
                    throw DicomifierException("Bad dictionary Bruker to Dicom");
                }
            }
        }

        // Add binary Data
        // TODO: who managers the buffer ?
        resultdcm = dataset->putAndInsertUint16Array(DCM_PixelData,
                                        (Uint16*)(&binarydata[generator.get_step()*frame_size]),
                                        frame_size);
        if (resultdcm.bad())
        {
            throw DicomifierException("MRImageStorage cannot insert PixelData: " +
                                      std::string(resultdcm.text()));
        }
        // TODO (maybe) delete[] binarydata;

        // Write DICOM Dataset
        // Create path:
        boost::filesystem::path const destination = this->get_destination_filename(dataset);

        // write file
        DcmFileFormat fileformat(dataset);
        OFCondition result = fileformat.saveFile(destination.c_str(),
                                                 EXS_LittleEndianExplicit);
        if (result.bad())
        {
            throw DicomifierException("Unable to save dataset: " + 
                                      std::string(result.text()));
        }

        generator.next();
    }
}

void 
EnhanceBrukerDicom
::create_EnhancedMRImageStorage(dicomifier::bruker::Dataset const & brukerdataset,
                                std::vector<int> indexlists,
                                std::string const & seriesnumber) const
{
    std::string conffile = "../configuration/Dictionary_BrukerToDICOM/EnhancedMRImageStorage.xml";
    if ( ! boost::filesystem::exists(boost::filesystem::path(conffile.c_str())) )
    {
        conffile = "/etc/dicomifier/Dictionary_BrukerToDICOM/EnhancedMRImageStorage.xml";
    }

    // Load Dictionary
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(conffile, pt);
    
    dicomifier::FrameIndexGenerator generator(indexlists);
    
    // Get binary data information
    int const highbit = dicomifier::endian::is_big_endian() ? 0 : 15;
    double rescaleintercept, rescaleslope;
    std::vector<Uint16> binarydata;
    this->_get_pixel_data(
        brukerdataset, binarydata, rescaleintercept, rescaleslope);

    // Create a new Dataset
    DcmDataset* dataset = new DcmDataset();
    
    OFCondition resultdcm = EC_Normal;

    // Set Frame information
    // Insert SeriesNumber => use to find Bruker data
    resultdcm = dataset->putAndInsertOFStringArray(DCM_SeriesNumber,
                                                   OFString(seriesnumber.c_str()));
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot insert SeriesNumber: " +
                                  std::string(resultdcm.text()));
    }
        
    // Set binary data information
    resultdcm = dataset->putAndInsertUint16(DCM_BitsAllocated, 16);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot insert BitsAllocated: " +
                                  std::string(resultdcm.text()));
    }
    resultdcm = dataset->putAndInsertUint16(DCM_BitsStored, 16);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot insert BitsStored: " +
                                  std::string(resultdcm.text()));
    }
    resultdcm = dataset->putAndInsertUint16(DCM_HighBit, highbit);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot insert HighBit: " +
                                  std::string(resultdcm.text()));
    }
    resultdcm = dataset->putAndInsertUint16(DCM_PixelRepresentation, 0);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot insert PixelRepresentation: " +
                                  std::string(resultdcm.text()));
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
                rule->run(const_cast<bruker::Dataset*>(&brukerdataset), generator, dataset);
            }
            else
            {
                throw DicomifierException("Bad dictionary Bruker to Dicom");
            }
        }
    }

    // Process
    DcmItem* seq = NULL;
    resultdcm = dataset->findOrCreateSequenceItem(DCM_SharedFunctionalGroupsSequence,
                                                  seq, 0);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot create SharedFunctionalGroupsSequence: " +
                                  std::string(resultdcm.text()));
    }
                                      
                                      
    // Begin Insert Pixel Value Transformation Sequence
    DcmItem* item = NULL;
    resultdcm = seq->findOrCreateSequenceItem(DCM_PixelValueTransformationSequence,
                                              item, -2);
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot create PixelValueTransformationSequence: " +
                                  std::string(resultdcm.text()));
    }
    
    std::stringstream stream;
    stream << rescaleintercept;
    resultdcm = item->putAndInsertOFStringArray(DCM_RescaleIntercept,
                                    OFString(stream.str().c_str()));
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot insert RescaleIntercept: " +
                                  std::string(resultdcm.text()));
    }

    std::stringstream stream2;
    stream2 << rescaleslope;
    resultdcm = item->putAndInsertOFStringArray(DCM_RescaleSlope,
                                    OFString(stream2.str().c_str()));
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot insert RescaleSlope: " +
                                  std::string(resultdcm.text()));
    }
    
    resultdcm = item->putAndInsertOFStringArray(DCM_RescaleType, OFString("US"));
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot insert RescaleType: " +
                                  std::string(resultdcm.text()));
    }
    // end Insert Pixel Value Transformation Sequence


    // Add binary Data
    // TODO: who managers the buffer ?
    resultdcm = dataset->putAndInsertUint16Array(DCM_PixelData,
                                                 (Uint16*)(&binarydata[0]),
                                                 binarydata.size());
    if (resultdcm.bad())
    {
        throw DicomifierException("EnhancedMRImageStorage cannot insert PixelData: " +
                                  std::string(resultdcm.text()));
    }
    // TODO (maybe) delete[] binarydata;

    // Create path:        
    boost::filesystem::path const destination = this->get_destination_filename(dataset);

    // Write DICOM Dataset
    DcmFileFormat fileformat(dataset);
    OFCondition result = fileformat.saveFile(destination.c_str(),
                                             EXS_LittleEndianExplicit);
    if (result.bad())
    {
        throw DicomifierException("Unable to save dataset: " + 
                                  std::string(result.text()));
    }
}
    
} // namespace actions

} // namespace dicomifier
