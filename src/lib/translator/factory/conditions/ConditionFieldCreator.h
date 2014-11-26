/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _7d45f57d_355d_4c4b_84ff_7c620724040b
#define _7d45f57d_355d_4c4b_84ff_7c620724040b

#include "translator/conditions/ConditionField.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The ConditionFieldCreator class
 */
class ConditionFieldCreator : public TranslationCreatorBase
{
public:
    typedef ConditionFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ConditionFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of ConditionFieldCreator
    virtual ~ConditionFieldCreator();

    /**
     * @brief Create Pointer to class BrukerFieldExist
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new ConditionField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset, 
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return ConditionField
     */
    static std::string get_class_name() { return "ConditionField"; }
    
protected:
    /// Create an instance of ConditionFieldCreator
    ConditionFieldCreator();
    
private:
    ConditionFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorConditionFieldCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag_cond;
        dicomifier::translator::Tag::Pointer pttag_true;
        dicomifier::translator::Tag::Pointer pttag_false;
        mutable dicomifier::translator::Tag::Pointer conditionfield;
        template<DcmEVR VR> void run() const;
    };
    
};

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier

#endif // _7d45f57d_355d_4c4b_84ff_7c620724040b
