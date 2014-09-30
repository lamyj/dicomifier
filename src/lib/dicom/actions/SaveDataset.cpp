/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "SaveDataset.h"

namespace dicomifier
{

namespace actions
{

SaveDataset::SaveDataset():
    _dataset(NULL), _filename(""), _includeMetaInfoHeader(false)
{
    // Nothing to do
}

SaveDataset
::SaveDataset(DcmDataset * dataset, 
              std::string filename,
              bool includeMetaInfoHeader):
    _dataset(dataset), _filename(filename), 
    _includeMetaInfoHeader(includeMetaInfoHeader)
{
    // Nothing to do
}

SaveDataset::~SaveDataset()
{
    // Nothing to do
}

DcmDataset *
SaveDataset
::get_dataset() const
{
    return this->_dataset;
}

void
SaveDataset
::set_dataset(DcmDataset * dataset)
{
    this->_dataset = dataset;
}

std::string const &
SaveDataset
::get_filename() const
{
    return this->_filename;
}

void
SaveDataset
::set_filename(std::string const & filename)
{
    this->_filename = filename;
}

bool
SaveDataset
::get_includeMetaInfoHeader() const
{
    return this->_includeMetaInfoHeader;
}

void
SaveDataset
::set_includeMetaInfoHeader(bool const & includeMetaInfoHeader)
{
    this->_includeMetaInfoHeader = includeMetaInfoHeader;
}

void
SaveDataset
::run() const
{
    if (this->_dataset == NULL)
    {
        throw DicomifierException("Unable to save empty dataset");
    }
    
    OFCondition result = EC_Normal;
    if (this->_includeMetaInfoHeader)
    {
        DcmFileFormat fileformat(this->_dataset);
        result = fileformat.saveFile(this->_filename.c_str(), 
                                     EXS_LittleEndianExplicit);
    }
    else
    {
        result = this->_dataset->saveFile(this->_filename.c_str(), 
                                          EXS_LittleEndianExplicit);
    }
                                                 
    if (result.bad())
    {
        throw DicomifierException("Unable to save dataset: " + 
                                  std::string(result.text()));
    }
}

} // namespace actions

} // namespace dicomifier
