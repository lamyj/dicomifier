/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#include "ConditionField.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
typename ConditionField<VR>::Pointer
ConditionField<VR>
::New()
{
    return Pointer(new Self());
}
    
template<DcmEVR VR>
typename ConditionField<VR>::Pointer
ConditionField<VR>
::New(std::vector<Tag::Pointer> conditions,
      Tag::Pointer thenactions,
      Tag::Pointer elseactions)
{
    return Pointer(new Self(conditions, thenactions, elseactions));
}
    
template<DcmEVR VR>
ConditionField<VR>
::ConditionField()
    :SubTag<VR>()
{
    // Nothing to do
}
    
template<DcmEVR VR>
ConditionField<VR>
::ConditionField(std::vector<Tag::Pointer> conditions,
                 Tag::Pointer thenactions,
                 Tag::Pointer elseactions)
    :SubTag<VR>(), _conditions(conditions), _thenActions(thenactions),
     _elseActions(elseactions)
{
    // Nothing to do
}

template<DcmEVR VR>
ConditionField<VR>
::~ConditionField()
{
    // Nothing to do
}

template<DcmEVR VR>
void
ConditionField<VR>
::run(dicomifier::bruker::BrukerDataset* brukerdataset,
      dicomifier::FrameIndexGenerator const & generator,
      DcmDataset* dataset)
{
    bool result = true;
    
    for (auto currentCond : this->_conditions)
    {
        ConditionBase::Pointer condition = std::dynamic_pointer_cast<ConditionBase>(currentCond);
        
        if (condition != NULL)
        {
            result &= condition->eval(dataset, brukerdataset);
        }
    }
    
    if (result)
    { // process ThenActions
        this->_thenActions->run(brukerdataset, generator, dataset);
        
        typename SubTag<VR>::Pointer subtag = 
            std::dynamic_pointer_cast<SubTag<VR>>(this->_thenActions);
        this->_array = subtag->get_array();
    }
    else
    { // process ElseActions
        this->_elseActions->run(brukerdataset, generator, dataset);
        
        typename SubTag<VR>::Pointer subtag = 
            std::dynamic_pointer_cast<SubTag<VR>>(this->_elseActions);
        this->_array = subtag->get_array();
    }
}

} // namespace translator
    
} // namespace dicomifier
