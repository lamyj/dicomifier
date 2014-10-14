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
    
class SpacingBetweenSlicesDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef SpacingBetweenSlicesDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~SpacingBetweenSlicesDcmFieldCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    static std::string get_class_name() { return "SpacingBetweenSlicesDcmField"; }

protected:
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
