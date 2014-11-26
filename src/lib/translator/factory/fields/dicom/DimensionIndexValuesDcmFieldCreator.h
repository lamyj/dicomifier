/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _fc505924_abe9_47d0_9567_3c4b31a5bd16
#define _fc505924_abe9_47d0_9567_3c4b31a5bd16

#include "translator/fields/dicom/DimensionIndexValuesDcmField.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The DimensionIndexValuesDcmFieldCreator class
 */
class DimensionIndexValuesDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef DimensionIndexValuesDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of DimensionIndexValuesDcmFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of DimensionIndexValuesDcmFieldCreator
    virtual ~DimensionIndexValuesDcmFieldCreator();

    /**
     * @brief Create Pointer to class DimensionIndexValuesDcmField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new DimensionIndexValuesDcmField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return DimensionIndexValuesDcmField
     */
    static std::string get_class_name() { return "DimensionIndexValuesDcmField"; }
    
protected:
    /// Create an instance of DimensionIndexValuesDcmFieldCreator
    DimensionIndexValuesDcmFieldCreator();

private:
    DimensionIndexValuesDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorDimensionIndexValuesDcmFieldCreator
    {
        mutable dicomifier::translator::Tag::Pointer dimensionindexvalues;
        template<DcmEVR VR> void run() const;
    };

};

} // namespace factory
    
} // namespace translator
    
} // namespace dicomifier

#endif // _fc505924_abe9_47d0_9567_3c4b31a5bd16
