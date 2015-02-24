/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "BrukerFieldExist.h"

namespace dicomifier
{
    
namespace translator
{
    
BrukerFieldExist
::BrukerFieldExist()
    :ConditionBase(), _brukerFieldName("")
{
    // Nothing to do
}
    
BrukerFieldExist
::BrukerFieldExist(std::string const & brukerfieldname)
    :ConditionBase(), _brukerFieldName(brukerfieldname)
{
    // Nothing to do
}

BrukerFieldExist
::~BrukerFieldExist()
{
    // Nothing to do
}

bool
BrukerFieldExist
::eval(DcmItem* dataset, dicomifier::bruker::BrukerDataset* brukerdataset)
{
    if (brukerdataset == NULL)
    {
        throw DicomifierException("Empty Bruker Dataset");
    }
    
    return brukerdataset->HasFieldData(this->_brukerFieldName);
}
    
} // namespace translator
    
} // namespace dicomifier
