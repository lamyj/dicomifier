/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SaveDataset.h"

namespace dicomifier
{
	
namespace actions
{
	
SaveDataset::SaveDataset()
{
	// Nothing to do
}

SaveDataset::SaveDataset(DcmDataset * dataset, std::string filename):
	_dataset(dataset), _filename(filename)
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

void
SaveDataset
::run() const
{
	if (this->_dataset != NULL)
    {
		this->_dataset->saveFile(this->_filename.c_str(), 
								 EXS_LittleEndianExplicit);
	}
}

} // namespace actions
	
} // namespace dicomifier
