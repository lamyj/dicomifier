/*************************************************************************
 * Dicomifier - Copyright (C) Universite de Strasbourg
 * Distributed under the terms of the CeCILL-B license, as published by
 * the CEA-CNRS-INRIA. Refer to the LICENSE file or to
 * http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html
 * for details.
 ************************************************************************/

#ifndef _6873c9e4_b97c_494f_9dbc_f93b59dda5d2
#define _6873c9e4_b97c_494f_9dbc_f93b59dda5d2

#include "translator/TranslationCreatorBase.h"

namespace dicomifier
{
    
namespace translator
{
    
namespace factory
{
    
/**
 * @brief The ImagePositionPatientDcmFieldCreator class
 */
class ImagePositionPatientDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef ImagePositionPatientDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    /// Create pointer to new instance of ImagePositionPatientDcmFieldCreator
    static Pointer New() { return Pointer(new Self()); }
    
    /// Destroy the instance of ImagePositionPatientDcmFieldCreator
    virtual ~ImagePositionPatientDcmFieldCreator();

    /**
     * @brief Create Pointer to class ImagePositionPatientDcmField
     * @param value: XML node
     * @param dataset: Dataset to modify
     * @param evr: EVR of tag
     * @return new ImagePositionPatientDcmField
     */
    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    /**
     * @brief get_class_name: return created class name
     * @return ImagePositionPatientDcmField
     */
    static std::string get_class_name() { return "ImagePositionPatientDcmField"; }

protected:
    /// Create an instance of ImagePositionPatientDcmFieldCreator
    ImagePositionPatientDcmFieldCreator();

private:
    ImagePositionPatientDcmFieldCreator(Self const & other); // Purposely not implemented
    Self const & operator=(Self const & other); // Purposely not implemented

    struct TranslatorImagePositionPatientDcmFieldCreator
    {
        mutable dicomifier::translator::Tag::Pointer imageposition;
        template<DcmEVR VR> void run() const;
    };

};
    
} // namespace factory

} // namespace translator

} // namespace dicomifier

#endif // _6873c9e4_b97c_494f_9dbc_f93b59dda5d2
