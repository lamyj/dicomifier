/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _b2acff4b_4252_4850_9a62_a9ecdc5f9520
#define _b2acff4b_4252_4850_9a62_a9ecdc5f9520

#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>

#include "core/actions/Action.h"

namespace dicomifier
{

namespace actions
{

/**
 * @brief The SaveDataset class: Save Dataset as DICOM File
 */
class SaveDataset : public Action
{
public:
    typedef SaveDataset Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of SaveDataset
    static Pointer New() { return Pointer(new Self()); }

    /**
     * @brief Create pointer to new instance of SaveDataset
     * @param dataset: Dataset to save
     * @param filename: DICOM file path
     * @param includeMetaInfoHeader: create Meta-information header
     * @return new instance of SaveDataset
     */
    static Pointer New(DcmDataset * dataset, std::string filename,
                       bool includeMetaInfoHeader = false) 
            { return Pointer(new Self(dataset, filename, includeMetaInfoHeader)); }

    /// Destroy the instance of SaveDataset
    virtual ~SaveDataset();

    /**
     * @brief get_dataset: getter for attribut dataset
     * @return dataset
     */
    DcmDataset * get_dataset() const;

    /**
     * @brief set_dataset: setter for attribut dataset
     * @param dataset: new value
     */
    void set_dataset(DcmDataset * dataset);
    
    /**
     * @brief get_filename: getter for attribut filename
     * @return filename
     */
    std::string const & get_filename() const;

    /**
     * @brief set_filename: setter for attribut filename
     * @param filename: new value
     */
    void set_filename(std::string const & filename);
    
    /**
     * @brief get_includeMetaInfoHeader: getter for attribut includeMetaInfoHeader
     * @return includeMetaInfoHeader
     */
    bool get_includeMetaInfoHeader() const;

    /**
     * @brief set_includeMetaInfoHeader: setter for attribut includeMetaInfoHeader
     * @param includeMetaInfoHeader: new value
     */
    void set_includeMetaInfoHeader(bool const & includeMetaInfoHeader);

    /**
     * @brief run: Execute the save Action
     */
    virtual void run() const;
    
    /**
     * @brief get_class_name: return this class name
     * @return SaveDataset
     */
    static std::string get_class_name() { return "SaveDataset"; }

protected:
    /// Create an instance of SaveDataset
    SaveDataset();

    /**
     * @brief Create an instance of SaveDataset
     * @param dataset: Dataset to save
     * @param filename: DICOM file path
     * @param includeMetaInfoHeader: create Meta-information header
     */
    SaveDataset(DcmDataset * dataset, std::string filename, 
                bool includeMetaInfoHeader = false);

private:
    /// Dataset to save
    DcmDataset * _dataset;

    /// Output file name
    std::string _filename;

    /// Flag indicate if Meta-Information header should be created
    bool _includeMetaInfoHeader;

    SaveDataset(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

};

} // namespace actions

} // namespace dicomifier

#endif // _b2acff4b_4252_4850_9a62_a9ecdc5f9520
