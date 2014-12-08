/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _3734bbd6_89a7_438d_a0ac_ac3862d7dc7d
#define _3734bbd6_89a7_438d_a0ac_ac3862d7dc7d

#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The ImageOrientationPatientDcmFieldCreator class
 */
class ImageOrientationPatientDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef ImageOrientationPatientDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ImageOrientationPatientDcmFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of ImageOrientationPatientDcmFieldCreator
    virtual ~ImageOrientationPatientDcmFieldCreator();

    /**
     * @brief Create Pointer to class ImageOrientationPatientDcmField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new ImageOrientationPatientDcmField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return ImageOrientationPatientDcmField
     */
    static std::string get_class_name() { return "ImageOrientationPatientDcmField"; }

protected:
    /// Create an instance of ImageOrientationPatientDcmFieldCreator
    ImageOrientationPatientDcmFieldCreator();

private:
    ImageOrientationPatientDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorImageOrientationPatientDcmFieldCreator
    {
        mutable dicomifier::translator::Tag::Pointer imageorientation;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _3734bbd6_89a7_438d_a0ac_ac3862d7dc7d
