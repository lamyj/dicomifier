/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _a1d24eb4_37bb_46b4_a769_d76392230052
#define _a1d24eb4_37bb_46b4_a769_d76392230052

#include <memory>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>

#include <dcmtkpp/DataSet.h>

#include "bruker/Dataset.h"
#include "core/FrameIndexGenerator.h"
#include "dicom/SOPClass.h"

namespace dicomifier
{
    
namespace bruker
{

/**
 * @brief The EnhanceBrukerDicom class: Convert Bruker directory into Dicom Datasets
 */
class EnhanceBrukerDicom
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
    static Pointer New(
        std::string const & brukerDir, std::string const & sopclassuid,
        std::string const & outputDir, std::string const & studyNumber,
        std::string const & seriesNumber)
    {
        return Pointer(
            new Self(
                brukerDir, sopclassuid, outputDir, studyNumber, seriesNumber));
    }
    
    /// Destroy the instance of EnhanceBrukerDicom
    virtual ~EnhanceBrukerDicom();
    
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
    void run() const;

    static std::string get_default_directory_name(boost::filesystem::path const &parentdirectory);

    static void replace_unavailable_char(std::string &text);

    /**
     * @brief get_destination_filename: get formatted output filepath
     * @param dataset: dataset to write
     * @return output filepath
     */
    boost::filesystem::path get_destination_filename(
        dcmtkpp::DataSet const & dataset, bool usefileformat = true) const;

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
    EnhanceBrukerDicom(std::string const & brukerDir,
                       std::string const & sopclassuid,
                       std::string const & outputDir,
                       std::string const & studyNumber,
                       std::string const & seriesNumber);

private:
    void _create_mr_image_storage(bruker::Dataset const & bruker_dataset) const;

    std::string create_directory_name(int sizemax, std::string const & prefix, std::string const & suffix) const;

    /// Path of Bruker directory
    std::string _brukerDir;

    /// DICOM SOP Class UID
    std::string _SOPClassUID;

    /// Path to write DICOM Datasets
    std::string _outputDir;

    std::string _studyNumber;

    std::string _seriesNumber;
    
    EnhanceBrukerDicom(Self const & other);     // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented
    
};
    
} // namespace bruker
    
} // namespace dicomifier

#endif // _a1d24eb4_37bb_46b4_a769_d76392230052
