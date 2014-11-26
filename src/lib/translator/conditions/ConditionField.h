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

/**
 * @brief The ConditionField class
 */
template<DcmEVR VR>
class ConditionField : public SubTag<VR>
{
public:
    typedef ConditionField Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ConditionField
    static Pointer New();
    
    /**
     * @brief Create pointer to new instance of ConditionField
     * @param conditions: Conditions to test
     * @param thenactions: Action to process if condition return true
     * @param elseactions: Action to process if condition return false
     * @return new instance of ConditionField
     */
    static Pointer New(std::vector<Tag::Pointer> conditions,
                       Tag::Pointer thenactions,
                       Tag::Pointer elseactions);
    
    /// Destroy the instance of ConditionField
    virtual ~ConditionField();
    
    /**
     * @brief run: Evaluate the conditions and process then or else Action
     * @param brukerdataset: Bruker input data
     * @param generator: index generator
     * @param dataset: DICOM output dataset
     */
    virtual void run(dicomifier::bruker::BrukerDataset* brukerdataset,
                     dicomifier::FrameIndexGenerator const & generator,
                     DcmItem* dataset);
    
    /**
     * @brief get_class_type: return type of this class.
     * @return ECT_ConditionField
     */
    virtual ClassType get_class_type() const { return ECT_ConditionField; }
    
protected:
    /// Create an instance of ConditionField
    ConditionField();
    
    /**
     * @brief Create an instance of ConditionField
     * @param conditions: Conditions to test
     * @param thenactions: Action to process if condition return true
     * @param elseactions: Action to process if condition return false
     */
    ConditionField(std::vector<Tag::Pointer> conditions,
                   Tag::Pointer thenactions,
                   Tag::Pointer elseactions);

private:
    /// Conditions to test
    std::vector<Tag::Pointer> _conditions;
    
    /// Action to process if condition return true
    Tag::Pointer _thenActions;
    
    /// Action to process if condition return false
    Tag::Pointer _elseActions;

};
    
} // namespace translator
    
} // namespace dicomifier

#include "ConditionField.txx"

#endif // _bd1d5c0f_c176_4dd7_a6a1_4156e38b255f
