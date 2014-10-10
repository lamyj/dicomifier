/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _bd1d5c0f_c176_4dd7_a6a1_4156e38b255f
#define _bd1d5c0f_c176_4dd7_a6a1_4156e38b255f

#include "ConditionBase.h"
#include "translator/SubTag.h"

namespace dicomifier
{
    
namespace translator
{
    
template<DcmEVR VR>
class ConditionField : public SubTag<VR>
{
public:
    typedef ConditionField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ConditionField
    static Pointer New();
    
    /// Create pointer to new instance of ConditionField
    static Pointer New(std::vector<Tag::Pointer> conditions,
                       Tag::Pointer thenactions,
                       Tag::Pointer elseactions);
    
    virtual ~ConditionField();
    
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmDataset* dataset);
    
    virtual ClassType get_class_type() const { return ECT_ConditionField; }
    
protected:
    ConditionField();
    
    ConditionField(std::vector<Tag::Pointer> conditions,
                   Tag::Pointer thenactions,
                   Tag::Pointer elseactions);

private:
    std::vector<Tag::Pointer> _conditions;
    
    Tag::Pointer _thenActions;
    
    Tag::Pointer _elseActions;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "ConditionField.txx"

#endif // _bd1d5c0f_c176_4dd7_a6a1_4156e38b255f
