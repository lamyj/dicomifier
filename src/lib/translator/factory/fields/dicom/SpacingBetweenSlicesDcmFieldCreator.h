/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _f0f74d76_3e3f_4cac_afb2_1bb7cc5b788e
#define _f0f74d76_3e3f_4cac_afb2_1bb7cc5b788e

#include "translator/fields/dicom/SpacingBetweenSlicesDcmField.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{

/**
 * @brief The SpacingBetweenSlicesDcmFieldCreator class
 */
class SpacingBetweenSlicesDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef SpacingBetweenSlicesDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of SpacingBetweenSlicesDcmFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of SpacingBetweenSlicesDcmFieldCreator
    virtual ~SpacingBetweenSlicesDcmFieldCreator();

    /**
     * @brief Create Pointer to class SpacingBetweenSlicesDcmField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new SpacingBetweenSlicesDcmField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return SpacingBetweenSlicesDcmField
     */
    static std::string get_class_name() { return "SpacingBetweenSlicesDcmField"; }

protected:
    /// Create an instance of SpacingBetweenSlicesDcmFieldCreator
    SpacingBetweenSlicesDcmFieldCreator();

private:
    SpacingBetweenSlicesDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorSpacingBetweenSlicesDcmFieldCreator
    {
        mutable dicomifier::translator::Tag::Pointer spacingbetweenslices;
        template<DcmEVR VR> void run() const;
    };

};

} // namespace factory
    
} // namespace translator

}// namespace dicomifier

#endif // _f0f74d76_3e3f_4cac_afb2_1bb7cc5b788e
