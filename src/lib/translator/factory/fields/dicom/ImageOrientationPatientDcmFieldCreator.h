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
    
class ImageOrientationPatientDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef ImageOrientationPatientDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~ImageOrientationPatientDcmFieldCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    static std::string get_class_name() { return "ImageOrientationPatientDcmField"; }

protected:
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
