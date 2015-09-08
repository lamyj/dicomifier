/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _dd823cac_d7b3_4eb7_b579_c6bb5e64c2a6
#define _dd823cac_d7b3_4eb7_b579_c6bb5e64c2a6

#include <memory>
#include <string>

#include <jsoncpp/json/json.h>

#include <nifti/nifti1_io.h>

namespace dicomifier
{

namespace nifti
{

enum NIfTI_Dimension
{
    Dimension3 = 3,
    Dimension4 = 4
};

class Dicom2Nifti
{
public:
    typedef Dicom2Nifti Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of Dicom2Nifti
    static Pointer New();

    /**
     * @brief Create pointer to new instance of Dicom2Nifti
     * @param brukerDir: Bruker Directory Path
     * @param outputDir: Directory to store NIfTI files
     * @return
     */
    static Pointer New(
        std::string const & dicomDir, std::string const & outputDir,
        NIfTI_Dimension outputDimension = NIfTI_Dimension::Dimension4);

    /// Destroy the instance of Dicom2Nifti
    virtual ~Dicom2Nifti();

    /**
     * @brief get_dicomDir: getter for _dicomDir
     * @return dicomDir
     */
    std::string const & get_dicomDir() const;

    /**
     * @brief set_dicomDir: setter for _dicomDir
     * @param dicomDir: new value
     */
    void set_dicomDir(std::string const & dicomDir);

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

    NIfTI_Dimension get_outputDimension() const;

    void set_outputDimension(NIfTI_Dimension outputDimension);

    /**
     * @brief run: Execute the conversion
     */
    void run() const;

protected:
    /// Create an instance of Dicom2Nifti
    Dicom2Nifti();

    /**
     * @brief Create an instance of Dicom2Nifti
     * @param dicomDir: input directory containing DICOM files
     * @param outputDir: Directory to store NIfTI files
     */
    Dicom2Nifti(std::string const & dicomDir, std::string const & outputDir,
                NIfTI_Dimension outputDimension = NIfTI_Dimension::Dimension4);

private:
    /// Path of DICOM directory
    std::string _dicomDir;

    /// Path to write NIfTI Datasets
    std::string _outputDir;

    NIfTI_Dimension _outputDimension;

    Dicom2Nifti(Self const & other);     // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    nifti_image * extract_information_from_dataset(
            Json::Value const & dataset, std::string const & prefix) const;

    void extract_stack_number(Json::Value const & dataset, nifti_image * nim) const;

    Json::Value extract_orientation(Json::Value const & dataset) const;

    Json::Value extract_position(Json::Value const & dataset) const;

    double get_distance_between_slice(Json::Value const & dataset) const;

};

} // namespace nifti

} // namespace dicomifier

#endif // _dd823cac_d7b3_4eb7_b579_c6bb5e64c2a6
