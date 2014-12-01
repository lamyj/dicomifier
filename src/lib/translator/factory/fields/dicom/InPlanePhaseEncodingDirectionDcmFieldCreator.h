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
    
class InPlanePhaseEncodingDirectionDcmFieldCreator : public TranslationCreatorBase
{
public:
    typedef InPlanePhaseEncodingDirectionDcmFieldCreator Self;
    typedef std::shared_ptr<Self> Pointer;
    typedef std::shared_ptr<Self const> ConstPointer;
    
    static Pointer New() { return Pointer(new Self()); }
    
    virtual ~InPlanePhaseEncodingDirectionDcmFieldCreator();

    virtual Tag::Pointer Create(boost::property_tree::ptree::value_type & value,
                                DcmDataset* dataset,
                                DcmEVR evr);

    static std::string get_class_name() { return "InPlanePhaseEncodingDirectionDcmField"; }

protected:
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
