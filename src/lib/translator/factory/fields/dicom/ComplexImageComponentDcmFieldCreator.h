/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _92bfe757_28dc_4afe_9be8_962c06d85177
#define _92bfe757_28dc_4afe_9be8_962c06d85177

#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{

namespace translator
{

namespace factory
{

/**
 * @brief The ComplexImageComponentDcmFieldCreator class
 */
class ComplexImageComponentDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef ComplexImageComponentDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;

    /// Create pointer to new instance of ComplexImageComponentDcmFieldCreator
    static Pointer New() { return Pointer(new Self()); }

    /// Destroy the instance of ComplexImageComponentDcmFieldCreator
    virtual ~ComplexImageComponentDcmFieldCreator();

    /**
     * @brief Create Pointer to class ComplexImageComponentDcmField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new ComplexImageComponentDcmField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return ComplexImageComponentDcmField
     */
    static std::string get_class_name() { return "ComplexImageComponentDcmField"; }

protected:
    /// Create an instance of ComplexImageComponentDcmFieldCreator
    ComplexImageComponentDcmFieldCreator();

private:
    ComplexImageComponentDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorComplexImageComponentDcmFieldCreator
    {
        bool perframe;
        mutable dicomifier::translator::Tag::Pointer compleximagecomponent;
        template<DcmEVR VR> void run() const;
    };

};

} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _92bfe757_28dc_4afe_9be8_962c06d85177
