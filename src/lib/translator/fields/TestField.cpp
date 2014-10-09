/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "TestField.h"

namespace dicomifier
{
    
namespace translator
{
    
TestField
::TestField()
    :Tag()
{
    // Nothing to do
}

TestField
::~TestField()
{
    // Nothing to do
}

void
TestField
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      std::vector<int> const & indexes,
      DcmDataset* dataset)
{
    // Nothing to do
}
    
} // namespace translator

} // namespace dicomifier
