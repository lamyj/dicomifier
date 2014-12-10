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
#include "core/Endian.h"
#include "core/Hashcode.h"
#include "EnhanceBrukerDicom.h"
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
    
    dicomifier::bruker::BrukerDirectory* brukerdirectory = 
            new dicomifier::bruker::BrukerDirectory();

    // Parse input bruker directory
    int result = brukerdirectory->CreateMap(this->_brukerDir);
    
    // Search SeriesNumber dicom element
    OFString str;
    OFCondition cond = this->_dataset->findAndGetOFStringArray(DCM_SeriesNumber, 
                                                               str);
    if (cond.bad())
    {
        throw dicomifier::DicomifierException("Can't read SeriesNumber attribut, error = " + 
                                              std::string(cond.text()));
    }

    // Search corresponding Bruker Dataset
    dicomifier::bruker::BrukerDataset* brukerdataset = 
            brukerdirectory->get_brukerDataset(str.c_str());

    if (brukerdataset == NULL)
    {
        throw DicomifierException("Bruker Dataset is NULL");
    }

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
    else if (sopclassuid == UID_EnhancedMRImageStorage)
    {
        this->create_EnhancedMRImageStorage(brukerdataset, indexlists, 
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
::get_binary_data_information(dicomifier::bruker::BrukerDataset* brukerdataset,
                              std::vector<Uint16>& uint16vector, int const & size,
                              int & highbit, bool & addtransformationsequence,
                              double & rescaleintercept, double & rescaleslope) const
{
    std::string const wordtype = brukerdataset->GetFieldData("VisuCoreWordType")->get_string(0);
    std::string const byteorder = brukerdataset->GetFieldData("VisuCoreByteOrder")->get_string(0);

    // Endianess
    highbit = dicomifier::endian::is_big_endian() ? 0 : 15;

    addtransformationsequence = true;
    if (wordtype == "_32BIT_SGN_INT")
    {
        std::vector<Sint32> sint32vector(size);

        // Read binary data
        std::ifstream is(brukerdataset->GetFieldData("PIXELDATA")->get_string(0).c_str(),
                         std::ifstream::binary);
        is.read((char*)(&sint32vector[0]), size*sizeof(Sint32));

        Sint32 min = *(std::min_element(sint32vector.begin(), sint32vector.end()));
        Sint32 max = *(std::max_element(sint32vector.begin(), sint32vector.end()));

        // Compute DICOM element 0028,1052 and 0028,1053
        rescaleintercept = (double)min;
        rescaleslope     = (max-min) / exp2(16.0);

        if (byteorder == "bigEndian")
        {
            dicomifier::endian::from_big_endian(sint32vector.begin(), sint32vector.end());
        }
        else
        {
            dicomifier::endian::from_little_endian(sint32vector.begin(), sint32vector.end());
        }

        // Convert data
        for (unsigned int i = 0; i < size; i++)
        {
            uint16vector[i] = (sint32vector[i] - min) * exp2(16.0) / (max - min) - exp2(15);
        }
    }
    else if (wordtype == "_16BIT_SGN_INT")
    {
        std::vector<Sint16> sint16vector(size);

        // Read binary data
        std::ifstream is(brukerdataset->GetFieldData("PIXELDATA")->get_string(0).c_str(),
                         std::ifstream::binary);
        is.read((char*)(&sint16vector[0]), size*sizeof(Sint16));

        // Compute DICOM element 0028,1052 and 0028,1053
        rescaleintercept = -exp2(15);
        rescaleslope     = 1;

        if (byteorder == "bigEndian")
        {
            dicomifier::endian::from_big_endian(sint16vector.begin(), sint16vector.end());
        }
        else
        {
            dicomifier::endian::from_little_endian(sint16vector.begin(), sint16vector.end());
        }

        for (unsigned int i = 0; i < size; i++)
        {
            uint16vector[i] = sint16vector[i] + exp2(15);
        }
    }
    else if (wordtype == "_8BIT_UNSGN_INT")
    {
        std::vector<Uint8> uint8vector(size);

        // Compute DICOM element 0028,1052 and 0028,1053
        rescaleintercept = 0;
        rescaleslope     = 1;
        addtransformationsequence = false;

        // Read binary data
        std::ifstream is(brukerdataset->GetFieldData("PIXELDATA")->get_string(0).c_str(),
                         std::ifstream::binary);
        is.read((char*)(&uint8vector[0]), size);

        for (unsigned int i = 0; i < size; i++)
        {
            uint16vector[i] = uint8vector[i];
        }

    }
    else if (wordtype == "_32BIT_FLOAT")
    {
        std::vector<float> floatvector(size);

        // Read binary data
        std::ifstream is(brukerdataset->GetFieldData("PIXELDATA")->get_string(0).c_str(),
                         std::ifstream::binary);
        is.read((char*)(&floatvector[0]), size*sizeof(float));

        float min = *(std::min_element(floatvector.begin(), floatvector.end()));
        float max = *(std::max_element(floatvector.begin(), floatvector.end()));

        // Compute DICOM element 0028,1052 and 0028,1053
        rescaleintercept = (double)min;
        rescaleslope     = (max-min) / exp2(16.0);

        if (byteorder == "bigEndian")
        {
            dicomifier::endian::from_big_endian(floatvector.begin(), floatvector.end());
        }
        else
        {
            dicomifier::endian::from_little_endian(floatvector.begin(), floatvector.end());
        }

        // Convert data
        for (unsigned int i = 0; i < size; i++)
        {
            uint16vector[i] = (floatvector[i] - min) * exp2(16.0) / (max - min) - exp2(15);
        }
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
::create_MRImageStorage(dicomifier::bruker::BrukerDataset* brukerdataset,
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
    int highbit;
    bool addtransformationsequence = false;
    double rescaleintercept, rescaleslope;

    // Compute buffer size
    int size  = brukerdataset->GetFieldData("VisuCoreSize")->get_int(0);
    size     *= brukerdataset->GetFieldData("VisuCoreSize")->get_int(1);

    std::vector<Uint16> binarydata(size*generator.get_countMax());

    this->get_binary_data_information(brukerdataset,
                                      binarydata, size, highbit,
                                      addtransformationsequence,
                                      rescaleintercept, rescaleslope);

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
        if (addtransformationsequence)
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
        resultdcm = dataset->putAndInsertUint16Array(DCM_PixelData,
                                        (Uint16*)(&binarydata[generator.get_step()*size]),
                                        size);
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
::create_EnhancedMRImageStorage(dicomifier::bruker::BrukerDataset* brukerdataset,
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
    int highbit;
    bool addtransformationsequence = false;
    double rescaleintercept, rescaleslope;

    // Compute buffer size
    int size  = brukerdataset->GetFieldData("VisuCoreSize")->get_int(0);
    size     *= brukerdataset->GetFieldData("VisuCoreSize")->get_int(1);

    std::vector<Uint16> binarydata(size*generator.get_countMax());

    this->get_binary_data_information(brukerdataset,
                                      binarydata, size, highbit,
                                      addtransformationsequence,
                                      rescaleintercept, rescaleslope);

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
                rule->run(brukerdataset, generator, dataset);
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
                                                 size*generator.get_countMax());
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
