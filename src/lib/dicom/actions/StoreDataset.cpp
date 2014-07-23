/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "core/DicomifierException.h"
#include "StoreDataset.h"

namespace dicomifier
{
    
namespace actions
{
    
StoreDataset::StoreDataset():
    _dataset(NULL),
    _address(""),
    _port(""),
    _AEremote(""),
    _AElocal("")
{
    // Nothing to do
}

StoreDataset::StoreDataset(DcmDataset* dataset, std::string const & address,
                           std::string const & port, std::string const & aeremote,
                           std::string const & aelocal):
    _dataset(dataset),
    _address(address),
    _port(port),
    _AEremote(aeremote),
    _AElocal(aelocal)
{
    // Nothing to do
}

StoreDataset::~StoreDataset()
{
    // Nothing to do
}
    
void
StoreDataset
::run() const
{
    if (this->_dataset == NULL)
    {
        throw DicomifierException("Dataset is NULL");
    }
}

} // namespace actions
    
} // namespace dicomifier
