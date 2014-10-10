/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ConditionBase.h"

namespace dicomifier
{
    
namespace translator
{
    
ConditionBase
::ConditionBase()
    :Tag()
{
    // Nothing to do
}

ConditionBase
::~ConditionBase()
{
    // Nothing to do
}

void
ConditionBase
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmDataset* dataset)
{
    // Nothing to do
}
    
} // namespace translator
    
} // namespace dicomifier
