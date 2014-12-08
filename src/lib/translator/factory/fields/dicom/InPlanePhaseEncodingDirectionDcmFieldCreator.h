/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _4802481b_c305_48ca_bb2f_ef373725e68e
#define _4802481b_c305_48ca_bb2f_ef373725e68e

#include "translator/fields/dicom/InPlanePhaseEncodingDirectionDcmField.h"
#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The InPlanePhaseEncodingDirectionDcmFieldCreator class
 */
class InPlanePhaseEncodingDirectionDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef InPlanePhaseEncodingDirectionDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of InPlanePhaseEncodingDirectionDcmFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of InPlanePhaseEncodingDirectionDcmFieldCreator
    virtual ~InPlanePhaseEncodingDirectionDcmFieldCreator();

    /**
     * @brief Create Pointer to class InPlanePhaseEncodingDirectionDcmField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new InPlanePhaseEncodingDirectionDcmField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return InPlanePhaseEncodingDirectionDcmField
     */
    static std::string get_class_name() { return "InPlanePhaseEncodingDirectionDcmField"; }

protected:
    /// Create an instance of InPlanePhaseEncodingDirectionDcmFieldCreator
    InPlanePhaseEncodingDirectionDcmFieldCreator();

private:
    InPlanePhaseEncodingDirectionDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorInPlanePhaseEncodingDirectionDcmFieldCreator
    {
        std::vector<dicomifier::translator::Tag::Pointer> pttag;
        mutable dicomifier::translator::Tag::Pointer inplanephaseencodingdir;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _4802481b_c305_48ca_bb2f_ef373725e68e
