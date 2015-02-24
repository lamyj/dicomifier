/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "SubTag.h"

namespace dicomifier
{
    
namespace translator
{
 
template<DcmEVR VR>
SubTag<VR>
::SubTag()
    :Tag()
{
    // Nothing to do
}

template<DcmEVR VR>
SubTag<VR>
::~SubTag()
{
    // Nothing to do
}

template<DcmEVR VR>
typename SubTag<VR>::ArrayType 
SubTag<VR>
::get_array() const
{
    return this->_array;
}

} // namespace translator
    
} // namespace dicomifier

