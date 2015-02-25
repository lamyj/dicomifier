/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a1d24eb4_37bb_46b4_a769_d76392230052
#define _a1d24eb4_37bb_46b4_a769_d76392230052

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "bruker/BrukerDirectory.h"
#include "core/actions/Action.h"
#include "core/FrameIndexGenerator.h"
#include "dicom/SOPClass.h"

namespace dicomifier
{
    
namespace actions
{

/**
 * @brief The EnhanceBrukerDicom class: Convert Bruker directory into Dicom Datasets
 */
class EnhanceBrukerDicom : public Action
{
public:
    typedef EnhanceBrukerDicom Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of EnhanceBrukerDicom
    static Pointer New() { return Pointer(new Self()); }

    /**
     * @brief Create pointer to new instance of EnhanceBrukerDicom
     * @param dataset: DICOM dataset
     * @param brukerDir: Bruker Directory Path
     * @param sopclassuid: Output SOP Class UID
     * @param outputDir: Directory to store DICOM files
     * @return
     */
    static Pointer New(DcmDataset * dataset, 
                       std::string const & brukerDir,
                       std::string const & sopclassuid,
                       std::string const & outputDir,
                       std::string const & studyNumber)
                { return Pointer(new Self(dataset, brukerDir, 
                                          sopclassuid, outputDir,
                                          studyNumber)); }
    
    /// Destroy the instance of EnhanceBrukerDicom
    virtual ~EnhanceBrukerDicom();

    /**
     * @brief get_dataset: getter for dataset
     * @return DICOM dataset
     */
    DcmDataset * get_dataset() const;

    /**
     * @brief set_dataset: setter for dataset
     * @param dataset: new value
     */
    void set_dataset(DcmDataset * dataset);
    
    /**
     * @brief get_brukerDir: getter for brukerDir
     * @return brukerDir
     */
    std::string const & get_brukerDir() const;

    /**
     * @brief set_brukerDir: setter for brukerDir
     * @param brukerDir: new value
     */
    void set_brukerDir(std::string const & brukerDir);
    
    /**
     * @brief get_SOPClassUID: getter for sopclassuid
     * @return sopclassuid
     */
    std::string const & get_SOPClassUID() const;

    /**
     * @brief set_SOPClassUID: setter for sopclassuid
     * @param sopclassuid: new value
     */
    void set_SOPClassUID(std::string const & sopclassuid);

    /**
     * @brief get_outputDir: getter for outputDir
     * @return outputDir
     */
    std::string const & get_outputDir() const;

    /**
     * @brief set_outputDir: setter for outputDir
     * @param outputDir: new value
     */
    void set_outputDir(std::string const & outputDir);

    /**
     * @brief run: Execute the conversion
     */
    virtual void run() const;
    
    /**
     * @brief get_class_name: return this class name
     * @return EnhanceBrukerDicom
     */
    static std::string get_class_name() { return "EnhanceBrukerDicom"; }

    static std::string get_default_directory_name(boost::filesystem::path const &parentdirectory);

    static void replace_unavailable_char(std::string &text);

protected:
    /// Create an instance of EnhanceBrukerDicom
    EnhanceBrukerDicom();

    /**
     * @brief Create an instance of EnhanceBrukerDicom
     * @param dataset: DICOM dataset
     * @param brukerDir: Bruker Directory Path
     * @param sopclassuid: Output SOP Class UID
     * @param outputDir: Directory to store DICOM files
     */
    EnhanceBrukerDicom(DcmDataset * dataset,
                       std::string const & brukerDir,
                       std::string const & sopclassuid,
                       std::string const & outputDir,
                       std::string const & studyNumber);

private:
    /**
     * @brief get_binary_data_information: Get all information about Image
     * @param brukerdataset: Bruker Dataset to convert
     * @param uint16vector: (out) image
     * @param size: size of the image
     * @param highbit: (out) high bit (depends on Little endian or Big endian)
     * @param addtransformationsequence: (out) Flag for indicate if buffer is convert to 16 bits
     * @param rescaleintercept: (out) value for DICOM field 0028,1052
     * @param rescaleslope: (out) value for DICOM field 0028,1053
     */
    void get_binary_data_information
        (
                dicomifier::bruker::BrukerDataset* brukerdataset,
                std::vector<Uint16>& uint16vector, int const & size,
                int & highbit, bool & addtransformationsequence,
                double & rescaleintercept, double & rescaleslope
        ) const;

    /**
     * @brief get_destination_filename: get formatted output filepath
     * @param dataset: dataset to write
     * @return output filepath
     */
    boost::filesystem::path get_destination_filename(DcmDataset* dataset) const;
                            
    /**
     * @brief create_MRImageStorage: Create DICOM files for SOP Class UID MRImageStorage
     * @param brukerdataset: Bruker Dataset to convert
     * @param indexlists: current indexes
     * @param seriesnumber: Series Number
     */
    void create_MRImageStorage(dicomifier::bruker::BrukerDataset* brukerdataset,
                               std::vector<int> indexlists,
                               std::string const & seriesnumber) const;
                               
    /**
     * @brief create_EnhancedMRImageStorage: Create DICOM files for SOP Class UID EnhancedMRImageStorage
     * @param brukerdataset: Bruker Dataset to convert
     * @param indexlists: current indexes
     * @param seriesnumber: Series Number
     */
    void create_EnhancedMRImageStorage(dicomifier::bruker::BrukerDataset* brukerdataset,
                                       std::vector<int> indexlists,
                                       std::string const & seriesnumber) const;

    std::string create_directory_name(int sizemax, std::string const & prefix, std::string const & suffix) const;
    
    /// DICOM Dataset
    DcmDataset * _dataset;

    /// Path of Bruker directory
    std::string _brukerDir;

    /// DICOM SOP Class UID
    std::string _SOPClassUID;

    /// Path to write DICOM Datasets
    std::string _outputDir;

    std::string _studyNumber;
    
    EnhanceBrukerDicom(Self const & other);     // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace actions
    
} // namespace dicomifier

#endif // _a1d24eb4_37bb_46b4_a769_d76392230052
